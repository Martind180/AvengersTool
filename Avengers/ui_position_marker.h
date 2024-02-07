#pragma once
#include "imgui.h"
#include "vectors.h"

class ui_position_marker
{
public:
    ui_position_marker(class Avengers* hud);
    ~ui_position_marker();
    void render(const vec3<float>& pos, vec2<float> &screen_pos, const ImVec4& color, const float radius);
    static ImU32 im_vec4_to_im_col32(const ImVec4& color);
};
