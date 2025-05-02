#pragma once
#include "cod4Structs.h"
#include "d3dx9/d3dx9.h"
#include "vectors.h"
#include "game_math.h"
#include "Lmove.h"
#include "memory.h"

enum connection_state_ : int
{
    connection_state_uninitialized,
    connection_state_disconnected,
    connection_state_authorizing,
    connection_state_connecting,
    connection_state_challenging,
    connection_state_established,
    connection_state_loading,
    connection_state_primed,
    connection_state_active,
    connection_state_connected
};

typedef struct cvar_s
{
	char* name;
	char* string;
	char* resetString;		// cvar_restart will reset to this value
	char* latchedString;		// for CVAR_LATCH vars
	int			flags;
	bool	modified;			// set each time the cvar is changed
	int			modificationCount;	// incremented each time the cvar is changed
	float		value;				// atof( string )
	int			integer;			// atoi( string )
	struct cvar_s* next;
	struct cvar_s* hashNext;
} cvar_t;

class game
{
public:
	struct GfxPointVertex
	{
		vec3<float> location;
		char color[4];
		GfxPointVertex() : location(0, 0, 0), color{ 0, 0, 0, 0 } {};
		GfxPointVertex(vec3<float> loc, ImColor col)
		{
			location = loc;
			color[0] = col.Value.z * 255;
			color[1] = col.Value.y * 255;
			color[2] = col.Value.x * 255;
			color[3] = col.Value.w * 255;
		}
		GfxPointVertex(vec3<float> loc, char r, char g, char b, char a)
		{
			location = loc;
			color[0] = b;
			color[1] = g;
			color[2] = r;
			color[3] = a;
		}
	};
	
	
	HWND get_window(); 
	bool is_focused();
	bool is_in_main_menu();
	LPDIRECT3DDEVICE9 get_device();
    bool is_connected();
    vec3<float> get_view();
    vec3<float> get_origin();
    vec3<float> get_velocity();
    float get_optimal_angle();
	bool isOnGround();
	static void send_command_to_console(const char* command);
	bool world_to_screen(vec3<float> world, float* screen_x, float* screen_y);
	int get_fps_wtmod();
	int get_fps_3_xp();
	void add_obituary(const std::string& msg);
	int getJumpTime();
    vec2<float> get_screen_res();
	mem::function<void(int count, int width, GfxPointVertex* verts, bool depthTest)> polyline = 0x613040;
    Lmove get_lmove();
	float get_fov();
	cvar_t* getCvar(const char* name);

private:
    vec3<float> get_delta_angles();
    float get_delta();
    float get_delta_optimal();
    float get_velocity_angle();
    float get_dir_diff();
    float get_accel();
    int get_fps();
    constexpr static float g_speed = 190.f;

};

