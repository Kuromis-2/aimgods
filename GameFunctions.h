#pragma once

// Weapon functions
const char* AGF_Weapon_NotifyHit = "Function AimGods.AGWeapon.ServerNotifyHit";
const char* AGF_Weapon_NotifyMiss = "Function AimGods.AGWeapon.ServerNotifyMiss";

// Player functions
const char* AGF_Player_FreezePlayer = "Function BP_AGCharacter.BP_AGCharacter_C.ToggleFreezePlayer";
const char* AGF_Player_SetupPlayerCard = "Function BP_AGCharacter.BP_AGCharacter_C.SetupPlayerCard";

// MISC
const char* MF_RecieveDrawHUD = "ReceiveDrawHUD";

bool CompareGameFunction(UFT::UFunction* Function, const char* FunctionName);
