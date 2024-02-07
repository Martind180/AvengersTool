#include "ui_fps_image.h"
#include "CJOpenHud.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void ui_fps_image::render()
{
    CJOpenHud* hud = CJOpenHud::get_instance();
	
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

	static int w1 = 0;
	static int h1 = 0;
	
	static int w2 = 0;
	static int h2 = 0;
	
	static int w3 = 0;
	static int h3 = 0;
	
	static int w4 = 0;
	static int h4 = 0;
	
	static int w5 = 0;
	static int h5 = 0;
	
	static int w6 = 0;
	static int h6 = 0;
	
	static int w0 = 0;
	static int h0 = 0;

	static int w40 = 0;
	static int h40 = 0;

	static int w76 = 0;
	static int h76 = 0;

	static int w1000 = 0;
	static int h1000 = 0;
	
	static int w15 = 0;
	static int h15 = 0;

	static bool init = false;
	float scale = hud->inst_ui_demoplayer->demo_player_states.image_scale;

	if (!init) {
		load_texture_from_file("1.png", &texture1, &w1, &h1);
		load_texture_from_file("2.png", &texture2, &w2, &h2);
		load_texture_from_file("3.png", &texture3, &w3, &h3);
		load_texture_from_file("4.png", &texture4, &w4, &h4);
		load_texture_from_file("5.png", &texture5, &w5, &h5);
		load_texture_from_file("6.png", &texture6, &w6, &h6);
		load_texture_from_file("0.png", &texture0, &w0, &h0);
		load_texture_from_file("15.png", &texture15, &w15, &h15);
		load_texture_from_file("40.png", &texture40, &w40, &h40);
		load_texture_from_file("76.png", &texture76, &w76, &h76);
		load_texture_from_file("1000.png", &texture1000, &w1000, &h1000);
		init = true;
	}

	ImGui::SetNextWindowBgAlpha(0.f);
	ImGui::Begin("Written by Wilhelm uwu", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration);
	
	int fps = 0;
	if (hud->inst_ui_demoplayer->demo_player_states.threexp) {
		fps = hud->inst_game->get_fps_3_xp();
	}
	else {
		fps = hud->inst_game->get_fps_wtmod();
	}

	switch (fps)
	{
	case 125:
		ImGui::Image(texture1, ImVec2(w1 * scale, h1 * scale));
		break;
	case 250:
		ImGui::Image(texture2, ImVec2(w2 * scale, h2 * scale));
		break;
	case 333:
		ImGui::Image(texture3, ImVec2(w3 * scale, h3 * scale));
		break;
	case 142:
		ImGui::Image(texture4, ImVec2(w4 * scale, h4 * scale));
		break;
	case 500:
		ImGui::Image(texture5, ImVec2(w5 * scale, h5 * scale));
		break;
	case 166:
		ImGui::Image(texture6, ImVec2(w6 * scale, h6 * scale));
		break;
	case 200:
		ImGui::Image(texture0, ImVec2(w0 * scale, h0 * scale));
		break;
	case 15:
		ImGui::Image(texture15, ImVec2(w15 * scale, h15 * scale));
		break;
	case 40:
		ImGui::Image(texture40, ImVec2(w40 * scale, h40 * scale));
		break;
	case 76:
		ImGui::Image(texture76, ImVec2(w76 * scale, h76 * scale));
		break;
	case 1000:
		ImGui::Image(texture1000, ImVec2(w1000 * scale, h1000 * scale));
		break;
	default:
		ImGui::Image(texture1, ImVec2(w1 * scale, h1 * scale));
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

ui_fps_image::ui_fps_image(class CJOpenHud* hud)
{
}

ui_fps_image::~ui_fps_image()
{
}

