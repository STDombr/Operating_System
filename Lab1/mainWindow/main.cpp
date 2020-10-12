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

#define CLICK_TEST_DEMO_1 8
#define CLICK_TEST_DEMO_2 9
#define CLICK_TEST_DEMO_3 10
#define CLICK_TEST_DEMO_4 11
#define CLICK_TEST_DEMO_5 12
#define CLICK_TEST_DEMO_6 13

using namespace std;

LRESULT CALLBACK MyWindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
void AddControls(HWND);
void AddMenus(HWND);

HWND input, console, button;
HMENU hMenu;

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
                        SetMenu(hwnd, NULL);
                        SetWindowText(console, "");
                        SetFocus(hwnd);

                        createProcess(false, stoi(X));
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
                case CLICK_TEST_DEMO_1:
                    SetWindowText(input, "0");
                    runDemoFunc(hwnd, 0);

                    break;
                case CLICK_TEST_DEMO_2:
                    SetWindowText(input, "1");
                    runDemoFunc(hwnd, 1);

                    break;
                case CLICK_TEST_DEMO_3:
                    SetWindowText(input, "2");
                    runDemoFunc(hwnd, 2);

                    break;
                case CLICK_TEST_DEMO_4:
                    SetWindowText(input, "3");
                    runDemoFunc(hwnd, 3);

                    break;
                case CLICK_TEST_DEMO_5:
                    SetWindowText(input, "4");
                    runDemoFunc(hwnd, 4);

                    break;
                case CLICK_TEST_DEMO_6:
                    SetWindowText(input, "5");
                    runDemoFunc(hwnd, 5);

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

    HMENU hTestMenu = CreateMenu();

    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_1, "F(x) finishes before G(x) with non-zero value");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_2, "G(x) finishes before F(x) with non-zero value");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_3, "F(x) finishes with zero value, G(x) hangs");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_4, "G(x) finishes with zero value, F(x) hangs");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_5, "F(x) finishes with non-zero value, G(x) hangs");
    AppendMenu(hTestMenu, MF_STRING, CLICK_TEST_6, "G(x) finishes with non-zero value, F(x) hangs");

    HMENU hTestDemoMenu = CreateMenu();

    AppendMenu(hTestDemoMenu, MF_STRING, CLICK_TEST_DEMO_1, "F(x) finishes before G(x) with non-zero value");
    AppendMenu(hTestDemoMenu, MF_STRING, CLICK_TEST_DEMO_2, "G(x) finishes before F(x) with non-zero value");
    AppendMenu(hTestDemoMenu, MF_STRING, CLICK_TEST_DEMO_3, "F(x) finishes with zero value, G(x) hangs");
    AppendMenu(hTestDemoMenu, MF_STRING, CLICK_TEST_DEMO_4, "G(x) finishes with zero value, F(x) hangs");
    AppendMenu(hTestDemoMenu, MF_STRING, CLICK_TEST_DEMO_5, "F(x) finishes with non-zero value, G(x) hangs");
    AppendMenu(hTestDemoMenu, MF_STRING, CLICK_TEST_DEMO_6, "G(x) finishes with non-zero value, F(x) hangs");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hTestMenu, "Tests");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hTestDemoMenu, "Tests(demofuncs)");

    SetMenu(hWnd, hMenu);
}