#include "ui_demoplayer.h"

#include "pch.h"
#include "Avengers.h"


void ui_demoplayer::render()
{
	Avengers* hud = Avengers::get_instance();
	if(hud->want_input && hud->inst_ui_menu->demoplayer_menu)
	{
		menu(hud);
	}

	if (playing_demos && !hud->want_input)
	{
		play_all_demos();
	}

	//simulate an F9 keypress after the last demo is played
	//as the default keybind to stop/start fraps recording is F9
	if (just_finished && hud->inst_game->is_in_main_menu()) {
		if (sim_f9) {
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
		just_finished = false;
	}

	if(show_fps_image)
	{
		hud->inst_ui_fps_image->render();
	}
}

void ui_demoplayer::menu(Avengers* hud)
{
	ImGui::Begin("Demo Player");
	
	if (ImGui::Button("Play Demos")) {
		hud->want_input = false;
		playing_demos = true;
	}

	ImGui::Checkbox("F9 on all demos played", &sim_f9);

	static char inp1[128] = "1";
	static char inp2[128] = "1";
	static char inp3[1024]{};
	static char inpDemoNum[10]{"1"};
	
	ImGui::InputText("Timescale", inp1, 128);
	timescale = atof(inp1);
	
	ImGui::InputText("Demo count", inp2, 128);
	demo_num = atoi(inp2);
	
	ImGui::InputText("Execute every demo", inp3, 128);
	
	extra_cmd = inp3;
	
	ImGui::InputText("Play demos from", inpDemoNum, 10);
	
	ImGui::Checkbox("Show FPS image", &show_fps_image);
	ImGui::Checkbox("WTMOD", &wtmod);
	ImGui::Checkbox("3XP", &threexp);
	ImGui::SliderFloat("FPS Image scale", &image_scale, 0.01f, 10.f);

	if (play_demos_from != atoi(inpDemoNum)) {
		play_demos_index = atoi(inpDemoNum);
	}
	
	play_demos_from = atoi(inpDemoNum);

	if (wtmod && threexp) {
		threexp = false;
	}

	ImGui::End();
}

void ui_demoplayer::play_all_demos()
{
	Avengers* hud = Avengers::get_instance();
	static bool demoPlayed = true;
	static bool cmdExecuted = false;

	*reinterpret_cast<float*>(addr_timescale) = timescale;

	std::string a = "demo ";
	a += std::to_string(play_demos_index);

	if (hud->inst_game->is_connected() && !demoPlayed) {
		demoPlayed = true;
		play_demos_index++;
	}

	if (play_demos_index > demo_num) {
		play_demos_index = play_demos_from;
		playing_demos = false;
		demoPlayed = true;
		cmdExecuted = false;
		just_finished = true;
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
		if (std::string(extra_cmd) != "") {
			hud->inst_game->send_command_to_console(extra_cmd);
		}
	}
}

ui_demoplayer::ui_demoplayer(Avengers* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}

ui_demoplayer::~ui_demoplayer()
{

}
