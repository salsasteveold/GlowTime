/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h  
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the 8-bit Waveform DAC (WaveDAC8) Component.
*
*   Note: 
*     
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



#include "cytypes.h"
#include "cyfitter.h"
#include <`$INSTANCE_NAME`_Wave1_DMA_dma.h>
#include <`$INSTANCE_NAME`_Wave2_DMA_dma.h>

#define `$INSTANCE_NAME`_DEFAULT_RANGE    `$DAC_Range`     /* Default DAC range */
#define `$INSTANCE_NAME`_DACMODE (((`$DAC_Range` == 0) || ( `$DAC_Range` == 1 ))?0:1)
#define `$INSTANCE_NAME`_VOLT_MODE     0
#define `$INSTANCE_NAME`_CURRENT_MODE  1



#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
#include <`$INSTANCE_NAME`_VDAC8.h>
#else
#include <`$INSTANCE_NAME`_IDAC8.h>
#endif

#if(`$Clock_SRC`)  
   #include <`$INSTANCE_NAME`_DacClk.h>
#endif

#if !defined(CY_WDAC8_`$INSTANCE_NAME`_H) 
#define CY_WDAC8_`$INSTANCE_NAME`_H


#define `$INSTANCE_NAME`_Wave1_DMA_TD_TERMOUT_EN ((`$INSTANCE_NAME`_Wave1_DMA__TERMOUT0_EN ? TD_TERMOUT0_EN : 0) | \
    (`$INSTANCE_NAME`_Wave1_DMA__TERMOUT1_EN ? TD_TERMOUT1_EN : 0))
	
#define `$INSTANCE_NAME`_Wave2_DMA_TD_TERMOUT_EN ((`$INSTANCE_NAME`_Wave2_DMA__TERMOUT0_EN ? TD_TERMOUT0_EN : 0) | \
    (`$INSTANCE_NAME`_Wave2_DMA__TERMOUT1_EN ? TD_TERMOUT1_EN : 0))
	

#define `$INSTANCE_NAME`_Wave1_DMA_BYTES_PER_BURST 1	
#define `$INSTANCE_NAME`_Wave1_DMA_REQUEST_PER_BURST 1
#define `$INSTANCE_NAME`_Wave2_DMA_BYTES_PER_BURST 1	
#define `$INSTANCE_NAME`_Wave2_DMA_REQUEST_PER_BURST 1

/***************************************
*   Data Struct Definition
***************************************/

/* Low power Mode API Support */
typedef struct _`$INSTANCE_NAME`_backupStruct
{
    uint8   enableState;
}   `$INSTANCE_NAME`_BACKUP_STRUCT;


/***************************************
*        Function Prototypes 
***************************************/

void    `$INSTANCE_NAME`_Start(void);
void    `$INSTANCE_NAME`_Init(void);
void    `$INSTANCE_NAME`_Enable(void);
void    `$INSTANCE_NAME`_Stop(void);
void    `$INSTANCE_NAME`_SetSpeed(uint8 speed);
void    `$INSTANCE_NAME`_SetRange(uint8 range);
void    `$INSTANCE_NAME`_SetValue(uint8 value);
void 	`$INSTANCE_NAME`_DacTrim(void);

void    `$INSTANCE_NAME`_Wave1Setup( uint8 * WavePtr, uint16 SampleSize);
void    `$INSTANCE_NAME`_Wave2Setup( uint8 * WavePtr, uint16 SampleSize);

void    `$INSTANCE_NAME`_SaveConfig(void);
void    `$INSTANCE_NAME`_RestoreConfig(void);
void    `$INSTANCE_NAME`_Sleep(void);
void    `$INSTANCE_NAME`_Wakeup(void);
  
  
/***************************************
*            API Constants
***************************************/

/* SetRange constants */
`#cy_declare_enum vDacRange`
#define `$INSTANCE_NAME`_RANGE_1V       (0x00u)
#define `$INSTANCE_NAME`_RANGE_4V       (0x04u)

#define `$INSTANCE_NAME`_RANGE_32uA     (0x00u)
#define `$INSTANCE_NAME`_RANGE_255uA    (0x04u)
#define `$INSTANCE_NAME`_RANGE_2mA      (0x08u)
#define `$INSTANCE_NAME`_RANGE_2048uA   (0x08u)


/* Power setting for Start API  */
#define `$INSTANCE_NAME`_LOWSPEED       0x00u
#define `$INSTANCE_NAME`_HIGHSPEED      0x02u


/***************************************
*  Initialization Parameter Constants
***************************************/

#define `$INSTANCE_NAME`_WAVE1_TYPE    `$Wave1_Type`     /* Waveform for wave1 */
#define `$INSTANCE_NAME`_WAVE2_TYPE    `$Wave2_Type`     /* Waveform for wave2 */
#define `$INSTANCE_NAME`_WAVE1_LENGTH  `$Wave1_Length`   /* Length for wave1 */
#define `$INSTANCE_NAME`_WAVE2_LENGTH  `$Wave2_Length`   /* Length for wave2 */
#define `$INSTANCE_NAME`_CLOCK_SRC     `$Clock_SRC`      /* Clock SRC 0=Ext, 1=Int */

#define `$INSTANCE_NAME`_SINE_WAVE       0x00
#define `$INSTANCE_NAME`_SQUARE_WAVE     0x01
#define `$INSTANCE_NAME`_TRIANGLE_WAVE   0x02
#define `$INSTANCE_NAME`_SAWTOOTH_WAVE   0x03

#define `$INSTANCE_NAME`_CLOCK_INT       0x01
#define `$INSTANCE_NAME`_CLOCK_EXT       0x00  


/***************************************
*              Registers        
***************************************/

#if(`$INSTANCE_NAME`_DACMODE == `$INSTANCE_NAME`_VOLT_MODE)
#define `$INSTANCE_NAME`_DAC8__D `$INSTANCE_NAME`_VDAC8_viDAC8__D
#else
#define `$INSTANCE_NAME`_DAC8__D `$INSTANCE_NAME`_IDAC8_viDAC8__D
#endif

/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE                  */
#define `$INSTANCE_NAME`_HS_MASK        0x02u
#define `$INSTANCE_NAME`_HS_LOWPOWER    0x00u
#define `$INSTANCE_NAME`_HS_HIGHSPEED   0x02u

/* Bit Field  DAC_MODE                  */
#define `$INSTANCE_NAME`_MODE_MASK      0x10u
#define `$INSTANCE_NAME`_MODE_V         0x00u
#define `$INSTANCE_NAME`_MODE_I         0x10u

/* Bit Field  DAC_RANGE                  */
#define `$INSTANCE_NAME`_RANGE_MASK     0x0Cu
#define `$INSTANCE_NAME`_RANGE_0        0x00u
#define `$INSTANCE_NAME`_RANGE_1        0x04u
#define `$INSTANCE_NAME`_RANGE_2        0x08u
#define `$INSTANCE_NAME`_RANGE_3        0x0Cu
#define `$INSTANCE_NAME`_IDIR_MASK      0x04u

#define `$INSTANCE_NAME`_DAC_RANGE  (( `$DAC_Range` << 2 ) & `$INSTANCE_NAME`_RANGE_MASK )
#define `$INSTANCE_NAME`_DAC_POL    (( `$DAC_Range` >> 1 ) & `$INSTANCE_NAME`_IDIR_MASK )  

#endif /* CY_VDAC8_`$INSTANCE_NAME`_H  */
/* [] END OF FILE */



