#pragma once
#include "vectors.h"

struct MenuStates
{
	bool demoplayer_menu = false;
	bool show_position = false;
	bool velo_meter = false;
	bool sep_velo = false;
	ImVec4 color = { 0.0f, 1.0f, 0.0f, 1.0f };
	float velo_scale = 1.5;
	bool lock_velo_pos = true;
	vec2<float> velo_pos = vec2<float>(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);
	float previous_velo;
	
	bool draw_marker1 = false;
	bool draw_marker2 = false;
	bool draw_marker3 = false;
	vec3<float> marker1;
	vec3<float> marker2;
	vec3<float> marker3;

	float marker_size = 20.0f;
	ImVec4 marker1_color = { 1.0f, 0.0f, 0.0f, 1.0f };
	ImVec4 marker2_color = { 0.0f, 1.0f, 0.0f, 1.0f };
	ImVec4 marker3_color = { 0.0f, 0.0f, 1.0f, 1.0f };

	char* demo_name;
	std::string copiedPosition = "";
};

struct values
{
	vec2<float> pos1;
	vec2<float> pos2;
	vec2<float> pos3;
	
	bool load_pos = false;
};

class ui_menu
{
	public:
	ui_menu(class CJOpenHud* hud);
	~ui_menu();
	void menu(CJOpenHud* hud);
	void render();

	MenuStates menuStates;
	static values values;
};

