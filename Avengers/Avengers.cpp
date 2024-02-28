#include "pch.h"
#include "Avengers.h"

#include "ui_demoplayer.h"

//pretend its an audio codec for the miles sound system
bool __stdcall RIB_Main(int a, int b)
{
	return true;
}

Avengers* Avengers::inst_Avengers = nullptr;
bool Avengers::bind_toggle_input(UINT key_state)
{
	if (key_state == WM_KEYDOWN) //return true on key down just so nothing else receives the key down stroke
		return true; 
	if (key_state == WM_KEYUP)
	{
		want_input = !want_input;
		return true;
	}
}

bool Avengers::bind_tp_to_saved_pos(UINT key_state)
{
	if (key_state == WM_KEYDOWN) //return true on key down just so nothing else receives the key down stroke
		return true; 
	if (key_state == WM_KEYUP)
	{
		if(inst_ui_menu->copied_position != "" && inst_game->is_connected())
			inst_game->send_command_to_console(("setviewpos " + inst_ui_menu->copied_position).c_str());
		return true;
	}
}

// Function to load configuration from a file or set default values
void Avengers::load_configuration() {
	// Specify the file path
	std::string filePath = "AvengersConfig.txt";

	// Check if the file exists
	if (std::ifstream config_file(filePath); config_file.is_open()) {
		std::string line;
		while (std::getline(config_file, line)) {
			if (line.find("Speedometer:") != std::string::npos)
			{
				int value;
				//Parse speedometer boolean
				sscanf_s(line.c_str(), "Speedometer: %d", &value);

				inst_ui_menu->velo_meter = value == 1;
			}
			else if(line.find("SepVelo:") != std::string::npos)
			{
				int value1;
				//Parse sep speedometer boolean
				sscanf_s(line.c_str(), "SepVelo: %d", &value1);

				inst_ui_menu->sep_velo = value1 == 1;
			}
			else if (line.find("Position:") != std::string::npos) {
				// Parse position
				sscanf_s(line.c_str(), "Position: %f %f", &inst_ui_menu->velo_pos.x, &inst_ui_menu->velo_pos.y);
			} else if (line.find("Color:") != std::string::npos) {
				// Parse color
				sscanf_s(line.c_str(), "Color: %f %f %f %f", &inst_ui_menu->color.x, &inst_ui_menu->color.y, &inst_ui_menu->color.z, &inst_ui_menu->color.w);
			}
			else if (line.find("Scale:") != std::string::npos) {
				// Parse scale
				sscanf_s(line.c_str(), "Scale: %f", &inst_ui_menu->velo_scale);
			}
			else if (line.find("PosHud:") != std::string::npos)
			{
				//Parse Position Hud boolean
				int value;
				sscanf_s(line.c_str(), "Speedometer: %d", &value);

				inst_ui_menu->show_position = value == 1;
			}
			else if (line.find("LastCopiedPosition:") != std::string::npos)
			{
				//Parse last copied position
				size_t pos = line.find_first_of("0123456789");

				std::string copied_position = line.substr(pos);
				
				inst_ui_menu->copied_position = copied_position;
			}
		}

		config_file.close();
	} else {
		std::cout << "Config file not found. Using default values.\n";
		save_configuration();
	}
}

void Avengers::save_configuration() {
	
	std::ofstream configFile("AvengersConfig.txt");  // Open a file for writing

	if (configFile.is_open()) {
		// Save Speedometer on
		configFile << "Speedometer: " << inst_ui_menu->velo_meter << "\n";

		// Save Sep Speedometer on
		configFile << "SepVelo: " << inst_ui_menu->sep_velo << "\n";
		
		// Save position
		configFile << "Position: " << inst_ui_menu->velo_pos.x << " " << inst_ui_menu->velo_pos.y << "\n";

		// Save color
		configFile << "Color: " << inst_ui_menu->color.x << " " << inst_ui_menu->color.y << " " << inst_ui_menu->color.z << " " << inst_ui_menu->color.w << "\n";

		//Save scale
		configFile << "Scale: " << inst_ui_menu->velo_scale << "\n";

		//Save Position
		configFile << "PosHud: " << inst_ui_menu->show_position << "\n";

		//Save Last Copied Position
		if (inst_ui_menu->copied_position != "")
		{
			configFile << "LastCopiedPosition: " << inst_ui_menu->copied_position << "\n";
		}

		configFile.close();  // Close the file
	} else {
		std::cerr << "Error opening config file for writing\n";
	}
}

Avengers::Avengers()
{
	exit = false;
	inst_Avengers = this;
	inst_hooks = std::shared_ptr<hook_wrapper>(new hook_wrapper);
	inst_game = std::shared_ptr<game>(new game());
	inst_input = std::shared_ptr<input>(new input(this));
	inst_render = std::shared_ptr<render>(new render(this));
	
	inst_ui_settings = std::shared_ptr<ui_settings>(new ui_settings(this));
	inst_ui_position = std::shared_ptr<ui_position>(new ui_position(this));
	inst_ui_velocity = std::shared_ptr<ui_velocity>(new ui_velocity(this));
	inst_ui_view = std::shared_ptr<ui_view>(new ui_view(this));
	inst_ui_menu = std::shared_ptr<ui_menu>(new ui_menu(this));
	inst_ui_demoplayer = std::shared_ptr<ui_demoplayer>(new ui_demoplayer(this));
	inst_ui_position_marker = std::shared_ptr<ui_position_marker>(new ui_position_marker(this));
	inst_ui_fps_image = std::shared_ptr<ui_fps_image>(new ui_fps_image(this));

	//Added both INSERT and F6 to open the menu for people who have smaller keyboards and cant find that INSERT key ¬_¬
	inst_input->add_callback(VK_INSERT, [this](UINT key_state) { return this->bind_toggle_input(key_state); });
	inst_input->add_callback(VK_F6, [this](UINT key_state) { return this->bind_toggle_input(key_state); });

	//Keybind to tp to the last saved postion
	inst_input->add_callback(VK_F3, [this](UINT key_state) { return this->bind_tp_to_saved_pos(key_state); });

	load_configuration();
}

Avengers::~Avengers()
{
}

Avengers* Avengers::get_instance()
{
	return inst_Avengers;
}