#include "wait.h"
void wait(double a){
    double b = 0;
    for(clock_t t = clock(); b < a; b = (clock() - t) / CLOCKS_PER_SEC)
        ;
}

bool hold(double a, clock_t t){
    double b = (clock() - t) / CLOCKS_PER_SEC;
    if(b < a)
        return true;
    else
        return false;
}

