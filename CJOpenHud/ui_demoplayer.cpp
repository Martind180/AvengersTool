#include "ui_demoplayer.h"

#include "pch.h"
#include "ui_position.h"
#include "CJOpenHud.h"


void ui_demoplayer::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();

	ImGui::Begin("Demo Player");
	
	if (ImGui::Button("Play Demos")) {
		hud->want_input = false;
		hud->inst_ui_menu->menuStates.playing_demos = true;
	}

	ImGui::Checkbox("F9 on all demos played", &hud->inst_ui_menu->menuStates.sim_f9);

	static char inp1[128] = "1";
	static char inp2[128] = "1";
	static char inp3[1024]{};
	static char inpDemoNum[10]{"1"};
	
	ImGui::InputText("Timescale", inp1, 128);
	hud->inst_ui_menu->menuStates.timescale = atof(inp1);
	
	ImGui::InputText("Demo count", inp2, 128);
	hud->inst_ui_menu->menuStates.demo_num = atoi(inp2);
	
	ImGui::InputText("Execute every demo", inp3, 128);
	
	hud->inst_ui_menu->menuStates.extra_cmd = inp3;
	
	ImGui::InputText("Play demos from", inpDemoNum, 10);
	
	ImGui::Checkbox("Show FPS image", &hud->inst_ui_menu->menuStates.show_fps_image);
	ImGui::Checkbox("WTMOD", &hud->inst_ui_menu->menuStates.wtmod);
	ImGui::Checkbox("3XP", &hud->inst_ui_menu->menuStates.threexp);
	ImGui::SliderFloat("FPS Image scale", &hud->inst_ui_menu->menuStates.image_scale, 0.01f, 10.f);

	if (hud->inst_ui_menu->menuStates.play_demos_from != atoi(inpDemoNum)) {
		hud->inst_ui_menu->menuStates.play_demos_index = atoi(inpDemoNum);
	}
	
	hud->inst_ui_menu->menuStates.play_demos_from = atoi(inpDemoNum);

	if (hud->inst_ui_menu->menuStates.wtmod && hud->inst_ui_menu->menuStates.threexp) {
		hud->inst_ui_menu->menuStates.threexp = false;
	}

	ImGui::End();
}

ui_demoplayer::ui_demoplayer(CJOpenHud* hud)
{
	
}

ui_demoplayer::~ui_demoplayer()
{

}
