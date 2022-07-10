#pragma once

#define WIN32_LEAN_AND_MEAN

#include "UFT/SDK.h"
#include "detours/detours.h"
#include <stdint.h>
#include <vector>
#include "Hooks.h"
#include <algorithm>
#include <vector>
#include <functional>
#include <Psapi.h>
#include <iostream>
#include <chrono>
#include <mutex>
#include <random>
#include "AG.h"
#include "Funcs.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
static __forceinline UFT::UGameplayStatics& GetGameplayStatics() { return *(UFT::UGameplayStatics*)UFT::UGameplayStatics::StaticClass(); };
static __forceinline UFT::UKismetMathLibrary& GetKismetMathLibrary() { return *(UFT::UKismetMathLibrary*)UFT::UKismetMathLibrary::StaticClass(); };
static __forceinline UFT::UKismetSystemLibrary& GetKismetSystemLibrary() { return *(UFT::UKismetSystemLibrary*)UFT::UKismetSystemLibrary::StaticClass(); };
typedef uintptr_t PTR;
#define IS_VALID(Actor) GetKismetSystemLibrary().STATIC_IsValid(Actor)

// Macros for different builds
#define SHIPPING 0
#define NO_SHIPPING 1

#define VERSION SHIPPING

#if VERSION == SHIPPING
#define COMMENT_IF_NO_SHIPPING //
#else
#define COMMENT_IF_NO_SHIPPING
#endif