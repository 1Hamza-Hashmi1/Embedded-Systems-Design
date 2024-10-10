#include "cmsis_os.h"     // CMSIS RTOS header file
#include "LED.h"          // LED control header file
#include "GLCD.h"         // GLCD control header file
#include <stdio.h>        // Standard I/O for sprintf

// Thread IDs for the tasks
osThreadId tid_Task1, tid_Task2, tid_Task3; // Use osThreadId

// Task 1: Updates a GLCD display
void Task1(void const *argument) {
    uint32_t count = 0;
    unsigned char msg[16];  // Buffer for GLCD message, changed to unsigned char

    GLCD_SetTextColor(Blue);  // Set text color to blue (ensure this constant is defined in GLCD.h)

    while (1) {
        sprintf((char *)msg, "Count: %d", count++);  // Format the count, cast to char *
        GLCD_DisplayString(2, 0,1, msg);
				GLCD_DisplayString(6, 0,1, "Thread 1");			// Update the GLCD display
        osDelay(1000);                               // Wait for 1 second
				
    }
}

// Task 2: Blinks an LED
void Task2(void const *argument) {
    while (1) {
        LED_On(0);       // Turn on LED0
        osDelay(500);    // Wait for 500ms
        LED_Off(0);      // Turn off LED0
				GLCD_DisplayString(6, 0,1, "Thead 2");
        osDelay(500);    // Wait for another 500ms
    }
}

// Task 3: Does some other work
void Task3(void const *argument) {
    // Task 3: Simulates or reads a temperature sensor and displays the value on GLCD
    uint32_t temp = 25;  // Starting temperature (simulated)
    unsigned char tempMsg[16];  // Buffer for temperature message, cast to unsigned char

    GLCD_SetTextColor(Red);  // Set text color to red for the temperature

    while (1) {
        // Simulate temperature fluctuation
        temp = (temp >= 30) ? 25 : temp + 1;  // Increment temp up to 30 then reset to 25
        sprintf((char *)tempMsg, "Temp: %d C", temp);  // Format the temperature display
        GLCD_DisplayString(4, 0,1, tempMsg);  // Display the temperature on the GLCD
        GLCD_DisplayString(6, 0,1, "Thread 3");
				osDelay(2000);  // Delay for 2 seconds
    }

}

osThreadDef(Task1,osPriorityNormal,1,0);
osThreadDef(Task2,osPriorityNormal,1,0);
osThreadDef(Task3,osPriorityNormal,1,0);

int Init_Thread(void) {
    LED_Init();       // Initialize the LED system
    GLCD_Init();      // Initialize the GLCD screen
    GLCD_Clear(White); // Clear the GLCD screen, ensure this function accepts the color parameter

    // Create threads for Task1, Task2, and Task3
    tid_Task1 = osThreadCreate(osThread(Task1), NULL);  // Create Task1
    tid_Task2 = osThreadCreate(osThread(Task2), NULL);  // Create Task2
    tid_Task3 = osThreadCreate(osThread(Task3), NULL);  // Create Task3
}
