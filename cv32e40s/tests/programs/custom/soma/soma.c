#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int a = 10;
    int b = 5;
    int res = 0;
    for(int i=0; i<b;i++){
        res += a*i;
    }
    return 0;
}
