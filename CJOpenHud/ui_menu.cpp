#include "pch.h"
#include "ui_menu.h"
#include "CJOpenHud.h"


values ui_menu::values;

void ui_menu::menu(CJOpenHud* hud)
{
	ImGui::Begin("Avengers Helper");

	//################ Demoplayer menu toggle ###############
	if(ImGui::Button("Demo Player"))
	{
		menuStates.demoplayer_menu = !menuStates.demoplayer_menu;
	}
	//#######################################################

	//################ Bind demo to load key ###############
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
	//#######################################################

	//################# Position ############################
	if (ImGui::Button("Copy position"))
	{
		vec3<float> pos = hud->inst_game->get_origin();
		vec3<float> view = hud->inst_game->get_view();

		std::stringstream ss;
		ss << std::fixed << std::setprecision(6) << pos.x <<  " " << pos.y << " " << pos.z + 60 << " " << view.y << " " << view.x;

		menuStates.copiedPosition = ss.str();
		hud->save_configuration();
		
		ImGui::SetClipboardText(menuStates.copiedPosition.c_str());
	}
	ImGui::SameLine(); if(ImGui::Checkbox("Show Coordinates", &menuStates.show_position))
	{
		hud->save_configuration();
	}

	//#######################################################
	
	//################# SPEEDOMETER ########################
	if (ImGui::Checkbox("Speedometer", &menuStates.velo_meter))
	{
		hud->save_configuration();
	}
	
	ImGui::SameLine(); ImGui::ColorButton("Color Button", menuStates.color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("ColorPickerPopup");
	}

	if(ImGui::BeginPopup("ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menuStates.color.x);

		ImGui::EndPopup();

		hud->save_configuration();
	}
	ImGui::SameLine(); ImGui::Checkbox("Lock Speed Position", &menuStates.lock_velo_pos);

	if(ImGui::Checkbox("Sep Speedometer", &menuStates.sep_velo))
	{
		hud->save_configuration();
	}
	
	if(ImGui::SliderFloat("Speed Size", &menuStates.velo_scale, 0.01f, 10.f))
	{
		hud->save_configuration();
	}
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
	//#######################################################

	
	ImGui::End();
}

void ui_menu::render()
{
	CJOpenHud* hud = CJOpenHud::get_instance();
	
	if(hud->want_input)
	{
		menu(hud);
	}

	if (menuStates.show_position) {
		hud->inst_ui_position->render();
		hud->inst_ui_view->render();

		hud->save_configuration();
	}

	if (menuStates.velo_meter && hud->inst_game->is_connected())
	{
		hud->inst_ui_velocity->render(hud, menuStates.lock_velo_pos, menuStates.velo_pos, menuStates.velo_scale, menuStates.color, menuStates.previous_velo);
	}
	
	if(menuStates.sep_velo && hud->inst_game->is_connected())
	{
		hud->inst_ui_velocity_sep->render(hud, menuStates.lock_velo_pos, menuStates.velo_pos, menuStates.velo_scale, menuStates.color, menuStates.previous_velo);
	}

	if (menuStates.draw_marker1 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(menuStates.marker1, values.pos1, menuStates.marker1_color, menuStates.marker_size);
	}

	if (menuStates.draw_marker2 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(menuStates.marker2, values.pos2, menuStates.marker2_color, menuStates.marker_size);
	}

	if (menuStates.draw_marker3 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(menuStates.marker3, values.pos3, menuStates.marker3_color, menuStates.marker_size);
	}
}

ui_menu::ui_menu(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_menu::~ui_menu()
{

}