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
	return *reinterpret_cast<int*>(addr_ingame) == connection_state_uninitialized;
}

LPDIRECT3DDEVICE9 game::get_device()
{
	return *(LPDIRECT3DDEVICE9*)0xCC9A408;
}

bool game::is_connected()
{
	int state = *(int*)addr_ingame;
	return state == connection_state_connected;
}

vec3<float> game::get_view()
{
	vec3<float> view = *(vec3<float>*)addr_view;
	return view;
}

vec3<float> game::get_origin()
{
	vec3<float> pos = *(vec3<float>*)addr_position;
	return pos;
}

vec3<float> game::get_velocity()
{
	vec3<float> vel = *(vec3<float>*)addr_velocity;
	return vel;
}

bool game::isOnGround()
{
	return *reinterpret_cast<int*>(addr_inair) != 1023;
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

bool game::world_to_screen(vec3<float> world, float* screen_x, float* screen_y)
{
	cg_t* ref = (cg_t*)0x0074E338;
	
	vec3<float> position = world - ref->Refdef.Origin;
	
	vec3<float> transform;
	transform.x = position.DotProduct(ref->Refdef.ViewAxis[1]);
	transform.y = position.DotProduct(ref->Refdef.ViewAxis[2]);
	transform.z = position.DotProduct(ref->Refdef.ViewAxis[0]);
	
	if (transform.z < 0.1f)
		return false;

	vec2 center = { ref->Refdef.ScreenWidth * 0.5f, ref->Refdef.ScreenHeight * 0.5f };

	*screen_x = center.x * (1 - (transform.x / ref->Refdef.FOV.x / transform.z));
	*screen_y = center.y * (1 - (transform.y / ref->Refdef.FOV.y / transform.z));

	return true;
}

int game::get_fps_wtmod()
{
	int maxFps = (int)*reinterpret_cast<float*>(addr_maxfps_wtmod);
	return maxFps;
}

int game::get_fps_3_xp()
{
	int maxFps = (int)*reinterpret_cast<float*>(addr_maxfps_3xp);
	return maxFps;
}

void game::add_obituary(const std::string& msg)
{
	std::string final_msg = msg + "\n";
	reinterpret_cast<void(__cdecl*)(conChannel_t, const char*, msgtype_t)>(0x4FCA50)(conChannel_t::CON_CHANNEL_GAMENOTIFY, final_msg.c_str(), msgtype_t::MSG_DEFAULT);
}