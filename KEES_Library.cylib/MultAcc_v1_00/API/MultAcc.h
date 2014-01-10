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
#ifndef `$INSTANCE_NAME`_HEADER
#define `$INSTANCE_NAME`_HEADER

#include <device.h>
#include "`$INSTANCE_NAME`_MACC.h"

void `$INSTANCE_NAME`_Init();
void `$INSTANCE_NAME`_Enable();
void `$INSTANCE_NAME`_Start();
void `$INSTANCE_NAME`_Stop();
//void `$INSTANCE_NAME`_Sleep();
//void `$INSTANCE_NAME`_Wakeup();

void `$INSTANCE_NAME`_SetCoherency(uint8 coherencyKeyByte);
void `$INSTANCE_NAME`_SetDalign(uint8 dalignKeyByte);

#if !`$EnableBlock`
	void `$INSTANCE_NAME`_LoadInput(int32 A, int32 B) ;
#endif

int32 `$INSTANCE_NAME`_GetResult();
float `$INSTANCE_NAME`_Q23ToFloat(int32 input);
int32 `$INSTANCE_NAME`_FloatToQ23(float input);

#if `$EnableBlock`
	void `$INSTANCE_NAME`_DMAInit(void);
	void `$INSTANCE_NAME`_DMAEnable(void);
	void `$INSTANCE_NAME`_DMADisable(void);
	void `$INSTANCE_NAME`_ProcessBlock(uint8 reset_accum);
	uint8 `$INSTANCE_NAME`_CheckStatus(uint8 flag_check);
#endif

#if `$EnableBlock`
		
	//extern int32 `$INSTANCE_NAME`_data_a[`$ArraySize`];
	//extern int32 `$INSTANCE_NAME`_data_b[`$ArraySize`];
	
	#define `$INSTANCE_NAME`_DMA_GO 		0x01
	#define `$INSTANCE_NAME`_NRQ_RESET 		0x04
	#define `$INSTANCE_NAME`_MACC_RESET 	0x02
	#define `$INSTANCE_NAME`_ARRAY_SIZE  	`$ArraySize`
	
	#define `$INSTANCE_NAME`_BLOCK_COMPLETE		0x01
	#define `$INSTANCE_NAME`_RESULT_READY		0x02
	#define `$INSTANCE_NAME`_NEW_RESULT			0x04
	#define `$INSTANCE_NAME`_NOT_BUSY			0x08
	#define `$INSTANCE_NAME`_OVERFLOW_DETECT	0x10
	#define `$INSTANCE_NAME`_RESET_STATUS		0x80
	
	#define `$INSTANCE_NAME`_RESET			1u
	#define `$INSTANCE_NAME`_CONTINUE		0u
	
	typedef struct
	{
		uint32 dat[`$INSTANCE_NAME`_ARRAY_SIZE];
	} `$INSTANCE_NAME`_ARRAY;
	
	extern `$INSTANCE_NAME`_ARRAY `$INSTANCE_NAME`_a;
	extern `$INSTANCE_NAME`_ARRAY `$INSTANCE_NAME`_b;
	
#endif

//----------------------------------------------------------

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component `$INSTANCE_NAME` requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*           API Constants
***************************************/

/* Channel Definitions */
#define `$INSTANCE_NAME`_A              (1u)
#define `$INSTANCE_NAME`_B              (0u)


/***************************************
*             Registers
***************************************/


#define `$INSTANCE_NAME`_SEM_REG                (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__SEMA)
#define `$INSTANCE_NAME`_SEM_PTR                (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__SEMA)

#define `$INSTANCE_NAME`_OUT8_PTR             	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAH)
#define `$INSTANCE_NAME`_OUT16_PTR             	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAM)
#define `$INSTANCE_NAME`_OUT24_PTR              (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDA)
#define `$INSTANCE_NAME`_OUT32_PTR              (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDA)

#define `$INSTANCE_NAME`_OUT8_REG             	(* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAH)
#define `$INSTANCE_NAME`_OUT16_REG             	(* (reg16 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAM)
#define `$INSTANCE_NAME`_OUT24_REG              (* (reg24 *) `$INSTANCE_NAME`_MACC_DFB__HOLDA)
#define `$INSTANCE_NAME`_OUT32_REG              (* (reg32 *) `$INSTANCE_NAME`_MACC_DFB__HOLDA)

#define `$INSTANCE_NAME`_IN_A8_PTR            	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAH)
#define `$INSTANCE_NAME`_IN_A16_PTR           	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAM)
#define `$INSTANCE_NAME`_IN_A24_PTR         	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEA)
#define `$INSTANCE_NAME`_IN_A32_PTR         	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEA)

#define `$INSTANCE_NAME`_IN_A8_REG            	(* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAH)
#define `$INSTANCE_NAME`_IN_A16_REG           	(* (reg16 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAM)
#define `$INSTANCE_NAME`_IN_A24_REG         	(* (reg24 *) `$INSTANCE_NAME`_MACC_DFB__STAGEA)
#define `$INSTANCE_NAME`_IN_A32_REG         	(* (reg32 *) `$INSTANCE_NAME`_MACC_DFB__STAGEA)

#define `$INSTANCE_NAME`_IN_B8_PTR            	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBH)
#define `$INSTANCE_NAME`_IN_B16_PTR            	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBM)
#define `$INSTANCE_NAME`_IN_B24_PTR           	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEB)
#define `$INSTANCE_NAME`_IN_B32_PTR           	(  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEB)

#define `$INSTANCE_NAME`_IN_B8_REG            	(* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBH)
#define `$INSTANCE_NAME`_IN_B16_REG            	(* (reg16 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBM)
#define `$INSTANCE_NAME`_IN_B24_REG           	(* (reg24 *) `$INSTANCE_NAME`_MACC_DFB__STAGEB)
#define `$INSTANCE_NAME`_IN_B32_REG           	(* (reg24 *) `$INSTANCE_NAME`_MACC_DFB__STAGEB)


#define `$INSTANCE_NAME`_HOLDA_REG              (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDA)
#define `$INSTANCE_NAME`_HOLDA_PTR              (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDA)
#define `$INSTANCE_NAME`_HOLDAH_REG             (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAH)
#define `$INSTANCE_NAME`_HOLDAH_PTR             (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAH)
#define `$INSTANCE_NAME`_HOLDAM_REG             (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAM)
#define `$INSTANCE_NAME`_HOLDAM_PTR             (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__HOLDAM)

#define `$INSTANCE_NAME`_STAGEA_REG             (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEA)
#define `$INSTANCE_NAME`_STAGEA_PTR             (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEA)
#define `$INSTANCE_NAME`_STAGEAH_REG            (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAH)
#define `$INSTANCE_NAME`_STAGEAH_PTR            (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAH)
#define `$INSTANCE_NAME`_STAGEAM_REG            (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAM)
#define `$INSTANCE_NAME`_STAGEAM_PTR            (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEAM)
#define `$INSTANCE_NAME`_STAGEB_REG             (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEB)
#define `$INSTANCE_NAME`_STAGEB_PTR             (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEB)
#define `$INSTANCE_NAME`_STAGEBH_REG            (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBH)
#define `$INSTANCE_NAME`_STAGEBH_PTR            (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBH)
#define `$INSTANCE_NAME`_STAGEBM_REG            (* (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBM)
#define `$INSTANCE_NAME`_STAGEBM_PTR            (  (reg8 *) `$INSTANCE_NAME`_MACC_DFB__STAGEBM)


/***************************************
*       Register Constants
***************************************/


/* Mask for bits within DFB Interrupt Control and Status Registers */
#define `$INSTANCE_NAME`_SEM_MASK               (0x07u)

/* Mask for bits within DFB Semaphore Register */
#define `$INSTANCE_NAME`_NEWFLAG             	(0x01u)
#define `$INSTANCE_NAME`_OVERFLOWDET            (0x02u)
#define `$INSTANCE_NAME`_DEBUG             		(0x04u)

#endif
//[] END OF FILE
