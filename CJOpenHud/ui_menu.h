#pragma once
#include "vectors.h"

struct MenuStates
{
	bool playing_demos = false;
	bool demoplayer_menu = false;
	float timescale;
	int demo_num;
	char* extra_cmd;
	bool sim_f9 = false;
	bool just_finished = false;
	int play_demos_from;
	int play_demos_index = 1;
	bool show_position;
	bool demo_playing = false;
	bool show_fps_image = false;
	bool wtmod = false;
	bool threexp = true;
	float image_scale = 0.7f;
	bool velo_meter = false;
	vec4<float> color = { 0.0f, 1.0f, 0.0f, 1.0f };
	float velo_scale;
	bool lock_velo_pos = true;
	vec2<float> velo_pos;
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
	void setStyle_noBorder();
	ui_menu(class CJOpenHud* hud);
	~ui_menu();
	void menu(CJOpenHud* hud);
	static ImU32 im_vec4_to_im_col32(ImVec4 color);
	void set_default_configuration(vec2<float> &position, vec4<float> &color, float &scale);
	void load_configuration();
	void save_configuration();
	ImVec4 vec4_to_im_vec4(vec4<float> vector);
	void tp_to_saved_position();
	void play_all_demos();
	void render();
	void render_fps_image();
	bool load_texture_from_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);

	MenuStates menuStates;
	static values values;
};

