#include "ui_demoplayer.h"

#include "pch.h"
#include "CJOpenHud.h"


void ui_demoplayer::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	if(hud->want_input && hud->inst_ui_menu->menuStates.demoplayer_menu)
	{
		menu(hud);
	}

	if (demo_player_states.playing_demos && !hud->want_input)
	{
		play_all_demos();
	}

	//simulate an F9 keypress after the last demo is played
	//as my keybind to stop/start fraps recording is F9
	if (demo_player_states.just_finished && hud->inst_game->is_in_main_menu()) {
		if (demo_player_states.sim_f9) {
			INPUT ip;
			ip.type = INPUT_KEYBOARD;
			ip.ki.wScan = 0; // hardware scan code for key
			ip.ki.time = 0;
			ip.ki.dwExtraInfo = 0;

			// Press the "F9" key
			ip.ki.wVk = VK_F9; // virtual-key code for the "F9" key
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));
		}
		demo_player_states.just_finished = false;
	}

	if(demo_player_states.show_fps_image)
	{
		hud->inst_ui_fps_image->render();
	}
}

void ui_demoplayer::menu(CJOpenHud* hud)
{
	ImGui::Begin("Demo Player");
	
	if (ImGui::Button("Play Demos")) {
		hud->want_input = false;
		demo_player_states.playing_demos = true;
	}

	ImGui::Checkbox("F9 on all demos played", &demo_player_states.sim_f9);

	static char inp1[128] = "1";
	static char inp2[128] = "1";
	static char inp3[1024]{};
	static char inpDemoNum[10]{"1"};
	
	ImGui::InputText("Timescale", inp1, 128);
	demo_player_states.timescale = atof(inp1);
	
	ImGui::InputText("Demo count", inp2, 128);
	demo_player_states.demo_num = atoi(inp2);
	
	ImGui::InputText("Execute every demo", inp3, 128);
	
	demo_player_states.extra_cmd = inp3;
	
	ImGui::InputText("Play demos from", inpDemoNum, 10);
	
	ImGui::Checkbox("Show FPS image", &demo_player_states.show_fps_image);
	ImGui::Checkbox("WTMOD", &demo_player_states.wtmod);
	ImGui::Checkbox("3XP", &demo_player_states.threexp);
	ImGui::SliderFloat("FPS Image scale", &demo_player_states.image_scale, 0.01f, 10.f);

	if (demo_player_states.play_demos_from != atoi(inpDemoNum)) {
		demo_player_states.play_demos_index = atoi(inpDemoNum);
	}
	
	demo_player_states.play_demos_from = atoi(inpDemoNum);

	if (demo_player_states.wtmod && demo_player_states.threexp) {
		demo_player_states.threexp = false;
	}

	ImGui::End();
}

void ui_demoplayer::play_all_demos()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	static bool demoPlayed = true;
	static bool cmdExecuted = false;

	*reinterpret_cast<float*>(addr_timescale) = demo_player_states.timescale;

	std::string a = "demo ";
	a += std::to_string(demo_player_states.play_demos_index);

	if (hud->inst_game->is_connected() && !demoPlayed) {
		demoPlayed = true;
		demo_player_states.play_demos_index++;
	}

	if (demo_player_states.play_demos_index > demo_player_states.demo_num) {
		demo_player_states.play_demos_index = demo_player_states.play_demos_from;
		demo_player_states.playing_demos = false;
		demoPlayed = true;
		cmdExecuted = false;
		demo_player_states.just_finished = true;
	}

	if (hud->inst_game->is_in_main_menu()) {
		using namespace std;
		static auto t = chrono::system_clock::now();
		int timeCount = abs(chrono::duration_cast<chrono::milliseconds>(t - chrono::system_clock::now()).count());
		if (timeCount > 1000.f) {
			hud->inst_game->send_command_to_console(a.c_str());
			demoPlayed = false;
			cmdExecuted = false;
			t = chrono::system_clock::now();
		}
	}

	if (hud->inst_game->is_connected() && !cmdExecuted) {
		cmdExecuted = true;
		if (std::string(demo_player_states.extra_cmd) != "") {
			hud->inst_game->send_command_to_console(demo_player_states.extra_cmd);
		}
	}
}

ui_demoplayer::ui_demoplayer(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}

ui_demoplayer::~ui_demoplayer()
{

}
