#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>

BOOL gotoxy(const WORD x, const WORD y);
enum {ESC=27};
void setcursor(bool, DWORD);
