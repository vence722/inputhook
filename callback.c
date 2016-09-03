#include "_cgo_export.h"
#include <stdio.h>
#include <Windows.h>

#define HOOK_TYPE_KEYBOARD 0
#define HOOK_TYPE_MOUSE    1

extern void keyboardCallback(int event, int val);
extern void mouseCallback(long x, long y, int event, unsigned long data);

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam){
	PKBDLLHOOKSTRUCT p;
	switch (wParam) {
	    case WM_KEYDOWN:
	    case WM_SYSKEYDOWN:
	    case WM_KEYUP:
	    case WM_SYSKEYUP:
	        p = (PKBDLLHOOKSTRUCT)lParam;
			keyboardCallback(wParam, p->vkCode);
	        break;
	}
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam){
	if(nCode == HC_ACTION){
		PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
		mouseCallback((p->pt).x, (p->pt).y, wParam, p->mouseData);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void hook(int hType){
	int idHook = 0;
	HOOKPROC hookProc;
	if(hType == HOOK_TYPE_KEYBOARD) {
		idHook = WH_KEYBOARD_LL;
		hookProc = LowLevelKeyboardProc;
	} else if(hType == HOOK_TYPE_MOUSE) {
		idHook = WH_MOUSE_LL;
		hookProc = LowLevelMouseProc;
	} else {
		return;
	}
    HHOOK hook = SetWindowsHookEx(idHook, hookProc, 0, 0);
    MSG msg;
    while (!GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
}