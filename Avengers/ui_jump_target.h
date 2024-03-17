#pragma once
class ui_jump_target
{
	std::unique_ptr<float> jump_target_closest_height_ = nullptr;
	std::unique_ptr<float> jump_target_closest_dist_ = nullptr;
	vec3<float> jump_target_closest_ = vec3<float>(0,0,0);
	std::chrono::time_point<std::chrono::steady_clock> prevent_spam_;
	
public:
	ui_jump_target(class Avengers* hud);
	~ui_jump_target();
	void render();
};

