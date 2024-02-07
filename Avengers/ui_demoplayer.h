#pragma once
#include <d3d9.h>

struct demo_player_states
{
	bool playing_demos = false;
	int demo_num;
	float timescale = 1;
	char* extra_cmd;
	bool sim_f9 = false;
	bool just_finished = false;
	int play_demos_from = 1;
	int play_demos_index = 1;
	bool demo_playing = false;
	bool show_fps_image = false;
	bool wtmod = false;
	bool threexp = true;
	float image_scale = 0.7f;
};

class ui_demoplayer
{
public:
	ui_demoplayer(class CJOpenHud* hud);
	~ui_demoplayer();
	void render();
	void menu(CJOpenHud* hud);
	void play_all_demos();

	demo_player_states demo_player_states;
};

