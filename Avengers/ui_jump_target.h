#pragma once
class ui_jump_target
{
	float jump_target_closest_height_ = 0.f;
	float jump_target_closest_dist_ = 0.f;
	vec3<float> jump_target_closest_ = vec3<float>(0,0,0);
	
public:
	ui_jump_target(class Avengers* hud);
	~ui_jump_target();
	void render();
};

