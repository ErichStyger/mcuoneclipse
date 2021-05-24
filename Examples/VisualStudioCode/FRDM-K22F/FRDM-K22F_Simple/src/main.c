#include "main.h"
#include <stdint.h>
#include <stdio.h>

static void bar(int32_t *p) {
    (*p)++;
}

int32_t global = 0;

int main(void) {
    int local = 0;
    for(;;) {
        global++;
        local += 2;
        bar(&global);
    }
    return 0;
}