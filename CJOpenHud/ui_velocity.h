#pragma once
#include "imgui.h"
#include "vectors.h"

class ui_velocity
{
public:
	ui_velocity(class CJOpenHud* hud);
	~ui_velocity();
	void render(CJOpenHud*& hud, bool& is_locked, vec2<float>& pos, float& scale, ImVec4& color, float& prev_velo);
};

