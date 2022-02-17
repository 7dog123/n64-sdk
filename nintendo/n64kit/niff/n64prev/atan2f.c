/*
=============================================================================
        Copyright (C) 1997, NINTENDO Co,Ltd.
=============================================================================
Function name: atan2f
-----------------------------------------------------------------------------
Form:   #include <math.h>
        float atan2f(float y, float x);
Argument:  x 
        y 
Return value: Returns arc tangent of Argument x /Argument y 
Explanation:  Returns arc tangent of Argument x /Argument y 

        atan(t) = t / (1+(t^2/(3+(2^2*t^2/(5+(3^2*t^2/(7+....)))))))
-----------------------------------------------------------------------------
Quoted from NuSTD  
*/
#include "pub.h"

float fabsf(float x)
{
    return ( x < 0.0f ) ? -x : x;
}

float atan2f(float y, float x)
{
    float   xx, z;
    float   a;
    int     i;

    if (x==0 && y==0) return 0.0f;
    if (x==0) {
        if (y>0) return PI/2;
        else return -PI/2;
    }

    xx = y/x;
    if (fabsf(xx)<=1) z = xx;
    else z = 1/xx;
    a = 0;
    for (i=14; i>=1; i--) a = i*i*z*z/(1+2*i+a);
    z = z/(1+a);
    if (xx> 1) z = PI/2 - z;
    if (xx<-1) z = -PI/2 - z;

    if (x>0) return z;
    else {
        if (y>0) return z+PI;
        else return z-PI;
    }
}
