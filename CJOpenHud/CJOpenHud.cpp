#include "pch.h"
#include "CJOpenHud.h"

#include "ui_demoplayer.h"

//pretend its an audio codec for the miles sound system
bool __stdcall RIB_Main(int a, int b)
{
	return true;
}

CJOpenHud* CJOpenHud::inst_CJOpenHud = nullptr;
bool CJOpenHud::bind_toggle_input(UINT key_state)
{
	if (key_state == WM_KEYDOWN) //return true on key down just so nothing else receives the key down stroke
		return true; 
	if (key_state == WM_KEYUP)
	{
		want_input = !want_input;
		return true;
	}
}

bool CJOpenHud::bind_tp_to_saved_pos(UINT key_state)
{
	if (key_state == WM_KEYDOWN) //return true on key down just so nothing else receives the key down stroke
		return true; 
	if (key_state == WM_KEYUP)
	{
		inst_ui_menu->tp_to_saved_position();
		return true;
	}
}

CJOpenHud::CJOpenHud()
{
	exit = false;
	inst_CJOpenHud = this;
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

	inst_input->add_callback(VK_INSERT, [this](UINT key_state) { return this->bind_toggle_input(key_state); });
	inst_input->add_callback(VK_F6, [this](UINT key_state) { return this->bind_toggle_input(key_state); });
	inst_input->add_callback(VK_F3, [this](UINT key_state) { return this->bind_tp_to_saved_pos(key_state); });
}

CJOpenHud::~CJOpenHud()
{
	delete inst_CJOpenHud;
}

CJOpenHud* CJOpenHud::get_instance()
{
	return inst_CJOpenHud;
}