#include "pch.h"
#include "ui_fps_image.h"
#include "Avengers.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void ui_fps_image::render()
{
    Avengers* hud = Avengers::get_instance();
	
	static LPDIRECT3DTEXTURE9 texture1 = nullptr;
	static LPDIRECT3DTEXTURE9 texture2 = nullptr;
	static LPDIRECT3DTEXTURE9 texture3 = nullptr;
	static LPDIRECT3DTEXTURE9 texture4 = nullptr;
	static LPDIRECT3DTEXTURE9 texture5 = nullptr;
	static LPDIRECT3DTEXTURE9 texture6 = nullptr;
	static LPDIRECT3DTEXTURE9 texture0 = nullptr;
	static LPDIRECT3DTEXTURE9 texture15 = nullptr;
	static LPDIRECT3DTEXTURE9 texture40 = nullptr;
	static LPDIRECT3DTEXTURE9 texture76 = nullptr;
	static LPDIRECT3DTEXTURE9 texture1000 = nullptr;

	static int width = 0;
	static int height = 0;

	static bool init = false;
	float scale = hud->inst_ui_demoplayer->image_scale;

	if (!init) {
		load_texture_from_file("1.png", &texture1, &width, &height);
		load_texture_from_file("2.png", &texture2, &width, &height);
		load_texture_from_file("3.png", &texture3, &width, &height);
		load_texture_from_file("4.png", &texture4, &width, &height);
		load_texture_from_file("5.png", &texture5, &width, &height);
		load_texture_from_file("6.png", &texture6, &width, &height);
		load_texture_from_file("0.png", &texture0, &width, &height);
		load_texture_from_file("15.png", &texture15, &width, &height);
		load_texture_from_file("40.png", &texture40, &width, &height);
		load_texture_from_file("76.png", &texture76, &width, &height);
		load_texture_from_file("1000.png", &texture1000, &width, &height);
		init = true;
	}

	ImGui::SetNextWindowBgAlpha(0.f);
	ImGui::Begin("Written by Wilhelm uwu", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration);
	
	int fps = 0;
	if (hud->inst_ui_demoplayer->threexp) {
		fps = hud->inst_game->get_fps_3_xp();
	}
	else {
		fps = hud->inst_game->get_fps_wtmod();
	}

	switch (fps)
	{
	case 125:
		ImGui::Image(texture1, ImVec2(width * scale, height * scale));
		break;
	case 250:
		ImGui::Image(texture2, ImVec2(width * scale, height * scale));
		break;
	case 333:
		ImGui::Image(texture3, ImVec2(width * scale, height * scale));
		break;
	case 142:
		ImGui::Image(texture4, ImVec2(width * scale, height * scale));
		break;
	case 500:
		ImGui::Image(texture5, ImVec2(width * scale, height * scale));
		break;
	case 166:
		ImGui::Image(texture6, ImVec2(width * scale, height * scale));
		break;
	case 200:
		ImGui::Image(texture0, ImVec2(width * scale, height * scale));
		break;
	case 15:
		ImGui::Image(texture15, ImVec2(width * scale, height * scale));
		break;
	case 40:
		ImGui::Image(texture40, ImVec2(width * scale, height * scale));
		break;
	case 76:
		ImGui::Image(texture76, ImVec2(width * scale, height * scale));
		break;
	case 1000:
		ImGui::Image(texture1000, ImVec2(width * scale, height * scale));
		break;
	default:
		ImGui::Image(texture1, ImVec2(width * scale, height * scale));
		break;
	}

	ImGui::End();
}

bool ui_fps_image::load_texture_from_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    // Load texture from disk
    PDIRECT3DTEXTURE9 texture;
    LPDIRECT3DDEVICE9 pDevice = *reinterpret_cast<LPDIRECT3DDEVICE9*>(0xcc9a408);
    HRESULT hr = D3DXCreateTextureFromFileA(pDevice, filename, &texture);
    if (hr != S_OK)
        return false;

    // Retrieve description of the texture surface so we can access its size
    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;

    int c;
    stbi_load(filename, out_width, out_height, &c, 0);
	
    return true;
}

ui_fps_image::ui_fps_image(class Avengers* hud)
{
}

ui_fps_image::~ui_fps_image()
{
}

