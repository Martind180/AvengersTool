#pragma once
#include "imgui.h"
#include "vectors.h"

class ui_velocity_sep
{
	bool velocity_increasing = true; // Track whether velocity is increasing or decreasing

	// Existing members
	int framesSinceLastColorUpdate = 0;
	int colorRefreshRateInFrames = 35; // Example: Update color every 30 frames
	vec3<float> currentVelocity;
	
public:
	ui_velocity_sep(class CJOpenHud* hud);
	~ui_velocity_sep();
	void render(CJOpenHud*& hud, bool& is_locked, vec2<float>& pos, float& scale, ImVec4& color, float& prev_velo);
};

