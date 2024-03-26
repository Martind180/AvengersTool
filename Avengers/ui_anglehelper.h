#pragma once
#include "Avengers.h"
#include "imgui.h"
#include "vectors.h"
#include "game_math.h"

class ui_anglehelper
{
public:
	ui_anglehelper(class Avengers* hud);
	~ui_anglehelper();
	void render(Avengers*& hud, ImVec4& color);
};

