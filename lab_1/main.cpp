#include <iostream>
#include "demofuncs"
#include <windows.h>
#include <stdlib.h>

#define COMPUTE_BUTTON 1

using namespace std;

LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
bool isInteger(char*);
void AddControls(HWND);

HWND input, check;
int res = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = MyWindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"WindowName", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 150, 500, 500, nullptr,
                  nullptr, nullptr, nullptr);

    MSG msg = {nullptr};

    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_CREATE:
            AddControls(hwnd);
            break;

        case WM_COMMAND:
            switch(wp){
                case COMPUTE_BUTTON:
                    char X[100];
                    GetWindowText(input, X, 100);

                    if (isInteger(X)){
                        SetWindowText(check, "");
                    } else
                        SetWindowText(check, "Invalid value!");

                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
}

void AddControls(HWND hWnd){

    CreateWindowW(L"static", L"Enter integer value X :", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 20, 150, 20, hWnd, NULL, NULL, NULL);

    input = CreateWindowW(L"edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL, 175, 42, 150, 20, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Compute the result", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 66, 150, 20, hWnd, (HMENU)COMPUTE_BUTTON, NULL, NULL);

    check = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 88, 150, 20, hWnd, NULL, NULL, NULL);
}

//Convert from char[] to int
bool isInteger(char *s){
    string temp(s);
    res = 0;
    int length = temp.size(), i = 0;

    //if number <0
    if (length > 1 && temp[0] == '-'){
        if (temp[1] >= '1' && temp[1] <= '9'){
            res = (temp[1] - '0') * (-1);

            for (i = 2; i<length; i++){
                if (temp[i] >= '0' && temp[i] <= '9')
                    res = res * 10 - (temp[i] - '0');
                else
                    return 0;
            }
            return 1;
        } else
            return 0;
    }

    //if number >=0
    for (i; i<length; i++){
        if (temp[i] >= '0' && temp[i] <= '9')
            res = res * 10 + (temp[i] - '0');
        else
            return 0;
    }

    return 1;
}