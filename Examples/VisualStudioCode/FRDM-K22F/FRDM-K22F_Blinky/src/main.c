static int i;

int main(void) {
    volatile int local = 0;
    for(;;) {
        __asm("nop");
        i++;
        local++;  
    }  
    return 0;
}