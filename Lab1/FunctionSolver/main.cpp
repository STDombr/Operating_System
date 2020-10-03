#include <iostream>
#include <dshow.h>
#include "Functions/functions.h"
#define MYMESSAGE 1

/**
 * function for sending messages to receiver
 * @param function contains function info
 * @param result
 * @return
 */
bool sendMessage(char function, int result);

/**
 * structure for receiving messages
 * func store info about function
 * res store result of the function
 */
typedef struct tagMyStruct{
    char func;
    int res;
} MYSTRUCT;

int main(int argc, char *argv[]) {
    int result;

    if (argc == 2)
    {
        std::string func = argv[0];
        std::string X = argv[1];


        if (func == "f")
        {
            result = f_func(stoi(X));

            sendMessage('f', result);
        }
        else
        {
            result = g_func(stoi(X));

            return sendMessage('g', result);
        }
    }
    else if (argc == 3)
    {
        std::string f = argv[1];
        std::string g = argv[2];

        result = binary_operation(stoi(f), stoi(g));

        return sendMessage('b', result);
    }

    return 0;
}

/**
 * function for sending messages to receiver
 * @param function contains function info
 * @param result
 * @return
 */
bool sendMessage(char function, int result){
    MYSTRUCT MyStruct;
    MyStruct.func = function;
    MyStruct.res = result;

    COPYDATASTRUCT MyCDS;
    // Fill the COPYDATA structure
    MyCDS.dwData = MYMESSAGE;
    MyCDS.cbData = sizeof(MyStruct);
    MyCDS.lpData = &MyStruct;

    // Call function, passing data in &MyStruct
    HWND hwDispatch = FindWindow( "Disp32Class", "Hidden Window" );
    if (hwDispatch != nullptr)
    {
        SendMessage(hwDispatch, WM_COPYDATA, (WPARAM)(HWND) NULL, (LPARAM)(LPVOID) &MyCDS);
        return true;
    }
    else
        return false;
}