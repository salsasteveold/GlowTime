// ======================================================================
// RGB_LED_Matrix.v generated from TopDesign.cysch
// 02/04/2014 at 23:48
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
module KEES_PinHelper_v1_1_0 ;





endmodule

// PSoC_4_Pioneer_Kit(ShowPins=true, CY_COMPONENT_NAME=PSoC_4_Pioneer_Kit, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=PSoC_4_Pioneer_Kit_1, CY_INSTANCE_SHORT_NAME=PSoC_4_Pioneer_Kit_1, CY_MAJOR_VERSION=0, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=PSoC_4_Pioneer_Kit_1, )
module PSoC_4_Pioneer_Kit_1 (
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

// Component: cy_analog_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_analog_virtualmux_v1_0\cy_analog_virtualmux_v1_0.v"
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

// Component: Bus_Connect_v1_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\Bus_Connect_v1_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\Bus_Connect_v1_10\Bus_Connect_v1_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\Bus_Connect_v1_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.0\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\Bus_Connect_v1_10\Bus_Connect_v1_10.v"
`endif

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

// ADC_SAR_SEQ_P4_v1_10(AdcAClock=6, AdcAdjust=0, AdcAlternateResolution=0, AdcAvgMode=1, AdcAvgSamplesNum=0, AdcBClock=4, AdcCClock=4, AdcChannelsEnConf=1, AdcChannelsModeConf=0, AdcClock=1, AdcClockFrequency=1200000, AdcCompareMode=0, AdcDataFormatJustification=0, AdcDClock=4, AdcDifferentialResultFormat=0, AdcHighLimit=4095, AdcInjChannelEnabled=false, AdcInputBufGain=0, AdcLowLimit=0, AdcMaxResolution=12, AdcSampleMode=0, AdcSarMuxChannelConfig=0, AdcSequencedChannels=1, AdcSingleEndedNegativeInput=0, AdcSingleResultFormat=1, AdcSymbolHasSingleEndedInputChannel=false, AdcTotalChannels=1, AdcVrefSelect=1, AdcVrefVoltage_mV=1650, rm_int=false, SeqChannelsConfigTable=<?xml version="1.0" encoding="utf-16"?><CyChannelsConfigTable xmlns:Version="1_10"><m_channelsConfigTable><CyChannelsConfigTableRow><m_enabled>false</m_enabled><m_resolution>Twelve</m_resolution><m_mode>Diff</m_mode><m_averaged>false</m_averaged><m_acqTime>AClocks</m_acqTime><m_limitsDetectIntrEnabled>false</m_limitsDetectIntrEnabled><m_saturationIntrEnabled>false</m_saturationIntrEnabled></CyChannelsConfigTableRow><CyChannelsConfigTableRow><m_enabled>true</m_enabled><m_resolution>Twelve</m_resolution><m_mode>Single</m_mode><m_averaged>true</m_averaged><m_acqTime>AClocks</m_acqTime><m_limitsDetectIntrEnabled>false</m_limitsDetectIntrEnabled><m_saturationIntrEnabled>false</m_saturationIntrEnabled></CyChannelsConfigTableRow></m_channelsConfigTable></CyChannelsConfigTable>, CY_COMPONENT_NAME=ADC_SAR_SEQ_P4_v1_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=ADC, CY_INSTANCE_SHORT_NAME=ADC, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=ADC, )
module ADC_SAR_SEQ_P4_v1_10_2 (
    soc,
    aclk,
    Vref,
    sdone,
    eoc,
    vinPlus0);
    input       soc;
    input       aclk;
    inout       Vref;
    electrical  Vref;
    output      sdone;
    output      eoc;
    inout       vinPlus0;
    electrical  vinPlus0;


          wire  Net_3093;
          wire  Net_3090;
          wire  Net_2786;
    electrical  Net_2785;
    electrical  Net_2784;
    electrical  Net_2783;
          wire  Net_2782;
    electrical  Net_2781;
    electrical  Net_2780;
    electrical  Net_2779;
    electrical  Net_2575;
    electrical  Net_2574;
    electrical  Net_2573;
    electrical  Net_2572;
    electrical  Net_2571;
    electrical  Net_2570;
    electrical  Net_2569;
    electrical  Net_2568;
    electrical  Net_2567;
    electrical  Net_2566;
    electrical  Net_2565;
    electrical  Net_2564;
    electrical  muxout_plus;
    electrical  Net_2563;
    electrical  Net_2562;
    electrical  Net_2561;
    electrical  Net_2560;
    electrical  Net_2559;
    electrical  Net_2557;
    electrical  Net_2556;
    electrical  Net_2555;
    electrical  Net_2554;
    electrical  muxout_minus;
    electrical  Net_2553;
    electrical  Net_2552;
    electrical  Net_2551;
    electrical  Net_2550;
    electrical  Net_2549;
    electrical  Net_2548;
    electrical  Net_2547;
    electrical [16:0] mux_bus_minus;
    electrical [16:0] mux_bus_plus;
    electrical  Net_2546;
    electrical  Net_2545;
    electrical  Net_2544;
    electrical  Net_2542;
    electrical  Net_2541;
          wire  Net_2221;
    electrical  Net_1849;
    electrical  Net_1848;
    electrical  Net_1846;
          wire  Net_2273;
          wire [11:0] Net_2272;
          wire  Net_2271;
          wire [3:0] Net_2270;
          wire  Net_2269;
          wire  Net_15;
          wire  Net_13;
          wire  Net_14;
          wire  Net_11;
          wire  Net_26;
    electrical  Net_2793;
    electrical  Net_2794;
          wire  Net_1845;
    electrical [0:0] Net_1450;
    electrical [0:0] Net_2375;
    electrical  Net_1851;
    electrical  Net_2580;
    electrical  Net_3046;
    electrical  Net_3016;
    electrical  Net_2020;
    electrical  Net_124;
    electrical  Net_2102;
    electrical  Net_2099;
          wire [1:0] Net_1963;
          wire  Net_17;
    electrical  Net_8;
    electrical  Net_43;

    cy_psoc4_sar_v1_0 cy_psoc4_sar (
        .vplus(Net_2020),
        .vminus(Net_124),
        .vref(Net_8),
        .ext_vref(Net_43),
        .clock(Net_17),
        .sw_negvref(Net_26),
        .cfg_st_sel(Net_1963[1:0]),
        .cfg_average(Net_11),
        .cfg_resolution(Net_14),
        .cfg_differential(Net_13),
        .trigger(soc),
        .data_hilo_sel(Net_15),
        .sample_done(sdone),
        .chan_id_valid(Net_2269),
        .chan_id(Net_2270[3:0]),
        .data_valid(Net_2271),
        .eos_intr(eoc),
        .data(Net_2272[11:0]),
        .irq(Net_2273));

	// clk_src_sel (cy_virtualmux_v1_0)
	assign Net_17 = Net_1845;

	// int_vref_sel (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 int_vref_sel_connect(Net_8, Net_1846);
	defparam int_vref_sel_connect.sig_width = 1;

	// ext_vref_sel (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 ext_vref_sel_connect(Net_43, Net_1848);
	defparam ext_vref_sel_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_1 (
        .noconnect(Net_1846));

    ZeroTerminal ZeroTerminal_3 (
        .z(Net_14));

    ZeroTerminal ZeroTerminal_4 (
        .z(Net_13));

    ZeroTerminal ZeroTerminal_5 (
        .z(Net_15));

    ZeroTerminal ZeroTerminal_6 (
        .z(Net_1963[0]));

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_1963[1]));


	cy_clock_v1_0
		#(.id("c0438d7d-b618-4458-bf19-9d8f78e88f79/a12a1691-924f-48e5-a017-176d592c3b32"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("833333333.333333"),
		  .is_direct(0),
		  .is_digital(0))
		intClock
		 (.clock_out(Net_1845));


    ZeroTerminal ZeroTerminal_2 (
        .z(Net_11));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_26));

	// ext_vneg_sel (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 ext_vneg_sel_connect(Net_2580, Net_1851);
	defparam ext_vneg_sel_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_3 (
        .noconnect(Net_1851));

	// cy_analog_virtualmux_vplus9 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus9_connect(mux_bus_plus[9], Net_2541);
	defparam cy_analog_virtualmux_vplus9_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus8 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus8_connect(mux_bus_plus[8], Net_2542);
	defparam cy_analog_virtualmux_vplus8_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus1_connect(mux_bus_plus[1], Net_2544);
	defparam cy_analog_virtualmux_vplus1_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus2 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus2_connect(mux_bus_plus[2], Net_2545);
	defparam cy_analog_virtualmux_vplus2_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus3 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus3_connect(mux_bus_plus[3], Net_2546);
	defparam cy_analog_virtualmux_vplus3_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus4 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus4_connect(mux_bus_plus[4], Net_2547);
	defparam cy_analog_virtualmux_vplus4_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus6 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus6_connect(mux_bus_plus[6], Net_2548);
	defparam cy_analog_virtualmux_vplus6_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus7 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus7_connect(mux_bus_plus[7], Net_2549);
	defparam cy_analog_virtualmux_vplus7_connect.sig_width = 1;

    Bus_Connect_v1_10 Connect_1 (
        .in_bus(mux_bus_plus[16:0]),
        .out_bus(Net_1450[0:0]));
    defparam Connect_1.in_width = 17;
    defparam Connect_1.out_width = 1;

	// cy_analog_virtualmux_vplus5 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus5_connect(mux_bus_plus[5], Net_2550);
	defparam cy_analog_virtualmux_vplus5_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus10 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus10_connect(mux_bus_plus[10], Net_2551);
	defparam cy_analog_virtualmux_vplus10_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus11 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus11_connect(mux_bus_plus[11], Net_2552);
	defparam cy_analog_virtualmux_vplus11_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus12 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus12_connect(mux_bus_plus[12], Net_2553);
	defparam cy_analog_virtualmux_vplus12_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus13 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus13_connect(mux_bus_plus[13], Net_2554);
	defparam cy_analog_virtualmux_vplus13_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus14 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus14_connect(mux_bus_plus[14], Net_2555);
	defparam cy_analog_virtualmux_vplus14_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus15 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus15_connect(mux_bus_plus[15], Net_2556);
	defparam cy_analog_virtualmux_vplus15_connect.sig_width = 1;

	// cy_analog_virtualmux_vplus_inj (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vplus_inj_connect(Net_3016, Net_2557);
	defparam cy_analog_virtualmux_vplus_inj_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_6 (
        .noconnect(Net_2544));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_7 (
        .noconnect(Net_2545));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_8 (
        .noconnect(Net_2546));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_9 (
        .noconnect(Net_2547));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_10 (
        .noconnect(Net_2550));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_11 (
        .noconnect(Net_2548));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_12 (
        .noconnect(Net_2549));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_13 (
        .noconnect(Net_2542));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_14 (
        .noconnect(Net_2541));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_15 (
        .noconnect(Net_2551));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_16 (
        .noconnect(Net_2552));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_17 (
        .noconnect(Net_2553));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_18 (
        .noconnect(Net_2554));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_19 (
        .noconnect(Net_2555));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_20 (
        .noconnect(Net_2556));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_21 (
        .noconnect(Net_2557));

	// cy_analog_virtualmux_37 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_37_connect(Net_3016, mux_bus_plus[1]);
	defparam cy_analog_virtualmux_37_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus0 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus0_connect(mux_bus_minus[0], Net_2559);
	defparam cy_analog_virtualmux_vminus0_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus1 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus1_connect(mux_bus_minus[1], Net_2560);
	defparam cy_analog_virtualmux_vminus1_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus2 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus2_connect(mux_bus_minus[2], Net_2561);
	defparam cy_analog_virtualmux_vminus2_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus3 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus3_connect(mux_bus_minus[3], Net_2562);
	defparam cy_analog_virtualmux_vminus3_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus4 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus4_connect(mux_bus_minus[4], Net_2563);
	defparam cy_analog_virtualmux_vminus4_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus5 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus5_connect(mux_bus_minus[5], Net_2564);
	defparam cy_analog_virtualmux_vminus5_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus6 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus6_connect(mux_bus_minus[6], Net_2565);
	defparam cy_analog_virtualmux_vminus6_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus7 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus7_connect(mux_bus_minus[7], Net_2566);
	defparam cy_analog_virtualmux_vminus7_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus8 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus8_connect(mux_bus_minus[8], Net_2567);
	defparam cy_analog_virtualmux_vminus8_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus9 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus9_connect(mux_bus_minus[9], Net_2568);
	defparam cy_analog_virtualmux_vminus9_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus10 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus10_connect(mux_bus_minus[10], Net_2569);
	defparam cy_analog_virtualmux_vminus10_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus11 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus11_connect(mux_bus_minus[11], Net_2570);
	defparam cy_analog_virtualmux_vminus11_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus12 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus12_connect(mux_bus_minus[12], Net_2571);
	defparam cy_analog_virtualmux_vminus12_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus13 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus13_connect(mux_bus_minus[13], Net_2572);
	defparam cy_analog_virtualmux_vminus13_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus14 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus14_connect(mux_bus_minus[14], Net_2573);
	defparam cy_analog_virtualmux_vminus14_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus15 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus15_connect(mux_bus_minus[15], Net_2574);
	defparam cy_analog_virtualmux_vminus15_connect.sig_width = 1;

	// cy_analog_virtualmux_vminus_inj (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_vminus_inj_connect(Net_3046, Net_2575);
	defparam cy_analog_virtualmux_vminus_inj_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_37 (
        .noconnect(Net_2575));

	// cy_analog_virtualmux_36 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_36_connect(Net_3046, mux_bus_minus[1]);
	defparam cy_analog_virtualmux_36_connect.sig_width = 1;

	// cy_analog_virtualmux_42 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_42_connect(Net_2020, muxout_plus);
	defparam cy_analog_virtualmux_42_connect.sig_width = 1;

	// cy_analog_virtualmux_43 (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 cy_analog_virtualmux_43_connect(Net_124, muxout_minus);
	defparam cy_analog_virtualmux_43_connect.sig_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_39 (
        .noconnect(Net_2779));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_40 (
        .noconnect(Net_2783));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_38 (
        .noconnect(Net_2780));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_41 (
        .noconnect(Net_2781));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_43 (
        .noconnect(Net_2784));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_44 (
        .noconnect(Net_2785));

    Bus_Connect_v1_10 Connect_2 (
        .in_bus(mux_bus_minus[16:0]),
        .out_bus(Net_2375[0:0]));
    defparam Connect_2.in_width = 17;
    defparam Connect_2.out_width = 1;

    cy_analog_noconnect_v1_0 cy_analog_noconnect_2 (
        .noconnect(Net_2559));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_4 (
        .noconnect(Net_2560));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_22 (
        .noconnect(Net_2561));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_23 (
        .noconnect(Net_2562));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_24 (
        .noconnect(Net_2563));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_25 (
        .noconnect(Net_2564));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_26 (
        .noconnect(Net_2565));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_27 (
        .noconnect(Net_2566));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_28 (
        .noconnect(Net_2567));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_29 (
        .noconnect(Net_2568));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_30 (
        .noconnect(Net_2569));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_31 (
        .noconnect(Net_2570));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_32 (
        .noconnect(Net_2571));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_33 (
        .noconnect(Net_2572));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_34 (
        .noconnect(Net_2573));

    cy_analog_noconnect_v1_0 cy_analog_noconnect_35 (
        .noconnect(Net_2574));


	cy_isr_v1_0
		#(.int_type(2'b10))
		IRQ
		 (.int_signal(Net_2273));



    assign Net_3093 = Net_1845 | Net_3090;

    ZeroTerminal ZeroTerminal_8 (
        .z(Net_3090));

	// adc_plus_in_sel (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 adc_plus_in_sel_connect(muxout_plus, mux_bus_plus[0]);
	defparam adc_plus_in_sel_connect.sig_width = 1;

	// adc_minus_in_sel (cy_analog_virtualmux_v1_0)
	cy_connect_v1_0 adc_minus_in_sel_connect(muxout_minus, mux_bus_minus[0]);
	defparam adc_minus_in_sel_connect.sig_width = 1;


    cy_connect_v1_0 vinPlus0__cy_connect_v1_0(vinPlus0, mux_bus_plus[0]);
    defparam vinPlus0__cy_connect_v1_0.sig_width = 1;


endmodule

// top
module top ;

    electrical  Net_8015;
          wire  Net_8035;
          wire  Net_8034;
          wire  Net_8033;
          wire  Net_8032;
    electrical  Net_8031;
          wire  Net_7615;
          wire  Net_7614;
          wire  Net_7613;
          wire  Net_7612;
          wire  Net_7611;
          wire  Net_7609;
    electrical  Net_7715;
          wire  Net_7608;
    electrical  Net_13;
          wire  Net_7607;
    electrical  Net_15;
          wire  Net_7606;
          wire  Net_7605;
    electrical  Net_7795;
    electrical  Net_7794;
    electrical  Net_7793;
    electrical  Net_7792;
    electrical  Net_7791;
    electrical  Net_7790;
    electrical  Net_7789;
    electrical  Net_7788;
    electrical  Net_7787;
    electrical  Net_7786;
    electrical  Net_7785;
    electrical  Net_7784;
    electrical  Net_7796;
    electrical  Net_7781;
    electrical  Net_7780;
    electrical  Net_7779;
    electrical  Net_7778;
    electrical  Net_7777;
    electrical  Net_7776;
    electrical  Net_7775;
    electrical  Net_7774;
    electrical  Net_7773;
    electrical  Net_7772;
    electrical  Net_7771;
    electrical  Net_7770;
    electrical  Net_7769;
    electrical  Net_7768;
    electrical  Net_7767;
    electrical  Net_7766;
          wire  lat;
    electrical  Net_7765;
    electrical  Net_7764;
    electrical  Net_7763;
    electrical  Net_7762;
    electrical  Net_7761;
    electrical  Net_7760;
    electrical  Net_7759;
    electrical  Net_7758;
    electrical  Net_7757;
    electrical  Net_7756;
    electrical  Net_7755;
    electrical  done;
    electrical  Net_7754;
    electrical  Net_7753;
    electrical  Net_7752;
    electrical  Net_7751;
    electrical  Net_7750;
    electrical  Net_7749;
    electrical  Net_7748;
    electrical  Net_7747;
    electrical  Net_7871;
    electrical  Net_7746;
    electrical  Net_7745;
    electrical  Net_7862;
    electrical  Net_7863;
    electrical  Net_7864;
    electrical  Net_7865;
    electrical  Net_7866;
    electrical  Net_12;
    electrical  Net_7870;
    electrical  Net_7744;
    electrical  Net_7743;
    electrical  Net_7742;
    electrical  Net_7741;
    electrical  Net_7740;
    electrical  Net_7739;
    electrical  Net_7738;
    electrical  Net_7737;
    electrical  Net_7861;
          wire  Net_7548;
    electrical  Net_16;
    electrical  Net_174;
    electrical  Net_176;
          wire  Net_7547;
          wire  Net_7546;
          wire  Net_7545;
          wire  Net_7544;
          wire  Net_7543;
          wire  Net_7542;
          wire  Net_7640;
          wire  Net_7538;
    electrical  Net_221;
          wire  Net_7537;
    electrical  Net_88;
    electrical  Net_178;
          wire  Net_7639;
          wire  Net_5619;
          wire  Net_7149;
          wire  Net_7153;
          wire  Net_7152;
    electrical  Net_11;
    electrical  Net_7869;

	wire [0:0] tmpOE__P1_2_A_net;
	wire [0:0] tmpFB_0__P1_2_A_net;
	wire [0:0] tmpIO_0__P1_2_A_net;
	wire [0:0] tmpINTERRUPT_0__P1_2_A_net;
	electrical [0:0] tmpSIOVREF__P1_2_A_net;

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
		P1_2_A
		 (.oe(tmpOE__P1_2_A_net),
		  .y({Net_7149}),
		  .fb({tmpFB_0__P1_2_A_net[0:0]}),
		  .io({tmpIO_0__P1_2_A_net[0:0]}),
		  .siovref(tmpSIOVREF__P1_2_A_net),
		  .interrupt({tmpINTERRUPT_0__P1_2_A_net[0:0]}),
		  .annotation({Net_178}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P1_2_A_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P3_1_CLK_net;
	wire [0:0] tmpFB_0__P3_1_CLK_net;
	wire [0:0] tmpIO_0__P3_1_CLK_net;
	wire [0:0] tmpINTERRUPT_0__P3_1_CLK_net;
	electrical [0:0] tmpSIOVREF__P3_1_CLK_net;

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
		P3_1_CLK
		 (.oe(tmpOE__P3_1_CLK_net),
		  .y({Net_7537}),
		  .fb({tmpFB_0__P3_1_CLK_net[0:0]}),
		  .io({tmpIO_0__P3_1_CLK_net[0:0]}),
		  .siovref(tmpSIOVREF__P3_1_CLK_net),
		  .interrupt({tmpINTERRUPT_0__P3_1_CLK_net[0:0]}),
		  .annotation({Net_88}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P3_1_CLK_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P0_6_OE_net;
	wire [0:0] tmpFB_0__P0_6_OE_net;
	wire [0:0] tmpIO_0__P0_6_OE_net;
	wire [0:0] tmpINTERRUPT_0__P0_6_OE_net;
	electrical [0:0] tmpSIOVREF__P0_6_OE_net;

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
		P0_6_OE
		 (.oe(tmpOE__P0_6_OE_net),
		  .y({Net_7538}),
		  .fb({tmpFB_0__P0_6_OE_net[0:0]}),
		  .io({tmpIO_0__P0_6_OE_net[0:0]}),
		  .siovref(tmpSIOVREF__P0_6_OE_net),
		  .interrupt({tmpINTERRUPT_0__P0_6_OE_net[0:0]}),
		  .annotation({Net_221}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P0_6_OE_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

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

    KEES_PinHelper_v1_1_0 KEES_PinHelper_1 ();

	wire [0:0] tmpOE__P1_1_B_net;
	wire [0:0] tmpFB_0__P1_1_B_net;
	wire [0:0] tmpIO_0__P1_1_B_net;
	wire [0:0] tmpINTERRUPT_0__P1_1_B_net;
	electrical [0:0] tmpSIOVREF__P1_1_B_net;

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
		P1_1_B
		 (.oe(tmpOE__P1_1_B_net),
		  .y({Net_7152}),
		  .fb({tmpFB_0__P1_1_B_net[0:0]}),
		  .io({tmpIO_0__P1_1_B_net[0:0]}),
		  .siovref(tmpSIOVREF__P1_1_B_net),
		  .interrupt({tmpINTERRUPT_0__P1_1_B_net[0:0]}),
		  .annotation({Net_176}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P1_1_B_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P1_5_C_net;
	wire [0:0] tmpFB_0__P1_5_C_net;
	wire [0:0] tmpIO_0__P1_5_C_net;
	wire [0:0] tmpINTERRUPT_0__P1_5_C_net;
	electrical [0:0] tmpSIOVREF__P1_5_C_net;

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
		P1_5_C
		 (.oe(tmpOE__P1_5_C_net),
		  .y({Net_7153}),
		  .fb({tmpFB_0__P1_5_C_net[0:0]}),
		  .io({tmpIO_0__P1_5_C_net[0:0]}),
		  .siovref(tmpSIOVREF__P1_5_C_net),
		  .interrupt({tmpINTERRUPT_0__P1_5_C_net[0:0]}),
		  .annotation({Net_174}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P1_5_C_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P3_0_B2_net;
	wire [0:0] tmpFB_0__P3_0_B2_net;
	wire [0:0] tmpIO_0__P3_0_B2_net;
	wire [0:0] tmpINTERRUPT_0__P3_0_B2_net;
	electrical [0:0] tmpSIOVREF__P3_0_B2_net;

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
		P3_0_B2
		 (.oe(tmpOE__P3_0_B2_net),
		  .y({Net_7548}),
		  .fb({tmpFB_0__P3_0_B2_net[0:0]}),
		  .io({tmpIO_0__P3_0_B2_net[0:0]}),
		  .siovref(tmpSIOVREF__P3_0_B2_net),
		  .interrupt({tmpINTERRUPT_0__P3_0_B2_net[0:0]}),
		  .annotation({Net_16}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P3_0_B2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P1_4_LAT_net;
	wire [0:0] tmpFB_0__P1_4_LAT_net;
	wire [0:0] tmpIO_0__P1_4_LAT_net;
	wire [0:0] tmpINTERRUPT_0__P1_4_LAT_net;
	electrical [0:0] tmpSIOVREF__P1_4_LAT_net;

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
		P1_4_LAT
		 (.oe(tmpOE__P1_4_LAT_net),
		  .y({lat}),
		  .fb({tmpFB_0__P1_4_LAT_net[0:0]}),
		  .io({tmpIO_0__P1_4_LAT_net[0:0]}),
		  .siovref(tmpSIOVREF__P1_4_LAT_net),
		  .interrupt({tmpINTERRUPT_0__P1_4_LAT_net[0:0]}),
		  .annotation({Net_7861}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P1_4_LAT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    PSoC_4_Pioneer_Kit_1 PSoC_4_Pioneer_Kit_1 (
        .Terminal_20(Net_7737),
        .Terminal_21(Net_7738),
        .Terminal_22(Net_7739),
        .Terminal_23(Net_7740),
        .Terminal_24(Net_7741),
        .Terminal_25(Net_7742),
        .Terminal_26(Net_7743),
        .Terminal_27(Net_7744),
        .Terminal_18(Net_7870),
        .Terminal_34(Net_12),
        .Terminal_35(Net_7866),
        .Terminal_36(Net_7865),
        .Terminal_37(Net_7864),
        .Terminal_38(Net_7863),
        .Terminal_39(Net_7862),
        .Terminal_40(Net_7745),
        .Terminal_41(Net_7746),
        .Terminal_42(Net_7871),
        .Terminal_43(Net_7747),
        .Terminal_44(Net_7748),
        .Terminal_45(Net_7749),
        .Terminal_46(Net_7750),
        .Terminal_47(Net_7751),
        .Terminal_48(Net_7752),
        .Terminal_49(Net_7753),
        .Terminal_50(Net_7754),
        .Terminal_57(Net_7755),
        .Terminal_59(Net_7756),
        .Terminal_61(Net_7757),
        .Terminal_63(Net_7758),
        .Terminal_65(Net_7759),
        .Terminal_67(Net_7760),
        .Terminal_68(Net_7761),
        .Terminal_66(Net_7762),
        .Terminal_64(Net_7763),
        .Terminal_62(Net_7764),
        .Terminal_60(Net_7765),
        .Terminal_58(Net_7766),
        .Terminal_33(Net_7767),
        .Terminal_32(Net_7768),
        .Terminal_31(Net_7769),
        .Terminal_30(Net_7770),
        .Terminal_29(Net_7771),
        .Terminal_28(Net_7772),
        .Terminal_19(Net_7773),
        .Terminal_17(Net_7774),
        .Terminal_14(Net_7775),
        .Terminal_16(Net_7776),
        .Terminal_15(Net_7777),
        .Terminal_13(Net_7778),
        .Terminal_10(Net_7779),
        .Terminal_12(Net_7780),
        .Terminal_11(Net_7781),
        .Terminal_9(Net_7796),
        .Terminal_6(done),
        .Terminal_8(done),
        .Terminal_7(Net_7784),
        .Terminal_5(Net_7785),
        .Terminal_2(Net_7786),
        .Terminal_4(Net_7787),
        .Terminal_3(Net_7788),
        .Terminal_1(Net_7789),
        .Terminal_55(Net_7790),
        .Terminal_56(Net_7791),
        .Terminal_54(Net_7792),
        .Terminal_53(Net_7793),
        .Terminal_51(Net_7794),
        .Terminal_52(Net_7795));

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
		  .annotation({Net_7869}),
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
		  .annotation({Net_7715}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P3_5_R2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__P1_3_done_net;
	wire [0:0] tmpFB_0__P1_3_done_net;
	wire [0:0] tmpIO_0__P1_3_done_net;
	wire [0:0] tmpINTERRUPT_0__P1_3_done_net;
	electrical [0:0] tmpSIOVREF__P1_3_done_net;

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
		P1_3_done
		 (.oe(tmpOE__P1_3_done_net),
		  .y({Net_7639}),
		  .fb({tmpFB_0__P1_3_done_net[0:0]}),
		  .io({tmpIO_0__P1_3_done_net[0:0]}),
		  .siovref(tmpSIOVREF__P1_3_done_net),
		  .interrupt({tmpINTERRUPT_0__P1_3_done_net[0:0]}),
		  .annotation({done}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__P1_3_done_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


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

    ADC_SAR_SEQ_P4_v1_10_2 ADC (
        .Vref(Net_8031),
        .sdone(Net_8032),
        .eoc(Net_8033),
        .aclk(1'b0),
        .soc(1'b0),
        .vinPlus0(Net_8015));

	wire [0:0] tmpOE__ADC_P2_0_net;
	wire [0:0] tmpFB_0__ADC_P2_0_net;
	wire [0:0] tmpIO_0__ADC_P2_0_net;
	wire [0:0] tmpINTERRUPT_0__ADC_P2_0_net;
	electrical [0:0] tmpSIOVREF__ADC_P2_0_net;

	cy_psoc3_pins_v1_10
		#(.id("05a9c8de-3ba2-4909-8250-95fdc61c0bf4"),
		  .drive_mode(3'b000),
		  .ibuf_enabled(1'b0),
		  .init_dr_st(1'b0),
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
		  .pin_mode("A"),
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
		ADC_P2_0
		 (.oe(tmpOE__ADC_P2_0_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__ADC_P2_0_net[0:0]}),
		  .analog({Net_8015}),
		  .io({tmpIO_0__ADC_P2_0_net[0:0]}),
		  .siovref(tmpSIOVREF__ADC_P2_0_net),
		  .interrupt({tmpINTERRUPT_0__ADC_P2_0_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__ADC_P2_0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b00))
		eoc
		 (.int_signal(Net_8033));




endmodule

