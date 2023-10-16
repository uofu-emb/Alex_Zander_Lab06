#include "counter.h"
#include <zephyr.h>

void busy_counter(){
    int i = 0;
    while(1){
        i++;
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

