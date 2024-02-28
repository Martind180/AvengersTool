#include "pch.h"
#include "ui_menu.h"
#include "Avengers.h"


void ui_menu::menu(Avengers* hud)
{
	ImGui::Begin("Avengers Helper");

	//################ Demoplayer menu toggle ###############
	if(ImGui::Button("Demo Player"))
	{
		demoplayer_menu = !demoplayer_menu;
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

		copied_position = ss.str();
		hud->save_configuration();
		
		ImGui::SetClipboardText(copied_position.c_str());
	}
	ImGui::SameLine(); if(ImGui::Checkbox("Show Coordinates", &show_position))
	{
		hud->save_configuration();
	}

	//#######################################################
	
	//################# SPEEDOMETER ########################
	if (ImGui::Checkbox("Speedometer", &velo_meter))
	{
		hud->save_configuration();
	}
	
	ImGui::SameLine(); ImGui::ColorButton("Color Button", color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("ColorPickerPopup");
	}

	if(ImGui::BeginPopup("ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &color.x);

		ImGui::EndPopup();

		hud->save_configuration();
	}
	ImGui::SameLine(); ImGui::Checkbox("Lock Speed Position", &lock_velo_pos);

	if(ImGui::Checkbox("Sep Speedometer", &sep_velo))
	{
		hud->save_configuration();
	}
	
	if(ImGui::SliderFloat("Speed Size", &velo_scale, 0.01f, 10.f))
	{
		hud->save_configuration();
	}
	//#######################################################

	//################# POSITION MARKERS ########################
	if (ImGui::Button("Mark Position 1"))
	{
		draw_marker1 = true;
		marker1 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 1 Colour Button", marker1_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker1ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker1ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &marker1_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 1"))
	{
		draw_marker1 = false;
	}
	
	if (ImGui::Button("Mark Position 2"))
	{
		draw_marker2 = true;
		marker2 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 2 Colour Button", marker2_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker2ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker2ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &marker2_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 2"))
	{
		draw_marker2 = false;
	}
	
	if (ImGui::Button("Mark Position 3"))
	{
		draw_marker3 = true;
		marker3 = hud->inst_game->get_origin();
	}
	ImGui::SameLine(); ImGui::ColorButton("Marker 3 Colour Button", marker3_color);

	if(ImGui::IsItemClicked())
	{
		ImGui::OpenPopup("Marker3ColorPickerPopup");
	}

	if(ImGui::BeginPopup("Marker3ColorPickerPopup"))
	{
		ImGui::ColorPicker4("Color Picker", &marker3_color.x);

		ImGui::EndPopup();
	}
	ImGui::SameLine(); if (ImGui::Button("Remove Marker 3"))
	{
		draw_marker3 = false;
	}

	ImGui::SliderFloat("Marker Size", &marker_size, 5.0f, 100.0f);
	//#######################################################

	
	ImGui::End();
}

void ui_menu::render()
{
	Avengers* hud = Avengers::get_instance();
	
	if(hud->want_input)
	{
		menu(hud);
	}

	if (show_position) {
		hud->inst_ui_position->render();
		hud->inst_ui_view->render();

		hud->save_configuration();
	}

	//Render speedometer
	if ((velo_meter || sep_velo) && hud->inst_game->is_connected())
	{
		hud->inst_ui_velocity->render(hud, lock_velo_pos, velo_pos, velo_scale, color, previous_velo);
	}

	//Draw markers
	//This can probably be made much better using an array to draw as many markers as needed if they shared the same color values
	if (draw_marker1 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(marker1, pos1, marker1_color, marker_size);
	}
	if (draw_marker2 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(marker2, pos2, marker2_color, marker_size);
	}
	if (draw_marker3 && hud->inst_game->is_connected())
	{
		hud->inst_ui_position_marker->render(marker3, pos3, marker3_color, marker_size);
	}
}

ui_menu::ui_menu(Avengers* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });
}
ui_menu::~ui_menu()
{

}