#pragma once
#include "imgui.h"
#include "vectors.h"

class ui_velocity
{
public:
	ui_velocity(class Avengers* hud);
	~ui_velocity();
	void render(Avengers*& hud, bool& is_locked, vec2<float>& pos, float& scale, ImVec4& color);
};

