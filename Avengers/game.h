#pragma once
#include "d3dx9/d3dx9.h"
#include "vectors.h"
#include "game_math.h"
#include "Lmove.h"

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

class game
{
public:
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

private:
    vec3<float> get_delta_angles();
    float get_delta();
    float get_delta_optimal();
    float get_velocity_angle();
    float get_dir_diff();
    Lmove get_lmove();
    float get_accel();
    int get_fps();
    constexpr static float g_speed = 190.f;

};

