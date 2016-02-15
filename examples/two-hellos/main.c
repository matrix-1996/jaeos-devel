/*
* Copyright (c) Andras Zsoter 2015-2016.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#include <rtos.h>
#include <board.h>
#include "utility.h"

#define STACK_SIZE 512
RTOS_StackItem_t stack_hello1[STACK_SIZE];
RTOS_StackItem_t stack_hello2[STACK_SIZE];
RTOS_StackItem_t stack_idle[RTOS_MIN_STACK_SIZE];

RTOS_Task task_hello1;
RTOS_Task task_hello2;
RTOS_Task task_idle;

// Say Hello!
void say_hello(void *p)
{
    while(1) 
    {
    	PrintHex(RTOS.InterruptNesting);
    	Board_Puts(RTOS_GetCurrentTask()->TaskName);
	Board_Putc('\r');
	Board_Putc('\n');
    	PrintHex(RTOS_Delay(10));
	// RTOS_YieldPriority();
    	PrintHex(RTOS_GetTime());
    }
    (void)p;	// Pacifier for the compiler.
}


int main()
{
    	RTOS_CreateTask(&task_idle,   "Idle",        RTOS_Priority_Idle,  stack_idle, RTOS_MIN_STACK_SIZE, &RTOS_DefaultIdleFunction, 0);
    	RTOS_CreateTask(&task_hello1, "Hello -- 01", RTOS_Priority_Hello1, stack_hello1, STACK_SIZE, &say_hello, 0);
	RTOS_CreateTask(&task_hello2, "Hello -- 02", RTOS_Priority_Hello2, stack_hello2, STACK_SIZE, &say_hello, 0);

	Board_HardwareInit();					// Initialize hardware as appropriate for the system/board.
	RTOS_StartMultitasking();
	Board_Puts("Something has gone seriously wrong!\r\n");	// We should never get here!
    	while(1);
    	return 0;						// Unreachable.
}


