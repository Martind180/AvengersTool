#include "pch.h"
#include "Game.h"


HWND game::get_window()
{
	return *(HWND*)0xCC1B6FC;
}
bool game::is_focused()
{
	return *(bool*)0x0CC1B704;
}

bool game::is_in_main_menu()
{
	return *reinterpret_cast<int*>(0x00C5F900) == 0;
}

LPDIRECT3DDEVICE9 game::get_device()
{
	return *(LPDIRECT3DDEVICE9*)0xCC9A408;
}

bool game::is_connected()
{
	int state = *(int*)0xC5F900;
	return state == connection_state_connected;
}

vec3<float> game::get_view()
{
	vec3<float> view = *(vec3<float>*)0x79B698;
	return view;
}

vec3<float> game::get_origin()
{
	vec3<float> pos = *(vec3<float>*)0x794490;
	return pos;
}

vec3<float> game::get_velocity()
{
	vec3<float> vel = *(vec3<float>*)0x79449c;
	return vel;
}

void game::send_command_to_console(const char* command)
{
	DWORD buffer_cmd = 0x4f8d90;
	__asm
	{
		mov eax, command
		mov ecx, 0
		call buffer_cmd
	}
}

bool game::WorldToScreen(vec3<float> World, float* screen_x, float* screen_y)
{
	cg_t* ref = (cg_t*)0x0074E338;
	vec3<float> Position = subtractVector(World, ref->Refdef.Origin);
	vec3<float> Transform;

	Transform.x = dotProduct(Position, ref->Refdef.ViewAxis[1]);
	Transform.y = dotProduct(Position, ref->Refdef.ViewAxis[2]);
	Transform.z = dotProduct(Position, ref->Refdef.ViewAxis[0]);

	if (Transform.z < 0.1f)
		return false;

	vec2<float> Center = { ref->Refdef.ScreenWidth * 0.5f, ref->Refdef.ScreenHeight * 0.5f };

	*screen_x = Center.x * (1 - (Transform.x / ref->Refdef.FOV.x / Transform.z));
	*screen_y = Center.y * (1 - (Transform.y / ref->Refdef.FOV.y / Transform.z));

	return true;
}

int game::getFps_wtmod()
{
	int maxFps = (int)*reinterpret_cast<float*>(addr_maxfps_wtmod);
	return maxFps;
}

int game::getFps_3xp()
{
	int maxFps = (int)*reinterpret_cast<float*>(addr_maxfps_3xp);
	return maxFps;
}