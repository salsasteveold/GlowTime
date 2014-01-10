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
#include "LED_Matrix_1.h"

void LED_Matrix_1_Start()
{
	uint8 interruptState;

//	/* Enter critical section - AUX_CTL is shared by multiple hardware Components */
//	interruptState = CyEnterCriticalSection();
//
//	#if 0 > 0
//		LED_Matrix_1_AUX_CTL_A_REG |= (LED_Matrix_1_F0_LEVEL_MODE_1 << LED_Matrix_1_F0_LEVEL_SHIFT);
//	#endif
//	
//	#if 0 > 0
//		LED_Matrix_1_AUX_CTL_A_REG |= (LED_Matrix_1_F1_LEVEL_MODE_1 << LED_Matrix_1_F1_LEVEL_SHIFT);
//	#endif
//	
//	#if 0 > 0
//		LED_Matrix_1_AUX_CTL_A_REG |= (LED_Matrix_1_F0_SINGLE_BUFFER_ENABLE << LED_Matrix_1_F0_SINGLE_BUFFER_SHIFT);
//	#endif
//	
//	#if 0 > 0
//		LED_Matrix_1_AUX_CTL_A_REG |= (LED_Matrix_1_F1_SINGLE_BUFFER_ENABLE << LED_Matrix_1_F1_SINGLE_BUFFER_SHIFT);
//	#endif
	
	/* Exit critical section */
	CyExitCriticalSection(interruptState);
	
	return;
}

/* [] END OF FILE */
