#pragma once
#include "vectors.h"

struct MenuStates
{
	bool debugOpen;
	bool mainShow;
	bool playingDemos;
	bool showFpsOverlay;
	bool lineupMenuOpen;
	float timescale;
	int demoNum;
	char* extraCmd;
	bool simF9;
	bool justFinished = false;
	int fpsSize;
	int playDemosFrom;
	int playDemosIndex = 1;
	bool show_position;
	bool demoPlaying;
	bool showFpsImage;
	bool wtmod;
	bool threexp;
	float imageScale = 0.7f;
	bool veloMeter = false;
	vec4<float> color = { 0.0f, 1.0f, 0.0f, 1.0f };
	float veloScale;
	bool lockVeloPos = true;
	vec2<float> veloPos;
	float previousVelo;
	
	bool drawMarker1;
	bool drawMarker2;
	bool drawMarker3;
	vec3<float> marker1;
	vec3<float> marker2;
	vec3<float> marker3;

	float markerSize = 20.0f;
	ImVec4 marker1Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	ImVec4 marker2Color = { 0.0f, 1.0f, 0.0f, 1.0f };
	ImVec4 marker3Color = { 0.0f, 0.0f, 1.0f, 1.0f };

	char* demoName;
	std::string copiedPosition = "";
};

struct values
{
	vec2<float> pos1;
	vec2<float> pos2;
	vec2<float> pos3;
	
	bool load_pos = false;
};

class ui_menu
{
	public:
	ui_menu(class CJOpenHud* hud);
	~ui_menu();
	void menu(CJOpenHud* hud);
	static ImU32 ImVec4ToImCol32(ImVec4 color);
	void SetDefaultConfiguration(vec2<float>& position, vec4<float>& color, float& scale);
	void LoadConfiguration(vec2<float>& position, vec4<float>& color, float& scale);
	void SaveConfiguration(const vec2<float>& position, const vec4<float>& color, const float& scale);
	ImVec4 vec4ToImVec4(vec4<float> vector);
	void render();

	MenuStates menuStates;
	static values values;
};

