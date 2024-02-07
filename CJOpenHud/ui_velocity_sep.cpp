#include "pch.h"
#include "ui_velocity_sep.h"
#include "CJOpenHud.h"

void ui_velocity_sep::render(CJOpenHud* &hud, bool &is_locked, vec2<float> &pos, float &scale, ImVec4 &color, float &prev_velo)
{
	currentVelocity = hud->inst_game->get_velocity();
	float current_velocity_magnitude = currentVelocity.Length2D();
	framesSinceLastColorUpdate++;

	if (framesSinceLastColorUpdate >= colorRefreshRateInFrames) {
		// Determine if velocity is increasing or decreasing
		velocity_increasing = current_velocity_magnitude >= prev_velo;
		prev_velo = current_velocity_magnitude; // Update for next comparison
		framesSinceLastColorUpdate = 0;
	}
	std::string velocityText = std::to_string(static_cast<int>(current_velocity_magnitude));

	ImGui::Begin("Sep Speedometer", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowFontScale(scale);

	ImGui::PushFont(hud->sep_font);
	
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	// Shadow settings
	ImVec2 shadowOffset = ImVec2(2, 2); // Shadow offset from the main text
	ImVec2 shadowPos = ImVec2(pos.x + shadowOffset.x, pos.y + shadowOffset.y);
	// Main text settings
	ImVec4 col = velocity_increasing ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1);
	ImU32 shadowColor = IM_COL32(0, 0, 0, 255); // Black

	if (!is_locked && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
		vec2<float> prevPos = pos;
		
		// Update the text position based on mouse drag
		pos.x += ImGui::GetIO().MouseDelta.x;
		pos.y += ImGui::GetIO().MouseDelta.y;

		if(prevPos != pos)
		{
			hud->save_configuration();
		}
	}
	// Draw shadow first 
	drawList->AddText(shadowPos, shadowColor, velocityText.c_str());
	// Draw main
	if (velocity_increasing)
	{
		drawList->AddText(ImVec2(pos.x, pos.y), hud->inst_ui_position_marker->im_vec4_to_im_col32(color), velocityText.c_str());
	}
	else
	{
		drawList->AddText(ImVec2(pos.x, pos.y), IM_COL32(255, 0, 0 ,255), velocityText.c_str());
	}

	ImGui::PopFont();

	ImGui::End();
}
ui_velocity_sep::ui_velocity_sep(CJOpenHud* hud)
{
	
}
ui_velocity_sep::~ui_velocity_sep()
{

}