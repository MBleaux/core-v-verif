#include <stddef.h>

/* write to this reg for outputting strings */
#define STDOUT_REG 0x00800000
/* write test result of program to this reg */
#define RESULT_REG 0x008000c0
/* write exit value of program to this reg */
#define EXIT_REG 0x008000c4

void exit(int exit_status) {
    *(volatile int *)EXIT_REG = exit_status;
    while(1){};
}

size_t print(const void *ptr, size_t len) {
    const void *eptr = ptr + len;
    while (ptr != eptr)
        *(volatile int *)STDOUT_REG = *(char *)(ptr++);
    return len;
}
