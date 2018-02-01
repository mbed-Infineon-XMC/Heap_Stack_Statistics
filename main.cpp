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

/******************************************************************* Includes */
#include "mbed.h"
#include "USBSerial.h"

/******************************************************************** Globals */
DigitalOut led1(LED1);
DigitalOut led2(LED2);
USBSerial pc;
Thread thread;

/****************************************************************** Functions */

/*
 * Communication thread
 */
void com_thread(){

    //
    while(1){
        wait(0.1);
        if(pc.readable()){
            led2 = !led2;
            while(pc.readable()){
                pc._putc(pc._getc());
            }
        }
    }
}

/**
 * Main Function
 */
int main() {

    pc.printf("USBSerial Example\n");
    /* Start com thread */
    thread.start(com_thread);

    /* Toggle LED1  */
    while (1) {
        wait(0.5);
        led1 = !led1;
    }
}

/*EOF*/
