#include "pch.h"
#include "ui_velocity.h"
#include "CJOpenHud.h"

void ui_velocity::render(CJOpenHud* &hud, bool &is_locked, vec2<float> &pos, float &scale, ImVec4 &color, float &prev_velo)
{
	ImGui::Begin("Velocity", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);	

	float velo = hud->inst_game->get_velocity().Length2D();

	//Velocity converted to string
	std::string veloText = std::to_string(static_cast<int>(velo));
		
	ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
		
		
	// Check if the mouse is over the text and is being dragged
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !is_locked) {
		vec2<float> prevPos = pos;;
		
		// Update the text position based on mouse drag
		pos.x += ImGui::GetIO().MouseDelta.x;
		pos.y += ImGui::GetIO().MouseDelta.y;

		if(prevPos != pos)
		{
			hud->save_configuration();
		}
	}

	ImVec2 outlinePosition(pos.x + 1, pos.y + 1);
		
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	ImGui::SetWindowFontScale(scale);
	ImGui::PushFont(hud->toxic_font);
	
	drawList->AddText(outlinePosition, outlineColor, veloText.c_str());
	if(prev_velo <= velo)
	{
		drawList->AddText(ImVec2(pos.x, pos.y), hud->inst_ui_position_marker->im_vec4_to_im_col32(color), veloText.c_str());
	}
	else
	{
		drawList->AddText(ImVec2(pos.x, pos.y), IM_COL32(255, 0, 0, 255), veloText.c_str());
	}
	ImGui::SetWindowFontScale(1.0f);

	prev_velo = velo;

	ImGui::PopFont();

	ImGui::End();
}
ui_velocity::ui_velocity(CJOpenHud* hud)
{
	
}
ui_velocity::~ui_velocity()
{

}