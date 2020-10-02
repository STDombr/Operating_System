#ifndef LAB_1_RECEIVER_H
#define LAB_1_RECEIVER_H

#include <iostream>
#include <windows.h>
#define MYMESSAGE 1

typedef struct tagMyStruct{
    char func;
    int res;
} MYSTRUCT;

PCOPYDATASTRUCT pMyCDS;
PROCESS_INFORMATION piF = {nullptr}, piG = {nullptr};
MYSTRUCT f, g;
extern HWND console, input, button;
std::string consoleMessages;

//create process to solv F(X) anf G(X)
void createProcess(int);

//create process to solv binary operation
void createFinalProcess(int, int);

//convert std::string to LPSTR
LPSTR stringToLPSTR(std::string);

//add new message and convert to std::string
std::string GetMessages(PCOPYDATASTRUCT);

bool breakProcess(bool f, bool g);

LRESULT CALLBACK receiverProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//create a child hide window to receive a messages
int WINAPI createReceiver(HWND hwndParent){

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = receiverProcedure;
    wc.lpszClassName = L"Disp32Class";

    if (!RegisterClassW(&wc))
        return -1;

    HWND hwnd = CreateWindowW(L"Disp32Class", L"Hidden Window", WS_OVERLAPPEDWINDOW | SW_HIDE, 400, 150, 500, 500,
            hwndParent,    //parent window handle
            nullptr, nullptr, nullptr);

    MSG msg = {nullptr};

    while (GetMessage(&msg, nullptr, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK receiverProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_CREATE:
            break;

        case WM_COMMAND:
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COPYDATA:
            pMyCDS = (PCOPYDATASTRUCT) lp;
            switch (pMyCDS->dwData)
            {
                case MYMESSAGE:
                    if ((char)((MYSTRUCT*)(pMyCDS->lpData))->func == 'f')
                    {
                        f.func = 'f';
                        f.res = (int)((MYSTRUCT*)(pMyCDS->lpData))->res;
                        SetWindowText(console, GetMessages(pMyCDS).c_str());

                        //if f returns 0, terminate process g
                        if (f.res == 0)
                        {
                            breakProcess(0, 1);

                            consoleMessages += "Binary operation calculated!\nF(x) * G(x) = 0";
                            SetWindowText(console, consoleMessages.c_str());
                        }
                        else if (g.func == 'g')
                            createFinalProcess(f.res, g.res);

                    }
                    else if ((char)((MYSTRUCT*)(pMyCDS->lpData))->func == 'g')
                    {
                        g.func = 'g';
                        g.res = (int)((MYSTRUCT*)(pMyCDS->lpData))->res;
                        SetWindowText(console, GetMessages(pMyCDS).c_str());

                        //if g returns 0, terminate process f
                        if (g.res == 0)
                        {
                            breakProcess(1, 0);

                            consoleMessages += "Binary operation calculated!\nF(x) * G(x) = 0";
                            SetWindowText(console, consoleMessages.c_str());
                        }
                        else if (f.func == 'f')
                            createFinalProcess(f.res, g.res);
                    } else
                    {
                        SetWindowText(console, GetMessages(pMyCDS).c_str());
                        breakProcess(1, 1);
                    }
                        break;
            }
            break;
        default:
            return DefWindowProcW(hwnd, msg, wp, lp);
    }
}


void createProcess(int X){
    consoleMessages = "";

    f.func = 0;
    std::string stringF = "f ";
    g.func = 0;
    std::string stringG = "g ";

    STARTUPINFO si = {0};

    CreateProcess(R"(D:\KNU\Operating_System\Lab1\FunctionSolver\cmake-build-debug\FunctionSolver.exe)", stringToLPSTR(stringF + std::to_string(X)), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &piF);

    CreateProcess(R"(D:\KNU\Operating_System\Lab1\FunctionSolver\cmake-build-debug\FunctionSolver.exe)", stringToLPSTR(stringG + std::to_string(X)), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &piG);
}

void createFinalProcess(int F, int G){
    std::string stringB = "b ";

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {nullptr};

    CreateProcess(R"(D:\KNU\Operating_System\Lab1\FunctionSolver\cmake-build-debug\FunctionSolver.exe)", stringToLPSTR(stringB + std::to_string(F) + " " + std::to_string(G)), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);
}
std::string GetMessages(PCOPYDATASTRUCT){
    int result = (char)((MYSTRUCT*)(pMyCDS->lpData))->res;
    if ((char)((MYSTRUCT*)(pMyCDS->lpData))->func == 'f')
    {
        consoleMessages += "F(x) calculate the result: F(x) = ";
    } else if ((char)((MYSTRUCT*)(pMyCDS->lpData))->func == 'g')
    {
        consoleMessages += "G(x) calculate the result: G(x) = ";
    } else
    {
        consoleMessages += "Binary operation calculated!\nF(x) * G(x) = ";
    }
    consoleMessages +=  std::to_string(result) + "\n";

    return consoleMessages;
}

LPSTR stringToLPSTR(std::string s){
    char* temp = const_cast<char*>(s.c_str());
    return const_cast<LPSTR>(temp);
}

bool breakProcess(bool f, bool g){
    if (f)
        if (TerminateProcess(piF.hProcess, 0))
        {

            consoleMessages += "Process F stopped.";
            if (g)
                consoleMessages += " (Cancellation by special key)";
            else
                consoleMessages += " (G(x) = 0);";
            consoleMessages += "\n";
        }

    if (g)
        if (TerminateProcess(piG.hProcess, 0))
        {
            consoleMessages += "Process G stopped.";
            if (f)
                consoleMessages += " (Cancellation by special key)";
            else
                consoleMessages += " (F(x) = 0);";
            consoleMessages += "\n";
        }
    SetWindowText(console, consoleMessages.c_str());

    EnableWindow(button, true);
    EnableWindow(input, true);
}
#endif //LAB_1_RECEIVER_H
