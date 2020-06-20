#pragma once

#include "framework.h"
#include "glb.h"
#include "str.h"

#define IN_RECT(x, y, rect) ((x) >= (rect).left && (x) <= (rect).right && (y) >= (rect).top && (y) <= (rect).top)

void paintMainInterface(HWND hWnd, HDC hdc); 
INT paintBmp(HWND, HDC hdc, PAINTSTRUCT& ps); 
INT paintBmpMem(UINT32, UINT32); 
