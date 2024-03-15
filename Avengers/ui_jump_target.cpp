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
		if(jt_origin[2] > jump_target_closest_height_)
		{
			jump_target_closest_height_ = jt_origin[2];
		}

		jump_target_closest_dist_ = player_origin.Dist(jt_origin);
		jump_target_closest_ = player_origin;
	}
	else
	{
		std::stringstream ss;

		ss << jt_origin[2] - jump_target_closest_height_ << " too low" << std::endl;
		ss << jump_target_closest_.Dist(jt_origin) << " units off" << std::endl;
		ss << jt_origin[2] - jump_target_closest_ << " too low at closest position";
		//TODO: correct the passed in value
		hud->inst_game->add_obituary(ss);
	}
}
ui_jump_target::ui_jump_target(Avengers* hud)
{
	
}
ui_jump_target::~ui_jump_target()
{

}