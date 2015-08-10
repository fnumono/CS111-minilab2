#include "schedos-app.h"
#include "x86sync.h"

/*****************************************************************************
 * schedos-1
 *
 *   This tiny application prints red "1"s to the console.
 *   It yields the CPU to the kernel after each "1" using the sys_yield()
 *   system call.  This lets the kernel (schedos-kern.c) pick another
 *   application to run, if it wants.
 *
 *   The other schedos-* processes simply #include this file after defining
 *   PRINTCHAR appropriately.
 *
 *****************************************************************************/

#ifndef PRINTCHAR
#define PRINTCHAR	('1' | 0x0C00)
#endif

// UNCOMMENT THE NEXT LINE TO USE EXERCISE 8 CODE INSTEAD OF EXERCISE 6
	// #define __EXERCISE_8__
	// Use the following structure to choose between them:
	//Inside the function
         // #define __PRIORITY_1__ 1
	// #define __PRIORITY_2__ 2
	// #define __PRIORITY_3__ 3
	// #define __PRIORITY_4__ 4
	
	// UNCOMMENT THESE LINES IF YOU DO EXERCISE 4.B
	// Use these #defines to initialize your implementation.
	// Changing one of these lines should change the initialization.
	// #define __SHARE_1__ 1
	// #define __SHARE_2__ 2
	// #define __SHARE_3__ 3
	// #define __SHARE_4__ 4

#ifndef __PRIORITY_1__ 
#define __PRIORITY_1__ 	 //Exercise 4A, used to demonstrate my sys_set_priority system call
			  //schedos-x.c has their own definitions
#endif
#ifndef __SHARE_1__ 
#define __SHARE_1__ 	 //Exercise 4B, used to demonstrate my sys_set_time_share system call
			  //schedos-x.c has their own definitions
#endif


void
start(void)
{
	int i;
	//sys_set_priority(__PRIORITY_1__); //Set this process' priority. Exercise 4A (scheduling_algorithm 2)
	//sys_set_time_share(__SHARE_1__); //Set this process' time Share. Exercise 4B (scheduling_algorith 3)
	for (i = 0; i < RUNCOUNT; i++) {
		// Write characters atomically to the console, yielding after each one.
		#ifdef  __EXERCISE_8__
		sys_print_char((uint16_t)PRINTCHAR); //Exercise 8, uncomment the MACRO defined above first
		#else
		while(atomic_swap(&lock,1)!=0) { //Polling for the global lock. Exercise 6
			continue;
		}
		*cursorpos++ = PRINTCHAR;
		atomic_swap(&lock,0); //Release the lock Exercise 6
		#endif
		sys_yield();
	}

	// Yield forever.
	//while (1)
		//sys_yield();
		sys_exit(0);
}
