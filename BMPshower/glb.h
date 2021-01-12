#pragma once

#include "framework.h"

//读取位图文件状态

#define READ_SUCCESS  0					//读取成功
#define NOT_TWENTY_FOUR_BITMAP 1		//非24色位图
#define BITMAP_DESTROYED 2				//位图损坏
#define READ_FAILURE 3					//读取位图文件失败
#define BITMAP_TOO_LARGE 4

#define PAINT_SUCCESS 0					//画图成功
#define FAIL_TO_GET_DCMEM 1				//获取内存失败
#define FAIL_TO_GET_CLIENT 2			//获取用户区失败

#define MAIN_WIN_WIDTH 864
#define MAIN_WIN_HEIGHT 486

#define ID_START_TIMER 9999

enum class displayModeType
{
	start, 
	display
}; 

//全局变量存放处

extern HINSTANCE hInst;                             //当前实例
extern HWND hWndMain;								//主窗口句柄

extern bool lBtnDown;								//鼠标左键是否按下
extern int xMv;									//x方向位移量
extern int yMv;									//y方向位移量
extern POINT lastCursorPos;							//之前鼠标的位置

extern std::string inputBmpName;					//位图文件名			
extern displayModeType displayMode;					//目前状态
extern UCHAR* bmpBuf;								//临时存储位图文件的缓冲区指针
extern HBITMAP hBmMem;								//存储当前位图
extern HBITMAP hBmMain;								//存储主界面位图

