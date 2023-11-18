#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <intrin.h>

#include "exports.h"
#include "Utils.h"

#pragma intrinsic(_ReturnAddress)


BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved);