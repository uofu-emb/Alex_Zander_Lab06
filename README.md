# Alex and Zander Lab06 - Scheduling

## Activity 0

Threads set with preemptive priority 3 and 4 for testing. When the higher priority thread is delay started after 30 ms and the supervisor sleeps for 30 ms to allow the low priority thread to run.

## Activity 1

Notes from running individual tests
1. Cooperative running `busy_busy`
   1. The thread that began first has more than 0 cycles run and the second thread doesn't run at all.
2. Cooperative running `busy_yield`
