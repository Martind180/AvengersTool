#include "ui_position_marker.h"
#include "CJOpenHud.h"
#include <algorithm>

void ui_position_marker::render(const vec3<float>& pos, vec2<float> &screen_pos, const ImVec4& color, const float radius)
{
    CJOpenHud* hud = CJOpenHud::get_instance();
    ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
    
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    
    hud->inst_game->world_to_screen(pos, &screen_pos.x, &screen_pos.y);
    
    ImU32 outlineColor = im_vec4_to_im_col32(color);
    int numSegments = 8;

    float distance = hud->inst_game->get_origin().Dist(pos);

    const float min_radius = 1.0f;
    const float max_radius = radius * 5;

    //make the circle get smaller and disappear if the player is over 512 units from the centre
    unsigned int new_radius = min_radius + (max_radius - min_radius) * (min_radius - distance / 512.0f); //ChatGPT FTW

    // Draw a circle around a point
    drawList->AddCircle(screen_pos.toImvec2(), new_radius, outlineColor, numSegments, 2);

    ImGui::End();
}

ImU32 ui_position_marker::im_vec4_to_im_col32(const ImVec4& color)
{
    return IM_COL32(
        static_cast<int>(color.x * 255),
        static_cast<int>(color.y * 255),
        static_cast<int>(color.z * 255),
        static_cast<int>(color.w * 255));
}

ui_position_marker::ui_position_marker(CJOpenHud* hud)
{
}

ui_position_marker::~ui_position_marker()
{
}

