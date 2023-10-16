#include "counter.h"
#include <zephyr.h>

void busy_counter(int *pointer){
    while(1){
        *pointer++;
    }
}

void busy_busy(char *name){
    for (int i = 0; ; i++);
}

void busy_yield(char *name){
    for (int i = 0; ; i++) {
        if (!(i & 0xFF)) {
            k_yield();
        }
    }
}

