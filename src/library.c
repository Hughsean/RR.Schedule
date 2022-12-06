#include "library.h"
#include <Windows.h>
#include <conio.h>

void          test() {}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {}
void          ma(void (*p)()) {
    MSG Msg;
    SetTimer(NULL, 1, 1000, TimerProc);  // 每隔一秒钟触发一次
    while (GetMessage(&Msg, NULL, 0, 0)) {
        DispatchMessage(&Msg);
        p();
        break;
    }
    KillTimer(NULL, 1);  // 销毁定时器
}