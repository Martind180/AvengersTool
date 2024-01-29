#pragma once
#ifndef CODSTRUCTS_H
#define CODSTRUCTS_H

#include "CJOpenHud.h"
#include "windows.h"
#include "mmath.h"

#pragma once
enum team_t
{
    TEAM_FREE = 0x0,
    TEAM_AXIS = 0x1,
    TEAM_ALLIES = 0x2,
    TEAM_SPECTATOR = 0x3,
    TEAM_NUM_TEAMS = 0x4,
};

enum userButtonEnums
{
    USER_FIRE = 1,
    USER_SPRINT = 2,
    USER_PRONE = 256,
    USER_CROUCH = 512,
    USER_JUMP = 1024,
    USER_ADS = 526336,
    USER_ADS_FIRE = 526337,
    USER_MENU = 1048576,
};



enum entityType_t
{
    ET_GENERAL,
    ET_PLAYER,
    ET_PLAYER_CORPSE,
    ET_ITEM,
    ET_MISSILE,
    ET_INVISIBLE,
    ET_SCRIPTMOVER,
    ET_SOUND_BLEND,
    ET_FX,
    ET_LOOP_FX,
    ET_PRIMARY_LIGHT,
    ET_MG42,
    ET_HELICOPTER,
    ET_PLANE,
    ET_VEHICLE,
    ET_VEHICLE_COLLMAP,
    ET_VEHICLE_CORPSE,
    ET_EVENTS
};

enum entityFlags_t
{
    EF_CROUCHING = 0x4,
    EF_PRONE = 0x8,
    EF_FIRING = 0x40,
    EF_ADS = 0x40000,
    EF_ISPLAYING = 0x200000,
};

enum perksEnum
{
    PERK_JAMRADAR = 0x0,
    PERK_ACCURACY = 0x1,
    PERK_FASTRELOAD = 0x2,
    PERK_RATEOFFIRE = 0x3,
    PERK_EXTRABREATH = 0x4,
    PERK_EXTRABP = 0x5,
    PERK_GRENADEDEATH = 0x6,
    PERK_PISTOLDEATH = 0x7,
    PERK_QUIETMOVE = 0x8,
    PERK_PARABOLIC = 0x9,
    PERK_LONGERSPRINT = 0xA,
    PERK_DETECTEXPLOSIVE = 0xB,
    PERK_EXPLOSIVEDMG = 0xC,
    PERK_EXPOSEENEMY = 0xD,
    PERK_BULLETDMG = 0xE,
    PERK_EXTRAAMMO = 0xF,
    PERK_TWOPRIMARIES = 0x10,
    PERK_ARMORVEST = 0x11,
    PERK_FRAGGRENADE = 0x12,
    PERK_SPECIALGRENADE = 0x13,
    PERK_COUNT = 0x14,
    PERK_UNKNOWN = 0x14,
};

enum weapType_t
{
    WEAPTYPE_BULLET = 0x0,
    WEAPTYPE_GRENADE = 0x1,
    WEAPTYPE_PROJECTILE = 0x2,
    WEAPTYPE_BINOCULARS = 0x3,
    WEAPTYPE_NUM = 0x4,
};

enum weapClass_t
{
    WEAPCLASS_RIFLE = 0,
    WEAPCLASS_MG = 1,
    WEAPCLASS_SMG = 2,
    WEAPCLASS_SPREAD = 3,
    WEAPCLASS_PISTOL = 4,
    WEAPCLASS_GRENADE = 5,
    WEAPCLASS_ROCKETLAUNCHER = 6,
    WEAPCLASS_TURRET = 7,
    WEAPCLASS_NON_PLAYER = 8,
    WEAPCLASS_ITEM = 9,
    WEAPCLASS_NUM = 10
};

enum weaponstate_t
{
    WEAPON_READY = 0x0,
    WEAPON_RAISING = 0x1,
    WEAPON_RAISING_ALTSWITCH = 0x2,
    WEAPON_DROPPING = 0x3,
    WEAPON_DROPPING_QUICK = 0x4,
    WEAPON_FIRING = 0x5,
    WEAPON_RECHAMBERING = 0x6,
    WEAPON_RELOADING = 0x7,
    WEAPON_RELOADING_INTERUPT = 0x8,
    WEAPON_RELOAD_START = 0x9,
    WEAPON_RELOAD_START_INTERUPT = 0xA,
    WEAPON_RELOAD_END = 0xB,
    WEAPON_MELEE_INIT = 0xC,
    WEAPON_MELEE_FIRE = 0xD,
    WEAPON_MELEE_END = 0xE,
    WEAPON_OFFHAND_INIT = 0xF,
    WEAPON_OFFHAND_PREPARE = 0x10,
    WEAPON_OFFHAND_HOLD = 0x11,
    WEAPON_OFFHAND_START = 0x12,
    WEAPON_OFFHAND = 0x13,
    WEAPON_OFFHAND_END = 0x14,
    WEAPON_DETONATING = 0x15,
    WEAPON_SPRINT_RAISE = 0x16,
    WEAPON_SPRINT_LOOP = 0x17,
    WEAPON_SPRINT_DROP = 0x18,
    WEAPON_NIGHTVISION_WEAR = 0x19,
    WEAPON_NIGHTVISION_REMOVE = 0x1A,
};

enum statIndex_t
{
    STAT_HEALTH = 0x0,
    STAT_DEAD_YAW = 0x1,
    STAT_MAX_HEALTH = 0x2,
    STAT_IDENT_CLIENT_NUM = 0x3,
    STAT_SPAWN_COUNT = 0x4,
    MAX_STATS = 0x5,
};

struct trajectory_t
{
    int Type; //0x0000
    int Time; //0x0004
    int Duration; //0x0008
    vec3<float> Base; //0x000C
    vec3<float> Delta; //0x0018
}; //Size=0x0024

struct cpose_t
{
    short LightingHandle; //0x0000
    unsigned char EType; //0x0002
    unsigned char ETypeUnion; //0x0003
    char _0x0004[0x18]; //0x0004
    vec3<float> Origin; //0x001C
    vec3<float> Angles; //0x0028
    char _0x0034[0x30]; //0x0034
}; //Size=0x0064

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

struct centity_t // adress 0x0084F2D8
{
    cpose_t Pose;
    LerpEntityState CurrentState; //0x0064
    entityState_t NextState; //0x00CC
    int Tree; //0x01C0
    char _0x01C4[0x18]; //0x01C4
}; //Size=0x01DC

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

struct WeaponDef // adress 0x00736DB8
{
    char* InternalName; //0x0000
    char* DisplayName; //0x0004
    char _0x0008[0x124]; //0x0008
    int WeaponType; //0x012C
    int WeaponClass; //0x0130
    int PenetrationType; //0x0134
    char _0x0138[0x204]; //0x0138
    int ShotCount; //0x033C
    char _0x0340[0xC];
    int Damage; //0x034C
    int PlayerDamage; //0x0350
    char _0x0354[0xE4]; //0x0354
    int OverlayReticle; //0x0438
    char _0x043C[0xA4]; //0x043C
    int RifleBullet; //0x04E0
    int ArmorPiercing; //0x04E4
    int AimDownSight; //0x04E8
    char _0x04EC[0x44];
    int SegmentedReload; //0x0530
    char _0x0534[0x1E8]; //0x0534
    float ADSSpread; //0x71C
    char _0x0720[0xEC];
    float MinDamageRange; //0x80C
};

#pragma pack(push, 4)

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

#pragma pack(pop)

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

struct ClientArchiveData
{
    int ServerTime; //0x0000
    vec3<float> Origin; //0x0004
    vec3<float> Velocity; //0x0010
    int BobCycle; //0x001C
    int MovementDirection; //0x0020
    vec3<float> ViewAngles; //0x0024
}; //Size: 0x30

struct clSnapshot_t
{
    BOOL Valid; //0x0000
    int SnapFlags; //0x0004
    int ServerTime; //0x0008
    int MessageNumber; //0x000C
    int DeltaNum; //0x0010
    int Ping; //0x0014
    int CmdNum; //0x0018
    playerState_t PlayerState; //0x001C
    int NumnerOfEntities; //0x2F80
    int NumberOfClients; //0x2F84
    int ParseEntitiesNumber; //0x2F88
    int ParseClientsNumber; //0x2F8C
    int ServerCommandNumber; //0x2F90
}; //Size = 0x2F94

struct gameState_t
{
    int StringOffsets[2442]; //0x00000
    char StringData[0x20000]; //0x02628
    int DataCount; //0x22628
}; //Size: 0x2262C

struct outPacket_t
{
    int CommandNumber; //0x0000
    int ServerTime; //0x0004
    int Realtime; //0x0008
}; //Size: 0xC

struct clientActive_t // adress 0x00C5F930
{
    BOOL IsADS; //0x0000
    int TimeoutCount; //0x0004
    clSnapshot_t Snapshot; //0x0008
    BOOL AlwaysFalse; //0x2F9C
    int ServerTime; //0x2FA0
    int OldServerTime; //0x2FA4
    int OldFrameServerTime; //0x2FA8
    int ServerTimeDelta; //0x2FAC
    int OldSnapServerTime; //0x2FB0
    BOOL ExtrapolatingSnapshot; //0x2FB4
    BOOL NewSnapshots; //0x2FB8
    gameState_t GameState; //0x2FBC
    char MapName[64]; //0x255E8
    int ParseEntitiesNum; //0x25628
    int ParseClientsNum; //0x2562C
    int MouseDX[2]; //0x25630
    int MouseDY[2]; //0x25638
    int MouseIndex; //0x25640
    BOOL StanceHeld; //0x25644
    BOOL Stance; //0x25648
    int StancePosition; //0x2564C
    int StanceTime; //0x25650
    int CGameUserCmdWeapon; //0x25654
    int CGameUserCmdOffHandIndex; //0x25658
    float CGameFOVSensitivityScale; //0x2565C
    float CGameMaxPitchSpeed; //0x25660
    float CGameMaxYawSpeed; //0x25664
    vec3<float> CGameKickAngles; //0x25668
    vec3<float> CGameOrigin; //0x25674
    vec3<float> CGameVelocity; //0x25680
    vec3<float> CGameViewAngles; //0x2568C
    int CGameBobCycle; //0x25698
    int CGameMovementDir; //0x2569C
    int CGameExtraButtons; //0x256A0
    int CGamePredictedDataServerTime; //0x256A4
    vec3<float> ViewAngles; //0x256A8
    int ServerID; //0x256B4
    int SkeletonTimestamp; //0x256B8
    int SkeletonMemoryPosition; //0x256BC
    char SkeletonMemory[0x40000]; //0x256C0
    int SkeletonMemoryStart; //0x656C0
    BOOL AllowedAllocSkeleton; //0x656C4
    usercmd_s Commands[128]; //0x656C8
    int CommandNumber; //0x666C8
    ClientArchiveData ClientArchive[256]; //0x666CC
    int ClientArchiveIndex; //0x696CC
    outPacket_t OutPackets[32]; //0x696D0
    clSnapshot_t Snapshots[32]; //0x69850
    entityState_t EntityBaselines[1024]; //0xC8AD0
    entityState_t ParseEntities[2048]; //0x105AD0
    clientState_s ParseClients[2048]; //0x17FAD0
    int CorruptedTranslationFile; //0x1B1AD0
    char TranslationVersion[256]; //0x1B1AD4
    float VehicleViewYaw; //0x1B1BD4
    float VehicleViewPitch; //0x1B1BD8
}; //Size: 0x1B1BDC

struct clientControllers_t
{
    vec3<float> Angles[6]; //0x0000
    vec3<float> TagOriginAngles; //0x0048
    vec3<float> TagOriginOffset; //0x0054
};

struct lerpFrame_t
{
    float YawAngle; //0x0000
    int Yawing; //0x0004
    float PitchAngle; //0x0008
    int Pitching; //0x000C
    int AnimationNumber; //0x0010
    void* Animation; //0x0014
    int AnimationTime; //0x0018
    vec3<float> OldFramePosition; //0x001C
    float AnimSpeedScale; //0x0028
    int OldFrameSnapshotTime; //0x002C
}; //Size: 0x30

#pragma pack(push, 4)
struct clientinfo_t // adress  0x00839270 
{
    int IsValid; //0x000
    int NextValid; //0x004
    int ClientNumber; //0x008
    char Name[16]; //0x000C
    team_t Team; //0x01C
    team_t OldTeam; //0x020
    int Rank; //0x0024
    int Prestige; //0x0028
    unsigned int Perks; //0x002C
    int Score; //0x0030
    int Location; //0x0034
    int Health; //0x0038
    char BodyModel[64]; //0x003C
    char AttachedModels[6][64]; //0x007C
    char AttachedTags[6][64]; //0x01FC
    lerpFrame_t Legs; //0x37C
    lerpFrame_t Torso; //0x3AC
    float LerpMoveDirection; //0x3DC
    float LerpLean; //0x3E0
    vec3<float> ViewAngles; //0x3E4
    bool LeftHandGun; //0x3F0
    bool DObjDirty; //0x3F4
    clientControllers_t Control; //0x3F8
    char _0x0458[0x50];
    void* AnimationTree; //0x4A8
    int DObjWeapon; //0x4AC
    int WeaponModel; //0x4B0
    int StanceTransitionTime; //0x4B4
    int TurnAnimationTime; //0x4B8
    bool TurnAnimationType; //0x4BC
    int AttachedVehicleEntityNumber; //0x4C0
    int AttachedVehicleSlotIndex; //0x4C4
    bool HideWeapon; //0x4C8
    bool UsingKnife; //0x4C9
}; //Size=0x04CC
#pragma pack(pop)

struct refdef_t
{
    int ScreenX; //0x0000
    int ScreenY; //0x0004
    int ScreenWidth; //0x0008
    int ScreenHeight; //0x000C
    vec2<float> FOV; //0x0010
    vec3<float> Origin; //0x0018
    vec3<float> ViewAxis[3]; //0x0024
   //vec3<float> ViewOffset; //0x0048
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


struct cgs_t // adress 0x0074A908
{
    int ScreenX; //0x0000
    int ScreenY; //0x0004
    int ScreenWidth; //0x0008
    int ScreenHeight; //0x000C
    float AspectRatio; //0x0010
    char _0x0014[0x8]; //0x0014
    int LocalServer; //0x001C
    char GameMode[32]; //0x0020
    char ServerName[256]; //0x0040
    int MaxClients; //0x0140
    char MapName[64]; //0x0144
    int GameEndTime; //0x0184
    int VoteTime; //0x0188
    int VoteYes; //0x018C
    int VoteNo; //0x0190
    char _0x0194[0x3890]; //0x0194
}; //Size=0x3A24

enum DvarType
{
    DVAR_TYPE_BOOL = 0x0,
    DVAR_TYPE_FLOAT = 0x1,
    DVAR_TYPE_VECTOR_2 = 0x2,
    DVAR_TYPE_VECTOR_3 = 0x3,
    DVAR_TYPE_VECTOR_4 = 0x4,
    DVAR_TYPE_INT = 0x5,
    DVAR_TYPE_ENUM = 0x6,
    DVAR_TYPE_STRING = 0x7,
    DVAR_TYPE_COLOR = 0x8,
    DVAR_TYPE_COUNT = 0x9,
};

typedef void(__cdecl* xcommand_t)();
struct cmd_function_s
{
    cmd_function_s* next;
    char* name;
    char* autocomplete1;
    char* autocomplete2;
    xcommand_t function;
};

union DvarLimits
{
    struct
    {
        int StringCount;
        char** Strings;
    } Enumeration;

    struct
    {
        int Min;
        int Max;
    } Integer;

    struct
    {
        float Min;
        float Max;
    } Float;

    struct
    {
        float min;
        float max;
    } Vector;
};

union DvarValue
{
    bool Enabled;
    int Integer;
    unsigned int UnsignedInteger;
    float Float;
    float Vector[4];
    const char* String;
    unsigned char Color[4];
};

struct dvar_s
{
    const char* Name; //0x0000
    const char* Description; //0x0004
    unsigned short Flags; //0x0008
    char Type; //0x000A
    bool Modified; //0x000B
    DvarValue Current; //0x000C
    DvarValue Latched; //0x001C
    DvarValue Reset; //0x002C
    DvarLimits Domain; //0x003C
    dvar_s* Next; //0x0044
    dvar_s* HashNext; //0x0048
};

enum TraceHitType
{
    TRACE_HITTYPE_NONE = 0x0,
    TRACE_HITTYPE_ENTITY = 0x1,
    TRACE_HITTYPE_DYNENT_MODEL = 0x2,
    TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
};


typedef struct trace_t
{
    float fraction;//0x00
    vec3<float> endpos; //0x04
    int surfaceFlags; //0x10
    bool allSolid; //0x14
    int contents; //0x18
    long hitType; //0x1C
    short hitId; //0x20
    short modelIndex; //0x24
    short partName; //2
    short partGroup; //2
    char allsolid; //1
    char startsolid;//1
    char walkable;//1
    char _padding;//1
} trace_t;

struct Weapon {
    char* clipName; //0
    char* Name; //4
    char pad[0x124]; //8
    int WeaponType; //12C
    int WeaponClass; // 130
    int PenetrationType; //134
    int BulletType; //138, 7 means fun!
    int pad2; //13C
    int fireType; //140
    char pad3[0x2E0]; //144
    float zoomFov; //424
    float zoomInFrac; //428
    float zoomOutFrac; //42C
    int adsOverlayShader; //430
    int adsOverlayShaderLowRes; //434
    int pad4[2];
    float adsOverlayWidth; //440
    float adsOverlayHeight; //444
    float adsCrosshairInFrac; //448
    float adsCrosshairOutFrac; //44C
    float hipSpreadStandMin; //450
    float hipSpreadDuckedMin; //454
    float hipSpreadProneMin; //458
    float hipSpreadMax; //45C
    float hipSpreadDuckedMax; //460
    float hipSpreadProneMax; //464
    float hipSpreadDecayRate; //468
    float hipSpreadFireAdd; //46C
    float hipSpreadTurnAdd; //470
    float hipSpreadMoveAdd; //474
    float hipSpreadDuckedDecay; //478
    float hipSpreadProneDecay; //47C
    int pad5[3];
    float adsIdleAmount; //48C
    float hipIdleAmount; //490
    float adsIdleSpeed; //494
    float hipIdleSpeed; //498
    float idleCrouchFactor; //49C
    float idleProneFactor; //4A0
    float gunMaxPitch; //4A4
    float gunMaxYaw; //4A8
    float swayMaxAngle; //4AC
    float swayLerpSpeed; //4B0
    float swayPitchScale; //4B4
    float swayYawScale; //4B8
    float swayHorizScale; //4BC
    float swayVertScale; //4C0
    float swayShellShockScale; //4C4
    float adsSwayMaxAngle; //4C8
    float adsSwayLerpSpeed; //4CC
    float adsSwayPitchScale; //4D0
    float adsSwayYawScale; //4D4
    float adsSwayHorizScale; //4D8
    float adsSwayVertScale; //4DC
    char pad6[0xC];
    int zoomable; //4EC
    char pad7[0x78]; //4F0
    int projectileSpeed; //568
    int projectileSpeedUp; //56C
    char pad8[0x8]; //570
    float projectileLifetime; //578
    char pad9[0x154]; //57C
    float adsBobFactor; //6D0
    float adsViewBobMult; //6D4
    float adsGunKickReducedKickBullets; //6D8
    float adsGunKickReducedKickPercent; //6DC
    float adsGunKickPitchMin; //6E0
    float adsGunKickPitchMax; //6E4
    float adsGunKickYawMin; //6E8
    float adsGunKickYawMax; //6EC
    float adsGunKickAccel; //6F0
    float adsGunKickSpeedMax; //6F4
    float adsGunKickSpeedDecay; //6F8
    float adsGunKickStaticDecay; //6FC
    float adsViewKickPitchMin; //700
    float adsViewKickPitchMax; //704
    float adsViewKickYawMin; //708
    float adsViewKickYawMax; //70C
    float adsViewKickCenterSpeed; //710
    char pad10[0xC];
    float hipGunKickReducedKickBullets; //720
    float hipGunKickReducedKickPercent; //724
    float hipGunKickPitchMin; //728
    float hipGunKickPitchMax; //72C
    float hipGunKickYawMin; //730
    float hipGunKickYawMax; //734
    float hipGunKickAccel; //738
    float hipGunKickSpeedMax; //73C
    float hipGunKickSpeedDecay; //740
    float hipGunKickStaticDecay; //744
    float hipViewKickPitchMin; //748
    float hipViewKickPitchMax; //74C
    float hipViewKickYawMin; //750
    float hipViewKickYawMax; //754
    float hipViewKickCenterSpeed; //758
    char pad11[0x8];
    float fightDist; //764
    float maxDist; //768
};

class CD3DInfomation {
public:
    static const int Queryinterface_Index = 0;
    static const int AddRef_Index = 1;
    static const int Release_Index = 2;
    static const int TestCooperativeLevel_Index = 3;
    static const int GetAvailableTextureMem_Index = 4;
    static const int EvictManagedResources_Index = 5;
    static const int GetDirect3D_Index = 6;
    static const int GetDeviceCaps_Index = 7;
    static const int GetDisplayMode_Index = 8;
    static const int GetCreationParameters_Index = 9;
    static const int SetCursorProperties_Index = 10;
    static const int SetCursorPosition_Index = 11;
    static const int ShowCursor_Index = 12;
    static const int CreateAdditionalSwapChain_Index = 13;
    static const int GetSwapChain_Index = 14;
    static const int GetNumberOfSwapChains_Index = 15;
    static const int Reset_Index = 16;
    static const int Present_Index = 17;
    static const int GetBackBuffer_Index = 18;
    static const int GetRasterStatus_Index = 19;
    static const int SetDialogBoxMode_Index = 20;
    static const int SetGammaRamp_Index = 21;
    static const int GetGammaRamp_Index = 22;
    static const int CreateTexture_Index = 23;
    static const int CreateVolumeTexture_Index = 24;
    static const int CreateCubeTexture_Index = 25;
    static const int CreateVertexBuffer_Index = 26;
    static const int CreateIndexBuffer_Index = 27;
    static const int CreateRenderTarget_Index = 28;
    static const int CreateDepthStencilSurface_Index = 29;
    static const int UpdateSurface_Index = 30;
    static const int UpdateTexture_Index = 31;
    static const int GetRenderTargetData_Index = 32;
    static const int GetFrontBufferData_Index = 33;
    static const int StretchRect_Index = 34;
    static const int ColorFill_Index = 35;
    static const int CreateOffscreenPlainSurface_Index = 36;
    static const int SetRenderTarget_Index = 37;
    static const int GetRenderTarget_Index = 38;
    static const int SetDepthStencilSurface_Index = 39;
    static const int GetDepthStencilSurface_Index = 40;
    static const int BeginScene_Index = 41;
    static const int EndScene_Index = 42;
    static const int Clear_Index = 43;
    static const int SetTransform_Index = 44;
    static const int GetTransform_Index = 45;
    static const int MultiplyTransform_Index = 46;
    static const int SetViewport_Index = 47;
    static const int GetViewport_Index = 48;
    static const int SetMaterial_Index = 49;
    static const int GetMaterial_Index = 50;
    static const int SetLight_Index = 51;
    static const int GetLight_Index = 52;
    static const int LightEnable_Index = 53;
    static const int GetLightEnable_Index = 54;
    static const int SetClipPlane_Index = 55;
    static const int GetClipPlane_Index = 56;
    static const int SetRenderState_Index = 57;
    static const int GetRenderState_Index = 58;
    static const int CreateStateBlock_Index = 59;
    static const int BeginStateBlock_Index = 60;
    static const int EndStateBlock_Index = 61;
    static const int SetClipStatus_Index = 62;
    static const int GetClipStatus_Index = 63;
    static const int GetTexture_Index = 64;
    static const int SetTexture_Index = 65;
    static const int GetTextureStageState_Index = 66;
    static const int SetTextureStageState_Index = 67;
    static const int GetSamplerState_Index = 68;
    static const int SetSamplerState_Index = 69;
    static const int ValidateDevice_Index = 70;
    static const int SetPaletteEntries_Index = 71;
    static const int GetPaletteEntries_Index = 72;
    static const int SetCurrentTexturePalette_Index = 73;
    static const int GetCurrentTexturePalette_Index = 74;
    static const int SetScissorRect_Index = 75;
    static const int GetScissorRect_Index = 76;
    static const int SetSoftwareVertexProcessing_Index = 77;
    static const int GetSoftwareVertexProcessing_Index = 78;
    static const int SetNPatchMode_Index = 79;
    static const int GetNPatchMode_Index = 80;
    static const int DrawPrimitive_Index = 81;
    static const int DrawIndexedPrimitive_Index = 82;
    static const int DrawPrimitiveUP_Index = 83;
    static const int DrawIndexedPrimitiveUP_Index = 84;
    static const int ProcessVertices_Index = 85;
    static const int CreateVertexDeclaration_Index = 86;
    static const int SetVertexDeclaration_Index = 87;
    static const int GetVertexDeclaration_Index = 88;
    static const int SetFVF_Index = 89;
    static const int GetFVF_Index = 90;
    static const int CreateVertexShader_Index = 91;
    static const int SetVertexShader_Index = 92;
    static const int GetVertexShader_Index = 93;
    static const int SetVertexShaderConstantF_Index = 94;
    static const int GetVertexShaderConstantF_Index = 95;
    static const int SetVertexShaderConstantI_Index = 96;
    static const int GetVertexShaderConstantI_Index = 97;
    static const int SetVertexShaderConstantB_Index = 98;
    static const int GetVertexShaderConstantB_Index = 99;
    static const int SetStreamSource_Index = 100;
    static const int GetStreamSource_Index = 101;
    static const int SetStreamSourceFreq_Index = 102;
    static const int GetStreamSourceFreq_Index = 103;
    static const int SetIndices_Index = 104;
    static const int GetIndices_Index = 105;
    static const int CreatePixelShader_Index = 106;
    static const int SetPixelShader_Index = 107;
    static const int GetPixelShader_Index = 108;
    static const int SetPixelShaderConstantF_Index = 109;
    static const int GetPixelShaderConstantF_Index = 110;
    static const int SetPixelShaderConstantI_Index = 111;
    static const int GetPixelShaderConstantI_Index = 112;
    static const int SetPixelShaderConstantB_Index = 113;
    static const int GetPixelShaderConstantB_Index = 114;
    static const int DrawRectPatch_Index = 115;
    static const int DrawTriPatch_Index = 116;
    static const int DeletePatch_Index = 117;
    static const int CreateQuery_Index = 118;
    static const int NumberOfFunctions = 118;
};


//===========================================Server stuff

typedef clientState_s clientState_t;

enum MissileFlightMode
{
    MISSILEFLIGHTMODE_TOP = 0x0,
    MISSILEFLIGHTMODE_DIRECT = 0x1,
};

enum MissileStage
{
    MISSILESTAGE_SOFTLAUNCH = 0x0,
    MISSILESTAGE_ASCENT = 0x1,
    MISSILESTAGE_DESCENT = 0x2,
};

struct item_ent_t
{
    int ammoCount;
    int clipAmmoCount;
    int index;
};

struct trigger_ent_t
{
    int threshold;
    int accumulate;
    int timestamp;
    int singleUserEntIndex;
    byte requireLookAt;
};

struct corpse_ent_t
{
    int deathAnimStartTime;
};

struct missile_ent_t
{
    float time;
    int timeOfBirth;
    float travelDist;
    vec3<float> surfaceNormal;
    enum team_s team;
    vec3<float> curvature;
    int targetEntNum;
    vec3<float> targetOffset;
    enum MissileStage stage;
    enum MissileFlightMode flightMode;
};

struct mover_ent_t
{
    float decelTime;
    float aDecelTime;
    float speed;
    float aSpeed;
    float midTime;
    float aMidTime;
    vec3<float> pos1;
    vec3<float> pos2;
    vec3<float> pos3;
    vec3<float> apos1;
    vec3<float> apos2;
    vec3<float> apos3;
};

typedef UINT16 uint16_t;

struct turretInfo_s
{
    int inuse;
    int flags;
    int fireTime;
    vec2<float> arcmin;
    vec2<float> arcmax;
    float dropPitch;
    int stance;
    int prevStance;
    int fireSndDelay;
    vec3<float> userOrigin;
    float playerSpread;
    float pitchCap;
    int triggerDown;
    char fireSnd;
    char fireSndPlayer;
    char stopSnd;
    char stopSndPlayer;
};

struct EntHandle
{
    uint16_t number;
    uint16_t infoIndex;
};  

struct entityShared_t
{
    byte        linked;             //0xf4 qfalse if not in any good cluster

    byte        bmodel;             //0xf5 if false, assume an explicit mins / maxs bounding box
                            // only set by trap_SetBrushModel
    byte        svFlags;
    byte        pad1;

    int     clientMask[2];
    byte        inuse;
    byte        pad2[3];
    int         broadcastTime;

    vec3<float>       mins, maxs;     //0x108  //0x114  from SharedEntity_t

    int     contents;       // CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
                        // a non-solid entity should set to 0

    vec3<float>       absmin, absmax;     //0x124  //0x130 derived from mins/maxs and origin + rotation

    // currentOrigin will be used for all collision detection and world linking.
    // it will not necessarily be the same as the trajectory evaluation for the current
    // time, because each entity must be moved one at a time after time is advanced
    // to avoid simultanious collision issues
    vec3<float>       currentOrigin;      //0x13c
    vec3<float>       currentAngles;      //0x148

    // when a trace call is made and passEntityNum != ENTITYNUM_NONE,
    // an ent will be excluded from testing if:
    // ent->s.number == passEntityNum   (don't interact with self)
    // ent->r.ownerNum == passEntityNum (don't interact with your own missiles)
    // entity[ent->r.ownerNum].r.ownerNum == passEntityNum  (don't interact with other missiles from owner)
    EntHandle ownerNum;
    int     eventTime;
};

#define MAX_NETNAME 16
typedef enum { qfalse, qtrue }  qboolean;
typedef usercmd_s usercmd_t;



typedef enum
{
    SESS_STATE_PLAYING, SESS_STATE_DEAD,
    SESS_STATE_SPECTATOR, SESS_STATE_INTERMISSION
}sessionState_t;//0x2f64

typedef enum
{
    CON_DISCONNECTED,
    CON_CONNECTING,
    CON_CONNECTED
} clientConnected_t;

typedef struct
{
    int location;
} playerTeamState_t;

struct clientSession_t
{

    sessionState_t sessionState; //0x2f64

    int forceSpectatorClient;
    int killCamEntity;
    int status_icon;
    int archiveTime;            //0x2f74


    int score; //0x2f78
    int deaths; //0x2f7c
    int kills; //0x2f80
    int assists; //0x2f84

    uint16_t scriptPersId;          //0x2f88 the first spawn should be at a cool location
    byte pad2;
    byte pad;
    clientConnected_t connected;    //0x2f8c 
    usercmd_t cmd;                  //0x2f90 we would lose angles if not persistant
    usercmd_t oldcmd;               //0x2fb0 previous command processed by pmove()
    qboolean localClient;           //0x2fd0 true if "ip" info key is "localhost"
    qboolean predictItemPickup;     //0x2fd4 based on cg_predictItems userinfo

    char newnetname[MAX_NETNAME];   //0x2fd8

    int maxHealth;                  // 0x2fe8 for handicapping
    int enterTime;                  // 0x2fec level.time the client entered the game

    playerTeamState_t teamState;    // status in teamplay games
    int voteCount;                  // 0x2ff4 to prevent people from constantly calling votes
    int teamVoteCount;              // to prevent people from constantly calling votes      // N/A

    float moveSpeedScaleMultiplier; // 0x2ffc

    int viewmodelIndex;             // 0x3000 //Model-index

    qboolean noSpectate;            // 0x3004
    int teamInfo;                   // 0x3008 is free (unused)addr 

    clientState_t cs;
    int psOffsetTime;

};

struct gclient_s
{
    // ps MUST be the first element, because the server expects it
    playerState_t ps;               //0x00 communicated by server to clients

    // the rest of the structure is private to game

    clientSession_t sess;       //0x2f64
    int spectatorClient;        //0x3074 for chasecam and follow mode
    qboolean noclip;        //0x3078
    qboolean ufo;           //0x307c
    qboolean bFrozen;   //0x3080

    int lastCmdTime;                //0x3084 level.time of last usercmd_t, for EF_CONNECTION
                                    // we can't just use pers.lastCommand.time, because
                                    // of the g_sycronousclients case
    //Buttonlogic
    int buttons;            //0x3088
    int oldbuttons;
    int latched_buttons;
    int buttonsSinceLastFrame;      //0x3094

    vec3<float> oldOrigin;

    // sum up damage over an entire frame, so
    // shotgun blasts give a single big kick
    float fGunPitch;
    float fGunYaw;
    int damage_blood;               // damage taken out of health
    vec3<float> damage_from;             //0x30b0 origin for vector calculation
    qboolean damage_fromWorld;      //0x30bc if true, don't use the damage_from vector

    int accurateCount;              // for "impressive" reward sound    N/A

    int accuracy_shots;             // total number of shots        N/A
    int accuracy_hits;              // total number of hits         N/A

    int inactivityTime;             //0x30cc kick players when time > this
    qboolean inactivityWarning;     //0x30d0 qtrue if the five second warning has been given
    int lastVoiceTime;              //0x30d4 ??
    int switchTeamTime;             //0x30d8

    int currentAimSpreadScale;      //0x30dc

    int jumpHeight; //Used for per player jump height -- bad place here. This should be part of playerState_t
    int lastFollowedClient;

    int dropWeaponTime;             //JPW NERVE last time a weapon was dropped

    int sniperRifleFiredTime;       //Free member
    float sniperRifleMuzzleYaw;     //Free member
    int PCSpecialPickedUpCount;     //Free member

    EntHandle useHoldEntity; //0x30f8

    int useHoldTime;             //0x30fc time the player switched teams

    int useButtonDone;

    int iLastCompassPlayerInfoEnt;

    int compassPingTime;

    int damageTime;
    float v_dmg_roll;
    float v_dmg_pitch;
    vec3<float> swayViewAngles;
    vec3<float> swayOffset;
    vec3<float> swayAngles;
    vec3<float> vLastMoveAng;
    float fLastIdleFactor;

    vec3<float> vGunOffset;
    vec3<float> vGunSpeed;

    int weapIdleTime;
    int lastServerTime;
    int lastSpawnTime;
    unsigned int lastWeapon;
    bool previouslyFiring;
    bool previouslyUsingNightVision;
    bool previouslySprinting;
    bool pad;
    qboolean hasRadar;
    int lastStand;
    int lastStandTime;
};

struct gentity_s
{
    entityState_t s;
    entityShared_t r;               // shared by both the server system and game

    // DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
    // EXPECTS THE FIELDS IN THAT ORDER!
    //================================

    struct gclient_s* client;            // NULL if not a client        0x15c

    struct turretInfo_s* pTurretInfo;
    struct scr_vehicle_s* scr_vehicle;  //we dont know the definition of this struct

    uint16_t model;
    byte physicsObject;
    byte takedamage;
    byte active;
    byte nopickup;
    byte handler;
    byte team;

    uint16_t classname;
    uint16_t target;

    uint16_t targetname;
    uint16_t pad;
    unsigned int attachIgnoreCollision;

    int spawnflags;
    int flags;
    int eventTime;

    int freeAfterEvent;
    int unlinkAfterEvent;
    int clipmask;
    int processedFrame;
    EntHandle parent;
    int nextthink;

    int health; /* 0x1A0 */
    int maxHealth;
    int damage;
    int count;

    struct gentity_s* chain;

    //  char unknown[104];
    union
    {
        struct item_ent_t item[2];
        struct trigger_ent_t trigger;
        struct mover_ent_t mover;
        struct corpse_ent_t corpse;
        struct missile_ent_t missile;
    };

    EntHandle missileTargetEnt;

    struct tagInfo_s* tagInfo;
    struct gentity_s* tagChildren;
    uint16_t attachModelNames[19];
    uint16_t attachTagNames[19];
    int useCount;
    struct gentity_s* nextFree;
}; /* Size: 0x274 */

#endif
