#include "pch.h"
#include "ui_jump_target.h"

#include "Avengers.h"

void ui_jump_target::render()
{
	Avengers* hud = Avengers::get_instance();
	if (!hud->inst_game->is_connected()) //only draw while connected to a server
		return;

	vec3<float> jt_origin = hud->inst_ui_menu->jump_target_origin;
	vec3<float> player_origin = hud->inst_game->get_origin();

	if(!hud->inst_game->isOnGround())
	{
		if(jump_target_closest_height_ == nullptr)
		{
			jump_target_closest_height_ = std::make_unique<float>(player_origin[2]);
		}
		else if(player_origin[2] > *jump_target_closest_height_)
		{
			*jump_target_closest_height_ = player_origin[2];
		}
		
		if(jump_target_closest_dist_ == nullptr)
		{
			jump_target_closest_dist_ = std::make_unique<float>(player_origin.Dist(jt_origin));
			jump_target_closest_ = player_origin;
		}
		else
		{
			const float dist = player_origin.Dist(jt_origin);
			if(dist < *jump_target_closest_dist_)
			{
				*jump_target_closest_dist_ = dist;
				jump_target_closest_ = player_origin;
			}
		}
	}
	else if (jump_target_closest_dist_ != nullptr && jump_target_closest_height_ != nullptr && hud->inst_game->getJumpTime())
	{
		auto time = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time - prevent_spam_);
		
		if(duration.count() >= 100)
		{
			std::stringstream ss;
			ss << jt_origin[2] - *jump_target_closest_height_ << " too low" << std::endl;
			ss << jump_target_closest_.Dist(jt_origin) << " units off" << std::endl;
			ss << jt_origin[2] - jump_target_closest_[2] << " too low at closest position";
			hud->inst_game->add_obituary(ss.str());
		}
		
	
		jump_target_closest_.clearXYZ();
		jump_target_closest_dist_ = nullptr;
		jump_target_closest_height_ = nullptr;
		prevent_spam_ = std::chrono::steady_clock::now();
	}
}
ui_jump_target::ui_jump_target(Avengers* hud)
{
	
}
ui_jump_target::~ui_jump_target()
{

}