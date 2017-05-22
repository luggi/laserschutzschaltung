/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <stdint.h>

typedef void (* outputFunctionPtr)(int32_t pidResult);

typedef struct pid
{
    int32_t P;
	int32_t I;
	int32_t D;
	int32_t Iterm;
	int32_t old_pv;
	int32_t windup;
	outputFunctionPtr write;
} pid; 

// Function declaration
void pid_init(pid *pid, outputFunctionPtr outputPtr);
void pid_calc(pid *pid, int32_t sp, int32_t pv, int32_t deltaT);
int32_t constrain(int32_t min, int32_t max, int32_t value);


/* [] END OF FILE */
