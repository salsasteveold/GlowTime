// ======================================================================
// RGB_LED_Matrix.v generated from TopDesign.cysch
// 01/11/2014 at 23:12
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PSOC4A 2
`define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17
`define CYDEV_CHIP_REV_PSOC4A_ES0 17
`define CYDEV_CHIP_DIE_PANTHER 3
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_PSOC5LP 4
`define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
`define CYDEV_CHIP_REV_PSOC5LP_ES0 0
`define CYDEV_CHIP_DIE_EXPECT 2
`define CYDEV_CHIP_REV_EXPECT 17
`define CYDEV_CHIP_DIE_ACTUAL 2
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_MEMBER_4A 2
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_MEMBER_5A 3
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_5B 4
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_FAMILY_USED 2
`define CYDEV_CHIP_MEMBER_USED 2
`define CYDEV_CHIP_REVISION_USED 17
// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// SCB_P4_v1_10(BitWidthReplacementStringRx=uint8, BitWidthReplacementStringTx=uint8, BufNum=1, Cond=#, EndCond=#endif, EzI2cBitWidthReplacementString=uint16, EzI2cClkFreqDes=1600, EzI2cClockFromTerm=false, EzI2cClockStretching=true, EzI2cDataRate=100, EzI2cIsPrimarySlaveAddressHex=true, EzI2cIsSecondarySlaveAddressHex=true, EzI2cMedianFilterEnable=true, EzI2cNumberOfAddresses=0, EzI2cOvsFactor=16, EzI2cPrimarySlaveAddress=8, EzI2cSecondarySlaveAddress=9, EzI2cSlaveAddressMask=254, EzI2cSubAddressSize=0, EzI2cWakeEnable=false, I2cAcceptAddress=false, I2cClkFreqDes=1600, I2cClockFromTerm=false, I2cDataRate=100, I2cIsSlaveAddressHex=true, I2cIsSlaveAddressMaskHex=true, I2cMedianFilterEnable=true, I2cMode=1, I2cOvsFactor=16, I2cOvsFactorHigh=8, I2cOvsFactorLow=8, I2cSlaveAddress=8, I2cSlaveAddressMask=254, I2cWakeEnable=false, RemoveI2cPins=true, RemoveMisoSdaTx=true, RemoveMosiSclRx=true, RemoveMosiSclRxWake=true, RemoveScbClk=false, RemoveScbIrq=true, RemoveSpiMasterPins=true, RemoveSpiMasterSs0Pin=true, RemoveSpiMasterSs1Pin=true, RemoveSpiMasterSs2Pin=true, RemoveSpiMasterSs3Pin=true, RemoveSpiSclk=true, RemoveSpiSlavePins=true, RemoveSpiSs0=true, RemoveSpiSs1=true, RemoveSpiSs2=true, RemoveSpiSs3=true, RemoveUartRxPin=false, RemoveUartRxTxPin=true, RemoveUartRxWake=true, RemoveUartRxWakeupIrq=true, RemoveUartTxPin=false, ScbClkFreqDes=1382.4, ScbClockSelect=1, ScbClockTermEnable=false, ScbInterruptTermEnable=false, ScbMisoSdaTxEnable=true, ScbMode=4, ScbModeHw=2, ScbMosiSclRxEnable=true, ScbRxWakeIrqEnable=false, ScbSclkEnable=false, ScbSs0Enable=false, ScbSs1Enable=false, ScbSs2Enable=false, ScbSs3Enable=false, SpiBitRate=1000, SpiBitsOrder=1, SpiClkFreqDes=16000, SpiClockFromTerm=false, SpiInterruptMode=1, SpiIntrMasterSpiDone=false, SpiIntrRxFull=false, SpiIntrRxNotEmpty=false, SpiIntrRxOverflow=false, SpiIntrRxTrigger=false, SpiIntrRxUnderflow=false, SpiIntrSlaveBusError=false, SpiIntrTxEmpty=false, SpiIntrTxNotFull=false, SpiIntrTxOverflow=false, SpiIntrTxTrigger=false, SpiIntrTxUnderflow=false, SpiLateMisoSampleEnable=false, SpiMedianFilterEnable=false, SpiMode=0, SpiNumberOfRxDataBits=8, SpiNumberOfSelectLines=1, SpiNumberOfTxDataBits=8, SpiOvsFactor=16, SpiRxBufferSize=8, SpiRxIntrMask=0, SpiRxTriggerLevel=7, SpiSclkMode=0, SpiSubMode=0, SpiTransferSeparation=1, SpiTxBufferSize=8, SpiTxIntrMask=0, SpiTxTriggerLevel=0, SpiWakeEnable=false, UartClkFreqDes=1382.4, UartClockFromTerm=false, UartDataRate=115200, UartDirection=3, UartDropOnFrameErr=false, UartDropOnParityErr=false, UartInterruptMode=0, UartIntrRxFrameErr=false, UartIntrRxFull=false, UartIntrRxNotEmpty=false, UartIntrRxOverflow=false, UartIntrRxParityErr=false, UartIntrRxTrigger=false, UartIntrRxUnderflow=false, UartIntrTxEmpty=false, UartIntrTxNotFull=false, UartIntrTxOverflow=false, UartIntrTxTrigger=false, UartIntrTxUartDone=false, UartIntrTxUartLostArb=false, UartIntrTxUartNack=false, UartIntrTxUnderflow=false, UartIrdaLowPower=false, UartIrdaPolarity=0, UartMedianFilterEnable=false, UartMpEnable=false, UartMpRxAcceptAddress=false, UartMpRxAddress=2, UartMpRxAddressMask=255, UartNumberOfDataBits=8, UartNumberOfStopBits=2, UartOvsFactor=12, UartParityType=2, UartRxBufferSize=8, UartRxEnable=true, UartRxIntrMask=0, UartRxTriggerLevel=7, UartSmCardRetryOnNack=false, UartSubMode=0, UartTxBufferSize=8, UartTxEnable=true, UartTxIntrMask=0, UartTxTriggerLevel=0, UartWakeEnable=false, CY_COMPONENT_NAME=SCB_P4_v1_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=UART, CY_INSTANCE_SHORT_NAME=UART, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=UART, )
module SCB_P4_v1_10_0 (
    sclk,
    interrupt,
    clock);
    output      sclk;
    output      interrupt;
    input       clock;


          wire [3:0] ss;
          wire  Net_459;
          wire  Net_452;
          wire  Net_373;
          wire  Net_433;
          wire  Net_449;
          wire  Net_436;
          wire  uncfg_rx_irq;
          wire  Net_427;
          wire  Net_453;
          wire  Net_152;
          wire  Net_150;
          wire  Net_149;
          wire  Net_84;
          wire  Net_88;
          wire  Net_458;
          wire  Net_430;
          wire  Net_237;
          wire  Net_413;
          wire  Net_244;
          wire  Net_422;
          wire  rx_irq;
          wire  Net_379;
          wire  Net_409;
          wire  Net_246;
          wire  Net_252;
          wire  Net_245;
          wire  Net_243;
          wire  Net_89;
          wire  Net_284;
          wire  Net_416;
          wire  Net_387;
          wire  Net_151;
          wire  Net_410;

    cy_m0s8_scb_v1_0 SCB (
        .rx(Net_244),
        .miso_m(Net_410),
        .clock(Net_237),
        .select_m(ss[3:0]),
        .sclk_m(Net_88),
        .mosi_s(Net_89),
        .select_s(Net_430),
        .sclk_s(Net_413),
        .mosi_m(Net_84),
        .scl(Net_149),
        .sda(Net_150),
        .tx(Net_151),
        .miso_s(Net_152),
        .interrupt(interrupt));
    defparam SCB.scb_mode = 2;

	wire [0:0] tmpOE__rx_net;
	wire [0:0] tmpIO_0__rx_net;
	wire [0:0] tmpINTERRUPT_0__rx_net;
	electrical [0:0] tmpSIOVREF__rx_net;

	cy_psoc3_pins_v1_10
		#(.id("1ec6effd-8f31-4dd5-a825-0c49238d524e/78e33e5d-45ea-4b75-88d5-73274e8a7ce4"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b0),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		rx
		 (.oe(tmpOE__rx_net),
		  .y({1'b0}),
		  .fb({Net_379}),
		  .io({tmpIO_0__rx_net[0:0]}),
		  .siovref(tmpSIOVREF__rx_net),
		  .interrupt({tmpINTERRUPT_0__rx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__rx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("1ec6effd-8f31-4dd5-a825-0c49238d524e/29084e80-7594-46a9-94af-639e276dfc5f"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("723379629.62963"),
		  .is_direct(0),
		  .is_digital(0))
		SCBCLK
		 (.clock_out(Net_284));



    assign sclk = Net_284 | Net_427;

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_427));

	wire [0:0] tmpOE__tx_net;
	wire [0:0] tmpFB_0__tx_net;
	wire [0:0] tmpIO_0__tx_net;
	wire [0:0] tmpINTERRUPT_0__tx_net;
	electrical [0:0] tmpSIOVREF__tx_net;

	cy_psoc3_pins_v1_10
		#(.id("1ec6effd-8f31-4dd5-a825-0c49238d524e/23b8206d-1c77-4e61-be4a-b4037d5de5fc"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		tx
		 (.oe(tmpOE__tx_net),
		  .y({Net_151}),
		  .fb({tmpFB_0__tx_net[0:0]}),
		  .io({tmpIO_0__tx_net[0:0]}),
		  .siovref(tmpSIOVREF__tx_net),
		  .interrupt({tmpINTERRUPT_0__tx_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__tx_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	// miso_m_VM (cy_virtualmux_v1_0)
	assign Net_410 = Net_436;

	// mosi_s_VM (cy_virtualmux_v1_0)
	assign Net_89 = Net_449;

	// sclk_s_VM (cy_virtualmux_v1_0)
	assign Net_413 = Net_433;

	// clock_VM (cy_virtualmux_v1_0)
	assign Net_237 = Net_284;

	// rx_wake_VM (cy_virtualmux_v1_0)
	assign Net_373 = uncfg_rx_irq;

	// rx_VM (cy_virtualmux_v1_0)
	assign Net_244 = Net_379;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_433));

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_436));

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_449));

    ZeroTerminal ZeroTerminal_4 (
        .z(Net_452));

	// select_s_VM (cy_virtualmux_v1_0)
	assign Net_430 = Net_459;

    ZeroTerminal ZeroTerminal_5 (
        .z(Net_459));



endmodule

// Component: CyControlReg_v1_70
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_70"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_70\CyControlReg_v1_70.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_70"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_70\CyControlReg_v1_70.v"
`endif

// KEES_PinHelper_v1_1(CY_COMPONENT_NAME=KEES_PinHelper_v1_1, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=KEES_PinHelper_1, CY_INSTANCE_SHORT_NAME=KEES_PinHelper_1, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=1, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=KEES_PinHelper_1, )
module KEES_PinHelper_v1_1_1 ;





endmodule

// PSoC_4_Pioneer_Kit(ShowPins=true, CY_COMPONENT_NAME=PSoC_4_Pioneer_Kit, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=PSoC_4_Pioneer_Kit_1, CY_INSTANCE_SHORT_NAME=PSoC_4_Pioneer_Kit_1, CY_MAJOR_VERSION=0, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=PSoC_4_Pioneer_Kit_1, )
module PSoC_4_Pioneer_Kit_2 (
    Terminal_1,
    Terminal_2,
    Terminal_3,
    Terminal_4,
    Terminal_5,
    Terminal_6,
    Terminal_7,
    Terminal_8,
    Terminal_9,
    Terminal_10,
    Terminal_11,
    Terminal_12,
    Terminal_13,
    Terminal_14,
    Terminal_15,
    Terminal_16,
    Terminal_17,
    Terminal_18,
    Terminal_19,
    Terminal_20,
    Terminal_21,
    Terminal_22,
    Terminal_23,
    Terminal_24,
    Terminal_25,
    Terminal_26,
    Terminal_27,
    Terminal_28,
    Terminal_29,
    Terminal_30,
    Terminal_31,
    Terminal_32,
    Terminal_33,
    Terminal_34,
    Terminal_35,
    Terminal_36,
    Terminal_37,
    Terminal_38,
    Terminal_39,
    Terminal_40,
    Terminal_41,
    Terminal_42,
    Terminal_43,
    Terminal_44,
    Terminal_45,
    Terminal_46,
    Terminal_47,
    Terminal_48,
    Terminal_49,
    Terminal_50,
    Terminal_51,
    Terminal_52,
    Terminal_53,
    Terminal_54,
    Terminal_55,
    Terminal_56,
    Terminal_57,
    Terminal_58,
    Terminal_59,
    Terminal_60,
    Terminal_61,
    Terminal_62,
    Terminal_63,
    Terminal_64,
    Terminal_65,
    Terminal_66,
    Terminal_67,
    Terminal_68);
    inout       Terminal_1;
    electrical  Terminal_1;
    inout       Terminal_2;
    electrical  Terminal_2;
    inout       Terminal_3;
    electrical  Terminal_3;
    inout       Terminal_4;
    electrical  Terminal_4;
    inout       Terminal_5;
    electrical  Terminal_5;
    inout       Terminal_6;
    electrical  Terminal_6;
    inout       Terminal_7;
    electrical  Terminal_7;
    inout       Terminal_8;
    electrical  Terminal_8;
    inout       Terminal_9;
    electrical  Terminal_9;
    inout       Terminal_10;
    electrical  Terminal_10;
    inout       Terminal_11;
    electrical  Terminal_11;
    inout       Terminal_12;
    electrical  Terminal_12;
    inout       Terminal_13;
    electrical  Terminal_13;
    inout       Terminal_14;
    electrical  Terminal_14;
    inout       Terminal_15;
    electrical  Terminal_15;
    inout       Terminal_16;
    electrical  Terminal_16;
    inout       Terminal_17;
    electrical  Terminal_17;
    inout       Terminal_18;
    electrical  Terminal_18;
    inout       Terminal_19;
    electrical  Terminal_19;
    inout       Terminal_20;
    electrical  Terminal_20;
    inout       Terminal_21;
    electrical  Terminal_21;
    inout       Terminal_22;
    electrical  Terminal_22;
    inout       Terminal_23;
    electrical  Terminal_23;
    inout       Terminal_24;
    electrical  Terminal_24;
    inout       Terminal_25;
    electrical  Terminal_25;
    inout       Terminal_26;
    electrical  Terminal_26;
    inout       Terminal_27;
    electrical  Terminal_27;
    inout       Terminal_28;
    electrical  Terminal_28;
    inout       Terminal_29;
    electrical  Terminal_29;
    inout       Terminal_30;
    electrical  Terminal_30;
    inout       Terminal_31;
    electrical  Terminal_31;
    inout       Terminal_32;
    electrical  Terminal_32;
    inout       Terminal_33;
    electrical  Terminal_33;
    inout       Terminal_34;
    electrical  Terminal_34;
    inout       Terminal_35;
    electrical  Terminal_35;
    inout       Terminal_36;
    electrical  Terminal_36;
    inout       Terminal_37;
    electrical  Terminal_37;
    inout       Terminal_38;
    electrical  Terminal_38;
    inout       Terminal_39;
    electrical  Terminal_39;
    inout       Terminal_40;
    electrical  Terminal_40;
    inout       Terminal_41;
    electrical  Terminal_41;
    inout       Terminal_42;
    electrical  Terminal_42;
    inout       Terminal_43;
    electrical  Terminal_43;
    inout       Terminal_44;
    electrical  Terminal_44;
    inout       Terminal_45;
    electrical  Terminal_45;
    inout       Terminal_46;
    electrical  Terminal_46;
    inout       Terminal_47;
    electrical  Terminal_47;
    inout       Terminal_48;
    electrical  Terminal_48;
    inout       Terminal_49;
    electrical  Terminal_49;
    inout       Terminal_50;
    electrical  Terminal_50;
    inout       Terminal_51;
    electrical  Terminal_51;
    inout       Terminal_52;
    electrical  Terminal_52;
    inout       Terminal_53;
    electrical  Terminal_53;
    inout       Terminal_54;
    electrical  Terminal_54;
    inout       Terminal_55;
    electrical  Terminal_55;
    inout       Terminal_56;
    electrical  Terminal_56;
    inout       Terminal_57;
    electrical  Terminal_57;
    inout       Terminal_58;
    electrical  Terminal_58;
    inout       Terminal_59;
    electrical  Terminal_59;
    inout       Terminal_60;
    electrical  Terminal_60;
    inout       Terminal_61;
    electrical  Terminal_61;
    inout       Terminal_62;
    electrical  Terminal_62;
    inout       Terminal_63;
    electrical  Terminal_63;
    inout       Terminal_64;
    electrical  Terminal_64;
    inout       Terminal_65;
    electrical  Terminal_65;
    inout       Terminal_66;
    electrical  Terminal_66;
    inout       Terminal_67;
    electrical  Terminal_67;
    inout       Terminal_68;
    electrical  Terminal_68;





endmodule

// Component: LED_Matrix_v1_00
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "..\LED_Matrix_v1_00"
`include "..\LED_Matrix_v1_00\LED_Matrix_v1_00.v"
`else
`define CY_BLK_DIR "C:\Users\Steve\Documents\Git\GlowTime\RGB_LED_Matrix.cydsn\LED_Matrix_v1_00"
`include "C:\Users\Steve\Documents\Git\GlowTime\RGB_LED_Matrix.cydsn\LED_Matrix_v1_00\LED_Matrix_v1_00.v"
`endif

// top
module top ;

          wire  Net_7615;
          wire  Net_7614;
          wire  Net_7613;
          wire  Net_7612;
          wire  Net_7611;
          wire  Net_7609;
          wire  Net_7608;
          wire  Net_7607;
          wire  Net_7606;
          wire  Net_7605;
    electrical  Net_7604;
    electrical  Net_7603;
    electrical  Net_7602;
    electrical  Net_7601;
    electrical  Net_7600;
    electrical  Net_7599;
    electrical  Net_7598;
    electrical  Net_7597;
    electrical  Net_7596;
    electrical  Net_7595;
    electrical  Net_7594;
    electrical  Net_7593;
    electrical  Net_7592;
    electrical  Net_7591;
    electrical  Net_7590;
    electrical  Net_7588;
    electrical  Net_7587;
    electrical  Net_7586;
    electrical  Net_7585;
    electrical  Net_7584;
    electrical  Net_7583;
    electrical  Net_7582;
    electrical  Net_7581;
    electrical  Net_7580;
    electrical  Net_7579;
    electrical  Net_7578;
    electrical  Net_7577;
    electrical  Net_7576;
    electrical  Net_7575;
    electrical  Net_7574;
    electrical  Net_7573;
    electrical  Net_7572;
    electrical  Net_7571;
    electrical  Net_7570;
    electrical  Net_7569;
    electrical  Net_7568;
    electrical  Net_7567;
    electrical  Net_7566;
    electrical  Net_7565;
    electrical  Net_7564;
    electrical  Net_7563;
    electrical  Net_7562;
    electrical  Net_7561;
    electrical  Net_7560;
    electrical  Net_7559;
    electrical  Net_7558;
    electrical  Net_7557;
    electrical  Net_7556;
    electrical  Net_7555;
          wire  lat;
    electrical  Net_7554;
    electrical  Net_7553;
    electrical  Net_7552;
    electrical  Net_7551;
    electrical  Net_7550;
    electrical  Net_7549;
          wire  Net_7548;
          wire  Net_7547;
          wire  Net_7546;
          wire  Net_7545;
          wire  Net_7544;
    electrical  done;
          wire  Net_7543;
          wire  Net_7542;
          wire  Net_7640;
          wire  Net_7636;
          wire  Net_7635;
          wire  Net_7634;
          wire  Net_7538;
          wire  Net_7537;
          wire  Net_7639;
          wire  Net_7149;
          wire  Net_7153;
          wire  Net_7152;
          wire  Net_5619;
    electrical  Net_221;
    electrical  Net_88;
    electrical  Net_11;
    electrical  Net_178;
    electrical  Net_176;
    electrical  Net_174;
    electrical  Net_172;
    electrical  Net_16;
    electrical  Net_15;
    electrical  Net_14;
    electrical  Net_13;
    electrical  Net_12;

	wire [0:0] tmpOE__P2_0_A_net;
	wire [0:0] tmpFB_0__P2_0_A_net;
	wire [0:0] tmpIO_0__P2_0_A_net;
	wire [0:0] tmpINTERRUPT_0__P2_0_A_net;
	electrical [0:0] tmpSIOVREF__P2_0_A_net;

	cy_psoc3_pins_v1_10
		#(.id("75d1b22d-84d9-4486-be37-a4550a9263f0"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_0_A
		 (.oe(tmpOE__P2_0_A_net),
		  .y({Net_7149}),
		  .fb({tmpFB_0__P2_0_A_net[0:0]}),
		  .io({tmpIO_0__P2_0_A_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_0_A_net),
		  .interrupt({tmpINTERRUPT_0__P2_0_A_net[0:0]}),
		  .annotation({Net_178}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_0_A_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P2_6_CLK_net;
	wire [0:0] tmpFB_0__P2_6_CLK_net;
	wire [0:0] tmpIO_0__P2_6_CLK_net;
	wire [0:0] tmpINTERRUPT_0__P2_6_CLK_net;
	electrical [0:0] tmpSIOVREF__P2_6_CLK_net;

	cy_psoc3_pins_v1_10
		#(.id("060f36b4-9439-49c1-b330-3e5a1d41d4fe"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_6_CLK
		 (.oe(tmpOE__P2_6_CLK_net),
		  .y({Net_7537}),
		  .fb({tmpFB_0__P2_6_CLK_net[0:0]}),
		  .io({tmpIO_0__P2_6_CLK_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_6_CLK_net),
		  .interrupt({tmpINTERRUPT_0__P2_6_CLK_net[0:0]}),
		  .annotation({Net_88}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_6_CLK_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P3_6_OE_net;
	wire [0:0] tmpFB_0__P3_6_OE_net;
	wire [0:0] tmpIO_0__P3_6_OE_net;
	wire [0:0] tmpINTERRUPT_0__P3_6_OE_net;
	electrical [0:0] tmpSIOVREF__P3_6_OE_net;

	cy_psoc3_pins_v1_10
		#(.id("9ebb7f97-ada4-4b1c-967b-6840fc72ca16"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P3_6_OE
		 (.oe(tmpOE__P3_6_OE_net),
		  .y({Net_7538}),
		  .fb({tmpFB_0__P3_6_OE_net[0:0]}),
		  .io({tmpIO_0__P3_6_OE_net[0:0]}),
		  .siovref(tmpSIOVREF__P3_6_OE_net),
		  .interrupt({tmpINTERRUPT_0__P3_6_OE_net[0:0]}),
		  .annotation({Net_221}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P3_6_OE_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    SCB_P4_v1_10_0 UART (
        .sclk(Net_7634),
        .interrupt(Net_7635),
        .clock(1'b0));

    CyControlReg_v1_70 CR_Addr (
        .control_1(Net_7152),
        .control_2(Net_7153),
        .control_3(Net_7640),
        .control_0(Net_7149),
        .control_4(Net_7542),
        .control_5(Net_7543),
        .control_6(Net_7544),
        .control_7(Net_7545),
        .clock(1'b0),
        .reset(1'b0));
    defparam CR_Addr.Bit0Mode = 0;
    defparam CR_Addr.Bit1Mode = 0;
    defparam CR_Addr.Bit2Mode = 0;
    defparam CR_Addr.Bit3Mode = 0;
    defparam CR_Addr.Bit4Mode = 0;
    defparam CR_Addr.Bit5Mode = 0;
    defparam CR_Addr.Bit6Mode = 0;
    defparam CR_Addr.Bit7Mode = 0;
    defparam CR_Addr.BitValue = 0;
    defparam CR_Addr.BusDisplay = 0;
    defparam CR_Addr.ExtrReset = 0;
    defparam CR_Addr.NumOutputs = 4;

    KEES_PinHelper_v1_1_1 KEES_PinHelper_1 ();

	wire [0:0] tmpOE__P2_1_B_net;
	wire [0:0] tmpFB_0__P2_1_B_net;
	wire [0:0] tmpIO_0__P2_1_B_net;
	wire [0:0] tmpINTERRUPT_0__P2_1_B_net;
	electrical [0:0] tmpSIOVREF__P2_1_B_net;

	cy_psoc3_pins_v1_10
		#(.id("7ebfc76c-7a0d-49dd-b6c4-d2508f903ec1"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_1_B
		 (.oe(tmpOE__P2_1_B_net),
		  .y({Net_7152}),
		  .fb({tmpFB_0__P2_1_B_net[0:0]}),
		  .io({tmpIO_0__P2_1_B_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_1_B_net),
		  .interrupt({tmpINTERRUPT_0__P2_1_B_net[0:0]}),
		  .annotation({Net_176}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_1_B_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P2_2_C_net;
	wire [0:0] tmpFB_0__P2_2_C_net;
	wire [0:0] tmpIO_0__P2_2_C_net;
	wire [0:0] tmpINTERRUPT_0__P2_2_C_net;
	electrical [0:0] tmpSIOVREF__P2_2_C_net;

	cy_psoc3_pins_v1_10
		#(.id("284f9716-7cda-497d-aaf8-7c9ced6d8217"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_2_C
		 (.oe(tmpOE__P2_2_C_net),
		  .y({Net_7153}),
		  .fb({tmpFB_0__P2_2_C_net[0:0]}),
		  .io({tmpIO_0__P2_2_C_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_2_C_net),
		  .interrupt({tmpINTERRUPT_0__P2_2_C_net[0:0]}),
		  .annotation({Net_174}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_2_C_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P2_7_B2_net;
	wire [0:0] tmpFB_0__P2_7_B2_net;
	wire [0:0] tmpIO_0__P2_7_B2_net;
	wire [0:0] tmpINTERRUPT_0__P2_7_B2_net;
	electrical [0:0] tmpSIOVREF__P2_7_B2_net;

	cy_psoc3_pins_v1_10
		#(.id("982dc5d3-03f9-43bb-9175-9049f841e191"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_7_B2
		 (.oe(tmpOE__P2_7_B2_net),
		  .y({Net_7548}),
		  .fb({tmpFB_0__P2_7_B2_net[0:0]}),
		  .io({tmpIO_0__P2_7_B2_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_7_B2_net),
		  .interrupt({tmpINTERRUPT_0__P2_7_B2_net[0:0]}),
		  .annotation({Net_16}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_7_B2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P2_3_LAT_net;
	wire [0:0] tmpFB_0__P2_3_LAT_net;
	wire [0:0] tmpIO_0__P2_3_LAT_net;
	wire [0:0] tmpINTERRUPT_0__P2_3_LAT_net;
	electrical [0:0] tmpSIOVREF__P2_3_LAT_net;

	cy_psoc3_pins_v1_10
		#(.id("6092f1c0-3e71-4097-b963-ebd0e0c40ed1"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_3_LAT
		 (.oe(tmpOE__P2_3_LAT_net),
		  .y({lat}),
		  .fb({tmpFB_0__P2_3_LAT_net[0:0]}),
		  .io({tmpIO_0__P2_3_LAT_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_3_LAT_net),
		  .interrupt({tmpINTERRUPT_0__P2_3_LAT_net[0:0]}),
		  .annotation({Net_172}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_3_LAT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    PSoC_4_Pioneer_Kit_2 PSoC_4_Pioneer_Kit_1 (
        .Terminal_20(Net_7549),
        .Terminal_21(Net_7550),
        .Terminal_22(Net_7551),
        .Terminal_23(Net_7552),
        .Terminal_24(Net_7553),
        .Terminal_25(Net_7554),
        .Terminal_26(Net_7555),
        .Terminal_27(Net_7556),
        .Terminal_18(Net_7557),
        .Terminal_34(Net_7558),
        .Terminal_35(Net_11),
        .Terminal_36(Net_12),
        .Terminal_37(Net_13),
        .Terminal_38(Net_14),
        .Terminal_39(Net_15),
        .Terminal_40(Net_16),
        .Terminal_41(Net_88),
        .Terminal_42(Net_221),
        .Terminal_43(Net_7559),
        .Terminal_44(Net_7560),
        .Terminal_45(Net_7561),
        .Terminal_46(Net_7562),
        .Terminal_47(Net_7563),
        .Terminal_48(Net_7564),
        .Terminal_49(Net_7565),
        .Terminal_50(Net_7566),
        .Terminal_57(Net_7567),
        .Terminal_59(Net_7568),
        .Terminal_61(Net_7569),
        .Terminal_63(Net_7570),
        .Terminal_65(Net_7571),
        .Terminal_67(Net_7572),
        .Terminal_68(Net_7573),
        .Terminal_66(Net_7574),
        .Terminal_64(Net_7575),
        .Terminal_62(Net_7576),
        .Terminal_60(Net_7577),
        .Terminal_58(Net_7578),
        .Terminal_33(Net_7579),
        .Terminal_32(Net_7580),
        .Terminal_31(Net_7581),
        .Terminal_30(Net_7582),
        .Terminal_29(Net_7583),
        .Terminal_28(Net_7584),
        .Terminal_19(Net_178),
        .Terminal_17(Net_7585),
        .Terminal_14(Net_7586),
        .Terminal_16(Net_176),
        .Terminal_15(Net_174),
        .Terminal_13(Net_7587),
        .Terminal_10(Net_7588),
        .Terminal_12(Net_172),
        .Terminal_11(done),
        .Terminal_9(Net_7590),
        .Terminal_6(Net_7591),
        .Terminal_8(Net_7592),
        .Terminal_7(Net_7593),
        .Terminal_5(Net_7594),
        .Terminal_2(Net_7595),
        .Terminal_4(Net_7596),
        .Terminal_3(Net_7597),
        .Terminal_1(Net_7598),
        .Terminal_55(Net_7599),
        .Terminal_56(Net_7600),
        .Terminal_54(Net_7601),
        .Terminal_53(Net_7602),
        .Terminal_51(Net_7603),
        .Terminal_52(Net_7604));

	wire [0:0] tmpOE__P0_7_R1_net;
	wire [0:0] tmpFB_0__P0_7_R1_net;
	wire [0:0] tmpIO_0__P0_7_R1_net;
	wire [0:0] tmpINTERRUPT_0__P0_7_R1_net;
	electrical [0:0] tmpSIOVREF__P0_7_R1_net;

	cy_psoc3_pins_v1_10
		#(.id("52f31aa9-2f0a-497d-9a1f-1424095e13e6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P0_7_R1
		 (.oe(tmpOE__P0_7_R1_net),
		  .y({Net_7605}),
		  .fb({tmpFB_0__P0_7_R1_net[0:0]}),
		  .io({tmpIO_0__P0_7_R1_net[0:0]}),
		  .siovref(tmpSIOVREF__P0_7_R1_net),
		  .interrupt({tmpINTERRUPT_0__P0_7_R1_net[0:0]}),
		  .annotation({Net_11}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P0_7_R1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P3_7_G1_net;
	wire [0:0] tmpFB_0__P3_7_G1_net;
	wire [0:0] tmpIO_0__P3_7_G1_net;
	wire [0:0] tmpINTERRUPT_0__P3_7_G1_net;
	electrical [0:0] tmpSIOVREF__P3_7_G1_net;

	cy_psoc3_pins_v1_10
		#(.id("072c43bd-b004-4237-9373-665572e73a21"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P3_7_G1
		 (.oe(tmpOE__P3_7_G1_net),
		  .y({Net_7606}),
		  .fb({tmpFB_0__P3_7_G1_net[0:0]}),
		  .io({tmpIO_0__P3_7_G1_net[0:0]}),
		  .siovref(tmpSIOVREF__P3_7_G1_net),
		  .interrupt({tmpINTERRUPT_0__P3_7_G1_net[0:0]}),
		  .annotation({Net_12}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P3_7_G1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P1_0_G2_net;
	wire [0:0] tmpFB_0__P1_0_G2_net;
	wire [0:0] tmpIO_0__P1_0_G2_net;
	wire [0:0] tmpINTERRUPT_0__P1_0_G2_net;
	electrical [0:0] tmpSIOVREF__P1_0_G2_net;

	cy_psoc3_pins_v1_10
		#(.id("5b353b43-9cea-4258-a34f-292bc4eb90fa"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P1_0_G2
		 (.oe(tmpOE__P1_0_G2_net),
		  .y({Net_7607}),
		  .fb({tmpFB_0__P1_0_G2_net[0:0]}),
		  .io({tmpIO_0__P1_0_G2_net[0:0]}),
		  .siovref(tmpSIOVREF__P1_0_G2_net),
		  .interrupt({tmpINTERRUPT_0__P1_0_G2_net[0:0]}),
		  .annotation({Net_15}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P1_0_G2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P0_0_B1_net;
	wire [0:0] tmpFB_0__P0_0_B1_net;
	wire [0:0] tmpIO_0__P0_0_B1_net;
	wire [0:0] tmpINTERRUPT_0__P0_0_B1_net;
	electrical [0:0] tmpSIOVREF__P0_0_B1_net;

	cy_psoc3_pins_v1_10
		#(.id("b50cefd4-3de6-4318-987d-b8598618ffd5"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P0_0_B1
		 (.oe(tmpOE__P0_0_B1_net),
		  .y({Net_7608}),
		  .fb({tmpFB_0__P0_0_B1_net[0:0]}),
		  .io({tmpIO_0__P0_0_B1_net[0:0]}),
		  .siovref(tmpSIOVREF__P0_0_B1_net),
		  .interrupt({tmpINTERRUPT_0__P0_0_B1_net[0:0]}),
		  .annotation({Net_13}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P0_0_B1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P3_5_R2_net;
	wire [0:0] tmpFB_0__P3_5_R2_net;
	wire [0:0] tmpIO_0__P3_5_R2_net;
	wire [0:0] tmpINTERRUPT_0__P3_5_R2_net;
	electrical [0:0] tmpSIOVREF__P3_5_R2_net;

	cy_psoc3_pins_v1_10
		#(.id("198ebeb7-39f0-499a-9fa5-ec6022a797d6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P3_5_R2
		 (.oe(tmpOE__P3_5_R2_net),
		  .y({Net_7609}),
		  .fb({tmpFB_0__P3_5_R2_net[0:0]}),
		  .io({tmpIO_0__P3_5_R2_net[0:0]}),
		  .siovref(tmpSIOVREF__P3_5_R2_net),
		  .interrupt({tmpINTERRUPT_0__P3_5_R2_net[0:0]}),
		  .annotation({Net_14}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P3_5_R2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P2_4_done_net;
	wire [0:0] tmpFB_0__P2_4_done_net;
	wire [0:0] tmpIO_0__P2_4_done_net;
	wire [0:0] tmpINTERRUPT_0__P2_4_done_net;
	electrical [0:0] tmpSIOVREF__P2_4_done_net;

	cy_psoc3_pins_v1_10
		#(.id("c2081a0c-63d9-4627-b938-24955bc459a8"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b1),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		P2_4_done
		 (.oe(tmpOE__P2_4_done_net),
		  .y({Net_7639}),
		  .fb({tmpFB_0__P2_4_done_net[0:0]}),
		  .io({tmpIO_0__P2_4_done_net[0:0]}),
		  .siovref(tmpSIOVREF__P2_4_done_net),
		  .interrupt({tmpINTERRUPT_0__P2_4_done_net[0:0]}),
		  .annotation({done}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P2_4_done_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b00))
		isr_2
		 (.int_signal(Net_7639));



	cy_clock_v1_0
		#(.id("eadeeaec-9d24-4202-9713-f8f99939158a"),
		  .source_clock_id("413DE2EF-D9F2-4233-A808-DFAF137FD877"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(0))
		Clock_3
		 (.clock_out(Net_5619));


    LED_Matrix_v1_00 LED_Matrix_1 (
        .clock(Net_5619),
        .resetHW(1'b0),
        .State_0(Net_7613),
        .State_1(Net_7614),
        .State_2(Net_7615),
        .r1(Net_7605),
        .b1(Net_7608),
        .done(Net_7639),
        .o_clk(Net_7537),
        .g1(Net_7606),
        .r2(Net_7609),
        .b2(Net_7548),
        .g2(Net_7607),
        .oe(Net_7538),
        .lat(lat));
    defparam LED_Matrix_1.A0_init_a = 0;
    defparam LED_Matrix_1.A1_init_a = 0;
    defparam LED_Matrix_1.D0_init_a = 0;
    defparam LED_Matrix_1.D1_init_a = 0;



endmodule

