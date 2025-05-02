#include "pch.h"
#include "ui_anglehelper.h"

void ui_anglehelper::render(Avengers*& hud, ImVec4& color)
{
	vec2<float> screen;
	vec2<float> center(hud->inst_game->get_screen_res().x / 2, hud->inst_game->get_screen_res().y / 2);
	float fpsWheelPos = hud->inst_game->get_screen_res().y / 2 + hud->inst_ui_menu->fpswheel_offset_y;
	float yaw = hud->inst_game->get_view().y;
	float optAngle = hud->inst_game->get_optimal_angle();
	float fov = hud->inst_game->get_fov();

	float pixelScale = (hud->inst_game->get_screen_res().x / fov);

	screen.y = hud->inst_game->get_screen_res().y / 2;
	float ahOffset = yaw - optAngle;

	screen.x = center.x + (ahOffset * pixelScale);

	float ahOffsetPixel = ahOffset * pixelScale;

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(screen.x, -30 + screen.y), ImVec2(2.5 + screen.x, 30 + screen.y), ImColor(color));
}

void ui_anglehelper::renderOnWheel(Avengers*& hud, ImVec4& color)  //TODO: refactor into 1 func w params
{
	vec2<float> screen;
	vec2<float> center(hud->inst_game->get_screen_res().x / 2, hud->inst_game->get_screen_res().y / 2);
	float fpsWheelPos = hud->inst_game->get_screen_res().y / 2 + hud->inst_ui_menu->fpswheel_offset_y;
	float yaw = hud->inst_game->get_view().y;
	float optAngle = hud->inst_game->get_optimal_angle();
	float fov = hud->inst_game->get_fov();

	float pixelScale = (hud->inst_game->get_screen_res().x / fov);

	screen.y = fpsWheelPos;
	float ahOffset = yaw - optAngle;

	screen.x = center.x + (ahOffset * pixelScale);

	float ahOffsetPixel = ahOffset * pixelScale;

	ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(screen.x, screen.y), ImVec2(2.5 + screen.x, hud->inst_ui_menu->fpswheel_size + screen.y), ImColor(color));
}

ui_anglehelper::ui_anglehelper(Avengers* hud)
{
	
}

ui_anglehelper::~ui_anglehelper()
{

}
