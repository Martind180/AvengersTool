#include "pch.h"
#include "ui_menu.h"
#include "CJOpenHud.h"

values ui_menu::values;

void ui_menu::menu(CJOpenHud* hud)
{
	static bool init = false;

	if (!init) {
		LoadConfiguration(menuStates.veloPos, menuStates.color, menuStates.veloScale);
		init = true;
	}
	
	ImGui::Begin("Avengers Helper");

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
	ImGui::Checkbox("Speedometer", &menuStates.veloMeter);
	ImGui::SameLine(); ImGui::ColorButton("Color Button", vec4ToImVec4(menuStates.color));

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("ColorPickerPopup");
	}

	if(ImGui::BeginPopup("ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.color.x);

		ImGui::EndPopup();

		SaveConfiguration(menuStates.veloPos, menuStates.color, menuStates.veloScale);
	}
	ImGui::SameLine(); ImGui::Checkbox("Lock Speed Position", &menuStates.lockVeloPos);
	
	ImGui::SliderFloat("Speed Size", &menuStates.veloScale, 0.01f, 10.f);
	//#######################################################

	//################# POSITION MARKERS ########################
	if (ImGui::Button("Mark Position 1"))
	{
		menuStates.drawMarker1 = true;
		menuStates.marker1 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 1 Colour Button", menuStates.marker1Color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker1ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker1ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.marker1Color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 1"))
	{
		menuStates.drawMarker1 = false;
	}
	
	if (ImGui::Button("Mark Position 2"))
	{
		menuStates.drawMarker2 = true;
		menuStates.marker2 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 2 Colour Button", menuStates.marker2Color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker2ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker2ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.marker2Color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 2"))
	{
		menuStates.drawMarker2 = false;
	}
	
	if (ImGui::Button("Mark Position 3"))
	{
		menuStates.drawMarker3 = true;
		menuStates.marker3 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 3 Colour Button", menuStates.marker3Color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker3ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker3ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.marker3Color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 3"))
	{
		menuStates.drawMarker3 = false;
	}

	ImGui::SliderFloat("Marker Size", &menuStates.markerSize, 5.0f, 100.0f);

	if (menuStates.wtmod && menuStates.threexp) {
		menuStates.threexp = false;
	}
	//#######################################################

	
	ImGui::End();
}

void ui_menu::SetDefaultConfiguration(vec2<float>& position, vec4<float>& color, float& scale) {
	position = vec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
	color = vec4(0.0f, 1.0f, 0.0f, 1.0f); // green color
	scale = 1.5f;
}

// Function to load configuration from a file or set default values
void ui_menu::LoadConfiguration(vec2<float>& position, vec4<float>& color, float& scale) {
	// Specify the file path
	std::string filePath = "AvengersConfig.txt";

	// Check if the file exists
	if (std::filesystem::exists(filePath)) {
		std::ifstream configFile(filePath);

		if (configFile.is_open()) {
			std::string line;
			while (std::getline(configFile, line)) {
				if (line.find("Position:") != std::string::npos) {
					// Parse position
					sscanf_s(line.c_str(), "Position: %f %f", &position.x, &position.y);
				} else if (line.find("Color:") != std::string::npos) {
					// Parse color
					sscanf_s(line.c_str(), "Color: %f %f %f %f", &color.x, &color.y, &color.z, &color.w);
				}
				else if (line.find("Scale:") != std::string::npos) {
					// Parse scale
					sscanf_s(line.c_str(), "Scale: %f", &scale);
				}
			}

			configFile.close();
		} else {
			std::cerr << "Error opening config file for reading\n";
		}
	} else {
		std::cout << "Config file not found. Using default values.\n";
		SetDefaultConfiguration(position,color,scale);  // Set default values if the file doesn't exist
		SaveConfiguration(position, color, scale);
		LoadConfiguration(position, color, scale);
	}
}

void ui_menu::SaveConfiguration(const vec2<float>& position, const vec4<float>& color, const float& scale) {
	std::ofstream configFile("AvengersConfig.txt");  // Open a file for writing

	if (configFile.is_open()) {
		// Save position
		configFile << "Position: " << position.x << " " << position.y << "\n";

		// Save color
		configFile << "Color: " << color.x << " " << color.y << " " << color.z << " " << color.w << "\n";

		//Save scale
		configFile << "Scale: " << scale << "\n";

		configFile.close();  // Close the file
	} else {
		std::cerr << "Error opening config file for writing\n";
	}
}

ImU32 ui_menu::ImVec4ToImCol32(ImVec4 color)
{
	return IM_COL32(
		static_cast<int>(color.x * 255),
		static_cast<int>(color.y * 255),
		static_cast<int>(color.z * 255),
		static_cast<int>(color.w * 255));
}

ImVec4 ui_menu::vec4ToImVec4(vec4<float> vector)
{
	return ImVec4(vector.x, vector.y, vector.z, vector.w);
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

	if (menuStates.veloMeter && hud->inst_game->is_connected())
	{
		ImGui::Begin("Velocity", 0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		hud->inst_ui_velocity->render(hud, menuStates.lockVeloPos, menuStates.veloPos, menuStates.veloScale, menuStates.color, menuStates.previousVelo);

		ImGui::End();
	}

	if (menuStates.drawMarker1 && hud->inst_game->is_connected())
	{
		ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		hud->inst_game->WorldToScreen(menuStates.marker1, &values.pos1.x, &values.pos1.y);
		
		ImVec2 center(values.pos1.x, values.pos1.y);
		ImU32 outlineColor = ImVec4ToImCol32(menuStates.marker1Color);
		int numSegments = 8;

		// Draw a circle around a point
		drawList->AddCircle(center, menuStates.markerSize, outlineColor, numSegments, 2);

		ImGui::End();
	}

	if (menuStates.drawMarker2 && hud->inst_game->is_connected())
	{
		ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		hud->inst_game->WorldToScreen(menuStates.marker2, &values.pos2.x, &values.pos2.y);
		
		ImVec2 center(values.pos2.x, values.pos2.y);
		ImU32 outlineColor = ImVec4ToImCol32(menuStates.marker2Color);
		int numSegments = 8;

		// Draw a circle around a point
		drawList->AddCircle(center, menuStates.markerSize, outlineColor, numSegments, 2);

		ImGui::End();
	}

	if (menuStates.drawMarker3 && hud->inst_game->is_connected())
	{
		ImGui::Begin("Position Marker by Toxic", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		hud->inst_game->WorldToScreen(menuStates.marker3, &values.pos3.x, &values.pos3.y);
		
		ImVec2 center(values.pos3.x, values.pos3.y);
		ImU32 outlineColor = ImVec4ToImCol32(menuStates.marker3Color);
		int numSegments = 8;

		// Draw a circle around a point
		drawList->AddCircle(center, menuStates.markerSize, outlineColor, numSegments, 2);

		ImGui::End();
	}
}
ui_menu::ui_menu(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_menu::~ui_menu()
{

}