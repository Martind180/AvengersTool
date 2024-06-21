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

float game::get_dir_diff()
{
	Lmove lMove = get_lmove();

	if (lMove.isForward) {
		return (lMove.isRight) ? -45.f : 45.f;
	}
	else {
		return (lMove.isRight) ? -90.f : +90.f;
	}

	return 0;
}

Lmove game::get_lmove()
{
	using namespace mm;
	input_s* input = (input_s*)addr_usercmd;
	usercmd_s* cmd = input->GetUserCmd(input->currentCmdNum);
	Lmove lMove;

	lMove.isInAir = *reinterpret_cast<int*>(addr_inair) == 1023 ? true : false;
	lMove.isSprint = *reinterpret_cast<int*>(addr_sprint) >= 20 || *reinterpret_cast<int*>(addr_sprint) == 5 ? true : false;
	lMove.isMoving = fabsf(get_velocity().Length2D()) > 0 ? true : false;
	lMove.fullLean = *reinterpret_cast<float*>(addr_lean) >= 0.5f || *reinterpret_cast<float*>(addr_lean) >= 0.25f ? true : false;

	if (cmd->forward != 0)
	{
		lMove.isBack = cmd->forward == 129 ? true : false;
		lMove.isForward = cmd->forward == 127 ? true : false;
	}
	else
	{
		lMove.isBack = false;
		lMove.isForward = false;
	}

	if (cmd->side != 0)
	{
		lMove.isRight = cmd->side == 127 ? true : false;
		lMove.isLeft = cmd->side == 129 ? true : false;
	}
	else
	{
		lMove.isLeft = false;
		lMove.isRight = false;
	}

	return lMove;
}

float game::get_velocity_angle()
{
	using namespace mm;
	vec3<float> velocity = *reinterpret_cast<vec3<float>*>(addr_velocity);
	return normalise(tilt_angle(truncate_vector(get_velocity())), 0.f, 360.f);
}

float game::get_delta()
{
	float accelAngle = 0.f;
	get_view();

	accelAngle = mm::normalise(get_view().y + get_dir_diff(), 0.f, 360.f);

	float delta = get_velocity_angle() - accelAngle;
	return mm::normalise(delta, -180.f, 180.f);
}

float game::get_delta_optimal()
{
	constexpr float g_speed = 190.f;

	Lmove lMove = get_lmove();
	float speed = get_velocity().Length2D();
	float deltaOpt = mm::to_degrees(acosf((g_speed - get_accel()) / speed));

	if (get_lmove().isLeft)
	{
		deltaOpt *= -1.f;
	}

	return deltaOpt;
}

int game::get_fps()
{
	int maxFps = *reinterpret_cast<int*>(addr_maxfps);
	return maxFps;
}

float game::get_accel()
{
	return g_speed / get_fps();
}

float game::get_optimal_angle()
{
	float delta = get_delta();
	float deltaOptimal = get_delta_optimal();

	float yaw = get_view().y;

	yaw += delta - deltaOptimal;

	return mm::normalise(yaw, 0.f, 360.f);
}

bool game::isOnGround()
{
	return *reinterpret_cast<int*>(addr_inair) != 1023;
}

int game::getJumpTime()
{
	auto ps = (playerState_t*)(0x794474);

	return ps->JumpTime;
}

vec2<float> game::get_screen_res()
{
	cg_t* ref = (cg_t*)0x0074E338;
	vec2<float> screenres{};
	screenres.x = ref->Refdef.ScreenWidth;
	screenres.y = ref->Refdef.ScreenHeight;
	return screenres;
}

vec3<float> game::get_delta_angles()
{
	return *reinterpret_cast<vec3<float>*>(addr_delta_angles);
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

void game::toggle_iwd_check(bool state)
{
	void* ptr = GetModuleHandleA("cod4x_021.dll");
	char* cPtr = static_cast<char*>(ptr);
	cPtr += addr_cod4x_pakcompare_offset;
	ptr = static_cast<void*>(cPtr);

	DWORD oldProtect;
	VirtualProtect(ptr, 0x1, PAGE_EXECUTE_READWRITE, std::addressof(oldProtect));

	if (state) {
		*reinterpret_cast<char*>(addr_disable_pure_check) = 1;
		*reinterpret_cast<char*>(ptr) = 0xEB;  //JNE -> JMP
	}
	else {
		*reinterpret_cast<char*>(addr_disable_pure_check) = 0;
		*reinterpret_cast<char*>(ptr) = 0x75;  //JMP -> JNE
	}

	VirtualProtect(ptr, 0x1, oldProtect, &oldProtect);
}
