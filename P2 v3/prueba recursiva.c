#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float calculo(float b, float e){
    if (e == 0){
        return 1;
    }
    else if (e == 1){
        return b;
    }
    else{
        return b * calculo(b, e - 1);
        
    }
}