# Alex and Zander Lab06 - Scheduling

## Activity 0

Threads set with preemptive priority 3 and 4 for testing. When the higher priority thread is delay started after 30 ms and the supervisor sleeps for 30 ms to allow the low priority thread to run.

## Activity 1

Notes from running individual tests

1. Equal priority
   1. Cooperative running `busy_busy`
      1. The thread that began first has more than 0 cycles run and the second thread doesn't run at all.
   2. Cooperative running `busy_yield`
      1. The threads have essentially equivalent runtime.
   3. Preemptive running `busy_busy`
      1. The thread that began first has more than 0 cycles and the second thread doesn't run at all.
   4. Preemptive running `busy_yield`
      1. The threads have essentially equivalent runtime
2. Unequal priority
   1. Cooperative running `busy_busy` any priority first
      1. The thread that begins first has all the runtime where the other does not.
   2. Cooperative running `busy_yield`
      1. No matter which thread begins first, the runtime is approximately equal between threads.
   3. Preemptive running `busy_busy`
      1. If the higher priority thread runs first, the low priority thread gets no runtime.
      2. If the lower priority thread runs first, the low priority thread gets some runtime before being preempted by the high priority thread.
   4. Preemptive running `busy_yield`
      1. If the higher priority thread runs first, the low priority thread gets no runtime.
      2. If the lower priority thread runs first, the low priority thread gets some runtime before being preempted by the high priority thread.

## Activity 2

Runtimes with same priority whether cooperative or preemptive priority get similar numbers each. The thread running `busy_yield` gets most of the runtime with the thread running `busy_sleep` gets some runtime.
