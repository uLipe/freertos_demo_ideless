/*
FreeRTOS V8.2.3 - Copyright (C) 2015 Real Time Engineers Ltd.
All rights reserved

VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

This file is part of the FreeRTOS distribution.

FreeRTOS is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License (version 2) as published by the
Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

***************************************************************************
>>!   NOTE: The modification to the GPL is included to allow you to     !<<
>>!   distribute a combined work that includes FreeRTOS without being   !<<
>>!   obliged to provide the source code for proprietary components     !<<
>>!   outside of the FreeRTOS kernel.                                   !<<
***************************************************************************

FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  Full license text is available on the following
link: http://www.freertos.org/a00114.html

***************************************************************************
*                                                                       *
*    FreeRTOS provides completely free yet professionally developed,    *
*    robust, strictly quality controlled, supported, and cross          *
*    platform software that is more than just the market leader, it     *
*    is the industry's de facto standard.                               *
*                                                                       *
*    Help yourself get started quickly while simultaneously helping     *
*    to support the FreeRTOS project by purchasing a FreeRTOS           *
*    tutorial book, reference manual, or both:                          *
*    http://www.FreeRTOS.org/Documentation                              *
*                                                                       *
***************************************************************************

http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
the FAQ page "My application does not run, what could be wrong?".  Have you
defined configASSERT()?

http://www.FreeRTOS.org/support - In return for receiving this top quality
embedded software for free we request you assist our global community by
participating in the support forum.

http://www.FreeRTOS.org/training - Investing in training allows your team to
be as productive as possible as early as possible.  Now you can receive
FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
Ltd, and the world's leading authority on the world's leading RTOS.

http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
including FreeRTOS+Trace - an indispensable productivity tool, a DOS
compatible FAT file system, and our tiny thread aware UDP/IP stack.

http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
licenses offer ticketed support, indemnification and commercial middleware.

http://www.SafeRTOS.com - High Integrity Systems also provide a safety
engineered and independently SIL3 certified version for use in safety and
mission critical applications that require provable dependability.

1 tab == 4 spaces!
*/

/**
 * @brief Homework #1 of coursera realtime systems course
 * @author Felipe Silva Neves
 *
 */


/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>


/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <queue.h>
#include <timers.h>
#include <math.h>
#include "MK64F12.h"
#include "fsl_debug_console.h"


/*
* Prototypes for the standard FreeRTOS callback/hook functions implemented
* within this file.
*/
void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
void vApplicationTickHook(void);

/*
* Writes trace data to a disk file when the trace recording is stopped.
* This function will simply overwrite any trace files that already exist.
*/
static void prvSaveTraceFile(void);

/* The user trace event posted to the trace recording on each tick interrupt.
Note tick events will not appear in the trace recording with regular period
because this project runs in a Windows simulator, and does not therefore
exhibit deterministic behaviour. */


/* Add two new tasks required by the exercise */
static void Task1(void *args);
static void Task2(void *args);

/* Define two new priority for these new tasks */
#define TASK1_PRIO (3)
#define TASK2_PRIO (1)

/* Define Stack depth for our new tasks */
#define TASK1_STACK_DEEP 1000
#define TASK2_STACK_DEEP 100

/* Define handles to manage  our new tasks */
TaskHandle_t task1;
TaskHandle_t task2;

/*-----------------------------------------------------------*/

int main(void)
{
	BaseType_t err = pdPASS;

	/* Installs homework application tasks */
	err = xTaskCreate(&Task1, "Task1", TASK1_STACK_DEEP,
   						 NULL, TASK1_PRIO, &task1 );
	if(err != pdPASS) {
		PRINTF("Failed to create task!\n\r");
		while(1);
	}

	err = xTaskCreate(&Task2, "Task2", TASK2_STACK_DEEP,
   						 NULL, TASK2_PRIO, &task2 );
	if(err != pdPASS) {
		PRINTF("Failed to create task!\n\r");
		while(1);
	}

	/* Starts the scheduler!*/
	vTaskStartScheduler();

	for (;;){
	}

	return 0;
}

/*-----------------------------------------------------------*/


/**
 * @brief homework task 1
 */
 static void Task1(void *args)
 {
	 /* define the number to ticks for a 100ms wait*/
	 const TickType_t task_period = configTICK_RATE_HZ / 10;
	 unsigned int exec = 0;

	 (void)args;

	 for(;;) {

		 PRINTF("This is task 1! \n\r");
		 PRINTF("Execs: %d \n\r", exec);
		 exec++;

		 /* Runs every 100ms */
		 vTaskDelay(task_period);
	 }
 }


 /**
  * @brief homework task 1
  */
  static void Task2(void *args)
  {
	  /* define the number to ticks for a 500ms wait*/
 	 const TickType_t task_period = configTICK_RATE_HZ / 2;
	 unsigned int exec = 0;
	 (void)args;

 	 for(;;) {
 		 PRINTF("This is task 2! \n\r");
		 PRINTF("Execs: %d \n\r", exec);
		 exec++;

		 /* Runs every 500ms */
 		 vTaskDelay(task_period);
 	 }
  }


/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook(void)
{
	PRINTF("RTOS Alloc failed! \n\r");
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
	/* for debug purposes */
	/* PRINTF("RTOS in Idle! \n\r"); */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
	(void)pcTaskName;
	(void)pxTask;

	PRINTF("RTOS, stack overflowed! \n\r");

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	vAssertCalled(__LINE__, __FILE__);
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{

}
/*-----------------------------------------------------------*/

void vAssertCalled(unsigned long ulLine, const char * const pcFileName)
{
}
/*-----------------------------------------------------------*/

static void prvSaveTraceFile(void)
{
}
/*-----------------------------------------------------------*/
