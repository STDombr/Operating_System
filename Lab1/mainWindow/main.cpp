#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include "Receiver.h"

#define COMPUTE_BUTTON 1
#define CLICK_TEST_1 2
#define CLICK_TEST_2 3
#define CLICK_TEST_3 4
#define CLICK_TEST_4 5
#define CLICK_TEST_5 6
#define CLICK_TEST_6 7

using namespace std;

LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void AddControls(HWND);
void AddMenus(HWND);

HWND input, console, button;
HMENU hMenu;
HMENU hTestMenu;

/**
 *
 * @param hInst
 * @param hPrevInst
 * @param args
 * @param ncmdshow
 * @return
 */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = MyWindowProcedure;


    if (!RegisterClassW(&wc))
        return -1;

    HWND hwnd = CreateWindowW(L"myWindowClass", L"Lab1", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 400, 150, 500, 300, nullptr, nullptr, nullptr, nullptr);

    return createReceiver(hwnd);
}

/**
 *  the Window Procedure
 */
LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_CREATE:
            AddControls(hwnd);
            AddMenus(hwnd);

            break;

        case WM_COMMAND:
            switch(wp){
                case COMPUTE_BUTTON:
                    char X[100];
                    GetWindowText(input, X, 100);

                    if (isInteger(X)){
                        EnableWindow(button, false);
                        EnableWindow(input, false);
                        //EnableMenuItem(hMenu, (UINT_PTR)hTestMenu, MF_DISABLED);
                        SetMenu(hwnd, NULL);
                        //SendMessage(hwnd, BM_CLICK, CLICK_TEST_1, 0);
                        SetWindowText(console, "");
                        SetFocus(hwnd);

                        createProcess(stoi(X));
                    } else
                        MessageBox(hwnd, "Enter valid integer value!", "Error", MB_OK);

                    break;
                case CLICK_TEST_1:
                    SetWindowText(input, "100");
                    SendMessage(button, BM_CLICK, 0, 0);

                    break;
                case CLICK_TEST_2:
                    SetWindowText(input, "5");
                    SendMessage(button, BM_CLICK, 0, 0);

                    break;
                case CLICK_TEST_3:
                    SetWindowText(input, "-100");
                    SendMessage(button, BM_CLICK, 0, 0);

                    break;
                case CLICK_TEST_4:
                    SetWindowText(input, "-2000");
                    SendMessage(button, BM_CLICK, 0, 0);

                    break;
                case CLICK_TEST_5:
                    SetWindowText(input, "-10");
                    SendMessage(button, BM_CLICK, 0, 0);

                    break;
                case CLICK_TEST_6:
                    SetWindowText(input, "-1000");
                    SendMessage(button, BM_CLICK, 0, 0);

                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);

            break;
        case WM_KEYDOWN:
            if(wp == VK_ESCAPE)
                breakProcess(1, 1);

            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
}

/**
 *  function for creating button and text windows
 * @param hWnd  handle to a main window
 */
void AddControls(HWND hWnd){

    CreateWindowW(L"static", L"Enter integer value X :", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 20, 150, 20, hWnd, nullptr, nullptr, nullptr);

    input = CreateWindowW(L"edit", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL, 175, 42, 150, 20, hWnd, nullptr, nullptr, nullptr);

    button = CreateWindowW(L"Button", L"Compute the result", WS_VISIBLE | WS_CHILD | SS_CENTER, 175, 66, 150, 20, hWnd, (HMENU)COMPUTE_BUTTON, nullptr, nullptr);

    console = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD, 75, 120, 350, 100, hWnd, nullptr, nullptr, nullptr);
}

/**
 *  function for creating menu with tests button
 * @param hWnd  handle to a main window
 */
void AddMenus(HWND hWnd){
    hMenu = CreateMenu();

    hTestMenu = CreateMenu();

    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_1, "F(x) finishes before G(x) with non-zero value");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_2, "G(x) finishes before F(x) with non-zero value");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_3, "F(x) finishes with zero value, G(x) hangs");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_4, "G(x) finishes with zero value, F(x) hangs");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_5, "F(x) finishes with non-zero value, G(x) hangs");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_6, "G(x) finishes with non-zero value, F(x) hangs");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hTestMenu, "Tests");

    SetMenu(hWnd, hMenu);
}
