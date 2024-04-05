#include "pch.h"
#include "ui_90_lines.h"
#include "Avengers.h"


void ui_90_lines::render()
{
	Avengers* hud = Avengers::get_instance();
	auto color = ImColor(hud->inst_ui_menu->lines_color);
	vec3<float> c_direction;
	std::vector<std::pair<game::GfxPointVertex, game::GfxPointVertex>> verts;
	for (int i = 0; i < 4; i++)
	{
		float length = 800;
		mm::angle_vectors({ 0, (float)(i * 90), 0 }, &c_direction, 0, 0);
		vec3<float> c_point = hud->inst_game->get_origin() + (c_direction * vec3<float>(length, length, length));
		verts.push_back({ game::GfxPointVertex(hud->inst_game->get_origin(), color), game::GfxPointVertex(c_point, color) });
	}

	hud->inst_game->polyline(verts.size(), 1, reinterpret_cast<game::GfxPointVertex*>(verts.data()), true);
}
ui_90_lines::ui_90_lines(Avengers* hud)
{
	
}
ui_90_lines::~ui_90_lines()
{

}