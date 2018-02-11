/* mbed Example Program
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Compile with symbols
// -DMBED_HEAP_STATS_ENABLED=1 -DMBED_STACK_STATS_ENABLED=1

/******************************************************************* Includes */
#include "mbed.h"
#include "rtos.h"
#include "mbed_stats.h"

/******************************************************************** Globals */
DigitalOut led1(LED1);
Thread thread1;
Thread thread2;

/******************************************************************** Defines */
#define STACK_ERROR

/****************************************************************** Functions */

/*
 * Thread allocates periodically memory.
 */
void error_thread(){

    while(1){
#ifdef STACK_ERROR
        static int i = 500;
        wait(4);
        /* Allocate bytes from user thread stack */
        char test_array[i+=500];
        for (size_t ix = 0; ix < sizeof(test_array); ix++) test_array[ix] = ix;
#else //HEAP ERROR
        wait(2);
        /* Allocate 3000 byte from Heap */
        void *allocation = malloc(3000);
        if(allocation == NULL){
            printf("System can not allocate block of memory!\n");
        }
#endif
    }
}

/*
 * Memory Statistics Thread
 */
void statistics_thread(){

    mbed_stats_heap_t heap_stats;
    int cnt;

    while(1){
        wait(3);
        /* Get heap statistics */
        mbed_stats_heap_get(&heap_stats);
        printf("\nCurrent heap: %lu\r\n", heap_stats.current_size);
        printf("Max heap size: %lu\r\n", heap_stats.max_size);

        /* Get stack size of each thread */
        cnt = osThreadGetCount();
        mbed_stats_stack_t *stats = (mbed_stats_stack_t*) malloc(cnt * sizeof(mbed_stats_stack_t));
        cnt = mbed_stats_stack_get_each(stats, cnt);
        for (int i = 0; i < cnt; i++) {
            printf("Thread: 0x%X, Stack size: %u, Max stack: %u\r\n", stats[i].thread_id, stats[i].reserved_size, stats[i].max_size);
        }
        free(stats);
    }
}

/**
 * Main Function
 */
int main() {

    printf("Heap Stack Statistics Example\n");
    /* Start memory leak thread thread */
    thread1.start(error_thread);
    /* Start memory statistics thread */
    thread2.start(statistics_thread);

    /* Toggle LED1  */
    while (1) {
        wait(1);
        led1 = !led1;
    }
}

/*EOF*/
