#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include "Receiver.h"

#define COMPUTE_BUTTON 1

using namespace std;

LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
bool isInteger(char*);
void AddControls(HWND);

HWND input, console1, console2, button;
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

    HWND hwnd = CreateWindowW(L"myWindowClass", L"WindowName", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 150, 500, 500, nullptr, nullptr, nullptr, nullptr);

    return createReceiver(hwnd);
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
                        EnableWindow(button, false);

                        createProcess(stoi(X));
                    } else
                        MessageBox(hwnd, "Enter valid integer value!", "Error", MB_OK);
                        //SetWindowText(check, "Invalid value!");

                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            if(wp == VK_ESCAPE)
                PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
}

void AddControls(HWND hWnd){

    CreateWindowW(L"static", L"Enter integer value X :", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 20, 150, 20, hWnd, nullptr, nullptr, nullptr);

    input = CreateWindowW(L"edit", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL, 175, 42, 150, 20, hWnd, nullptr, nullptr, nullptr);

    button = CreateWindowW(L"Button", L"Compute the result", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 66, 150, 20, hWnd, (HMENU)COMPUTE_BUTTON, nullptr, nullptr);

    console1 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD, 100, 150, 300, 100, hWnd, nullptr, nullptr, nullptr);

    console2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD, 100, 200, 300, 100, hWnd, nullptr, nullptr, nullptr);
}

//Convert from char[] to int
bool isInteger(char *s){
    string temp(s);
    res = 0;
    int length = temp.size(), i = 0;

    if (length <= 0)
        return false;

    //if number <0
    if (length > 1 && temp[0] == '-'){
        if (temp[1] >= '1' && temp[1] <= '9'){
            res = (temp[1] - '0') * (-1);

            for (i = 2; i<length; i++){
                if (temp[i] >= '0' && temp[i] <= '9')
                    res = res * 10 - (temp[i] - '0');
                else
                    return false;
            }
            return true;
        } else
            return false;
    }

    //if number >=0
    for (i; i<length; i++){
        if (temp[i] >= '0' && temp[i] <= '9')
            res = res * 10 + (temp[i] - '0');
        else
            return false;
    }

    return true;
}
