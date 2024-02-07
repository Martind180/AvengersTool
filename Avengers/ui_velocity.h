#pragma once
#include "imgui.h"
#include "vectors.h"

class ui_velocity
{
	int frames_since_last_color_update_ = 0;
	bool velocity_increasing_ = false;
public:
	ui_velocity(class Avengers* hud);
	~ui_velocity();
	void render(Avengers*& hud, bool& is_locked, vec2<float>& pos, float& scale, ImVec4& color, float& prev_velo);
};

