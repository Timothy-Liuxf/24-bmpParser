#include "glb.h"

HINSTANCE hInst;                                // 当前实例
HWND hWndMain;								//主窗口句柄

int xMv = 0;	
int yMv = 0;	
bool lBtnDown = false; 
POINT lastCursorPos = { 0, 0 }; 

std::string inputBmpName; 
displayModeType displayMode = displayModeType::start; 
UCHAR* bmpBuf = NULL; 
HBITMAP hBmMem = NULL; 
HBITMAP hBmMain = NULL; 
