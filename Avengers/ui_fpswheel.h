#pragma once
#include <map>
#include "cod4Structs.h"
#include "vectors.h"
#include "game_math.h"

class ui_fpswheel
{
public:
	ui_fpswheel(class Avengers* hud);
	~ui_fpswheel();
	void render(class Avengers* hud);
private:
	std::multimap<int, vec2<float>> fpsZones
	{
		//CENTER 90
		{125, vec2<float>(103.7f, 118.9f)},
		{200, vec2<float>(94.5f, 103.7f)},
		{250, vec2<float>(73.6f, 86.9f)},
		{251, vec2<float>(86.9f, 94.5f)},
		{333, vec2<float>(28.90f, 73.6f)},
	};;
};
