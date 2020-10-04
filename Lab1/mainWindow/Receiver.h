#ifndef LAB_1_RECEIVER_H
#define LAB_1_RECEIVER_H

#include <iostream>
#include <windows.h>
#define MYMESSAGE 1

/**
 * structure for receiving messages
 * func store info about function
 * res store resultof the function
 */
typedef struct tagMyStruct{
    char func;
    int res;
} MYSTRUCT;

PCOPYDATASTRUCT pMyCDS;
PROCESS_INFORMATION piF = {nullptr}, piG = {nullptr};

MYSTRUCT f, g;
extern HWND console, input, button;
//handle to a main window
HWND mainHwnd;
extern HMENU hMenu;
std::string consoleMessages;

/**
 * function for creating process to solv F(X) anf G(X)
 * if demofunc = true, start demofuncs
 */
void createProcess(bool demofunc, int X);

/**
 * function for creating process to solv binary operation
 */
void createFinalProcess(int, int);

/**
 * function for convert std::string to LPSTR
 * @return LPSTR
 */
LPSTR stringToLPSTR(std::string);

/**
 * function for add new message and convert to std::string
 * @return new message
 */
std::string GetMessages(PCOPYDATASTRUCT);

/**
 * function for determinate integer from char*
 * @return bool
 */
bool isInteger(char*);

/**
 * function for break some process
 * @param f true if needed to terminate
 * @param g true if needed to terminate
 */
void breakProcess(bool f, bool g);

/**
 *  the Window Procedure
 */
LRESULT CALLBACK receiverProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

/**
 * function for run demofuncs
 * @param hwnd  handle to a main window
 * @param X
 */
void runDemoFunc(HWND hwnd, int X);

/**
 * function for creating a child hide window to receive a messages
 * @param hwndParent  handle to a main window
 */
int WINAPI createReceiver(HWND hwndParent){

    mainHwnd = hwndParent;
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

/**
 *  the Window Procedure
 */
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

/**
 * function for creating process to solv F(X) anf G(X)
 */
void createProcess(bool demofunc, int X){
    consoleMessages = "";

    f.func = 0;
    std::string stringF;
    g.func = 0;
    std::string stringG;

    if (demofunc)
    {
        stringF = "demoF ";
        stringG = "demoG ";
    } else
    {
        stringF = "f ";
        stringG = "g ";
    }

    STARTUPINFO si = {0};

    CreateProcess(R"(D:\KNU\Operating_System\Lab1\FunctionSolver\cmake-build-debug\FunctionSolver.exe)", stringToLPSTR(stringF + std::to_string(X)), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &piF);

    CreateProcess(R"(D:\KNU\Operating_System\Lab1\FunctionSolver\cmake-build-debug\FunctionSolver.exe)", stringToLPSTR(stringG + std::to_string(X)), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &piG);
}

/**
 * function for creating process to solv binary operation
 */
void createFinalProcess(int F, int G){
    std::string stringB = "b ";

    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {nullptr};

    CreateProcess(R"(D:\KNU\Operating_System\Lab1\FunctionSolver\cmake-build-debug\FunctionSolver.exe)", stringToLPSTR(stringB + std::to_string(F) + " " + std::to_string(G)), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi);
}

/**
 * function for add new message and convert to std::string
 * @return new message
 */
std::string GetMessages(PCOPYDATASTRUCT){
    int result = (int)((MYSTRUCT*)(pMyCDS->lpData))->res;

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

/**
 * function for convert std::string to LPSTR
 * @return LPSTR
 */
LPSTR stringToLPSTR(std::string s){
    char* temp = const_cast<char*>(s.c_str());
    return const_cast<LPSTR>(temp);
}

/**
 * function for break some process
 * @param f true if needed to terminate
 * @param g true if needed to terminate
 */
void breakProcess(bool f, bool g){
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
    SetMenu(mainHwnd, hMenu);
}

/**
 * function for determinate integer from char*
 * @return bool
 */
bool isInteger(char *s){
    std::string temp(s);
    int length = temp.size(), i = 0;

    if (length <= 0)
        return false;

    //if number <0
    if (length > 1 && temp[0] == '-'){
        if (temp[1] >= '1' && temp[1] <= '9'){

            for (i = 2; i<length; i++){
                if (!(temp[i] >= '0' && temp[i] <= '9'))
                    return false;
            }
            return true;
        } else
            return false;
    }

    //if number >=0
    for (i; i<length; i++){
        if (!(temp[i] >= '0' && temp[i] <= '9'))
            return false;
    }

    return true;
}

/**
 * function for run demofuncs
 * @param hwnd  handle to a main window
 * @param X
 */
void runDemoFunc(HWND hwnd, int X){
    EnableWindow(button, false);
    EnableWindow(input, false);
    SetMenu(hwnd, NULL);
    SetWindowText(console, "");
    SetFocus(hwnd);

    createProcess(true, X);
}

#endif //LAB_1_RECEIVER_H
