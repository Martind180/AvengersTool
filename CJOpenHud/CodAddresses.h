#pragma once
#ifndef CODADDRESSES_H
#define CODADDRESSES_H

constexpr int addr_inair = 0x007944E4;  //1023 - in air, !1023 not
constexpr int addr_velocity = 0x0079449C;
constexpr int addr_setVelocity = 0x013255D0;
//constexpr int addr_velocity = 0x00C5F97C;
constexpr int addr_mapname = 0x00E36218;
constexpr int addr_position = 0x00794490;
constexpr int addr_setPosition = 0x013255C4;
constexpr int addr_sprint = 0x00794560; // >= 20 is sprint
constexpr int addr_inFocus = 0x0CC1B704;
constexpr int addr_ingame = 0xC5F900;
constexpr int addr_playerState = 0x00794474;
constexpr int addr_playerName = 0x0150DFEC;
constexpr int func_addr_jump_p = 0x00462f40;  //jump+
constexpr int func_addr_jump_m = 0x00462f90;  //jump-
constexpr int func_addr_forward_p = 0x00462980;  //forward+
constexpr int func_addr_forward_m = 0x00462990;  //forward+
constexpr int func_addr_right_p = 0x00462a20;  //right+
constexpr int func_addr_right_m = 0x00462a30;  //right
constexpr int func_addr_sprint_p = 0x00462a30;  //sprint+
constexpr int func_addr_sprint_m = 0x00462fc0;  //sprint-
constexpr int addr_timescale = 0x0CBABC88;
constexpr int addr_3xp_fps = 0x00771F84;
constexpr int addr_deltaAngles = 0x0074E3D0;  //float
constexpr int addr_viewAngles = 0x00C84FD8;  //vec3f
constexpr int addr_createMove = 0x00463E00;
constexpr int addr_usercmd = 0x00CC4FF8;
constexpr int addr_maxfps_wtmod = 0x00795150;
constexpr int addr_maxfps_3xp = 0x00771F84;

#endif
