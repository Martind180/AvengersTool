#include "pch.h"
#include "ui_settings.h"
#include "Avengers.h"


void ui_settings::render()
{

}
ui_settings::ui_settings(Avengers* hud)
{
	hud->inst_render->add_callback([this]() { this->render(); });

}
ui_settings::~ui_settings()
{

}