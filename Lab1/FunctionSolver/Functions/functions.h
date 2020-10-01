#include <iostream>
#include <windows.h>

int f_func(int x){
    if (x == 1)
        Sleep(6000);
    else if (x < -1000)
        Sleep(60000);
    else if (x == -100)
        while(1){}
    Sleep(8000);

    return ((x + 1) / 3);
}

int g_func(int x){
    if (x == -1)
        Sleep(10000);
    else if (x > 1000)
        Sleep(40000);
    else if (x == 100)
        while(1){}
    Sleep(4000);

    return ((x - 1) * 4);
}

int binary_operation(int f, int g){
    Sleep(2000);
    return (f * g);
}