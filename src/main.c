#include <zephyr.h>
#include "counter.h"


#define STACKSIZE 1000

typedef struct k_thread k_thread_t;
typedef struct k_stack k_stack_t;

K_THREAD_STACK_DEFINE(stack_low, STACKSIZE);
K_THREAD_STACK_DEFINE(stack_high, STACKSIZE);

void main(void)
{
    int count_low = 0;
    int count_high = 0;
    k_thread_t thread_low, thread_high;
    
    k_thread_create(&thread_low,
                    stack_low,
                    STACKSIZE,
                    (k_thread_entry_t) busy_counter,
                    &count_low,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(3),
                    0,
                    K_FOREVER);
    k_thread_create(&thread_high,
                    stack_high,
                    STACKSIZE,
                    (k_thread_entry_t) busy_counter,
                    &count_high,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(7),
                    0,
                    K_NO_WAIT);

    k_thread_start(&thread_high);
    
    k_busy_wait(30000);
    k_thread_abort(&thread_high);
    k_thread_abort(&thread_low);
    printk("Low Prio count: %d\nHigh Prio Count: %d", count_low, count_high);

    
}
