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
		menu_states.demoplayer_menu = !menu_states.demoplayer_menu;
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

		menu_states.copied_position = ss.str();
		hud->save_configuration();
		
		ImGui::SetClipboardText(menu_states.copied_position.c_str());
	}
	ImGui::SameLine(); if(ImGui::Checkbox("Show Coordinates", &menu_states.show_position))
	{
		hud->save_configuration();
	}

	//#######################################################
	
	//################# SPEEDOMETER ########################
	if (ImGui::Checkbox("Speedometer", &menu_states.velo_meter))
	{
		hud->save_configuration();
	}
	
	ImGui::SameLine(); ImGui::ColorButton("Color Button", menu_states.color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("ColorPickerPopup");
	}

	if(ImGui::BeginPopup("ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menu_states.color.x);

		ImGui::EndPopup();

		hud->save_configuration();
	}
	ImGui::SameLine(); ImGui::Checkbox("Lock Speed Position", &menu_states.lock_velo_pos);

	if(ImGui::Checkbox("Sep Speedometer", &menu_states.sep_velo))
	{
		hud->save_configuration();
	}
	
	if(ImGui::SliderFloat("Speed Size", &menu_states.velo_scale, 0.01f, 10.f))
	{
		hud->save_configuration();
	}
	//#######################################################

	//################# POSITION MARKERS ########################
	if (ImGui::Button("Mark Position 1"))
	{
		menu_states.draw_marker1 = true;
		menu_states.marker1 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 1 Colour Button", menu_states.marker1_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker1ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker1ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menu_states.marker1_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 1"))
	{
		menu_states.draw_marker1 = false;
	}
	
	if (ImGui::Button("Mark Position 2"))
	{
		menu_states.draw_marker2 = true;
		menu_states.marker2 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 2 Colour Button", menu_states.marker2_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker2ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker2ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menu_states.marker2_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 2"))
	{
		menu_states.draw_marker2 = false;
	}
	
	if (ImGui::Button("Mark Position 3"))
	{
		menu_states.draw_marker3 = true;
		menu_states.marker3 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 3 Colour Button", menu_states.marker3_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker3ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker3ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &menu_states.marker3_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 3"))
	{
		menu_states.draw_marker3 = false;
	}

	ImGui::SliderFloat("Marker Size", &menu_states.marker_size, 5.0f, 100.0f);
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

	if (menu_states.show_position) {
		hud->inst_ui_position->render();
		hud->inst_ui_view->render();

		hud->save_configuration();
	}

	//Render speedometer
	if ((menu_states.velo_meter || menu_states.sep_velo) && hud->inst_game->is_connected())
	{
		hud->inst_ui_velocity->render(hud, menu_states.lock_velo_pos, menu_states.velo_pos, menu_states.velo_scale, menu_states.color, menu_states.previous_velo);
	}

	//Draw markers
	//This can probably be made much better using an array to draw as many markers as needed if they shared the same color values
	if (menu_states.draw_marker1 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(menu_states.marker1, values.pos1, menu_states.marker1_color, menu_states.marker_size);
	}
	if (menu_states.draw_marker2 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(menu_states.marker2, values.pos2, menu_states.marker2_color, menu_states.marker_size);
	}
	if (menu_states.draw_marker3 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(menu_states.marker3, values.pos3, menu_states.marker3_color, menu_states.marker_size);
	}
}

ui_menu::ui_menu(CJOpenHud* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_menu::~ui_menu()
{

}