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

/***************************************
*        Function Prototypes 
***************************************/
#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"  /* needed for the CyScPumpEnabled definition in init function */


void `$INSTANCE_NAME`_Start(void);

void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);

/***************************************
*              Registers        
***************************************/
// CFG
#define `$INSTANCE_NAME`_CR0_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__CR0 )
#define `$INSTANCE_NAME`_CR0_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__CR0 )

#define `$INSTANCE_NAME`_CR1_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__CR1 )
#define `$INSTANCE_NAME`_CR1_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__CR1 )

#define `$INSTANCE_NAME`_CR2_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__CR2 )
#define `$INSTANCE_NAME`_CR2_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__CR2 )

#define `$INSTANCE_NAME`_PUMP_CR1_REG             (* (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)
#define `$INSTANCE_NAME`_PUMP_CR1_PTR             (  (reg8 *) CYDEV_ANAIF_CFG_PUMP_CR1)

// RT
#define `$INSTANCE_NAME`_SW0_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW0 )
#define `$INSTANCE_NAME`_SW0_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW0 )

#define `$INSTANCE_NAME`_SW2_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW2 )
#define `$INSTANCE_NAME`_SW2_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW2 )

#define `$INSTANCE_NAME`_SW3_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW3 )
#define `$INSTANCE_NAME`_SW3_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW3 )

#define `$INSTANCE_NAME`_SW4_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW4 )
#define `$INSTANCE_NAME`_SW4_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW4 )

#define `$INSTANCE_NAME`_SW6_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW6 )
#define `$INSTANCE_NAME`_SW6_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW6 )

#define `$INSTANCE_NAME`_SW7_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW7 )
#define `$INSTANCE_NAME`_SW7_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW7 )

#define `$INSTANCE_NAME`_SW8_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW8 )
#define `$INSTANCE_NAME`_SW8_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW8 )

#define `$INSTANCE_NAME`_SW10_REG                 (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SW10 )
#define `$INSTANCE_NAME`_SW10_PTR                 (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SW10 )

#define `$INSTANCE_NAME`_CLK_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__CLK )
#define `$INSTANCE_NAME`_CLK_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__CLK )

#define `$INSTANCE_NAME`_BST_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__BST )
#define `$INSTANCE_NAME`_BST_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__BST )

#define `$INSTANCE_NAME`_SC_MISC_REG              (* (reg8 *) CYDEV_ANAIF_RT_SC_MISC)
#define `$INSTANCE_NAME`_SC_MISC_PTR              (  (reg8 *) CYDEV_ANAIF_RT_SC_MISC)

// WRK
#define `$INSTANCE_NAME`_SR_REG                   (* (reg8 *) `$INSTANCE_NAME`_ScBlock__SR )
#define `$INSTANCE_NAME`_SR_PTR                   (  (reg8 *) `$INSTANCE_NAME`_ScBlock__SR )

#define `$INSTANCE_NAME`_WRK1_REG                 (* (reg8 *) `$INSTANCE_NAME`_ScBlock__WRK1 )
#define `$INSTANCE_NAME`_WRK1_PTR                 (  (reg8 *) `$INSTANCE_NAME`_ScBlock__WRK1 )

#define `$INSTANCE_NAME`_MSK_REG                  (* (reg8 *) `$INSTANCE_NAME`_ScBlock__MSK )
#define `$INSTANCE_NAME`_MSK_PTR                  (  (reg8 *) `$INSTANCE_NAME`_ScBlock__MSK )

#define `$INSTANCE_NAME`_CMPINV_REG               (* (reg8 *) `$INSTANCE_NAME`_ScBlock__CMPINV )
#define `$INSTANCE_NAME`_CMPINV_PTR               (  (reg8 *) `$INSTANCE_NAME`_ScBlock__CMPINV )

#define `$INSTANCE_NAME`_CPTR_REG                 (* (reg8 *) `$INSTANCE_NAME`_ScBlock__CPTR )
#define `$INSTANCE_NAME`_CPTR_PTR                 (  (reg8 *) `$INSTANCE_NAME`_ScBlock__CPTR )

// power manager
#define `$INSTANCE_NAME`_PM_ACT_CFG_REG           (* (reg8 *) `$INSTANCE_NAME`_ScBlock__PM_ACT_CFG )
#define `$INSTANCE_NAME`_PM_ACT_CFG_PTR           (  (reg8 *) `$INSTANCE_NAME`_ScBlock__PM_ACT_CFG )  

#define `$INSTANCE_NAME`_PM_STBY_CFG_REG          (* (reg8 *) `$INSTANCE_NAME`_ScBlock__PM_STBY_CFG )
#define `$INSTANCE_NAME`_PM_STBY_CFG_PTR          (  (reg8 *) `$INSTANCE_NAME`_ScBlock__PM_STBY_CFG )  


// PM
// *************** MODES *****************
/* PM_ACT_CFG (Active Power Mode CFG Register)mask */ 
#define `$INSTANCE_NAME`_ACT_PWR_EN          `$INSTANCE_NAME`_ScBlock__PM_ACT_MSK 

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register)mask */ 
#define `$INSTANCE_NAME`_STBY_PWR_EN          `$INSTANCE_NAME`_ScBlock__PM_STBY_MSK 


// CFG
// *************** MASKS ****************
// CFG CR0
#define `$INSTANCE_NAME`_DFT_MASK               (0x30u)
#define `$INSTANCE_NAME`_MODE_MASK              (0x0Eu)
// CFG CR1
#define `$INSTANCE_NAME`_GAIN_MASK              (0x20u)
#define `$INSTANCE_NAME`_DIV2_MASK              (0x10u)
#define `$INSTANCE_NAME`_COMP_MASK              (0x0Cu)
#define `$INSTANCE_NAME`_DRIVE_MASK             (0x03u)
// CFG CR2
#define `$INSTANCE_NAME`_PGA_GNDVREF_MASK       (0x80u)
#define `$INSTANCE_NAME`_RVAL_MASK              (0x70u)
#define `$INSTANCE_NAME`_REDC_MASK              (0x0Cu)
#define `$INSTANCE_NAME`_R20_40B_MASK           (0x02u)
#define `$INSTANCE_NAME`_BIAS_CTL_MASK          (0x01u)
// PUMP CR1
#define `$INSTANCE_NAME`_PUMP_MASK              (0x80u)

// *************** SHIFTS ****************
// CFG CR0
#define `$INSTANCE_NAME`_DFT_SHIFT              (4u)
#define `$INSTANCE_NAME`_MODE_SHIFT             (1u)
// CFG CR1
#define `$INSTANCE_NAME`_GAIN_SHIFT             (5u)
#define `$INSTANCE_NAME`_DIV2_SHIFT             (4u)
#define `$INSTANCE_NAME`_COMP_SHIFT             (2u)
#define `$INSTANCE_NAME`_DRIVE_SHIFT            (0u)
// CFG CR2
#define `$INSTANCE_NAME`_PGA_GNDVREF_SHIFT      (7u)
#define `$INSTANCE_NAME`_RVAL_SHIFT             (4u)
#define `$INSTANCE_NAME`_REDC_SHIFT             (2u)
#define `$INSTANCE_NAME`_R20_40B_SHIFT          (1u)
#define `$INSTANCE_NAME`_BIAS_CTL_SHIFT         (0u)
// PUMP CR1
#define `$INSTANCE_NAME`_PUMP_SHIFT             (7u)

// *************** MODES ****************
// CFG CR0
// DFT
#define `$INSTANCE_NAME`_DFT_NORMAL             (0x0u)
#define `$INSTANCE_NAME`_DFT_VBOOST             (0x1u)
// PGA = Voltage Integrator, TIA = Charge integrator, Naked Opamp = Comparator
#define `$INSTANCE_NAME`_DFT_MODE_DEPENDENT     (0x2u)  
#define `$INSTANCE_NAME`_DFT_RESET              (0x3u)
// MODE
#define `$INSTANCE_NAME`_MODE_NAKED_OP_AMP      (0x0u)
#define `$INSTANCE_NAME`_MODE_TIA               (0x1u)
#define `$INSTANCE_NAME`_MODE_CTMIXER           (0x2u)
#define `$INSTANCE_NAME`_MODE_NRZ_SH            (0x3u)
#define `$INSTANCE_NAME`_MODE_UNITY             (0x4u)
#define `$INSTANCE_NAME`_MODE_1ST_MOD           (0x5u)
#define `$INSTANCE_NAME`_MODE_PGA               (0x6u)
#define `$INSTANCE_NAME`_MODE_TRACKANDHOLD      (0x7u)
// CFG CR1
// GAIN
#define `$INSTANCE_NAME`_GAIN_0DB               (0u)
#define `$INSTANCE_NAME`_GAIN_6DB               (1u)
// DIV2
#define `$INSTANCE_NAME`_DIV2_DISABLE           (0u)
#define `$INSTANCE_NAME`_DIV2_ENABLE            (1u)
// COMP
#define `$INSTANCE_NAME`_COMP_3P0PF             (0u)
#define `$INSTANCE_NAME`_COMP_3P6PF             (1u)
#define `$INSTANCE_NAME`_COMP_4P35PF            (2u)
#define `$INSTANCE_NAME`_COMP_5P1PF             (3u)
// DRIVE
#define `$INSTANCE_NAME`_DRIVE_175UA            (0u)
#define `$INSTANCE_NAME`_DRIVE_260UA            (1u)
#define `$INSTANCE_NAME`_DRIVE_330UA            (2u)
#define `$INSTANCE_NAME`_DRIVE_400UA            (3u)
// CFG CR2
// PGA GNDVREF
#define `$INSTANCE_NAME`_PGA_GNDVREF_DISABLE    (0u)
#define `$INSTANCE_NAME`_PGA_GNDVREF_ENABLE     (1u)
// RVAL
#define `$INSTANCE_NAME`_RVAL_20K               (0u)
#define `$INSTANCE_NAME`_RVAL_30K               (1u)
#define `$INSTANCE_NAME`_RVAL_40K               (2u)
#define `$INSTANCE_NAME`_RVAL_80K               (3u)
#define `$INSTANCE_NAME`_RVAL_120K              (4u)
#define `$INSTANCE_NAME`_RVAL_250K              (5u)
#define `$INSTANCE_NAME`_RVAL_500K              (6u)
#define `$INSTANCE_NAME`_RVAL_1M                (7u)
// REDC
#define `$INSTANCE_NAME`_REDC_00                (0u)
#define `$INSTANCE_NAME`_REDC_01                (1u)
#define `$INSTANCE_NAME`_REDC_10                (2u)
#define `$INSTANCE_NAME`_REDC_11                (3u)
// R20 40B
#define `$INSTANCE_NAME`_R20_40B_40K            (0u)
#define `$INSTANCE_NAME`_R20_40B_20K            (1u)
// BIAS CTRL
#define `$INSTANCE_NAME`_BIAS_CTL_1X            (0u)
#define `$INSTANCE_NAME`_BIAS_CTL_2X            (1u)
// PUMP CR1
#define `$INSTANCE_NAME`_PUMP_EXTERNAL          (0u)
#define `$INSTANCE_NAME`_PUMP_INTERNAL          (1u)

// ANAIF
// *************** MASKS ****************
// CLK
#define `$INSTANCE_NAME`_DYN_CNTL_EN_MASK       (0x20u)
#define `$INSTANCE_NAME`_BYPASS_SYNC_MASK       (0x10u)
#define `$INSTANCE_NAME`_CLK_EN_MASK            (0x08u)
#define `$INSTANCE_NAME`_MX_CLK_MASK            (0x07u)
// BST
#define `$INSTANCE_NAME`_BST_CLK_EN_MASK        (0x08u)
#define `$INSTANCE_NAME`_MX_BST_CLK_MASK        (0x07u)
#define `$INSTANCE_NAME`_SC_PUMP_FORCE_MASK		(0x20u)
#define `$INSTANCE_NAME`_SC_PUMP_AUTO_MASK		(0x10u)
#define `$INSTANCE_NAME`_DIFF_PGA_1_3_MASK		(0x02u)
#define `$INSTANCE_NAME`_DIFF_PGA_0_2_MASK		(0x01u)

// *************** SHIFTS ****************
// CLK
#define `$INSTANCE_NAME`_DYN_CNTL_EN_SHIFT      (5u)
#define `$INSTANCE_NAME`_BYPASS_SYNC_SHIFT      (4u)
#define `$INSTANCE_NAME`_CLK_EN_SHIFT           (3u)
#define `$INSTANCE_NAME`_MX_CLK_SHIFT           (0u)
// BST
#define `$INSTANCE_NAME`_BST_CLK_EN_SHIFT       (3u)
#define `$INSTANCE_NAME`_MX_BST_CLK_SHIFT       (0u)
#define `$INSTANCE_NAME`_SC_PUMP_FORCE_SHIFT	(5u)
#define `$INSTANCE_NAME`_SC_PUMP_AUTO_SHIFT		(4u)
#define `$INSTANCE_NAME`_DIFF_PGA_1_3_SHIFT		(1u)
#define `$INSTANCE_NAME`_DIFF_PGA_0_2_SHIFT		(0u)


// *************** MODES ****************
// CLK
// DYN CNTRL EN
#define `$INSTANCE_NAME`_DYN_CNTL_EN_DISABLE    (0u)
#define `$INSTANCE_NAME`_DYN_CNTL_EN_ENABLE     (1u)
// BYPASS SYNC
#define `$INSTANCE_NAME`_BYPASS_SYNC_DISABLE    (0u)
#define `$INSTANCE_NAME`_BYPASS_SYNC_ENABLE     (1u)
// CLK EN
#define `$INSTANCE_NAME`_CLK_EN_DISABLE         (0u)
#define `$INSTANCE_NAME`_CLK_EN_ENABLE          (1u)
// MX CLK
#define `$INSTANCE_NAME`_MX_CLK_0               (0u)
#define `$INSTANCE_NAME`_MX_CLK_1               (1u)
#define `$INSTANCE_NAME`_MX_CLK_2               (2u)
#define `$INSTANCE_NAME`_MX_CLK_3               (3u)
#define `$INSTANCE_NAME`_MX_CLK_UDB             (4u)
// BST
// BST_CLK_EN
#define `$INSTANCE_NAME`_BST_CLK_EN_DISABLE     (0u)
#define `$INSTANCE_NAME`_BST_CLK_EN_ENABLE      (1u)
// MX BST CLK
#define `$INSTANCE_NAME`_MX_BST_CLK_0           (0u)
#define `$INSTANCE_NAME`_MX_BST_CLK_1           (1u)
#define `$INSTANCE_NAME`_MX_BST_CLK_2           (2u)
#define `$INSTANCE_NAME`_MX_BST_CLK_3           (3u)
#define `$INSTANCE_NAME`_MX_BST_CLK_UDB         (4u)
// SC MISC
// FORCE PUMP
#define `$INSTANCE_NAME`_SC_PUMP_NO_FORCE		(0u)
#define `$INSTANCE_NAME`_SC_PUMP_FORCE			(1u)
// PUMP AUTO
#define `$INSTANCE_NAME`_SC_PUMP_NO_AUTO		(0u)
#define `$INSTANCE_NAME`_SC_PUMP_AUTO			(1u)
// DIFF PGA 1 3
#define `$INSTANCE_NAME`_DIFF_PGA_1_3_DISABLE	(0u)
#define `$INSTANCE_NAME`_DIFF_PGA_1_3_ENABLE	(1u)
// DIFF PGA 0 2
#define `$INSTANCE_NAME`_DIFF_PGA_0_2_DISABLE	(0u)
#define `$INSTANCE_NAME`_DIFF_PGA_0_2_ENABLE	(1u)


// **************** ANALOG SWITCHES ****************
// since the switches are different depending on which SC/CT block is used,
// all of the defines are provided, but it is up to the user
// to force the placement of the block to ensure that the switches
// that are needed will be available
// SW0
#define `$INSTANCE_NAME`_VIN_AG7                (0x80u)
#define `$INSTANCE_NAME`_VIN_AG6                (0x40u)
#define `$INSTANCE_NAME`_VIN_AG5                (0x20u)
#define `$INSTANCE_NAME`_VIN_AG4                (0x10u)
#define `$INSTANCE_NAME`_VIN_AG3                (0x08u)
#define `$INSTANCE_NAME`_VIN_AG2                (0x04u)
#define `$INSTANCE_NAME`_VIN_AG1                (0x02u)
#define `$INSTANCE_NAME`_VIN_AG0                (0x01u)
// SW2
#define `$INSTANCE_NAME`_VIN_ABUS3              (0x08u)
#define `$INSTANCE_NAME`_VIN_ABUS2              (0x04u)
//  v-- AVAILABILITY VARIES WITH SC/CT POSITION --v
#define `$INSTANCE_NAME`_VIN_ABUS1              (0x02u)
#define `$INSTANCE_NAME`_VIN_ABUS0              (0x01u)
//  ^-- AVAILABILITY VARIES WITH SC/CT POSITION --^
// SW3
#define `$INSTANCE_NAME`_VREF_BGVREF            (0x20u)
#define `$INSTANCE_NAME`_VIN_BGVREF             (0x02u)
#define `$INSTANCE_NAME`_VIN_AMX                (0x01u)
// SW4
//  v-- AVAILABILITY VARIES WITH SC/CT POSITION --v
#define `$INSTANCE_NAME`_VREF_AG7               (0x80u)
#define `$INSTANCE_NAME`_VREF_AG6               (0x40u)
#define `$INSTANCE_NAME`_VREF_AG5               (0x20u)
#define `$INSTANCE_NAME`_VREF_AG4               (0x10u)
#define `$INSTANCE_NAME`_VREF_AG3               (0x08u)
#define `$INSTANCE_NAME`_VREF_AG2               (0x04u)
#define `$INSTANCE_NAME`_VREF_AG1               (0x02u)
#define `$INSTANCE_NAME`_VREF_AG0               (0x01u)
//  ^-- AVAILABILITY VARIES WITH SC/CT POSITION --^
// SW6
//  v-- AVAILABILITY VARIES WITH SC/CT POSITION --v
#define `$INSTANCE_NAME`_VREF_ABUS1             (0x02u)
#define `$INSTANCE_NAME`_VREF_ABUS0             (0x01u)
//  ^-- AVAILABILITY VARIES WITH SC/CT POSITION --^
// SW7
#define `$INSTANCE_NAME`_VIN_VO                 (0x04u)
// SW8
//  v-- AVAILABILITY VARIES WITH SC/CT POSITION --v
#define `$INSTANCE_NAME`_VO_AG7                 (0x80u)
#define `$INSTANCE_NAME`_VO_AG6                 (0x40u)
#define `$INSTANCE_NAME`_VO_AG5                 (0x20u)
#define `$INSTANCE_NAME`_VO_AG4                 (0x10u)
#define `$INSTANCE_NAME`_VO_AG3                 (0x08u)
#define `$INSTANCE_NAME`_VO_AG2                 (0x04u)
#define `$INSTANCE_NAME`_VO_AG1                 (0x02u)
#define `$INSTANCE_NAME`_VO_AG0                 (0x01u)
//  ^-- AVAILABILITY VARIES WITH SC/CT POSITION --^
// SW10
//  v-- AVAILABILITY VARIES WITH SC/CT POSITION --v
#define `$INSTANCE_NAME`_VO_ABUS3               (0x08u)
#define `$INSTANCE_NAME`_VO_ABUS2               (0x04u)
#define `$INSTANCE_NAME`_VO_ABUS1               (0x02u)
#define `$INSTANCE_NAME`_VO_ABUS0               (0x01u)
//  ^-- AVAILABILITY VARIES WITH SC/CT POSITION --^

// WRK
// *************** MASKS ****************
// SR
#define `$INSTANCE_NAME`_SC3_MODOUT_MASK        (0x08u)
#define `$INSTANCE_NAME`_SC2_MODOUT_MASK        (0x04u)
#define `$INSTANCE_NAME`_SC1_MODOUT_MASK        (0x02u)
#define `$INSTANCE_NAME`_SC0_MODOUT_MASK        (0x01u)
// MSK
#define `$INSTANCE_NAME`_SC3_MSK_MASK           (0x08u)
#define `$INSTANCE_NAME`_SC2_MSK_MASK           (0x04u)
#define `$INSTANCE_NAME`_SC1_MSK_MASK           (0x02u)
#define `$INSTANCE_NAME`_SC0_MSK_MASK           (0x01u)
// CMP INV
#define `$INSTANCE_NAME`_SC3_CMPINV_MASK        (0x08u)
#define `$INSTANCE_NAME`_SC2_CMPINV_MASK        (0x04u)
#define `$INSTANCE_NAME`_SC1_CMPINV_MASK        (0x02u)
#define `$INSTANCE_NAME`_SC0_CMPINV_MASK        (0x01u)
// CPTR
#define `$INSTANCE_NAME`_SC3_CPTR_MASK          (0x08u)
#define `$INSTANCE_NAME`_SC2_CPTR_MASK          (0x04u)
#define `$INSTANCE_NAME`_SC1_CPTR_MASK          (0x02u)
#define `$INSTANCE_NAME`_SC0_CPTR_MASK          (0x01u)

// *************** SHIFTS ****************
// SR
#define `$INSTANCE_NAME`_SC3_MODOUT_SHIFT       (3u)
#define `$INSTANCE_NAME`_SC2_MODOUT_SHIFT       (2u)
#define `$INSTANCE_NAME`_SC1_MODOUT_SHIFT       (1u)
#define `$INSTANCE_NAME`_SC0_MODOUT_SHIFT       (0u)
// MSK
#define `$INSTANCE_NAME`_SC3_MSK_SHIFT          (3u)
#define `$INSTANCE_NAME`_SC2_MSK_SHIFT          (2u)
#define `$INSTANCE_NAME`_SC1_MSK_SHIFT          (1u)
#define `$INSTANCE_NAME`_SC0_MSK_SHIFT          {0u)
// CMP INV
#define `$INSTANCE_NAME`_SC3_CMPINV_SHIFT       (3u)
#define `$INSTANCE_NAME`_SC2_CMPINV_SHIFT       (2u)
#define `$INSTANCE_NAME`_SC1_CMPINV_SHIFT       (1u)
#define `$INSTANCE_NAME`_SC0_CMPINV_SHIFT       (0u)
// CPTR
#define `$INSTANCE_NAME`_SC3_CPTR_SHIFT         (3u)
#define `$INSTANCE_NAME`_SC2_CPTR_SHIFT         (2u)
#define `$INSTANCE_NAME`_SC1_CPTR_SHIFT         (1u)
#define `$INSTANCE_NAME`_SC0_CPTR_SHIFT         (0u)


// *************** MODES ****************
// MSK
#define `$INSTANCE_NAME`_SC3_MSK_DISABLE        (0u)
#define `$INSTANCE_NAME`_SC3_MSK_ENABLE         (1u)
// CMP INV
#define `$INSTANCE_NAME`_SC3_CMPINV_NORMAL      (0u)
#define `$INSTANCE_NAME`_SC3_CMPINV_INVERT      (1u)
// CPTR
#define `$INSTANCE_NAME`_SC3_CPTR_EDGE          (0u)
#define `$INSTANCE_NAME`_SC3_CPTR_LEVEL         (1u)

/***************************************
*            Register Constants        
***************************************/

#endif
//[] END OF FILE