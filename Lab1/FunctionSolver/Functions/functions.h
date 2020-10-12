#include <iostream>
#include <windows.h>
#include "demofuncs"

/**
 * Function F(x)
 * @param x
 *  (-infinity; -1000] f hangs
 *  (-1000; -100] f return 0
 *  (-100; infinity) f return (x + 1) / 3
 * @return result
 */

int f_func(int x){
    if (x <= -1000)
        while(1){}
    else if ((x <= -100) && (x > -1000))
    {
        Sleep(4000);
        return 0;
    }

    Sleep(5000);

    return ((x + 1) / 3);
}

/**
 * Function G(x)
 * @param x
 *  (-infinity; -2000] g return 0
 *  (-2000; -1000] and (0; infinity) g return (x - 1) * 4
 *  (-1000; 0] g hangs
 * @return result
 */
int g_func(int x){
    if (x <= -2000)
    {
        Sleep(7000);
        return 0;
    }
    else if ((x <= -1000) && (x > -2000) || (x >= 100))
    {
        Sleep(7000);
    }
    else if ((x <= 0) && (x > -1000))
        while(1){}

    Sleep(3000);

    return ((x - 1) * 4);
}

/**
 * demofunc F(x)
 * @param x
 * @return result
 */
template<spos::lab1::demo::op_group O>
int f_func_demo(int x){
    return spos::lab1::demo::f_func<O>(x);
}

/**
 * demofunc G(x)
 * @param x
 * @return result
 */
template<spos::lab1::demo::op_group O>
int g_func_demo(int x){
    return spos::lab1::demo::g_func<O>(x);
}

/**
 * Binary operation
 * @param f
 * @param g
 * @return f*g
 */
int binary_operation(int f, int g){
    return (f * g);
}