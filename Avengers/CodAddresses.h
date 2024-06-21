#pragma once
#ifndef CODADDRESSES_H
#define CODADDRESSES_H

constexpr int addr_inair = 0x007944E4;  //1023 - in air, !1023 not
constexpr int addr_velocity = 0x0079449C;
constexpr int addr_position = 0x00794490;
constexpr int addr_ingame = 0xC5F900;
constexpr int addr_timescale = 0x0CBABC88;
constexpr int addr_view = 0x79B698;  //vec3f
constexpr int addr_maxfps_wtmod = 0x00795150;
constexpr int addr_maxfps_3xp = 0x00771F84;
constexpr int addr_delta_angles = 0x0074E3D0;
constexpr int addr_usercmd = 0x00CC4FF8;
constexpr int addr_sprint = 0x00794560; // >= 20 is sprint
constexpr int addr_lean = 0x007944D0;
constexpr int addr_maxfps = 0x0CBAB8AC;  //float
constexpr int addr_engine_draw = 0x658860;
constexpr int addr_disable_pure_check = 0xD5EC497;

constexpr int addr_cod4x_pakcompare_offset = 0x183D7;

#endif
