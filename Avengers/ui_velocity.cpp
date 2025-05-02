#include "pch.h"
#include "ui_velocity.h"
#include "Avengers.h"

void ui_velocity::render(Avengers* &hud, bool &is_locked, vec2<float> &pos, float &scale, ImVec4 &color)
{
	ImGui::Begin("Velocity", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);	

	float velo = hud->inst_game->get_velocity().Length2D();
	static float prev_velo = hud->inst_game->get_velocity().Length2D();

	static int frames_to_wait_for_velo_decrease = 0;  //Velo drops. Wait X frames for velo to drop again.
	static int frames_checking_for_velo_decrease = 0;  // After having waited X frames, wait Y frames and check if it decreased again.
	static int frames_to_decrease_velo_for = 0;  //Mark velocity as decreasing for Z frames.
	static bool velocity_decreasing = false;

	if (velo < prev_velo && frames_to_decrease_velo_for > 0) {
		frames_to_decrease_velo_for = 50;
	}

	if (velo < prev_velo
		&& frames_to_wait_for_velo_decrease == 0 && frames_checking_for_velo_decrease == 0 && frames_to_decrease_velo_for == 0
		&& !hud->inst_game->isOnGround()) {
		frames_to_wait_for_velo_decrease = 10;
		frames_checking_for_velo_decrease = 0;
		frames_to_decrease_velo_for = 0;
	}

	if (velo > prev_velo) {
		velocity_decreasing = false;
		frames_to_decrease_velo_for = 0;
		frames_to_wait_for_velo_decrease = 0;
		frames_checking_for_velo_decrease = 0;
	}

	if (frames_to_wait_for_velo_decrease > 0) {
		frames_to_wait_for_velo_decrease--;
		if (frames_to_wait_for_velo_decrease == 0) {
			frames_checking_for_velo_decrease = 10;
		}
	}

	if (frames_checking_for_velo_decrease > 0) {
		frames_checking_for_velo_decrease--;
		if (velo < prev_velo) {
			velocity_decreasing = true;
			frames_to_decrease_velo_for = 50;
		}
	}

	if (frames_to_decrease_velo_for > 0) {
		frames_to_decrease_velo_for--;
		if (frames_to_decrease_velo_for == 0) {
			velocity_decreasing = false;
		}
	}


	prev_velo = velo;

	//Velocity converted to string
	std::string veloText = std::to_string(static_cast<int>(velo));
		
	ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
		
		
	// Check if the mouse is over the text and is being dragged
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !is_locked) {
		vec2<float> prevPos = pos;
		
		// Update the text position based on mouse drag
		pos.x += ImGui::GetIO().MouseDelta.x;
		pos.y += ImGui::GetIO().MouseDelta.y;

		if(prevPos != pos)
		{
			hud->save_configuration();
		}
	}

	ImVec2 outline_position(pos.x + 1, pos.y + 1);
		
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

	ImGui::SetWindowFontScale(scale);
	if (hud->inst_ui_menu->sep_velo)
	{
		ImGui::PushFont(hud->sep_font);
	}
	else
	{
		ImGui::PushFont(hud->toxic_font);
	}
	
	draw_list->AddText(outline_position, outlineColor, veloText.c_str());
	
	if(!velocity_decreasing)
	{
		draw_list->AddText(ImVec2(pos.x, pos.y), hud->inst_ui_position_marker->im_vec4_to_im_col32(color), veloText.c_str());
	}
	else
	{
		draw_list->AddText(ImVec2(pos.x, pos.y), IM_COL32(255, 0, 0, 255), veloText.c_str());
	}
	ImGui::SetWindowFontScale(1.0f);

	prev_velo = velo;

	ImGui::PopFont();

	ImGui::End();
}

ui_velocity::ui_velocity(Avengers* hud)
{
	
}

ui_velocity::~ui_velocity()
{

}
