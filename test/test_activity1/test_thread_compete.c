#include <stdio.h>
#include <zephyr.h>
#include <arch/cpu.h>
#include <unity.h>
#include "counter.h"

typedef struct k_thread k_thread_t;
typedef struct k_stack k_stack_t;

#define STACKSIZE 1000

K_THREAD_STACK_DEFINE(thread1_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(super_stack, STACKSIZE);

void super_entry(k_thread_t *thread1, k_thread_t *thread2)
{
    printk("Suspending threads\n");
    k_thread_suspend(thread1);
    k_thread_suspend(thread2);
}

void setUp(void) {}

void tearDown(void) {}

void coop_equal_busy_busy(void)
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(100));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(150));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void coop_equal_busy_yield(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(100));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(150));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void preempt_equal_busy_busy(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(100));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(150));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void preempt_equal_busy_yield(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(100));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(150));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void coop_high_busy_busy(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(5),
                    0,
                    K_MSEC(150));

    k_thread_join(&super, K_MSEC(1200));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void coop_low_busy_busy(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(120));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(5),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void coop_high_busy_yield(void) 
{k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(150));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);}

void coop_low_busy_yield(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(120));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(2),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void preempt_high_busy_busy(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(5),
                    0,
                    K_MSEC(150));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void preempt_low_busy_busy(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(120));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_busy,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(5),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void preempt_high_busy_yield(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(12));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(5),
                    0,
                    K_MSEC(150));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

void preempt_low_busy_yield(void) 
{
    k_thread_t thread1, thread2, super;
    k_thread_runtime_stats_t thread1_stats, thread2_stats;

    k_thread_create(&super,
                    super_stack,
                    STACKSIZE,
                    (k_thread_entry_t) super_entry,
                    &thread1,
                    &thread2,
                    NULL,
                    -CONFIG_NUM_COOP_PRIORITIES,
                    0,
                    K_MSEC(1000));
    k_thread_create(&thread1,
                    thread1_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(2),
                    0,
                    K_MSEC(120));
    k_thread_create(&thread2,
                    thread2_stack,
                    STACKSIZE,
                    (k_thread_entry_t) busy_yield,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_PREEMPT(5),
                    0,
                    K_MSEC(15));

    k_thread_join(&super, K_MSEC(1500));
    
    k_thread_runtime_stats_get(&thread1, &thread1_stats);
    k_thread_runtime_stats_get(&thread2, &thread2_stats);
    k_thread_abort(&thread1);
    k_thread_abort(&thread2);
    printk("Thread1 cycles: %llu\nThread2 cycles: %llu\n", thread1_stats.execution_cycles, thread2_stats.execution_cycles);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(coop_equal_busy_busy);
    RUN_TEST(preempt_equal_busy_busy);
    RUN_TEST(coop_equal_busy_yield);
    RUN_TEST(preempt_equal_busy_yield);
    RUN_TEST(coop_high_busy_busy);
    RUN_TEST(coop_low_busy_busy);
    RUN_TEST(coop_high_busy_yield);
    RUN_TEST(coop_low_busy_yield);
    RUN_TEST(preempt_high_busy_busy);
    RUN_TEST(preempt_low_busy_busy);
    RUN_TEST(preempt_high_busy_yield);
    RUN_TEST(preempt_low_busy_yield);
    return UNITY_END();
}