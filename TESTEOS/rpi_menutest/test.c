#include <stdio.h>
#include <stdint.h>

int8_t modulo(int8_t x){
    return x >= 0 ? x : -x;
}

int main(){
    printf("%d, %d, %d, %d", modulo(-128), modulo(127), modulo(0), modulo (-127));
}