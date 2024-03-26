#include "pch.h"
#include "ui_anglehelper.h"

void ui_anglehelper::render(Avengers*& hud, ImVec4& color)
{
	using namespace mm;

	vec3<float> player_pos = hud->inst_game->get_origin();
	vec3<float> normal_view = hud->inst_game->get_view();
	vec3<float> orb_pos;
	orb_pos.x = player_pos.x + 40.f;
	orb_pos.y = player_pos.y;
	orb_pos.z = player_pos.z - normal_view.x + 40.f;

	vec2<float> screen;

	vec2<float> rotated2D = rotate_point(truncate_vector(orb_pos), truncate_vector(player_pos), hud->inst_game->get_optimal_angle());
	orb_pos.x = rotated2D.x;
	orb_pos.y = rotated2D.y;

	hud->inst_game->world_to_screen(orb_pos, &screen.x, &screen.y);
	screen.y = hud->inst_game->get_screen_res().y / 2;

	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(screen.x, -30 + screen.y), ImVec2(2.5 + screen.x, 30 + screen.y), ImColor(color));
}

ui_anglehelper::ui_anglehelper(Avengers* hud)
{
	
}

ui_anglehelper::~ui_anglehelper()
{

}
