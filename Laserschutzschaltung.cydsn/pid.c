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
#include "pid.h"

/* 
Pid initialisation 
P = P/10
I = I/100
D = D/100
*/
void pid_init(pid *pidData, outputFunctionPtr outputPtr)
{
	pidData->Iterm = 0;
	pidData->old_pv = 0;	
	pidData->write = outputPtr;
}

void pid_calc(pid *pidData, int32_t sp, int32_t pv, int32_t deltaTms)
{
	int32_t error, output;
	
	error = sp - pv;
    
	pidData->Iterm += error * pidData->I;
	pidData->Iterm = constrain(-pidData->windup, pidData->windup, pidData->Iterm);
	
	output = ((error * pidData->P) / 10) + ((pidData->Iterm * deltaTms) / (1000 * 100))  - (((pv - pidData->old_pv) * pidData->D * 10) / deltaTms);
	
	pidData->old_pv = pv;
	
	pidData->write(output);
    //pidData->write(0);
}

int32_t constrain(int32_t min, int32_t max, int32_t value)
{
	if(value > max)
		value = max;
	else if(value < min)
		value = min;
	
	return value;
}



/* [] END OF FILE */
