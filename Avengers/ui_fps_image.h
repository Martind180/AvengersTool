#pragma once
#include "imgui.h"
#include <d3d9.h>

class ui_fps_image
{
public:
    ui_fps_image(class Avengers* hud);
    ~ui_fps_image();
    void render();
    bool load_texture_from_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height);
};
