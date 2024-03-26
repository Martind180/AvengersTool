#pragma once
#ifndef CODSTRUCTS_H
#define CODSTRUCTS_H

#include "Avengers.h"
#include "windows.h"

#pragma once
enum team_t
{
    TEAM_FREE = 0x0,
    TEAM_AXIS = 0x1,
    TEAM_ALLIES = 0x2,
    TEAM_SPECTATOR = 0x3,
    TEAM_NUM_TEAMS = 0x4,
};

enum class  msgtype_t : int {
    MSG_DEFAULT,
    MSG_NA,    //Not defined
    MSG_WARNING,
    MSG_ERROR,
    MSG_NORDPRINT
};
enum class conChannel_t : int
{
    CON_CHANNEL_DONT_FILTER = 0x0,
    CON_CHANNEL_ERROR = 0x1,
    CON_CHANNEL_GAMENOTIFY = 0x2,
    CON_CHANNEL_BOLDGAME = 0x3,
    CON_CHANNEL_SUBTITLE = 0x4,
    CON_CHANNEL_OBITUARY = 0x5,
    CON_CHANNEL_LOGFILEONLY = 0x6,
    CON_CHANNEL_CONSOLEONLY = 0x7,
    CON_CHANNEL_GFX = 0x8,
    CON_CHANNEL_SOUND = 0x9,
    CON_CHANNEL_FILES = 0xA,
    CON_CHANNEL_DEVGUI = 0xB,
    CON_CHANNEL_PROFILE = 0xC,
    CON_CHANNEL_UI = 0xD,
    CON_CHANNEL_CLIENT = 0xE,
    CON_CHANNEL_SERVER = 0xF,
    CON_CHANNEL_SYSTEM = 0x10,
    CON_CHANNEL_PLAYERWEAP = 0x11,
    CON_CHANNEL_AI = 0x12,
    CON_CHANNEL_ANIM = 0x13,
    CON_CHANNEL_PHYS = 0x14,
    CON_CHANNEL_FX = 0x15,
    CON_CHANNEL_LEADERBOARDS = 0x16,
    CON_CHANNEL_LIVE = 0x17,
    CON_CHANNEL_PARSERSCRIPT = 0x18,
    CON_CHANNEL_SCRIPT = 0x19,
    CON_CHANNEL_SPAWNSYSTEM = 0x1A,
    CON_CHANNEL_COOPINFO = 0x1B,
    CON_CHANNEL_SERVERDEMO = 0x1C,
    CON_CHANNEL_DDL = 0x1D,
    CON_CHANNEL_NETWORK = 0x1E,
    CON_CHANNEL_SCHEDULER = 0x1F,
    CON_FIRST_DEBUG_CHANNEL = 0x1F,
    CON_CHANNEL_TASK = 0x20,
    CON_CHANNEL_SPU = 0x21,
    CON_CHANNEL_FILEDL = 0x22,
    CON_BUILTIN_CHANNEL_COUNT = 0x23
};

struct SprintState
{
    int SprintButtonUpRequired; //0x0000
    int SprintDelay; //0x0004
    int LastSprintStart; //0x0008
    int LastSprintEnd; //0x000C
    int SprintStartMaxLength; //0x0010
}; //Size=0x0014

struct MantleState
{
    float Yaw; //0x0000
    int Timer; //0x0004
    int TransIndex; //0x0008
    int Flags; //0x000C
}; //Size=0x0010

struct playerState_t // adress is 0x00794474
{
    int CommandTime; //0x0000
    int PM_Type; //0x0004
    int BobCycle; //0x0008
    int PM_Flags; //0x000C
    int WeaponFlags; //0x0010
    int OtherFlags; //0x0014
    int PM_Time; //0x0018
    vec3<float> Origin; //0x001C
    vec3<float> Velocity; //0x0028
    vec2<float> OldVelocity; //0x0034
    int WeaponTime; //0x003C
    int WeaponDelay; //0x0040
    int GrenadeTimeLeft; //0x0044
    int ThrowbackGrenadeOwner; //0x0048
    int ThrowbackGrenadeTimeLeft; //0x004C
    int WeaponRestrictKickTime; //0x0050
    int FoliageSoundTime; //0x0054
    int Gravity; //0x0058
    float Lean; //0x005C
    int Speed; //0x0060
    vec3<float> DeltaAngles; //0x0064
    int GroundEntityNum; //0x0070
    vec3<float> LadderVec; //0x0074
    int JumpTime; //0x0080
    float JumpOriginZ; //0x0084
    int LegsTimer; //0x0088
    int LegsAnim; //0x008C
    int TorsoTimer; //0x0090
    int TorsoAnim; //0x0094
    int LegsAnimDuration; //0x0098
    int TorsoAnimDuration; //0x009C
    int DamageTimer; //0x00A0
    int DamageDuration; //0x00A4
    int FlinchYawAnim; //0x00A8
    int MovementDir; //0x00AC
    int EFlags; //0x00B0
    int EventSequence; //0x00B4
    int Events[4]; //0x00B8
    int EventParams[4]; //0x00C8
    int OldEventSequence; //0x00D8
    int ClientNum; //0x00DC
    int OffHandIndex; //0x00E0
    int OffhandSecondary; //0x00E4
    int Weapon; //0x00E8
    int WeaponState; //0x00EC
    int WeaponShotCount; //0x00F0
    float WeaponPosFraction; //0x00F4
    int ADSDelayTime; //0x00F8
    int SpreadOverride; //0x00FC
    int SpreadOverrideState; //0x0100
    int ViewModelIndex; //0x0104
    vec3<float> ViewAngles; //0x0108
    int ViewHeightTarget; //0x0114
    float ViewHeightCurrent; //0x0118
    int ViewHeightLerpTime; //0x011C
    int ViewHeightLerpTarget; //0x0120
    int ViewHeightLerpDown; //0x0124
    vec2<float> ViewAngleClampBase; //0x0128
    vec2<float> ViewAngleClampRange; //0x0130
    int DamageEvent; //0x0138
    int DamageYaw; //0x013C
    int DamagePitch; //0x0140
    int DamageCount; //0x0144
    int Stats[5]; //0x0148
    int Ammo[128]; //0x015C
    int AmmoInClip[128]; //0x035C
    int Weapons[4]; //0x055C
    int WeaponsOld[4]; //0x056C
    int WeaponRechamber[4]; //0x057C
    float ProneDirection; //0x058C
    float ProneDirectionPitch; //0x0590
    float ProneTorsoPitch; //0x0594
    int ViewLocked; //0x0598
    int ViewLockedEntNum; //0x059C
    int CursorHint; //0x05A0
    int CursorHintString; //0x05A4
    int CursorHintEntIndex; //0x05A8
    int ICompassPlayerInfo; //0x05AC
    int RadarEnabled; //0x05B0
    int LocationSelectionInfo; //0x05B4
    SprintState SprintState; //0x05B8
    float TorsoPitch; //0x05CC
    float WaistPitch; //0x05D0
    float HoldBreathScale; //0x05D4
    int HoldBreathTimer; //0x05D8
    float MoveSpeedScaleMultiplier; //0x05DC
    MantleState MantleState; //0x05E0
    float MeleeChargeYaw; //0x05F0
    int MeleeChargeDistance; //0x05F4
    int MeleeChargeTime; //0x05F8
    int Perks; //0x05FC
    int ActionSlotType[4]; //0x0600
    int ActionSlotParam[4]; //0x0610
    int EntityEventSequence; //0x0620
    int WeaponAnim; //0x0624
    float AimSpreadScale; //0x0628
    int ShellShockIndex; //0x062C
    int ShellShockTime; //0x0630
    int ShellShockDuration; //0x0634
    float DOFNearStart; //0x0638
    float DOFNearEnd; //0x063C
    float DOFFarStart; //0x0640
    float DOFFarEnd; //0x0644
    float DOFNearBlur; //0x0648
    float DOFFarBlur; //0x064C
    float DOFViewModelStart; //0x0650
    float DOFViewModelEnd; //0x0654
    char _0x0658[0x1C4]; //0x0658
    char WeaponModels[128]; //0x81C
    int DeltaTime; //0x089C
    int KillCamEntity; //0x08A0
    char _0x08A4[0x26C0]; //hudelems cba to reverse rn
}; //Size=0x2F64
struct trajectory_t
{
    int Type; //0x0000
    int Time; //0x0004
    int Duration; //0x0008
    vec3<float> Base; //0x000C
    vec3<float> Delta; //0x0018
}; //Size=0x0024

struct LerpEntityState
{
    unsigned int EntityFlags; //0x0000
    trajectory_t Postion; //0x0004
    trajectory_t APostion; //0x0028
    char _0x004C[0x1C]; //0x004C
}; //Size=0x0068

struct entityState_t
{
    int Number; //0x0000
    int EType; //0x0004
    LerpEntityState Lerp; //0x0008
    int Time2; //0x0070
    int OtherEntityNum; //0x0074
    int AttackerEntityNum; //0x0078
    int GroundEntityNum; //0x007C
    int LoopSound; //0x0080
    int SurfaceType; //0x0084
    int Index; //0x0088
    int ClientNum; //0x008C
    int IHeadIcon; //0x0090
    int IHeadIconTeam; //0x0094
    int Solid; //0x0098
    int EventParam; //0x009C
    int EventSequence; //0x00A0
    int Events[4]; //0x00A4
    int EventParams[4]; //0x00B4
    int Weapon; //0x00C4
    int WeaponModel; //0x00C8
    int LegsAnim; //0x00CC
    int TorsoAnim; //0x00D0
    int Union1; //0x00D4
    int Union2; //0x00D8
    float TorsoPitch; //0x00DC
    float WaistPitch; //0x00E0
    int PartBits[4]; //0x00E4
}; //Size=0x00F4
struct clientState_s
{
    int ClientIndex; //0x0000
    team_t Team; //0x0004
    int Modelindex; //0x0008
    int AttachModelIndex[6]; //0x000C
    int AttachTagIndex[6]; //0x0024
    char Name[16]; //0x003C
    float MaxSprintTimeMultiplier; //0x004C
    int Rank; //0x0050
    int Prestige; //0x0054
    int Perks; //0x0058
    int AttachedVehEntNum; //0x005C
    int AttachedVehSlotIndex; //0x0060
}; //Size: 0x64

struct snapshot_t
{
    int Flags; //0x0000
    int Ping; //0x0004
    int ServerTime; //0x0008
    playerState_t PlayerState; //0x000C
    int  NumEntities; //0x2F70
    int  NumClients; //0x2F74
    entityState_t Entities[512]; //0x2F78
    clientState_s Clients[64]; //0x21778
    int ServerCommandSequence; //0x23078
}; //Size = 0x2307C

struct refdef_t
{
    int ScreenX; //0x0000
    int ScreenY; //0x0004
    int ScreenWidth; //0x0008
    int ScreenHeight; //0x000C
    vec2<float> FOV; //0x0010
    vec3<float> Origin; //0x0018
    vec3<float> ViewAxis[3]; //0x0024
    //vec3f ViewOffset; //0x0048
    char unknown142[0x4050];
    vec3<float> ViewAngles;
};  //0x00797600

struct cg_t // adress 0x0074E338
{
    int ClientNum; //0x0000
    char _0x0004[0x1C]; //0x0004
    snapshot_t* CurrentSnap; //0x0020
    snapshot_t* NextSnap; //0x0024
    char _0x0028[0x460FC]; //0x0028
    int FrameTime; //0x46124
    int Time; //0x46128
    int OldTime; //0x4612C
    int PhysicsTime; //0x46130
    int MapRestart; //0x46134
    int RenderingThirdPerson; //0x46138
    playerState_t PredictedPlayerState; //0x4613C
    char _0x490A0[0x228];
    refdef_t Refdef; //0x492C8
}; //Size=0xFE7F0

enum OffhandSecondaryClass
{
    PLAYER_OFFHAND_SECONDARY_SMOKE = 0x0,
    PLAYER_OFFHAND_SECONDARY_FLASH = 0x1,
    PLAYER_OFFHAND_SECONDARIES_TOTAL = 0x2,
};

enum ViewLockTypes
{
    PLAYERVIEWLOCK_NONE = 0x0,
    PLAYERVIEWLOCK_FULL = 0x1,
    PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
    PLAYERVIEWLOCKCOUNT = 0x3,
};

enum ActionSlotType
{
    ACTIONSLOTTYPE_DONOTHING = 0x0,
    ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
    ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
    ACTIONSLOTTYPE_NIGHTVISION = 0x3,
    ACTIONSLOTTYPECOUNT = 0x4,
};

struct ActionSlotParam_SpecifyWeapon
{
    unsigned int index;
};

struct ActionSlotParam
{
    ActionSlotParam_SpecifyWeapon specifyWeapon;
};

enum objectiveState_t
{
    OBJST_EMPTY = 0x0,
    OBJST_ACTIVE = 0x1,
    OBJST_INVISIBLE = 0x2,
    OBJST_DONE = 0x3,
    OBJST_CURRENT = 0x4,
    OBJST_FAILED = 0x5,
    OBJST_NUMSTATES = 0x6,
};

struct objective_t
{
    objectiveState_t state;
    float origin[3];
    int entNum;
    int teamNum;
    int icon;
};

enum he_type_t
{
    HE_TYPE_FREE = 0x0,
    HE_TYPE_TEXT = 0x1,
    HE_TYPE_VALUE = 0x2,
    HE_TYPE_PLAYERNAME = 0x3,
    HE_TYPE_MAPNAME = 0x4,
    HE_TYPE_GAMETYPE = 0x5,
    HE_TYPE_MATERIAL = 0x6,
    HE_TYPE_TIMER_DOWN = 0x7,
    HE_TYPE_TIMER_UP = 0x8,
    HE_TYPE_TENTHS_TIMER_DOWN = 0x9,
    HE_TYPE_TENTHS_TIMER_UP = 0xA,
    HE_TYPE_CLOCK_DOWN = 0xB,
    HE_TYPE_CLOCK_UP = 0xC,
    HE_TYPE_WAYPOINT = 0xD,
    HE_TYPE_COUNT = 0xE,
};

struct $C96EA5EC2ACBB9C0BF22693F316ACC67
{
    char r;
    char g;
    char b;
    char a;
};

union hudelem_color_t
{
    $C96EA5EC2ACBB9C0BF22693F316ACC67 __s0;
    int rgba;
};

struct hudelem_s
{
    he_type_t type;
    float x;
    float y;
    float z;
    int targetEntNum;
    float fontScale;
    int font;
    int alignOrg;
    int alignScreen;
    hudelem_color_t color;
    hudelem_color_t fromColor;
    int fadeStartTime;
    int fadeTime;
    int label;
    int width;
    int height;
    int materialIndex;
    int offscreenMaterialIdx;
    int fromWidth;
    int fromHeight;
    int scaleStartTime;
    int scaleTime;
    float fromX;
    float fromY;
    int fromAlignOrg;
    int fromAlignScreen;
    int moveStartTime;
    int moveTime;
    int time;
    int duration;
    float value;
    int text;
    float sort;
    hudelem_color_t glowColor;
    int fxBirthTime;
    int fxLetterTime;
    int fxDecayStartTime;
    int fxDecayDuration;
    int soundID;
    int flags;
};

struct $15067B6A14D88D7E1E730369692C3A81
{
    hudelem_s current[31];
    hudelem_s archival[31];
};

struct playerState_s
{
    int commandTime;
    int pm_type;
    int bobCycle;
    int pm_flags;
    int weapFlags;
    int otherFlags;
    int pm_time;
    float origin[3];
    float velocity[3];
    float oldVelocity[2];
    int weaponTime;
    int weaponDelay;
    int grenadeTimeLeft;
    int throwBackGrenadeOwner;
    int throwBackGrenadeTimeLeft;
    int weaponRestrictKickTime;
    int foliageSoundTime;
    int gravity;
    float leanf;
    int speed;
    float delta_angles[3];
    int groundEntityNum;
    float vLadderVec[3];
    int jumpTime;
    float jumpOriginZ;
    int legsTimer;
    int legsAnim;
    int torsoTimer;
    int torsoAnim;
    int legsAnimDuration;
    int torsoAnimDuration;
    int damageTimer;
    int damageDuration;
    int flinchYawAnim;
    int movementDir;
    int eFlags;
    int eventSequence;
    int events[4];
    unsigned int eventParms[4];
    int oldEventSequence;
    int clientNum;
    int offHandIndex;
    OffhandSecondaryClass offhandSecondary;
    unsigned int weapon;
    int weaponstate;
    unsigned int weaponShotCount;
    float fWeaponPosFrac;
    int adsDelayTime;
    int spreadOverride;
    int spreadOverrideState;
    int viewmodelIndex;
    float viewangles[3];
    int viewHeightTarget;
    float viewHeightCurrent;
    int viewHeightLerpTime;
    int viewHeightLerpTarget;
    int viewHeightLerpDown;
    float viewAngleClampBase[2];
    float viewAngleClampRange[2];
    int damageEvent;
    int damageYaw;
    int damagePitch;
    int damageCount;
    int stats[5];
    int ammo[128];
    int ammoclip[128];
    unsigned int weapons[4];
    unsigned int weaponold[4];
    unsigned int weaponrechamber[4];
    float proneDirection;
    float proneDirectionPitch;
    float proneTorsoPitch;
    ViewLockTypes viewlocked;
    int viewlocked_entNum;
    int cursorHint;
    int cursorHintString;
    int cursorHintEntIndex;
    int iCompassPlayerInfo;
    int radarEnabled;
    int locationSelectionInfo;
    SprintState sprintState;
    float fTorsoPitch;
    float fWaistPitch;
    float holdBreathScale;
    int holdBreathTimer;
    float moveSpeedScaleMultiplier;
    MantleState mantleState;
    float meleeChargeYaw;
    int meleeChargeDist;
    int meleeChargeTime;
    int perks;
    ActionSlotType actionSlotType[4];
    ActionSlotParam actionSlotParam[4];
    int entityEventSequence;
    int weapAnim;
    float aimSpreadScale;
    int shellshockIndex;
    int shellshockTime;
    int shellshockDuration;
    float dofNearStart;
    float dofNearEnd;
    float dofFarStart;
    float dofFarEnd;
    float dofNearBlur;
    float dofFarBlur;
    float dofViewmodelStart;
    float dofViewmodelEnd;
    int hudElemLastAssignedSoundID;
    objective_t objective[16];
    char weaponmodels[128];
    int deltaTime;
    int killCamEntity;
    $15067B6A14D88D7E1E730369692C3A81 hud;
};

struct usercmd_s
{
    int Commandtime; //0x0000
    int buttons; //0x0004
    int viewangles[3]; //0x0008
    short weapon; // 0x14
    BYTE forward; //0x16
    BYTE side; //0x17
    BYTE unk1; // 0x18
    BYTE unn[3];
    float unk2; // 0x20
};

struct pmove_t
{
    playerState_s* ps;
    usercmd_s cmd;
    usercmd_s oldcmd;
    int tracemask;
    int numtouch;
    int touchents[32];
    float mins[3];
    float maxs[3];
    float xyspeed;
    int proneChange;
    float maxSprintTimeMultiplier;
    bool mantleStarted;
    float mantleEndPos[3];
    int mantleDuration;
    int viewChangeTime;
    float viewChange;
    char handler;
};

struct input_s // don't really know the type
{
    usercmd_s usercmds[128]; // 0x0
    int currentCmdNum; // 0x1000

    usercmd_s* GetUserCmd(int cmdNum)
    {
        int id = cmdNum & 0x7F;
        return &usercmds[id];
    }
};

#endif
