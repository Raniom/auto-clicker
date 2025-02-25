#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "clicker.h"

HANDLE hStopEvent = NULL;
HINSTANCE hInst;
HWND hInterval, hClickType, hKeyEdit;
int running = 0;
float interval = 0.1;
int click_type = MOUSEEVENTF_LEFTDOWN;
UINT toggleKey = 'S'; 
NOTIFYICONDATA nid;
HFONT hFont;
HBRUSH hBrushBg;
COLORREF textColor = RGB(0, 0, 0);
COLORREF bgColor = RGB(250, 250, 250);

DWORD WINAPI AutoClickerThread(LPVOID lpParam) {
    if (hStopEvent == NULL) {
        MessageBox(NULL, "Stop event is not valid!", "Error", MB_ICONERROR);
        return 0;
    }

    while (WaitForSingleObject(hStopEvent, (DWORD)(interval * 1000)) == WAIT_TIMEOUT) {
        INPUT inputs[2] = {0};

        inputs[0].type = INPUT_MOUSE;
        inputs[0].mi.dwFlags = click_type;
        inputs[1].type = INPUT_MOUSE;
        inputs[1].mi.dwFlags = (click_type == MOUSEEVENTF_LEFTDOWN) ? MOUSEEVENTF_LEFTUP :
                               (click_type == MOUSEEVENTF_RIGHTDOWN) ? MOUSEEVENTF_RIGHTUP :
                               MOUSEEVENTF_MIDDLEUP;

        if (SendInput(2, inputs, sizeof(INPUT)) == 0) {
            MessageBox(NULL, "Error sending mouse events.", "Error", MB_ICONERROR);
            break;
        }
    }
    return 0;
}



void ToggleAutoClicker() {
    running = !running;
    if (running) {
        hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);  
        if (!hStopEvent) {
            MessageBox(NULL, "Failed to create event!", "Error", MB_ICONERROR);
            running = 0;
            return;
        }

        char buffer[10];
        GetWindowText(hInterval, buffer, sizeof(buffer));
        interval = atof(buffer);

        if (interval < 0) {  
            MessageBox(NULL, "Invalid interval. Minimum: 0", "Error", MB_ICONERROR);
            running = 0;
            CloseHandle(hStopEvent);
            return;
        }

        int selected = SendMessage(hClickType, CB_GETCURSEL, 0, 0);
        click_type = (selected == 1) ? MOUSEEVENTF_RIGHTDOWN :
                     (selected == 2) ? MOUSEEVENTF_MIDDLEDOWN :
                                       MOUSEEVENTF_LEFTDOWN;

        HANDLE hThread = CreateThread(NULL, 0, AutoClickerThread, NULL, 0, NULL);
        if (!hThread) {
            MessageBox(NULL, "Error creating thread.", "Error", MB_ICONERROR);
            running = 0;
            CloseHandle(hStopEvent);
        } else {
            CloseHandle(hThread);  
        }
    } else {
        SetEvent(hStopEvent);
        CloseHandle(hStopEvent);
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                               OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                               VARIABLE_PITCH, "Segoe UI");
            hBrushBg = CreateSolidBrush(bgColor);
            RegisterHotKey(hWnd, KEY_TOGGLE, 0, toggleKey);

            HWND hStatic1 = CreateWindow("STATIC", "Interval (sec) :", WS_VISIBLE | WS_CHILD,
                         10, 10, 70, 20, hWnd, NULL, hInst, NULL);
            SendMessage(hStatic1, WM_SETFONT, (WPARAM)hFont, TRUE);
            hInterval = CreateWindow("EDIT", "0.5", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     120, 10, 80, 20, hWnd, (HMENU)ID_EDIT_INTERVAL, hInst, NULL);
            SendMessage(hInterval, WM_SETFONT, (WPARAM)hFont, TRUE);

            HWND hStatic2 = CreateWindow("STATIC", "Click Type :", WS_VISIBLE | WS_CHILD,
                         10, 40, 70, 20, hWnd, NULL, hInst, NULL);
            SendMessage(hStatic2, WM_SETFONT, (WPARAM)hFont, TRUE);
            hClickType = CreateWindow("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                                      120, 40, 80, 100, hWnd, (HMENU)ID_COMBO_CLICK_TYPE, hInst, NULL);
            SendMessage(hClickType, WM_SETFONT, (WPARAM)hFont, TRUE);
            SendMessage(hClickType, CB_ADDSTRING, 0, (LPARAM)"Left Click");
            SendMessage(hClickType, CB_ADDSTRING, 0, (LPARAM)"Right Click");
            SendMessage(hClickType, CB_ADDSTRING, 0, (LPARAM)"Middle Click");
            SendMessage(hClickType, CB_SETCURSEL, 0, 0);

            HWND hStatic3 = CreateWindow("STATIC", "Key :", WS_VISIBLE | WS_CHILD,
                         10, 70, 70, 20, hWnd, NULL, hInst, NULL);
            SendMessage(hStatic3, WM_SETFONT, (WPARAM)hFont, TRUE);
            hKeyEdit = CreateWindow("EDIT", "S", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                       120, 70, 80, 20, hWnd, (HMENU)ID_KEY_EDIT, hInst, NULL);
            SendMessage(hKeyEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
            break;

        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
            SetTextColor((HDC)wParam, textColor);
            SetBkColor((HDC)wParam, bgColor);
            return (LRESULT)hBrushBg;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_KEY_EDIT && HIWORD(wParam) == EN_CHANGE) {
                char buffer[10];
                GetWindowText(hKeyEdit, buffer, sizeof(buffer));
                if (strlen(buffer) > 0) {
                    toggleKey = toupper(buffer[0]);
                    if (!UnregisterHotKey(hWnd, KEY_TOGGLE)) {
                        MessageBox(hWnd, "Error unregistering key.", "Error", MB_ICONERROR);
                    }
                    if (!RegisterHotKey(hWnd, KEY_TOGGLE, 0, toggleKey)) {
                        MessageBox(hWnd, "Error registering key.", "Error", MB_ICONERROR);
                    }
                }
            }
            break;

        case WM_HOTKEY:
            if (wParam == KEY_TOGGLE) {
                ToggleAutoClicker();
            }
            break;

        case WM_CLOSE:
            running = 0;
            Shell_NotifyIcon(NIM_DELETE, &nid);
            UnregisterHotKey(hWnd, KEY_TOGGLE);
            DeleteObject(hFont);
            DeleteObject(hBrushBg);
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    HANDLE hMutex = CreateMutex(NULL, TRUE, "AutoClickerMutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBox(NULL, "AutoClicker is already running!", "Warning", MB_ICONWARNING);
        return 0;
    }

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "AutoClicker";
    wc.hbrBackground = CreateSolidBrush(bgColor);
    RegisterClass(&wc);

    HWND hWnd = CreateWindow("AutoClicker", "ACS", WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 230, 150, NULL, NULL, wc.hInstance, NULL);

    HICON hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.hIcon = hIcon;
    strcpy(nid.szTip, "AutoClicker");
    Shell_NotifyIcon(NIM_ADD, &nid);

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ReleaseMutex(hMutex);
    CloseHandle(hMutex);

    return (int)msg.wParam;
}