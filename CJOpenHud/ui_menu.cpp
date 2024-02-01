#include "pch.h"
#include "ui_menu.h"
#include "CJOpenHud.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

values ui_menu::values;

void ui_menu::menu(CJOpenHud* hud)
{
	static bool init = false;

	if (!init) {
		load_configuration();
		init = true;
	}
	
	ImGui::Begin("Avengers Helper");

	if(ImGui::Button("Demo Player"))
	{
		menuStates.demoplayer_menu = !menuStates.demoplayer_menu;
	}

	static char demoName[128] = "";
	ImGui::InputText("Demo Name", demoName, 128);
	ImGui::SameLine(); if (ImGui::Button("Bind demo to load key"))
	{
		if (std::string(demoName) != "")
		{
			std::stringstream ss;
			ss << "bind f \"openscriptmenu cj load;stoprecord;record " << demoName << "\"";
			
			hud->inst_game->send_command_to_console(ss.str().c_str());
		}
		else
		{
			std::string cmd = "bind f \"openscriptmenu cj load;stoprecord;record\"";

			hud->inst_game->send_command_to_console(cmd.c_str());
		}
	}

	if (ImGui::Button("Copy position"))
	{
		vec3<float> pos = hud->inst_game->get_origin();
		vec3<float> view = hud->inst_game->get_view();

		std::stringstream ss;
		ss << std::fixed << std::setprecision(6) << pos.x <<  " " << pos.y << " " << pos.z + 60 << " " << view.y << " " << view.x;

		menuStates.copiedPosition = ss.str();

		ImGui::SetClipboardText(menuStates.copiedPosition.c_str());
	}
	ImGui::SameLine(); ImGui::Checkbox("Show Coordinates", &menuStates.show_position);

	
	//################# SPEEDOMETER ########################
	ImGui::Checkbox("Speedometer", &menuStates.velo_meter);
	ImGui::SameLine(); ImGui::ColorButton("Color Button", vec4_to_im_vec4(menuStates.color));

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("ColorPickerPopup");
	}

	if(ImGui::BeginPopup("ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.color.x);

		ImGui::EndPopup();

		save_configuration();
	}
	ImGui::SameLine(); ImGui::Checkbox("Lock Speed Position", &menuStates.lock_velo_pos);
	
	ImGui::SliderFloat("Speed Size", &menuStates.velo_scale, 0.01f, 10.f);
	//#######################################################

	//################# POSITION MARKERS ########################
	if (ImGui::Button("Mark Position 1"))
	{
		menuStates.draw_marker1 = true;
		menuStates.marker1 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 1 Colour Button", menuStates.marker1_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker1ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker1ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.marker1_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 1"))
	{
		menuStates.draw_marker1 = false;
	}
	
	if (ImGui::Button("Mark Position 2"))
	{
		menuStates.draw_marker2 = true;
		menuStates.marker2 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 2 Colour Button", menuStates.marker2_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker2ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker2ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.marker2_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 2"))
	{
		menuStates.draw_marker2 = false;
	}
	
	if (ImGui::Button("Mark Position 3"))
	{
		menuStates.draw_marker3 = true;
		menuStates.marker3 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 3 Colour Button", menuStates.marker3_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker3ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker3ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.marker3_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 3"))
	{
		menuStates.draw_marker3 = false;
	}

	ImGui::SliderFloat("Marker Size", &menuStates.marker_size, 5.0f, 100.0f);

	if (menuStates.wtmod && menuStates.threexp) {
		menuStates.threexp = false;
	}
	//#######################################################

	
	ImGui::End();
}

void ui_menu::set_default_configuration(vec2<float> &position, vec4<float> &color, float &scale) {
	position = vec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
	color = vec4(0.0f, 1.0f, 0.0f, 1.0f); // green color
	scale = 1.5f;
}

// Function to load configuration from a file or set default values
void ui_menu::load_configuration() {
	CJOpenHud* hud = CJOpenHud::get_instance();
	
	// Specify the file path
	std::string filePath = "AvengersConfig.txt";

	// Check if the file exists
	if (std::filesystem::exists(filePath)) {
		std::ifstream configFile(filePath);

		if (configFile.is_open()) {
			std::string line;
			while (std::getline(configFile, line)) {
				if (line.find("Speedometer:") != std::string::npos)
				{
					//Parse speedometer boolean
					std::string bool_string = line.substr(line.find("Speedometer:") + strlen("Speedometer: "));

					if(bool_string == "true")
					{
						hud->inst_ui_menu->menuStates.velo_meter = true;
					}
					else
					{
						hud->inst_ui_menu->menuStates.velo_meter = false;
					}
				}
				else if (line.find("Position:") != std::string::npos) {
					// Parse position
					sscanf_s(line.c_str(), "Position: %f %f", &hud->inst_ui_menu->menuStates.velo_pos.x, &hud->inst_ui_menu->menuStates.velo_pos.y);
				} else if (line.find("Color:") != std::string::npos) {
					// Parse color
					sscanf_s(line.c_str(), "Color: %f %f %f %f", &hud->inst_ui_menu->menuStates.color.x, &hud->inst_ui_menu->menuStates.color.y, &hud->inst_ui_menu->menuStates.color.z, &hud->inst_ui_menu->menuStates.color.w);
				}
				else if (line.find("Scale:") != std::string::npos) {
					// Parse scale
					sscanf_s(line.c_str(), "Scale: %f", &hud->inst_ui_menu->menuStates.velo_scale);
				}
				else if (line.find("PosHud:") != std::string::npos)
				{
					//Parse Position boolean
					std::string bool_string = line.substr(line.find("PosHud:") + strlen("PosHud: "));

					if(bool_string == "true")
					{
						hud->inst_ui_menu->menuStates.show_position = true;
					}
					else
					{
						hud->inst_ui_menu->menuStates.show_position = false;
					}
				}
				else if (line.find("LastCopiedPosition:") != std::string::npos)
				{
					std::string pos = line.substr(line.find("LastCopiedPosition:") + strlen("LastCopiedPosition: "));

					hud->inst_ui_menu->menuStates.copiedPosition = pos;
				}
			}

			configFile.close();
		} else {
			std::cerr << "Error opening config file for reading\n";
		}
	} else {
		std::cout << "Config file not found. Using default values.\n";
		set_default_configuration(hud->inst_ui_menu->menuStates.velo_pos,hud->inst_ui_menu->menuStates.color,hud->inst_ui_menu->menuStates.velo_scale);  // Set default values if the file doesn't exist
		save_configuration();
		load_configuration();
	}
}

void ui_menu::save_configuration() {
	CJOpenHud* hud = CJOpenHud::get_instance();
	
	std::ofstream configFile("AvengersConfig.txt");  // Open a file for writing

	if (configFile.is_open()) {
		// Save Speedometer on
		configFile << "Speedometer: " << hud->inst_ui_menu->menuStates.velo_meter << "\n";
		
		// Save position
		configFile << "Position: " << hud->inst_ui_menu->menuStates.velo_pos.x << " " << hud->inst_ui_menu->menuStates.velo_pos.x << "\n";

		// Save color
		configFile << "Color: " << hud->inst_ui_menu->menuStates.color.x << " " << hud->inst_ui_menu->menuStates.color.y << " " << hud->inst_ui_menu->menuStates.color.z << " " << hud->inst_ui_menu->menuStates.color.w << "\n";

		//Save scale
		configFile << "Scale: " << hud->inst_ui_menu->menuStates.velo_scale << "\n";

		//Save Position
		configFile << "PosHud: " << hud->inst_ui_menu->menuStates.show_position << "\n";

		//Save Last Copied Position
		configFile << "LastCopiedPosition: " << hud->inst_ui_menu->menuStates.copiedPosition << "\n";
		

		configFile.close();  // Close the file
	} else {
		std::cerr << "Error opening config file for writing\n";
	}
}

ImU32 ui_menu::im_vec4_to_im_col32(ImVec4 color)
{
	return IM_COL32(
		static_cast<int>(color.x * 255),
		static_cast<int>(color.y * 255),
		static_cast<int>(color.z * 255),
		static_cast<int>(color.w * 255));
}

ImVec4 ui_menu::vec4_to_im_vec4(vec4<float> vector)
{
	return ImVec4(vector.x, vector.y, vector.z, vector.w);
}

void ui_menu::tp_to_saved_position()
{
	CJOpenHud* hud = CJOpenHud::get_instance();

	if(hud->inst_game->is_connected())
		hud->inst_game->send_command_to_console(("setviewpos " + menuStates.copiedPosition).c_str());
}

void ui_menu::play_all_demos()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	static bool demoPlayed = true;
	static bool cmdExecuted = false;

	*reinterpret_cast<float*>(addr_timescale) = menuStates.timescale;

	std::string a = "demo ";
	a += std::to_string(menuStates.play_demos_index);

	if (hud->inst_game->is_connected() && !demoPlayed) {
		demoPlayed = true;
		menuStates.play_demos_index++;
	}

	if (menuStates.play_demos_index > menuStates.demo_num) {
		menuStates.play_demos_index = menuStates.play_demos_from;
		menuStates.playing_demos = false;
		demoPlayed = true;
		cmdExecuted = false;
		menuStates.just_finished = true;
	}

	if (hud->inst_game->is_in_main_menu()) {
		using namespace std;
		static auto t = chrono::system_clock::now();
		int timeCount = abs(chrono::duration_cast<chrono::milliseconds>(t - chrono::system_clock::now()).count());
		if (timeCount > 1000.f) {
			hud->inst_game->send_command_to_console(a.c_str());
			demoPlayed = false;
			cmdExecuted = false;
			t = chrono::system_clock::now();
		}
	}

	if (hud->inst_game->is_connected() && !cmdExecuted) {
		cmdExecuted = true;
		if (std::string(menuStates.extra_cmd) != "") {
			hud->inst_game->send_command_to_console(menuStates.extra_cmd);
		}
	}
}

void ui_menu::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();

	ImGui::Begin("Avengers Functionality", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
	
	if(hud->want_input)
	{
		menu(hud);
	}

	if (menuStates.show_position) {
		hud->inst_ui_position->render();
		hud->inst_ui_view->render();
	}

	if (menuStates.velo_meter && hud->inst_game->is_connected())
	{
		hud->inst_ui_velocity->render(hud, menuStates.lock_velo_pos, menuStates.velo_pos, menuStates.velo_scale, menuStates.color, menuStates.previous_velo);
	}

	if (menuStates.draw_marker1 && hud->inst_game->is_connected())
	{
		ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		hud->inst_game->WorldToScreen(menuStates.marker1, &values.pos1.x, &values.pos1.y);
		
		ImVec2 center(values.pos1.x, values.pos1.y);
		ImU32 outlineColor = im_vec4_to_im_col32(menuStates.marker1_color);
		int numSegments = 8;

		// Draw a circle around a point
		drawList->AddCircle(center, menuStates.marker_size, outlineColor, numSegments, 2);

		ImGui::End();
	}

	if (menuStates.draw_marker2 && hud->inst_game->is_connected())
	{
		ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		hud->inst_game->WorldToScreen(menuStates.marker2, &values.pos2.x, &values.pos2.y);
		
		ImVec2 center(values.pos2.x, values.pos2.y);
		ImU32 outlineColor = im_vec4_to_im_col32(menuStates.marker2_color);
		int numSegments = 8;

		// Draw a circle around a point
		drawList->AddCircle(center, menuStates.marker_size, outlineColor, numSegments, 2);

		ImGui::End();
	}

	if (menuStates.draw_marker3 && hud->inst_game->is_connected())
	{
		ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		hud->inst_game->WorldToScreen(menuStates.marker3, &values.pos3.x, &values.pos3.y);
		
		ImVec2 center(values.pos3.x, values.pos3.y);
		ImU32 outlineColor = im_vec4_to_im_col32(menuStates.marker3_color);
		int numSegments = 8;

		// Draw a circle around a point
		drawList->AddCircle(center, menuStates.marker_size, outlineColor, numSegments, 2);

		ImGui::End();
	}

	if (menuStates.playing_demos && !hud->want_input) {
		play_all_demos();
	}

	if (menuStates.just_finished && hud->inst_game->is_in_main_menu()) {
		if (menuStates.sim_f9) {
			INPUT ip;
			ip.type = INPUT_KEYBOARD;
			ip.ki.wScan = 0; // hardware scan code for key
			ip.ki.time = 0;
			ip.ki.dwExtraInfo = 0;

			// Press the "F9" key
			ip.ki.wVk = VK_F9; // virtual-key code for the "F9" key
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));
		}
		menuStates.just_finished = false;
	}

	if(menuStates.show_fps_image)
	{
		render_fps_image();
	}

	if (hud->want_input && menuStates.demoplayer_menu)
	{
		hud->inst_ui_demoplayer->render();
	}
}

void ui_menu::render_fps_image()
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
	float scale = hud->inst_ui_menu->menuStates.image_scale;

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
	//setStyle_noBorder();
	ImGui::Begin("Written by Wilhelm uwu", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration);
	
	int fps = 0;
	if (hud->inst_ui_menu->menuStates.threexp) {
		fps = hud->inst_game->getFps_3xp();
	}
	else {
		fps = hud->inst_game->getFps_wtmod();
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

bool ui_menu::load_texture_from_file(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
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

void ui_menu::setStyle_noBorder()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	/// 0 = FLAT APPEARENCE
	/// 1 = MORE "3D" LOOK
	int is3D = 1;

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
	colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
	colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

	style.PopupRounding = 3;

	style.WindowPadding = ImVec2(4, 4);
	style.FramePadding = ImVec2(6, 4);
	style.ItemSpacing = ImVec2(6, 2);

	style.ScrollbarSize = 18;

	style.WindowBorderSize = 0;
	style.ChildBorderSize = 0;
	style.PopupBorderSize = 0;
	style.FrameBorderSize = is3D;

	style.WindowRounding = 3;
	style.ChildRounding = 3;
	style.FrameRounding = 3;
	style.ScrollbarRounding = 2;
	style.GrabRounding = 3;

#ifdef IMGUI_HAS_DOCK 
	style.TabBorderSize = is3D;
	style.TabRounding = 3;

	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.85f, 0.85f, 0.85f, 0.28f);

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
#endif
}


ui_menu::ui_menu(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_menu::~ui_menu()
{

}