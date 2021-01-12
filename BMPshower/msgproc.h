#pragma once

#include "framework.h"
#include "glb.h"
#include "str.h"
#include "paint.h"
#include "resource.h"
#include "readbmp.h"

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	//主窗口消息处理函数
BOOL CALLBACK iFDlgProc(HWND, UINT, WPARAM, LPARAM);		//输入文件路径对话框消息处理函数

