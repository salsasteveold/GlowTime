/******************************************************************************
* File Name: CyADC_ApiGen.cs
* *****************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.IO;
using System.Collections;
using KEES_ADC_DelSig_Mod_v2_30;


namespace KEES_ADC_DelSig_Mod_v2_30
{
    partial class CyCustomizer : ICyAPICustomize_v1
    {
        public const string HEX_PREFIX = "0X";
        public const string HEX_FORMAT1 = "X2";
        public const string HEX_FORMAT2 = "X4";
        public const string FORMAT_SPECIFIER = "u";
        #region ParameterNamesValues
        const float MAX_VDDA3_VALUE = 3.75F;
        string [] DEC_CR_ParamName     = {"DFLT_DEC_CR", "DFLT_DEC_CR_CFG2", "DFLT_DEC_CR_CFG3", "DFLT_DEC_CR_CFG4"};
        string [] DEC_SR_ParamName     = {"DFLT_DEC_SR", "DFLT_DEC_SR_CFG2", "DFLT_DEC_SR_CFG3", "DFLT_DEC_SR_CFG4"};
        string [] DEC_SHIFT1_ParamName = {"DFLT_DEC_SHIFT1", "DFLT_DEC_SHIFT1_CFG2", "DFLT_DEC_SHIFT1_CFG3", 
                                          "DFLT_DEC_SHIFT1_CFG4"};
        string [] DEC_SHIFT2_ParamName = {"DFLT_DEC_SHIFT2", "DFLT_DEC_SHIFT2_CFG2", "DFLT_DEC_SHIFT2_CFG3", 
                                          "DFLT_DEC_SHIFT2_CFG4"};
        string [] DEC_DR2_ParamName    = {"DFLT_DEC_DR2", "DFLT_DEC_DR2_CFG2", "DFLT_DEC_DR2_CFG3", 
                                             "DFLT_DEC_DR2_CFG4"};
        string [] DEC_DR2H_ParamName   = {"DFLT_DEC_DR2H", "DFLT_DEC_DR2H_CFG2", "DFLT_DEC_DR2H_CFG3", 
                                             "DFLT_DEC_DR2H_CFG4"};
        string [] DEC_DR1_ParamName    = {"DFLT_DEC_DR1", "DFLT_DEC_DR1_CFG2", "DFLT_DEC_DR1_CFG3", 
                                             "DFLT_DEC_DR1_CFG4"};
        string [] DEC_OCOR_ParamName   = {"DFLT_DEC_OCOR", "DFLT_DEC_OCOR_CFG2", "DFLT_DEC_OCOR_CFG3", 
                                             "DFLT_DEC_OCOR_CFG4"};
        string [] DEC_OCORM_ParamName  = {"DFLT_DEC_OCORM", "DFLT_DEC_OCORM_CFG2", "DFLT_DEC_OCORM_CFG3", 
                                             "DFLT_DEC_OCORM_CFG4"};
        string [] DEC_OCORH_ParamName  = {"DFLT_DEC_OCORH", "DFLT_DEC_OCORH_CFG2", "DFLT_DEC_OCORH_CFG3", 
                                             "DFLT_DEC_OCORH_CFG4"};
        string [] DEC_GVAL_ParamName   = {"DFLT_DEC_GVAL", "DFLT_DEC_GVAL_CFG2","DFLT_DEC_GVAL_CFG3", 
                                             "DFLT_DEC_GVAL_CFG4"};
        string [] DEC_GCOR_ParamName   = {"DFLT_DEC_GCOR", "DFLT_DEC_GCOR_CFG2", "DFLT_DEC_GCOR_CFG3", 
                                             "DFLT_DEC_GCOR_CFG4"};
        string [] DEC_GCORH_ParamName  = {"DFLT_DEC_GCORH", "DFLT_DEC_GCORH_CFG2", "DFLT_DEC_GCORH_CFG3", 
                                             "DFLT_DEC_GCORH_CFG4"};
        string [] DEC_COHER_ParamName  = {"DFLT_DEC_COHER", "DFLT_DEC_COHER_CFG2", "DFLT_DEC_COHER_CFG3", 
                                             "DFLT_DEC_COHER_CFG4"};

        string []DSM_CR0_ParamName = {"DFLT_DSM_CR0", "DFLT_DSM_CR0_CFG2", "DFLT_DSM_CR0_CFG3", "DFLT_DSM_CR0_CFG4"};
        string []DSM_CR1_ParamName = {"DFLT_DSM_CR1", "DFLT_DSM_CR1_CFG2", "DFLT_DSM_CR1_CFG3", "DFLT_DSM_CR1_CFG4"};
        string []DSM_CR2_ParamName = {"DFLT_DSM_CR2", "DFLT_DSM_CR2_CFG2", "DFLT_DSM_CR2_CFG3", "DFLT_DSM_CR2_CFG4"};
        string []DSM_CR3_ParamName = {"DFLT_DSM_CR3", "DFLT_DSM_CR3_CFG2",  "DFLT_DSM_CR3_CFG3",  "DFLT_DSM_CR3_CFG4"};
        string []DSM_CR4_ParamName = {"DFLT_DSM_CR4", "DFLT_DSM_CR4_CFG2", "DFLT_DSM_CR4_CFG3", "DFLT_DSM_CR4_CFG4"};
        string []DSM_CR5_ParamName = {"DFLT_DSM_CR5", "DFLT_DSM_CR5_CFG2", "DFLT_DSM_CR5_CFG3", "DFLT_DSM_CR5_CFG4"};
        string []DSM_CR6_ParamName = {"DFLT_DSM_CR6", "DFLT_DSM_CR6_CFG2", "DFLT_DSM_CR6_CFG3", "DFLT_DSM_CR6_CFG4"};
        string []DSM_CR7_ParamName = {"DFLT_DSM_CR7", "DFLT_DSM_CR7_CFG2", "DFLT_DSM_CR7_CFG3", "DFLT_DSM_CR7_CFG4"};
        string []DSM_CR8_ParamName = {"DFLT_DSM_CR8", "DFLT_DSM_CR8_CFG2", "DFLT_DSM_CR8_CFG3", "DFLT_DSM_CR8_CFG4"};
        string []DSM_CR9_ParamName = {"DFLT_DSM_CR9", "DFLT_DSM_CR9_CFG2", "DFLT_DSM_CR9_CFG3", "DFLT_DSM_CR9_CFG4"};

        string []DSM_CR10_ParamName = {"DFLT_DSM_CR10", "DFLT_DSM_CR10_CFG2", "DFLT_DSM_CR10_CFG3", 
                                          "DFLT_DSM_CR10_CFG4"};
        string []DSM_CR11_ParamName = {"DFLT_DSM_CR11", "DFLT_DSM_CR11_CFG2", "DFLT_DSM_CR11_CFG3", 
                                          "DFLT_DSM_CR11_CFG4"};
        string []DSM_CR12_ParamName = {"DFLT_DSM_CR12", "DFLT_DSM_CR12_CFG2", "DFLT_DSM_CR12_CFG3", 
                                          "DFLT_DSM_CR12_CFG4"};
        string []DSM_CR13_ParamName = {"DFLT_DSM_CR13", "DFLT_DSM_CR13_CFG2", "DFLT_DSM_CR13_CFG3", 
                                          "DFLT_DSM_CR13_CFG4"};
        string []DSM_CR14_ParamName = {"DFLT_DSM_CR14", "DFLT_DSM_CR14_CFG2", "DFLT_DSM_CR14_CFG3", 
                                          "DFLT_DSM_CR14_CFG4"};
        string []DSM_CR15_ParamName = {"DFLT_DSM_CR15", "DFLT_DSM_CR15_CFG2", "DFLT_DSM_CR15_CFG3", 
                                          "DFLT_DSM_CR15_CFG4"};
        string []DSM_CR16_ParamName = {"DFLT_DSM_CR16", "DFLT_DSM_CR16_CFG2", "DFLT_DSM_CR16_CFG3", 
                                          "DFLT_DSM_CR16_CFG4"};
        string []DSM_CR17_ParamName = {"DFLT_DSM_CR17", "DFLT_DSM_CR17_CFG2", "DFLT_DSM_CR17_CFG3", 
                                          "DFLT_DSM_CR17_CFG4"};

        string []DSM_REF0_ParamName = {"DFLT_DSM_REF0", "DFLT_DSM_REF0_CFG2", "DFLT_DSM_REF0_CFG3", 
                                          "DFLT_DSM_REF0_CFG4"};
        string []DSM_REF2_ParamName = {"DFLT_DSM_REF2", "DFLT_DSM_REF2_CFG2", "DFLT_DSM_REF2_CFG3", 
                                          "DFLT_DSM_REF2_CFG4"};
        string []DSM_REF3_ParamName = {"DFLT_DSM_REF3", "DFLT_DSM_REF3_CFG2", "DFLT_DSM_REF3_CFG3", 
                                          "DFLT_DSM_REF3_CFG4"};

        string []DSM_DEM0_ParamName = {"DFLT_DSM_DEM0", "DFLT_DSM_DEM0_CFG2", "DFLT_DSM_DEM0_CFG3", 
                                          "DFLT_DSM_DEM0_CFG4"};
        string []DSM_DEM1_ParamName = {"DFLT_DSM_DEM1", "DFLT_DSM_DEM1_CFG2", "DFLT_DSM_DEM1_CFG3", 
                                          "DFLT_DSM_DEM1_CFG4"};
        string DSM_MISC_ParamName   =  "DFLT_DSM_MISC";
        string DSM_CLK_ParamName    =  "DFLT_DSM_CLK";
        string DSM_REF1_ParamName   =  "DFLT_DSM_REF1";

        string []DSM_BUF0_ParamName = {"DFLT_DSM_BUF0", "DFLT_DSM_BUF0_CFG2", "DFLT_DSM_BUF0_CFG3", 
                                          "DFLT_DSM_BUF0_CFG4"};
        string []DSM_BUF1_ParamName = {"DFLT_DSM_BUF1", "DFLT_DSM_BUF1_CFG2", "DFLT_DSM_BUF1_CFG3", 
                                          "DFLT_DSM_BUF1_CFG4"};
        string []DSM_BUF2_ParamName = {"DFLT_DSM_BUF2", "DFLT_DSM_BUF2_CFG2", "DFLT_DSM_BUF2_CFG3", 
                                          "DFLT_DSM_BUF2_CFG4"};
        string []DSM_BUF3_ParamName = {"DFLT_DSM_BUF3", "DFLT_DSM_BUF3_CFG2", "DFLT_DSM_BUF3_CFG3", 
                                          "DFLT_DSM_BUF3_CFG4"};
        string []DSM_OUT0_ParamName = {"DFLT_DSM_OUT0", "DFLT_DSM_OUT0_CFG2", "DFLT_DSM_OUT0_CFG3", 
                                          "DFLT_DSM_OUT0_CFG4"};
        string []DSM_OUT1_ParamName = {"DFLT_DSM_OUT1", "DFLT_DSM_OUT1_CFG2", "DFLT_DSM_OUT1_CFG3", 
                                          "DFLT_DSM_OUT1_CFG4"};
        string []adcClockFrequency_ParamName = {"DFLT_CLK_FREQ", "DFLT_CLK_FREQ_CFG2", "DFLT_CLK_FREQ_CFG3", 
                                                "DFLT_CLK_FREQ_CFG4"};
        string []chargePumpClockFrequency_ParamName = {"DFLT_CP_CLK_FREQ", "DFLT_CP_CLK_FREQ_CFG2", "DFLT_CP_CLK_FREQ_CFG3", 
                                                "DFLT_CP_CLK_FREQ_CFG4"};
        string []clocksPerSample_ParamName = {"DFLT_CLOCKS_PER_SAMPLE", "DFLT_CLOCKS_PER_SAMPLE_CFG2", 
                                                 "DFLT_CLOCKS_PER_SAMPLE_CFG3", "DFLT_CLOCKS_PER_SAMPLE_CFG4"};

        // Commenting out this since this is no more used in the new version CDT 50250 
        string []DSM_SW3_ParamName = {"DFLT_DSM_SW3","DFLT_DSM_SW3_CFG2","DFLT_DSM_SW3_CFG3", "DFLT_DSM_SW3_CFG4"};

        string ADC_ClockParamName = CyADC_DelSigParameters.ADC_CLOCK;
        string ADC_ClockTermName = CyADC_DelSigParameters.CLOCK_FREQUENCY;
        string ConfigParamName =  CyADC_DelSigParameters.CONFIGS;
        string ADC_ChargePumpParamName = CyADC_DelSigParameters.ADC_CHARGE_PUMP_CLOCK;
        string ADC_nVrefParamName = CyADC_DelSigParameters.ADC_nVref;
        string[] ADC_Input_ModeValue_ParamName = {CyADC_DelSigParameters.INPUT_MODE, 
                                                     CyADC_DelSigParameters.INPUT_MODE_CONFIG2, 
                                                     CyADC_DelSigParameters.INPUT_MODE_CONFIG3, 
                                                     CyADC_DelSigParameters.INPUT_MODE_CONFIG4};
        string ADC_Input_ModeParamName = CyADC_DelSigParameters.ADC_INPUT_MODE;

        string[] ADC_Input_RangeParamName = {CyADC_DelSigParameters.INPUT_RANGE, 
                                                CyADC_DelSigParameters.INPUT_RANGE_CONFIG2, 
                                                CyADC_DelSigParameters.INPUT_RANGE_CONFIG3, 
                                                CyADC_DelSigParameters.INPUT_RANGE_CONFIG4};
        string[] ADC_Input_RangeValue_ParamName = {CyADC_DelSigParameters.INPUT_RANGEVALUE, 
                                                      CyADC_DelSigParameters.INPUT_RANGEVALUE_CONFIG2, 
                                                      CyADC_DelSigParameters.INPUT_RANGEVALUE_CONFIG3, 
                                                      CyADC_DelSigParameters.INPUT_RANGEVALUE_CONFIG4};
       
        string[] ADC_ReferenceParamName = {CyADC_DelSigParameters.ADC_REFERENCE, 
                                              CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2, 
                                              CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3, 
                                              CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4 };
        string[] ADC_ResolutionParamName = {CyADC_DelSigParameters.RESOLUTION, 
                                               CyADC_DelSigParameters.RESOLUTION_CONFIG2, 
                                               CyADC_DelSigParameters.RESOLUTION_CONFIG3, 
                                               CyADC_DelSigParameters.RESOLUTION_CONFIG4 };
        string[] Conversion_ModeParamName = {CyADC_DelSigParameters.CONVERSION_MODE, 
                                                CyADC_DelSigParameters.CONVERSION_MODE_CONFIG2, 
                                                CyADC_DelSigParameters.CONVERSION_MODE_CONFIG3, 
                                                CyADC_DelSigParameters.CONVERSION_MODE_CONFIG4 };
        string[] Input_Buffer_GainParamName = {CyADC_DelSigParameters.INPUT_BUFFER_GAIN, 
                                                  CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG2, 
                                                  CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG3, 
                                                  CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG4 };
        string[] Input_Buffer_ModeParamName = {CyADC_DelSigParameters.INPUT_BUFFER_MODE, 
                                                  CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG2, 
                                                  CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG3, 
                                                  CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG4 };
        string[] Sample_RateParamName = {CyADC_DelSigParameters.SAMPLE_RATE, 
                                            CyADC_DelSigParameters.SAMPLE_RATE_CONFIG2, 
                                            CyADC_DelSigParameters.SAMPLE_RATE_CONFIG3, 
                                            CyADC_DelSigParameters.SAMPLE_RATE_CONFIG4};
        string   Start_of_ConversionParamName = CyADC_DelSigParameters.START_OF_CONVERSION;
        string[] Ref_VoltageParamName = {CyADC_DelSigParameters.REF_VOLTAGE, 
                                            CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, 
                                            CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, 
                                            CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4};
        string[] CountsPerVoltParamName ={"DFLT_COUNTS_PER_VOLT", "DFLT_COUNTS_PER_VOLT_CFG2", 
                                             "DFLT_COUNTS_PER_VOLT_CFG3", "DFLT_COUNTS_PER_VOLT_CFG4"};
        string[] RefVoltage_ParamName = {"DFLT_REF_VOLTAGE", "DFLT_REF_VOLTAGE_CFG2", "DFLT_REF_VOLTAGE_CFG3", 
                                            "DFLT_REF_VOLTAGE_CFG4"};
        string[] IdealDecGain_ParamName = {"DFLT_IDEAL_DEC_GAIN", "DFLT_IDEAL_DEC_GAIN_CFG2", 
                                              "DFLT_IDEAL_DEC_GAIN_CFG3", "DFLT_IDEAL_DEC_GAIN_CFG4"};
        string[] IdealOddDecGain_ParamName = {"DFLT_IDEAL_ODDDEC_GAIN", "DFLT_IDEAL_ODDDEC_GAIN_CFG2", 
                                                 "DFLT_IDEAL_ODDDEC_GAIN_CFG3", "DFLT_IDEAL_ODDDEC_GAIN_CFG4"};
        string[] IPCap1Value_ParamName = {"DFLT_IPCap1Value", "DFLT_IPCap1Value_CFG2", "DFLT_IPCap1Value_CFG3", 
                                             "DFLT_IPCap1Value_CFG4"};
        string[] DACCapValue_ParamName = {"DFLT_DACCapValue", "DFLT_DACCapValue_CFG2", "DFLT_DACCapValue_CFG3", 
                                             "DFLT_DACCapValue_CFG4"};
        
        uint ADC_Clock;
        uint []ADC_Input_Range = new uint[4]{0,0,0,0};
        uint []ADC_Reference= new uint[4]{0,0,0,0};
        uint []ADC_Resolution= new uint[4]{0,0,0,0};
        uint []Conversion_Mode= new uint[4]{0,0,0,0};
        uint []Input_Buffer_Gain= new uint[4]{0,0,0,0};
        uint []Sample_Rate= new uint[4]{0,0,0,0};
        uint Start_of_Conversion;
        float[]Ref_Voltage= new float[4]{0,0,0,0};
        uint []CountsPerVolt= new uint[4]{0,0,0,0};
        uint []Input_Buffer_Mode = new uint[4]{0,0,0,0};
        uint NumConfigs;
        uint ADC_Input_Mode;
        uint []ADC_Input_ModeValue = new uint[4]{0, 0, 0, 0} ;
        double []ADC_Input_RangeValue = new double[4]{0,0,0,0};
        uint ADC_ChargePump;
        uint ADC_nVref;
        
        uint []DecCrReg = new uint[4]{0,0,0,0};
        uint []DecSrReg = new uint[4]{0,0,0,0};
        uint []DecShift1Reg = new uint[4]{0,0,0,0};
        uint []DecShift2Reg = new uint[4]{0,0,0,0};
        uint []DecDr2Reg = new uint[4]{0,0,0,0};
        uint []DecDr2hReg = new uint[4]{0,0,0,0};
        uint []DecDr1Reg = new uint[4]{0,0,0,0};
        uint []DecOcorReg = new uint[4]{0,0,0,0};
        uint []DecOcormReg = new uint[4]{0,0,0,0};
        uint []DecOcorhReg = new uint[4]{0,0,0,0};
        uint []DecGvalReg = new uint[4]{0,0,0,0};
        uint []DecGcorReg = new uint[4]{0,0,0,0};
        uint []DecGcorhReg = new uint[4]{0,0,0,0};
        uint []DecCoherReg = new uint[4]{0,0,0,0};

        uint []DsmCr0Reg = new uint[4]{0,0,0,0};
        uint []DsmCr1Reg = new uint[4]{0,0,0,0};
        uint []DsmCr2Reg = new uint[4]{0,0,0,0};
        uint []DsmCr3Reg = new uint[4]{0,0,0,0};
        uint []DsmCr4Reg = new uint[4]{0,0,0,0};
        uint []DsmCr5Reg = new uint[4]{0,0,0,0};
        uint []DsmCr6Reg = new uint[4]{0,0,0,0};
        uint []DsmCr7Reg = new uint[4]{0,0,0,0};
        uint []DsmCr8Reg = new uint[4]{0,0,0,0};
        uint []DsmCr9Reg = new uint[4]{0,0,0,0};
        uint []DsmCr10Reg = new uint[4]{0,0,0,0};
        uint []DsmCr11Reg = new uint[4]{0,0,0,0};
        uint []DsmCr12Reg = new uint[4]{0,0,0,0};
        uint []DsmCr13Reg = new uint[4]{0,0,0,0};
        uint []DsmCr14Reg = new uint[4]{0,0,0,0};
        uint []DsmCr15Reg = new uint[4]{0,0,0,0};
        uint []DsmCr16Reg = new uint[4]{0,0,0,0};
        uint []DsmCr17Reg = new uint[4]{0,0,0,0};

        uint []DsmRef0Reg = new uint[4]{0,0,0,0};
        uint []DsmRef2Reg = new uint[4]{0,0,0,0};
        uint []DsmRef3Reg = new uint[4]{0,0,0,0};

        uint []DsmDem0Reg = new uint[4]{0,0,0,0};
        uint []DsmDem1Reg = new uint[4]{0,0,0,0};
        uint DsmMiscReg;
        uint DsmClkReg;
        uint DsmRef1Reg;


        uint []DsmBuf0Reg = new uint[4]{0,0,0,0};
        uint []DsmBuf1Reg = new uint[4]{0,0,0,0};
        uint []DsmBuf2Reg = new uint[4]{0,0,0,0};
        uint []DsmBuf3Reg = new uint[4]{0,0,0,0};
        uint []DsmOut0Reg = new uint[4]{0,0,0,0};
        uint []DsmOut1Reg = new uint[4]{0,0,0,0};

        // Commenting this due to CDT 50250 
        uint []DsmSw3Reg = new uint[4]{0,0,0,0};
        uint []Ideal_Dec_Gain = new uint[4]{0,0,0,0};
        uint []Ideal_OddDec_Gain = new uint[4]{0,0,0,0};
        uint []IPCap1Value = new uint[4]{0,0,0,0};
        uint []DACCapValue = new uint[4]{0,0,0,0};
        
        ICyTerminalQuery_v1 m_termQuery;
        ICyInstQuery_v1 m_instQuery;
  

#endregion

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, 
                                                           IEnumerable<CyAPICustomizer> apis)
        {
            List<CyClockData> clockStuff = termQuery.GetClockData(ADC_ClockTermName, 3);

            Dictionary<string, string> paramDict = null;
            m_termQuery = termQuery;
            m_instQuery = query;
            foreach (CyAPICustomizer api in apis)
            {
                // Get parameter dictionary
                paramDict = api.MacroDictionary;
                
            }
            
            bool isPSoC3 = query.GetCommittedParam(Resource.DsmNameText).Value == Resource.DSMText;
            float vdda = float.Parse(query.GetCommittedParam(Resource.VddaValueText).Value);

            // Calculate values
            CalcValues(ref paramDict, isPSoC3, vdda);

            // Assign dictionary back to API customizers
            foreach (CyAPICustomizer api in apis)
            {
                // Get parameter dictionary
                api.MacroDictionary = paramDict;
            }
            // Return customizers
            return apis;

        }
       
        #endregion


/// <summary>
/// Set ADC resolution.
/// </summary>
/// <param name="resolution">Set the ADC resolution </param>
/// <param name="inputRange">Input range selected.</param>
/// <param name="config">ADC configuration number</param>
/// <param name="isPSOC3">Flag to identify PSoC3 silicon</param>
void SetResolution(uint resolution, uint inputRange, uint config, bool isPSOC3)
{
    uint rShiftOffset = 0;
    
    ADC_Resolution[config] = resolution;
    // Offset correction 
    // This could be used to offset result for signed and unsigned results 
    DecOcorReg[config] = 0;
    DecOcormReg[config]  = 0;
    DecOcorhReg[config]  = 0;

    // Gain correction 
   // DecGvalReg[config]   = 0;
    DecGcorReg[config]   = 0;
    DecGcorhReg[config]  = 0;

    if (resolution < Cyrc.MIN_RESOLUTION) resolution = Cyrc.MIN_RESOLUTION;
    if (resolution > Cyrc.MAX_RESOLUTION) resolution = Cyrc.MAX_RESOLUTION;


    // If single ended mode, don't shift an additional bit 
    if ((ADC_Input_Range[config] == Cyrc.ADC_IR_VSSA_TO_VREF) | 
        (ADC_Input_Range[config] == Cyrc.ADC_IR_VSSA_TO_VDDA) |
        (ADC_Input_Range[config]== Cyrc.ADC_IR_VSSA_TO_6VREF) | 
        ((ADC_Input_Range[config]== Cyrc.ADC_IR_VSSA_TO_2VREF) && (isPSOC3 == false)))
    {
        rShiftOffset = 1;
    }

    resolution -= Cyrc.MIN_RESOLUTION;

    // Set resolution constants from table 
    DecDr1Reg[config] = CyresSettings.dr1[resolution];
    DecShift1Reg[config] = CyresSettings.shift1[resolution];

    DecDr2Reg[config] = CyresSettings.dr2[resolution];
    DecDr2hReg[config] = CyresSettings.dr2h[resolution];
    DecShift2Reg[config] = CyresSettings.shift2[resolution] - rShiftOffset;
}


/// <summary>
/// Set input buffer range.
/// </summary>
/// <param name="gain">Two bit value to select a gain of 1, 2, 4, or 8</param>
/// <param name="config">configuration selected</param>
/// 
void SetBufferGain(uint gain,uint config)
{
   uint tmpReg;
   uint gainSetting = 1;
   if (gain != 0)
   {
       switch (gain)
       {
           case 1:
               gainSetting = Cyrc.DSM_GAIN_1X;
               break;
           case 2:
               gainSetting = Cyrc.DSM_GAIN_2X;
               break;
           case 4:
               gainSetting = Cyrc.DSM_GAIN_4X;
               break;
           case 8:
               gainSetting = Cyrc.DSM_GAIN_8X;
               break;
           default:
               gainSetting = Cyrc.ADC_IBG_1X;
               break;

       }

       tmpReg = DsmBuf1Reg[config] & ~Cyrc.DSM_GAIN_MASK;
       tmpReg |= gainSetting;
       DsmBuf1Reg[config] = tmpReg;

   }
  
}

void SetBufferMode(uint mode, uint config)
{
    uint tmp = 0;
    
    if (mode == Cyrc.BUF_MODE_BYPASS_BUFFER)
    {
        DsmBuf0Reg[config] = Cyrc.DSM_BYPASS_P;   // Bypass positive buffer channel
        DsmBuf1Reg[config] = Cyrc.DSM_BYPASS_N;   // Bypass negative buffer channel
        DsmBuf2Reg[config] = 0x00;              // Disable power and RC
        DsmBuf3Reg[config] = 0x00;              // Disable chopper
    }
    else if (mode == Cyrc.BUF_MODE_RAIL_TO_RAIL)
    {
        tmp |= Cyrc.DSM_ENABLE_P;//Enable positive buffer
        tmp |= Cyrc.DSM_RAIL_RAIL_EN;//Enables Rail to Rail operation
        DsmBuf0Reg[config] = tmp;
        if (ADC_Input_Mode == Cyrc.INPUT_MODE_SINGLE)     
        {            
            tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
            tmp |= Cyrc.DSM_BYPASS_N;//Bypasses the negative buffer
            DsmBuf1Reg[config] = tmp;
        }
        else
        {
            tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
            tmp |= Cyrc.DSM_ENABLE_N;//Enable the negative buffer
            DsmBuf1Reg[config] = tmp;
        }
    }
    else if (mode == Cyrc.BUF_MODE_LEVEL_SHIFT)
    {
        tmp |= Cyrc.DSM_ENABLE_P;//Enables postive buffer
        DsmBuf0Reg[config] = tmp;
        
        tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
        tmp |= Cyrc.DSM_ENABLE_N;//Enable the negative buffer
        DsmBuf1Reg[config] = tmp;
    }
    
    // Enable the chopping only if both the input buffers are enabled 
    if (((DsmBuf0Reg[config] & Cyrc.DSM_ENABLE_P) != 0) && ((DsmBuf1Reg[config] & Cyrc.DSM_ENABLE_N) != 0 ))
    {
        DsmBuf3Reg[config] = Cyrc.DSM_BUF_CHOP_EN | Cyrc.DSM_BUF_FCHOP_FS8;
    }
    else
    {
         DsmBuf3Reg[config] = 0x00;
    }      
}


/// <summary> 
/// Sets reference for ADC
/// </summary>
/// <param name="refMode">Reference configuration.</param>
/// <param name="inputMode">ipnut range selcted.</param>
/// <param name="config">configuration selected.</param>
/// <param name="isPSOC3">silicon selected.</param>
/// <param name="vdda">vdda value entered in the system wide resource file. Based on this value
///                   reference will be selected.</param>
void SetRef(uint refMode, uint inputMode, uint config, bool isPSOC3, float vdda)
{
    // Mask off reference 
    DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;

    // Connect the switch matrix for the proper reference mode 
    if (inputMode != Cyrc.ADC_IR_VSSA_TO_VDDA)
    {
        switch (refMode)
        {
            case Cyrc.ADC_INT_REF_NOT_BYPASSED:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_BYPASSED_ON_P32:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN | 
                                     Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_BYPASSED_ON_P03:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_EXT_REF_ON_P03:
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN;
                if (inputMode == Cyrc.ADC_IR_VSSA_TO_2VREF)
                {
                    DsmRef3Reg[config] = Cyrc.DSM_REF3_S9_EN | Cyrc.DSM_REF3_S11_EN | Cyrc.DSM_REF3_S12_EN;
                    DsmRef0Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF_INN;
                }
                else
                {
                    DsmRef3Reg[config] = Cyrc.DSM_REF3_S9_EN | Cyrc.DSM_REF3_S11_EN;
                }
                DsmCr17Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF;  // Disable Int Ref Amp 
                break;

            case Cyrc.ADC_EXT_REF_ON_P32:
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S2_EN | Cyrc.DSM_REF2_S5_EN | Cyrc.DSM_REF2_S6_EN;
                if (inputMode == Cyrc.ADC_IR_VSSA_TO_2VREF)
                {
                    DsmRef3Reg[config] = Cyrc.DSM_REF3_S12_EN;
                    DsmRef0Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF_INN;
                }
                else
                {
                    DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                }
                DsmCr17Reg[config] &= ~Cyrc.DSM_EN_BUF_VREF;   // Disable Int Ref Amp 
                break;
                
            case Cyrc.ADC_INT_REF_VDDA_4:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P03:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P32:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN | 
                                      Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_VDDA_3:    
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P03:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P32:
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN;
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN | 
                                     Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            default:
                break;
        }
    }
    else  // VSSA to VDDA
    {
        if (isPSOC3)
        {
            if (vdda < MAX_VDDA3_VALUE)
            {
                DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
            }
            else
            {
                DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
            }
        }
        else
        {
            DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN|Cyrc.DSM_VCMSEL_0_8V);
        }
        switch (refMode)
        {
            case Cyrc.ADC_INT_REF_NOT_BYPASSED:
            case Cyrc.ADC_INT_REF_VDDA_4:
            case Cyrc.ADC_INT_REF_VDDA_3:
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S3_EN | Cyrc.DSM_REF2_S4_EN | Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_BYPASSED_ON_P32:
            case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P32:
            case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P32:
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S0_EN | Cyrc.DSM_REF2_S1_EN | Cyrc.DSM_REF2_S2_EN | 
                                     Cyrc.DSM_REF2_S6_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_NO_SW;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_INT_REF_BYPASSED_ON_P03:
            case Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P03:
            case Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P03:
                DsmRef2Reg[config] = Cyrc.DSM_REF2_S6_EN | Cyrc.DSM_REF2_S7_EN;
                DsmRef3Reg[config] = Cyrc.DSM_REF3_S8_EN | Cyrc.DSM_REF3_S9_EN;
                DsmCr17Reg[config] |= Cyrc.DSM_EN_BUF_VREF;  // Enable Int Ref Amp 
                break;

            case Cyrc.ADC_EXT_REF_ON_P03:
            case Cyrc.ADC_EXT_REF_ON_P32:                    
            default:
                break;

        }
    }
}


/// <summary>
/// Sets input range of the ADC independent of the input buffer gain.
/// </summary>
/// <param name="inputMode">ADC input configuration mode.</param>
/// <param name="refVoltage">Reference voltage selected in the reference voltage numerical up down menu..</param>
/// <param name="config">ADC configuration number.</param>
/// <param name="isPSOC3">Flag to identify the silicon version selected is PSoC3 or later</param>
/// <param name="vdda">Vdda value entered in the system wide resource file. Based on this value reference
///         will be selected for Vssa to Vdda input range.</param>
void SetInputRange(uint inputMode, float refVoltage, uint config, bool isPSOC3, float vdda)
{
    //uint CapRatio;
    double[] DesiredGain =  {1.000, 1.000, 0.250, 0.167, 1.000, 0.500, 0.167, 2.000, 4.000, 8.000, 16.000 };
    uint[] IPCap1_Res8to15  = { 896,  896, 1088, 992,  896,  1088, 992, 1600, 2800,  3488,  5696};
    uint[] IPCap1_Res16to20 = {3888, 3888, 1392, 992,  3888, 2192, 992, 6000, 12000, 17588, 17200};
    uint[] DACCap_Res8to15  = { 992,  992, 4896, 6000,  992, 2496, 6000,  896,   800,   496,   400};
    uint[] DACCap_Res16to20 = {4400, 4400, 6192, 6000, 4400, 4896, 6000, 3392,  3392,  2496,  1200};
    uint IPCap1_Res8to15_Vdda_3 = 1088;
    uint IPCap1_Res16to20_Vdda_3 = 1888;
    uint DACCap_Res8to15_Vdda_3 = 3600;
    uint DACCap_Res16to20_Vdda_3 = 6288;
    double DesiredGain_Vdda_3 = 0.333;
    // Resolution                      8       9      10      11      12     13      14     15
    double[] Decimator_Ratio_Gain = {1.000, 0.8205, 0.9377, 0.9875, 1.000, 0.9066, 0.9368, 0.9866};
    
    double Ideal_DecGain, DecGain;
    double CapRatio;
    uint OffsetCorrection, resolution;

    resolution = ADC_Resolution[config];
    resolution -= Cyrc.MIN_RESOLUTION;

    // Default setting
    
    if (ADC_Resolution[config] > 15)  // 16 to 20 bit resolution
    {
        if ((vdda < MAX_VDDA3_VALUE) && (inputMode == Cyrc.ADC_IR_VSSA_TO_VDDA) && isPSOC3)
        {
            IPCap1Value[config] = IPCap1_Res16to20_Vdda_3;
            DACCapValue[config] = DACCap_Res16to20_Vdda_3;
            CapRatio = ((double)IPCap1_Res16to20_Vdda_3 / DACCap_Res16to20_Vdda_3);
            DecGain = (DesiredGain_Vdda_3 / CapRatio);
        }
        else
        {
            IPCap1Value[config] = IPCap1_Res16to20[inputMode];
            DACCapValue[config] = DACCap_Res16to20[inputMode];
            CapRatio = ((double)IPCap1_Res16to20[inputMode] / DACCap_Res16to20[inputMode]);
            DecGain = (DesiredGain[inputMode] / CapRatio);
            
        }
        
        Ideal_DecGain = Math.Round((DecGain*1.000), 5);
        Ideal_Dec_Gain[config] = (uint)Math.Truncate(Ideal_DecGain * Cyrc.IDEAL_GAIN_CONST);
        Ideal_OddDec_Gain[config] = (uint)Cyrc.IDEAL_GAIN_CONST;
    }
    else                              // 8 to 15 bits of resolution
    {
        if ((vdda < MAX_VDDA3_VALUE) && (inputMode == Cyrc.ADC_IR_VSSA_TO_VDDA) && isPSOC3)
        {
            IPCap1Value[config] = IPCap1_Res8to15_Vdda_3;
            DACCapValue[config] = DACCap_Res8to15_Vdda_3;
            CapRatio = ((double)IPCap1_Res8to15_Vdda_3 / DACCap_Res8to15_Vdda_3);
            DecGain = (DesiredGain_Vdda_3 / CapRatio);
        }
        else
        {
            IPCap1Value[config] = IPCap1_Res8to15[inputMode];
            DACCapValue[config] = DACCap_Res8to15[inputMode];
            CapRatio = ((double)IPCap1_Res8to15[inputMode] / DACCap_Res8to15[inputMode]);
            DecGain = (DesiredGain[inputMode] / CapRatio);
        }
        Ideal_DecGain = DecGain;
        Ideal_DecGain = Math.Round(Ideal_DecGain, 5);
        Ideal_Dec_Gain[config] = (uint)Math.Truncate(Ideal_DecGain * Cyrc.IDEAL_GAIN_CONST);
        
        Ideal_OddDec_Gain[config] = (uint)Math.Truncate(Decimator_Ratio_Gain[resolution] * Cyrc.IDEAL_GAIN_CONST);
    }
    // Convert the double into hex value and feed that into the reg 

    // Configure Ref switches, reference, and input buffer
    switch (inputMode)
    {
        
        case Cyrc.ADC_IR_VSSA_TO_VREF: // Single ended, Vssa to Vref
            // Set Single Ended input and disable negative buffer
            
            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config]|= Cyrc.DSM_REFMUX_1_024V;

            // Set modulator gain input caps to a gain of 1
            
            // Connect negative input to Vssa
            DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;
            
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 1;
            ADC_Input_RangeValue[config] = Math.Round(refVoltage, 4);
            break;

        case Cyrc.ADC_IR_VSSA_TO_2VREF: // Single ended, Vssa to 2*Vref
        
            uint rShiftOffset = 1;
            // Settings based on selected silicon revision 
            if (isPSOC3)
            {  
                // Input is connected as differential with Vref conencted to negative input
                // Set reference mux to 1.024V reference
                DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
                DsmRef0Reg[config] |= Cyrc.DSM_EN_BUF_VREF_INN;  // newly added as per CDT 93460.
                if (Input_Buffer_Mode[config] != 0)
                {
                    DsmBuf1Reg[config] = Cyrc.DSM_ENABLE_N;
                    DsmBuf3Reg[config] = Cyrc.DSM_BUF_CHOP_EN | Cyrc.DSM_BUF_FCHOP_FS8;
                    SetBufferGain(Input_Buffer_Gain[config], config);
                }
                
                if (ADC_Resolution[config] > 15)
                {
                    OffsetCorrection = (uint)(Math.Pow(2, ADC_Resolution[config]- 1) / Ideal_DecGain);
                }
                else
                {
                    Ideal_DecGain = Math.Round((DecGain * Decimator_Ratio_Gain[resolution]), 5);
                    OffsetCorrection = (uint)(Math.Pow(2, ADC_Resolution[config]- 1) / Ideal_DecGain);
                }
                DecOcorReg[config]  = BitConverter.GetBytes(OffsetCorrection)[0];
                DecOcormReg[config] = BitConverter.GetBytes(OffsetCorrection)[1];
                DecOcorhReg[config] = BitConverter.GetBytes(OffsetCorrection)[2];            
            }
            else
            {            
                // Set reference mux to 1.024V reference
                DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
                DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
    
                // Set modulator gain input caps to a gain of 1
                // Default setting
    
                // Connect negative input to Vssa
                DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;
    
                // Set input gain to 2
                DsmCr5Reg[config] = Cyrc.DSM_IPCAP1_1600FF;
                DsmCr6Reg[config] = Cyrc.DSM_DACCAP_3200FF;
                
                // Set resolution constants from table 
                // For 0 to 2*Vref mode with PSoC5A silicon
                //   we are using old values for DR1, Shift1 and Shift2 registers 
                DecDr1Reg[config] = CyresSettings.dr1_2VREF_ES2[resolution];
                DecShift1Reg[config] = CyresSettings.shift1_2VREF_ES2[resolution];

                DecShift2Reg[config] = CyresSettings.shift2_2VREF_ES2[resolution] - rShiftOffset;
            }
            
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 1;
            ADC_Input_RangeValue[config] = Math.Round(2 * refVoltage, 4);
            break;

       case Cyrc.ADC_IR_VSSA_TO_6VREF:
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

            // Set modulator gain input caps to a gain of 6
            // Default setting

            // Connect negative input to Vssa
            DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;
       
            
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 1;
            ADC_Input_RangeValue[config] = Math.Round(6 * refVoltage, 4);
            break;

        case Cyrc.ADC_IR_VSSA_TO_VDDA:  // Single ended, Vssa to Vdda
                                      // Vref = Vdda/4, Input gain = 1/2
                                      // INN = Vref, differential mode
            if (isPSOC3)
            {
                if (vdda < MAX_VDDA3_VALUE)
                {
                    // Set reference mux to VDA/3 reference
                    DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_3 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
                }
                else
                {
                    // Set reference mux to VDA/4 reference
                    DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
                }
            }
            else
            {
                DsmRef0Reg[config] = (Cyrc.DSM_REFMUX_VDA_4 | Cyrc.DSM_VREF_RES_DIV_EN | Cyrc.DSM_VCMSEL_0_8V);
            }
            ADC_Input_RangeValue[config] = Math.Round(vdda, 4);
            // Connect negative input to Vssa
            DsmSw3Reg[config] = Cyrc.DSM_VN_VSSA;
            
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 1;
            break;

        case Cyrc.ADC_IR_VNEG_VREF_DIFF:  // Diff, -Input +/- Vref

            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

            // Set modulator gain input caps to a gain of 1
            // disconnect references from -Input
            DsmSw3Reg[config] = 0x00;
            
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(refVoltage, 4);

            break;

        case Cyrc.ADC_IR_VNEG_2VREF_DIFF:  // Diff, -Input +/- 2*Vref

            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

            // disconnect references from -Input
            DsmSw3Reg[config] = 0x00;
            
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(2 * refVoltage, 4);
            break;
            
        case Cyrc.ADC_IR_VNEG_6VREF_DIFF:
        
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

            // Set modulator gain input caps to a gain of 6
            // Default setting

            // Connect negative input to Vssa
            DsmSw3Reg[config] = 0x00;
  
            // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(6 * refVoltage, 4);
            break;

        case Cyrc.ADC_IR_VNEG_VREF_2_DIFF:  // Diff, -Input +/- Vref/2
        
            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

            // disconnect references from -Input
            DsmSw3Reg[config] = 0x00;
            
             // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(refVoltage / 2, 4);
            break;


        case Cyrc.ADC_IR_VNEG_VREF_4_DIFF:  // Diff, -Input +/- Vref/4
        
            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;

            // disconnect references from -Input
            DsmSw3Reg[config] = 0x00;
            
             // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(refVoltage / 4, 4);
            break;

        case Cyrc.ADC_IR_VNEG_VREF_8_DIFF:

            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
          
            // disconnect references from -Input
            DsmSw3Reg[config] = 0x00;
            
             // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(refVoltage / 8, 4);

            break;


       case Cyrc.ADC_IR_VNEG_VREF_16_DIFF :
 
            // Set reference mux to 1.024V reference
            DsmRef0Reg[config] &= ~Cyrc.DSM_REFMUX_MASK;
            DsmRef0Reg[config] |= Cyrc.DSM_REFMUX_1_024V;
           
            // disconnect references from -Input
            DsmSw3Reg[config] = 0x00;
            
             // Set input mode and input range value 
            ADC_Input_ModeValue[config] = 2;
            ADC_Input_RangeValue[config] = Math.Round(refVoltage / 16, 4);

            break;

        default:
            break;
    }
}


/// <summary>
/// Sets operatonal mode of the Modulator input buffer.
///  Buffer modes   
///     Bypass P input => Bypass P input amp  ( Default, not bypassed )
///     Bypass N input => Bypass N input amp  ( Default, not bypassed )
///     Rail-To-Rail   => Enable mode for inputs to swiing rail to rail ( Default, not rail-to-rail)
///     Enable Filter  => Enable output R/C filter (Default, no filter )
///     Low Power      => Enable low power mode (Defalt, normal power mode )
/// </summary>
/// <param name="bufMode">Buffer mode value</param>
/// <param name="config">Configuration selected</param>
void SetBuffer(uint bufMode, uint config)
{

    uint tmp = 0;

    // Setup BUF0 Register 
    // Check for positive buffer being bypassed 
    if ((bufMode & Cyrc.BUF_BYPASS_POS) > 0)
    {
        tmp |= Cyrc.DSM_BYPASS_P;
    }
    else /// POS buffer not bypassed, turn on buffer 
    {
        // If input gain is 0, then bypass positive channel buffer
        if (Input_Buffer_Gain[config] != 0)
            tmp |= Cyrc.DSM_ENABLE_P;
        else
            tmp |= Cyrc.DSM_BYPASS_P;
    }

    // Check for rail to rail operation 
    if ((bufMode & Cyrc.BUF_RAIL_TO_RAIL) > 0)
    {
        tmp |= Cyrc.DSM_RAIL_RAIL_EN;
    }

    DsmBuf0Reg[config] = tmp;   // Set Buf0 Register 


    // Setup BUF1 Register 
    // Check for negative buffer being bypassed, but don't mess with gain. 
    tmp = DsmBuf1Reg[config] & Cyrc.DSM_GAIN_MASK;
    if ((bufMode & Cyrc.BUF_BYPASS_NEG) > 0)
    {
        tmp |= Cyrc.DSM_BYPASS_N;
    }
    else // NEG buffer not bypassed, turn on buffer 
    {
        // If input buffer gain is 0, then disable negative channel buffer
        if (Input_Buffer_Gain[config] != 0)
            tmp |= Cyrc.DSM_ENABLE_N;
        else
            tmp |= Cyrc.DSM_BYPASS_N;
    }
    DsmBuf1Reg[config] = tmp;   // Set Buf1 Register 



    // Setup BUF2 Register 
    tmp = 0;
    // Check for Low Power 
    if ((bufMode & Cyrc.BUF_LOW_PWR)> 0)
    {
        tmp |= Cyrc.DSM_ENABLE_N;
    }

    // Check for Filer enable 
    if ((bufMode & Cyrc.BUF_FILTER_EN)> 0)
    {
        tmp |= Cyrc.DSM_ADD_EXTRA_RC;
    }
    DsmBuf2Reg[config] = tmp;   // Set Buf2 Register 

    // If both the positive and negative buffers are enabled, enable chopping.
    if (((DsmBuf0Reg[config] & Cyrc.DSM_ENABLE_P) != 0) && ((DsmBuf1Reg[config] & Cyrc.DSM_ENABLE_N) != 0 ))
    {
        DsmBuf3Reg[config] = Cyrc.DSM_BUF_CHOP_EN | Cyrc.DSM_BUF_FCHOP_FS8;
    }
    else
    {
        DsmBuf3Reg[config] = 0x00;
    }

}


/// <summary>
/// Calculates the frequency required for the given resolution, sample rate,
///  and conversion mode.
/// </summary>
/// <param name="resolution">resolution selected</param>
/// <param name="sampleRate">sample rate selected</param>
/// <param name="conversionMode">conversin mode selected</param>
/// <returns>Desired clock frequency.</returns>
static public uint SetClock(uint resolution, uint sampleRate, uint conversionMode)
{
    uint clockFrequency;
    uint clocksPerSample;

    clocksPerSample = ClocksPerSample(resolution, conversionMode);
    
    clockFrequency = clocksPerSample * sampleRate;
  
    return clockFrequency;
}


/// <summary>
/// Calculates the maximum/minimum sample rate required for the given resolution, frequency,
///  and conversion mode.
/// </summary>
/// <param name="resolution">resolution selected</param>
/// <param name="frequency">Frequency calculated</param>
/// <param name="conversionMode">Conversion mode selected</param>
/// <param name="maximum">Maximum sample rate</param>
/// <returns>Desired sample rate</returns>
static public uint GetSampleRate(uint resolution, float frequency, uint conversionMode, bool maximum)
{
    uint sampleRate;
    uint clocksPerSample;

    clocksPerSample = ClocksPerSample(resolution, conversionMode);

    if (maximum)
    {
        sampleRate = (uint) (frequency / clocksPerSample);
    } else 
    {
        sampleRate = (uint) Math.Ceiling(frequency / clocksPerSample);
    }
  
    return sampleRate;
}


/// <summary>
/// Calculates how may ADC clocks are required per sample
/// </summary>
/// <param name="resolution">Resolution between 8 and 20</param>
/// <param name="conversionMode">Mode of operation</param>
/// <returns>Clocks required for a single sample.</returns>
static public uint ClocksPerSample(uint resolution, uint conversionMode)
{
    uint resIndex;
    uint clocksPerSample;

    // Make sure resolution in not out of range.
    if (resolution < Cyrc.MIN_RESOLUTION)
    {
        resolution = Cyrc.MIN_RESOLUTION;
    }

    if (resolution > Cyrc.MAX_RESOLUTION)
    {
        resolution = Cyrc.MAX_RESOLUTION;
    }

    resIndex = resolution - Cyrc.MIN_RESOLUTION;
    switch (conversionMode)
    {
        case Cyrc.ADC_CM_SINGLE_SAMPLE:
            clocksPerSample = (((CyresSettings.dr1[resIndex] + 1) * 4) + 3) * (CyresSettings.dr2[resIndex] + 1);
            break;

        case Cyrc.ADC_CM_FAST_FILER:
            clocksPerSample = (((CyresSettings.dr1[resIndex] + 1) * 4) + 3) * (CyresSettings.dr2[resIndex] + 1);
            break;

        case Cyrc.ADC_CM_CONTINUOUS:
            clocksPerSample = (CyresSettings.dr1[resIndex] + 1) * (CyresSettings.dr2[resIndex] + 1);
            break;

        case Cyrc.ADC_CM_FAST_FIR:
            clocksPerSample = (((CyresSettings.dr2[resIndex] + 1) + 3) * (CyresSettings.dr1[resIndex] + 1)) + 6;
            break;

        default:
            clocksPerSample = (((CyresSettings.dr2[resIndex] + 1) + 3) * (CyresSettings.dr1[resIndex] + 1)) + 4;
            break;
    };

    return clocksPerSample;
}


/// <summary>
/// Calculates the clocks per volt scale factor for the voltage conversion functions.
/// </summary>
/// <param name="resolution">Resolution between 8 and 20 </param>
/// <param name="inputRange">input range selected</param>
/// <param name="refVoltage">refVoltage set in the customizer</param>
/// <param name="config">configuration selected</param>
/// <param name="vdda">Vdda value set in the DWR file</param>
/// <returns>Counts per Volt</returns>
static public uint CalcCountsPerVolt(uint resolution, uint inputRange, float refVoltage,uint config, float vdda)
{
    float []countsPerVolt;
    uint counts = 1;
    uint i;

    countsPerVolt = new float[4];

    // Raise counts to the 2^resolution
    for(i=0; i < resolution; i++)
    {
        counts *= 2;
    }

    switch (inputRange)
    {
        case Cyrc.ADC_IR_VSSA_TO_VREF:  // Vssa to Vref
            countsPerVolt[config] = counts / refVoltage; 
            break;

        case Cyrc.ADC_IR_VSSA_TO_2VREF:   // Vssa to 2*Vref
            countsPerVolt[config] = counts / (refVoltage * 2); 
            break;       

        case Cyrc.ADC_IR_VSSA_TO_6VREF:   // Vssa to 6*Vref
            countsPerVolt[config] = counts / (refVoltage *6); 
            break;
            
        case Cyrc.ADC_IR_VSSA_TO_VDDA:   // Vssa to Vdda
            countsPerVolt[config] = counts / vdda;
            break;

        case Cyrc.ADC_IR_VNEG_VREF_DIFF:   // -Vin +/- Vref (Diff)
            countsPerVolt[config] = counts / ( refVoltage * 2); 
            break;

        case Cyrc.ADC_IR_VNEG_2VREF_DIFF:  // -Vin +/- 2*Vref (Diff)
            countsPerVolt[config] = counts / ( refVoltage * 4); 
            break;
            
        case Cyrc.ADC_IR_VNEG_6VREF_DIFF:  // -Vin +/- 6*Vref (Diff)
            countsPerVolt[config] = counts / ( refVoltage * 12); 
            break;

        case Cyrc.ADC_IR_VNEG_VREF_2_DIFF:  // -Vin +/- 0.5Vref (Diff)
            countsPerVolt[config] = (counts * 2) / (refVoltage * 2); 
            break;

        case Cyrc.ADC_IR_VNEG_VREF_4_DIFF:  // -Vin +/- 0.25Vref (Diff)
            countsPerVolt[config] = (counts * 4) / (refVoltage * 2); 
            break;
        
        case Cyrc.ADC_IR_VNEG_VREF_8_DIFF:  // -Vin +/- 0.125Vref (Diff)
            countsPerVolt[config] = (counts * 8) / (refVoltage * 2); 
            break;
            
        case Cyrc.ADC_IR_VNEG_VREF_16_DIFF:  // -Vin +/- 0.0625Vref (Diff)
            countsPerVolt[config] = (counts * 16) / (refVoltage * 2); 
            break;

        default:
            countsPerVolt[config] = (counts*2) / refVoltage;
            break;
    };

    return Convert.ToUInt32(countsPerVolt[config]);
}

/// <summary>
/// Calculates the frequency required for the external charge pump clock
/// </summary>
/// <param name="resolution">adcClockFrequency calculated</param>
/// <returns>Desired Charge pump clock frequency.</returns>
static public uint GetChargePumpClock(uint adcClockFrequency)
{
    uint cpClockFrequency;

    cpClockFrequency = ((4 * adcClockFrequency > Cyrc.MAXCHARGEPUMPCLOCK)?(Cyrc.MAXCHARGEPUMPCLOCK) : 
                        ((4 * adcClockFrequency < Cyrc.MINCHARGEPUMPCLOCK) ? (Cyrc.MINCHARGEPUMPCLOCK) : 
                        (4 * adcClockFrequency)));
    return cpClockFrequency;
}


/// <summary>
/// Calculate all register values.
/// </summary>
/// <param name="paramDict"></param>
/// <param name="isPSOC3"></param>
/// <param name="vdda"></param>
void CalcValues(ref Dictionary<string, string> paramDict, bool isPSOC3, float vdda)
     {
            uint tmp;
            uint i = 1;
            string tmpString = "";
            uint[] clockFrequency = new uint[4] {0, 0, 0, 0};
            uint[] cpClockFrequency = new uint[4] {0, 0, 0, 0};
            uint[] clocksPerCycle = new uint[4] {0, 0, 0, 0};
         
            List<CyClockData> clkdata = m_termQuery.GetClockData(Resource.ClockText, 0);
            ICyDesignQuery_v1 desquery = m_instQuery.DesignQuery;
            
            // Read all the paramters, since register values are based on them.
            paramDict.TryGetValue(ADC_ClockParamName, out tmpString);
            ADC_Clock = uint.Parse(tmpString);

            paramDict.TryGetValue(ADC_Input_ModeParamName, out tmpString);
            ADC_Input_Mode = uint.Parse(tmpString);
              
            paramDict.TryGetValue(Start_of_ConversionParamName, out tmpString);
            Start_of_Conversion = uint.Parse(tmpString);

            paramDict.TryGetValue(ConfigParamName, out tmpString);
            NumConfigs = uint.Parse(tmpString);
                  
            paramDict.TryGetValue(ADC_ChargePumpParamName, out tmpString);
            ADC_ChargePump = uint.Parse(tmpString);
            
            paramDict.TryGetValue(ADC_nVrefParamName, out tmpString);
            ADC_nVref = uint.Parse(tmpString);
        
            DsmMiscReg = Cyrc.DSM_SEL_ECLK_CP;
            DsmClkReg |= (Cyrc.DSM_CLK_BYPASS_SYNC | Cyrc.DSM_CLK_CLK_EN);
            DsmRef1Reg = 0x00;
             
//            if (ADC_ChargePump == 0)
//            {
//                DsmMiscReg = rc.DSM_SEL_ICLK_CP;
//            }
            
            if (ADC_nVref == 1)
            {
                DsmRef1Reg = Cyrc.DSM_DAC_GND_SEL_EXT;
            }         
            // Add code Here
            paramDict.Add(DSM_MISC_ParamName, HEX_PREFIX + DsmMiscReg.ToString(HEX_FORMAT1) + FORMAT_SPECIFIER);
            paramDict.Add(DSM_CLK_ParamName, HEX_PREFIX + DsmClkReg.ToString(HEX_FORMAT1) + FORMAT_SPECIFIER);
            paramDict.Add(DSM_REF1_ParamName, HEX_PREFIX + DsmRef1Reg.ToString(HEX_FORMAT1) + FORMAT_SPECIFIER);

              
            for (i = 0; i < Cyrc.MAX_CONFIGS; i++)
            {
                paramDict.TryGetValue(ADC_Input_RangeParamName[i], out tmpString);
                ADC_Input_Range[i] = uint.Parse(tmpString);          
          
                paramDict.TryGetValue(ADC_ReferenceParamName[i], out tmpString);
                ADC_Reference[i] = uint.Parse(tmpString);
                
                paramDict.TryGetValue(ADC_ResolutionParamName[i], out tmpString);
                ADC_Resolution[i] = uint.Parse(tmpString);
                
                paramDict.TryGetValue(Conversion_ModeParamName[i], out tmpString);
                Conversion_Mode[i] = uint.Parse(tmpString);
                
                paramDict.TryGetValue(Input_Buffer_GainParamName[i], out tmpString);
                Input_Buffer_Gain[i] = uint.Parse(tmpString);
                
                paramDict.TryGetValue(Sample_RateParamName[i], out tmpString);
                Sample_Rate[i] = uint.Parse(tmpString);
                
                paramDict.TryGetValue(Ref_VoltageParamName[i], out tmpString);
                Ref_Voltage[i] = float.Parse(tmpString);
                if (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_VDDA)
                {
                    if (vdda < MAX_VDDA3_VALUE)
                    {
                        Ref_Voltage[i] = vdda / 3;
                    }
                    else
                    {
                        Ref_Voltage[i] = vdda / 4;
                    }
                }
                else
                {
                    if ((ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_3) || 
                        (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P03) ||
                        (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_3_BYPASSED_ON_P32))
                    {
                        Ref_Voltage[i] = vdda / 3;
                    }
                    else if ((ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_4) ||
                             (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P03) ||
                             (ADC_Reference[i] == Cyrc.ADC_INT_REF_VDDA_4_BYPASSED_ON_P32))
                    {
                        Ref_Voltage[i] = vdda / 4;
                    }
                }
                
                paramDict.TryGetValue(Input_Buffer_ModeParamName[i], out tmpString);
                Input_Buffer_Mode[i] = uint.Parse(tmpString);
              

                // First, setup the default settings.
                //   DecCrReg    See below
                DecSrReg[i] = Cyrc.DEC_INTR_PULSE | Cyrc.DEC_INTR_CLEAR;
                DecOcorReg[i] = 0x00;
                DecOcormReg[i] = 0x00;
                DecOcorhReg[i] = 0x00;

                DecCoherReg[i] = Cyrc.DEC_SAMP_KEY_LOW;
                DsmCr0Reg[i] = Cyrc.DSM_QLEV_9 | Cyrc.DSM_NONOV_HIGH;
                DsmCr1Reg[i] = 0x00;
                // Chop freq must be higher than Decimation rate. (Divider lower) 
                DsmCr2Reg[i] = (Cyrc.DSM_MOD_CHOP_EN | Cyrc.DSM_FCHOP_DIV8) | Cyrc.DSM_RESET1_EN | 
                                Cyrc.DSM_RESET2_EN | Cyrc.DSM_RESET3_EN;
                DsmCr3Reg[i] = 0x00;
                DsmCr13Reg[i] = 0x00;
                DsmRef0Reg[i] = Cyrc.DSM_VCMSEL_0_8V | Cyrc.DSM_REFMUX_1_024V;
                DsmRef2Reg[i] = 0x00;
                DsmRef3Reg[i] = 0x00;
                DsmDem0Reg[i] = Cyrc.DSM_EN_SCRAMBLER0 | Cyrc.DSM_EN_SCRAMBLER1 | Cyrc.DSM_EN_DEM;
                DsmDem1Reg[i] = 0x00;
                DsmBuf0Reg[i] = Cyrc.DSM_ENABLE_P | Cyrc.DSM_RAIL_RAIL_EN;
                DsmBuf1Reg[i] = Cyrc.DSM_ENABLE_N | (Input_Buffer_Gain[i] << 2);
                DsmBuf2Reg[i] = Cyrc.DSM_LOWPOWER_EN;
                DsmBuf3Reg[i] = 0x00;
                DsmOut0Reg[i] = 0;
                DsmOut1Reg[i] = 0;
                DecGvalReg[i] = 0x00;
                
               // GVAL reg setting based on Resolution 
                if (ADC_Resolution[i] > 13)
                {
                    DecGvalReg[i] = Cyrc.DEC_GVAL_MAX;
                }
                else
                {
                    DecGvalReg[i] = (ADC_Resolution[i] + 1);
                }

                clockFrequency[i] = SetClock(ADC_Resolution[i], Sample_Rate[i], Conversion_Mode[i]);                
                cpClockFrequency[i] = GetChargePumpClock(clockFrequency[i]);
                // Setup cap settings.
                if (ADC_Resolution[i] > 15)    // 16 to 20 bit Resolution
                {
                    DsmCr4Reg[i] = Cyrc.DSM_FCAP1_1600FF | Cyrc.DSM_FCAP1_6400FF;
                    if ((vdda < MAX_VDDA3_VALUE) && (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_VDDA) && isPSOC3)
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_16_20_Vdda_3;
                        DsmCr6Reg[i] = Cyrc.DacCap_16_20_Vdda_3;
                    }
                    else
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_16_20[ADC_Input_Range[i]];
                        DsmCr6Reg[i] = Cyrc.DacCap_16_20[ADC_Input_Range[i]];
                    }
                    DsmCr7Reg[i] = Cyrc.CapOffset_16_20[ADC_Input_Range[i]];

                    // Power settings 
                    //DsmCr14Reg[i] = rc.DSM_POWER1_2 | rc.DSM_OPAMP1_BW_0;
                    //DsmCr15Reg[i] = rc.DSM_POWER_12MHZ | rc.DSM_POWER2_3_HIGH;
                    if ((Cyrc.HIGH_FREQ_16BIT / 4) <= clockFrequency[i] &&  clockFrequency[i] <= Cyrc.HIGH_FREQ_16BIT)
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_2 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_NORMAL | Cyrc.DSM_POWER2_3_HIGH;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_HIGH | Cyrc.DSM_CP_PWRCTL_TURBO;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_2 | Cyrc.DSM_PWR_CTRL_VCM_2 | 
                                         Cyrc.DSM_PWR_CTRL_VREF_INN_3;
                        DsmBuf2Reg[i] &= ~Cyrc.DSM_LOWPOWER_EN;
                    }
                    else if ((Cyrc.HIGH_FREQ_16BIT / 16) <= clockFrequency[i] && clockFrequency[i] < 
                              (Cyrc.HIGH_FREQ_16BIT / 4))
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_1 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_NORMAL | Cyrc.DSM_POWER2_3_MED;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_MED | Cyrc.DSM_CP_PWRCTL_2X;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_1 | Cyrc.DSM_PWR_CTRL_VCM_1 | 
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_2;
                        //DsmBuf2Reg[i] |= rc.DSM_LOWPOWER_EN;
                    }
                    else
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_0 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_VERYLOW | Cyrc.DSM_POWER2_3_LOW;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_LOW | Cyrc.DSM_CP_PWRCTL_HIGH;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_0 | Cyrc.DSM_PWR_CTRL_VCM_0 | 
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_1;
                        //DsmBuf2Reg[i] |= rc.DSM_LOWPOWER_EN;
                        //DsmCr16Reg[i] = rc.DSM_POWER_SUM_HIGH | rc.DSM_CP_PWRCTL_DEFAULT;
                        //DsmCr17Reg[i] = rc.DSM_EN_BUF_VCM | rc.DSM_PWR_CTRL_VREF_2 | rc.DSM_PWR_CTRL_VCM_2 | 
                        //rc.DSM_PWR_CTRL_VREF_INN_2;
                    }
                    
                }
                else   // 8 to 15 bit resolution
                {
                    DsmCr4Reg[i] = Cyrc.DSM_FCAP1_1600FF | Cyrc.DSM_FCAP1_400FF;
                    if ((vdda < MAX_VDDA3_VALUE) && (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_VDDA) && isPSOC3)
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_8_15_Vdda_3;
                        DsmCr6Reg[i] = Cyrc.DacCap_8_15_Vdda_3;
                    }
                    else
                    {
                        DsmCr5Reg[i] = Cyrc.IpCap1_8_15[ADC_Input_Range[i]];
                        DsmCr6Reg[i] = Cyrc.DacCap_8_15[ADC_Input_Range[i]];
                    }
                    DsmCr7Reg[i] = 0x00;

                    // Power settings 
                    //DsmCr14Reg[i] = rc.DSM_POWER1_2 | rc.DSM_OPAMP1_BW_0;
                    //DsmCr15Reg[i] = rc.DSM_POWER_12MHZ | rc.DSM_POWER2_3_HIGH;
                    if ((Cyrc.HIGH_FREQ_12BIT / 4) <= clockFrequency[i] && clockFrequency[i] <= Cyrc.HIGH_FREQ_12BIT)
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_2 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_6MHZ | Cyrc.DSM_POWER2_3_HIGH;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_HIGH | Cyrc.DSM_CP_PWRCTL_TURBO;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_2 | Cyrc.DSM_PWR_CTRL_VCM_2 | 
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_3;
                        DsmBuf2Reg[i] &= ~Cyrc.DSM_LOWPOWER_EN;
                    }
                    else if ((Cyrc.HIGH_FREQ_12BIT / 16) <= clockFrequency[i] && clockFrequency[i] < 
                             (Cyrc.HIGH_FREQ_12BIT / 4))
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_1 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_NORMAL | Cyrc.DSM_POWER2_3_MED;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_MED | Cyrc.DSM_CP_PWRCTL_2X;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_1 | Cyrc.DSM_PWR_CTRL_VCM_1 | 
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_2;
                        //DsmBuf2Reg[i] |= rc.DSM_LOWPOWER_EN;
                    }
                    else 
                    {
                        DsmCr14Reg[i] = Cyrc.DSM_POWER1_0 | Cyrc.DSM_OPAMP1_BW_0;
                        DsmCr15Reg[i] = Cyrc.DSM_POWER_VERYLOW | Cyrc.DSM_POWER2_3_LOW;
                        DsmCr16Reg[i] = Cyrc.DSM_POWER_SUM_LOW | Cyrc.DSM_CP_PWRCTL_HIGH;
                        DsmCr17Reg[i] = Cyrc.DSM_EN_BUF_VCM | Cyrc.DSM_PWR_CTRL_VREF_0 | Cyrc.DSM_PWR_CTRL_VCM_0 | 
                                        Cyrc.DSM_PWR_CTRL_VREF_INN_1;
                        //DsmBuf2Reg[i] |= rc.DSM_LOWPOWER_EN;
                        //DsmCr16Reg[i] = rc.DSM_POWER_SUM_HIGH | rc.DSM_CP_PWRCTL_DEFAULT;
                        //DsmCr17Reg[i] = rc.DSM_EN_BUF_VCM | rc.DSM_PWR_CTRL_VREF_2 | rc.DSM_PWR_CTRL_VCM_2 | 
                        //rc.DSM_PWR_CTRL_VREF_INN_2;
                    }
                }
                DsmCr8Reg[i] = Cyrc.DSM_IPCAP2_50_FF | Cyrc.DSM_FCAP2_100_FF; //Common to all resolutions
                DsmCr9Reg[i] = Cyrc.DSM_IPCAP3_50_FF | Cyrc.DSM_FCAP3_300_FF;
                DsmCr10Reg[i] = Cyrc.SumCap12_8_20[ADC_Input_Range[i]];
                DsmCr11Reg[i] = Cyrc.SumCap3Fb_8_20[ADC_Input_Range[i]];
                DsmCr12Reg[i] = Cyrc.SumCapin8_20[ADC_Input_Range[i]];

                DecCoherReg[i] = Cyrc.DEC_SAMP_KEY_LOW;
        
                SetResolution(ADC_Resolution[i], ADC_Input_Range[i], i, isPSOC3);
                SetBufferMode(Input_Buffer_Mode[i], i);
                if (Input_Buffer_Mode[i] != 0)
                {
                     SetBufferGain(Input_Buffer_Gain[i], i);
                }
                SetInputRange(ADC_Input_Range[i], Ref_Voltage[i], i, isPSOC3, vdda);
                SetRef(ADC_Reference[i], ADC_Input_Range[i], i, isPSOC3, vdda);
                
                // If the second decimator is not used, don't turn on the FIR filter
                if ((DecDr2Reg[i] == 0) && (DecDr2hReg[i] == 0))
                {
                    DecCrReg[i] = (Conversion_Mode[i] << 2) | (Start_of_Conversion << 1) | Cyrc.DEC_OCOR_EN | 
                                   Cyrc.DEC_GCOR_EN;
                }
                else
                {
                    DecCrReg[i] = (Conversion_Mode[i] << 2) | (Start_of_Conversion << 1) | Cyrc.DEC_FIR_EN | 
                                   Cyrc.DEC_OCOR_EN | Cyrc.DEC_GCOR_EN;
                    // To check whether Conversion mode is Single samle with resolution > 16 
                    tmp = DecCrReg[i] & 0x0C;
                    if (tmp == 0x00)
                    {
                        DecCrReg[i] |= (Cyrc.ADC_CM_FAST_FIR << 2);
                    }
                }
                
                // Disable gain correction feature for PSoC5A silicons 
                if (ADC_Input_Range[i] == Cyrc.ADC_IR_VSSA_TO_2VREF && isPSOC3 == false)
                {
                    DecCrReg[i] &= ~Cyrc.DEC_GCOR_EN;
                }
                
                // Write out the register constants
                paramDict.Add(DEC_CR_ParamName[i], HEX_PREFIX + DecCrReg[i].ToString(HEX_FORMAT1) + FORMAT_SPECIFIER);
                paramDict.Add(DEC_SR_ParamName[i], HEX_PREFIX + DecSrReg[i].ToString(HEX_FORMAT1) + FORMAT_SPECIFIER);
                paramDict.Add(DEC_SHIFT1_ParamName[i], HEX_PREFIX + DecShift1Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_SHIFT2_ParamName[i], HEX_PREFIX + DecShift2Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_DR2_ParamName[i], HEX_PREFIX + DecDr2Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_DR2H_ParamName[i], HEX_PREFIX + DecDr2hReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_DR1_ParamName[i], HEX_PREFIX + DecDr1Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);

                paramDict.Add(DEC_OCOR_ParamName[i], HEX_PREFIX + DecOcorReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_OCORM_ParamName[i], HEX_PREFIX + DecOcormReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_OCORH_ParamName[i], HEX_PREFIX + DecOcorhReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);

                paramDict.Add(DEC_COHER_ParamName[i], HEX_PREFIX + DecCoherReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR0_ParamName[i], HEX_PREFIX + DsmCr0Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR1_ParamName[i], HEX_PREFIX + DsmCr1Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR2_ParamName[i], HEX_PREFIX + DsmCr2Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR3_ParamName[i], HEX_PREFIX + DsmCr3Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR4_ParamName[i], HEX_PREFIX + DsmCr4Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR5_ParamName[i], HEX_PREFIX + DsmCr5Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR6_ParamName[i], HEX_PREFIX + DsmCr6Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR7_ParamName[i], HEX_PREFIX + DsmCr7Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR8_ParamName[i], HEX_PREFIX + DsmCr8Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR9_ParamName[i], HEX_PREFIX + DsmCr9Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR10_ParamName[i], HEX_PREFIX + DsmCr10Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR11_ParamName[i], HEX_PREFIX + DsmCr11Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR12_ParamName[i], HEX_PREFIX + DsmCr12Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR13_ParamName[i], HEX_PREFIX + DsmCr13Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR14_ParamName[i], HEX_PREFIX + DsmCr14Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR15_ParamName[i], HEX_PREFIX + DsmCr15Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR16_ParamName[i], HEX_PREFIX + DsmCr16Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_CR17_ParamName[i], HEX_PREFIX + DsmCr17Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);

                paramDict.Add(DSM_REF0_ParamName[i], HEX_PREFIX + DsmRef0Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_REF2_ParamName[i], HEX_PREFIX + DsmRef2Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_REF3_ParamName[i], HEX_PREFIX + DsmRef3Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);

                paramDict.Add(DSM_DEM0_ParamName[i], HEX_PREFIX + DsmDem0Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_DEM1_ParamName[i], HEX_PREFIX + DsmDem1Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);

                paramDict.Add(DSM_BUF0_ParamName[i], HEX_PREFIX + DsmBuf0Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_BUF1_ParamName[i], HEX_PREFIX + DsmBuf1Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_BUF2_ParamName[i], HEX_PREFIX + DsmBuf2Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_BUF3_ParamName[i], HEX_PREFIX + DsmBuf3Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_OUT0_ParamName[i], HEX_PREFIX + DsmOut0Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DSM_OUT1_ParamName[i], HEX_PREFIX + DsmOut1Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);

                paramDict.Add(DSM_SW3_ParamName[i], HEX_PREFIX + DsmSw3Reg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_GVAL_ParamName[i], HEX_PREFIX + DecGvalReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_GCOR_ParamName[i], HEX_PREFIX + DecGcorReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DEC_GCORH_ParamName[i], HEX_PREFIX + DecGcorhReg[i].ToString(HEX_FORMAT1) + 
                              FORMAT_SPECIFIER);
           
                // Voltage conversion defaults.
                paramDict.Add(RefVoltage_ParamName[i], Ref_Voltage[i].ToString("0.0000"));
                CountsPerVolt[i] = CalcCountsPerVolt(ADC_Resolution[i], ADC_Input_Range[i], Ref_Voltage[i], i, vdda);
                paramDict.Add(CountsPerVoltParamName[i], CountsPerVolt[i].ToString());
                paramDict.Add(adcClockFrequency_ParamName[i], clockFrequency[i].ToString());
                paramDict.Add(chargePumpClockFrequency_ParamName[i], cpClockFrequency[i].ToString());
                clocksPerCycle[i] = ClocksPerSample(ADC_Resolution[i], Conversion_Mode[i]);
                paramDict.Add(clocksPerSample_ParamName[i], HEX_PREFIX + clocksPerCycle[i].ToString(HEX_FORMAT2) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(IdealDecGain_ParamName[i], HEX_PREFIX + Ideal_Dec_Gain[i].ToString(HEX_FORMAT2) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(IdealOddDecGain_ParamName[i], HEX_PREFIX + Ideal_OddDec_Gain[i].ToString(HEX_FORMAT2) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(IPCap1Value_ParamName[i], HEX_PREFIX + IPCap1Value[i].ToString(HEX_FORMAT2) + 
                              FORMAT_SPECIFIER);
                paramDict.Add(DACCapValue_ParamName[i], HEX_PREFIX + DACCapValue[i].ToString(HEX_FORMAT2) + 
                              FORMAT_SPECIFIER);
                
                // Input mode and input range values 
                paramDict.Add(ADC_Input_ModeValue_ParamName[i], ADC_Input_ModeValue[i].ToString() + 
                              FORMAT_SPECIFIER);
                paramDict.Add(ADC_Input_RangeValue_ParamName[i], ADC_Input_RangeValue[i].ToString());
                
             }
        }
        
    }

    public static class CyresSettings
    {
            //                       Resolution     8  9  10  11  12  13  14  15  16  17  18  19  20    21

            public static uint[] dr1 =          { 15, 19, 22, 26, 31, 38, 45, 53, 63, 63, 63, 127, 127, 127 };
            public static uint[] dr2 =          { 0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  15, 63,  127, 127 };
            public static uint[] dr2h =         { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,   0 };
            public static uint[] shift1 =       { 4,  4,  5,  5,  6,  6,  5,  4,  4,  4,  4,  0,   0,   0 };
            public static uint[] shift2 =       { 7,  7,  8,  8,  9,  9,  8,  7,  7,  8,  9,  10,  10,  9 };     
            
            // Added these as a workaournd for 0 to 2*Vref mode with PSoC5A silicon 
            //   With PSoC5A silicon, the -ve input of DSM is connected to Vssa instead of
            //   Vref. So for this case we are using the old values of cap ratios  DR1, shift1, and Shift2 registers. 
            public static uint[] dr1_2VREF_ES2 =    { 15, 15, 15, 31, 31, 31, 31, 63, 63, 63, 63, 127, 127, 127 };
            public static uint[] shift1_2VREF_ES2 = {  4, 4, 4, 4, 6, 6, 6, 4, 4, 4, 4, 0, 0, 0 };
            public static uint[] shift2_2VREF_ES2 = {  7, 6, 5, 8, 9, 8, 7, 8, 7, 8, 9, 10, 10, 9 };     

    }

    // ADC Decimator and Modulator constants
    public static class Cyrc
    {

        public const uint MAX_CONFIGS = 4;
        public const uint IDEAL_GAIN_CONST = 32768;
        public const uint MIN_RESOLUTION = 8;
        public const uint MAX_RESOLUTION = 20;
        public const uint HIGH_FREQ = 3600000;
        public const uint HIGH_FREQ_16BIT = 3072000;
        public const uint HIGH_FREQ_12BIT = 6144000;
        public const uint MAXCHARGEPUMPCLOCK = 12000000;
        public const uint MINCHARGEPUMPCLOCK = 1000000;

        public static uint [] MAX_FREQ_16_20_BITS = {3072000, 3072000, 3072000, 3072000, 3072000, 3072000, 3072000, 
                                                     2800000, 1000000, 1000000, 1000000};

       public static uint[] MAX_FREQ_8_15_BITS = { 6144000, 6144000, 2200000, 1900000, 6144000, 3700000, 1900000, 
                                                    4800000, 3000000, 2800000, 1500000 };

        public const uint MIN_FREQ_15_20_BITS = 128000;
        public const uint MIN_FREQ_8_14_BITS = 128000;
        
        /// <summary>
        /// ADC_Clock Constants
        /// </summary>
        public const uint ADC_CLOCK_INTERNAL = 0;
        public const uint ADC_CLOCK_EXTERNAL = 1;
        
        /// <summary>
        /// INPUT_MODE Constants
        /// </summary>
        public const uint INPUT_MODE_DIFFERENTIAL = 0;
        public const uint INPUT_MODE_SINGLE = 1;

        /// <summary>
        /// ADC_Input_Range Constants
        /// </summary>
        public const uint ADC_IR_VSSA_TO_VREF    = 0x00;
        public const uint ADC_IR_VSSA_TO_2VREF   = 0x01;
        public const uint ADC_IR_VSSA_TO_VDDA    = 0x02;
        public const uint ADC_IR_VSSA_TO_6VREF    = 0x03;
        public const uint ADC_IR_VNEG_VREF_DIFF  = 0x04;
        public const uint ADC_IR_VNEG_2VREF_DIFF = 0x05;
        public const uint ADC_IR_VNEG_6VREF_DIFF = 0x06;
        public const uint ADC_IR_VNEG_VREF_2_DIFF = 0x07;
        public const uint ADC_IR_VNEG_VREF_4_DIFF = 0x08;
        public const uint ADC_IR_VNEG_VREF_8_DIFF = 0x09;
        public const uint ADC_IR_VNEG_VREF_16_DIFF = 0x0A;


        public static uint[] SumCapin8_20 ={
                            DSM_SUMCAPIN_250_FF,  // VSSA to VREF
                            DSM_SUMCAPIN_250_FF,  // VSSA to 2*VREF
                            DSM_SUMCAPIN_50_FF,   // VSSA to VDDA
                            DSM_SUMCAPIN_50_FF,   // VSSA to 6*VREF
                            DSM_SUMCAPIN_250_FF,  // VNEG +/- VREF
                            DSM_SUMCAPIN_100_FF,  // VNEG +/- 2*VREF
                            DSM_SUMCAPIN_50_FF,   // VNEG +/- 6*VREF
                            DSM_SUMCAPIN_400_FF,  // VNEG +/- VREF/2
                            DSM_SUMCAPIN_800_FF,  // VNEG +/- VREF/4
                            DSM_SUMCAPIN_800_FF,  // VNEG +/- VREF/8
                            DSM_SUMCAPIN_800_FF };// VNEG +/- VREF/16



        public static uint[] IpCap1_8_15 = { 
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_96FF ),                     //  900 fF VSSA to VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_96FF ),                     //  900 fF VSSA to 2*VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF),   // 1100 fF VSSA to VDDA
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF),                     // 1000 fF VSSA to 6*VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_96FF ),                     //  900 fF VNEG +/- VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF),   // 1100 fF VNEG +/- 2*VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF),                     // 1000 fF VNEG +/- 6*VREF
                            (DSM_IPCAP1_1600FF ),                                      // 1600 fF VNEG +/- VREF/2
                            (DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF | DSM_IPCAP1_400FF ),// 2800 fF VNEG +/- VREF/4
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF),  // 3500 fF VNEG +/- VREF/8
                            // 5700 fF VNEG +/- VREF/16
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF |DSM_IPCAP1_800FF |DSM_IPCAP1_96FF) 
                            };

        // IpCap1 values for Vssa to Vdda range with reference option Vdda/3. 
        public static uint IpCap1_8_15_Vdda_3 = (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF);
        public static uint IpCap1_16_20_Vdda_3 = (DSM_IPCAP1_1600FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF);
        
                            
        public static uint[] DacCap_8_15 = { 
                            //  992 fF VSSA to VREF
                            (DSM_DACCAP_800FF | DSM_DACCAP_192FF ),                                              
                            //  992 fF VSSA to 2*VREF
                            (DSM_DACCAP_800FF | DSM_DACCAP_192FF ),
                             // 4896 fF VSSA to VDDA
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_96FF),    
                            // 6000 fF VSSA to 6*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF),
                            //  992 fF VNEG +/- VREF
                            (DSM_DACCAP_800FF | DSM_DACCAP_192FF ),  
                            // 2496 fF VNEG +/- 2*VREF
                            (DSM_DACCAP_1600FF | DSM_DACCAP_800FF | DSM_DACCAP_96FF), 
                            // 6000 fF VNEG +/- 6*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            //  896 fF VNEG +/- VREF/2
                            (DSM_DACCAP_800FF | DSM_DACCAP_96FF ), 
                            //  800 fF VNEG +/- VREF/4
                            (DSM_DACCAP_800FF ), 
                            //  496 fF VNEG +/- VREF/8
                            (DSM_DACCAP_400FF | DSM_DACCAP_96FF), 
                            //  400 fF VNEG +/- VREF/16
                            (DSM_DACCAP_400FF )                             
                            };

        // DacCap values for Vssa to Vdda range with reference option Vdda/3. 
        public static uint DacCap_8_15_Vdda_3 = (DSM_DACCAP_3200FF | DSM_DACCAP_400FF);
        public static uint DacCap_16_20_Vdda_3 = (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_800FF | 
                                                  DSM_DACCAP_400FF | DSM_DACCAP_192FF | DSM_DACCAP_96FF);
                            
        public static uint[] IpCap1_16_20 = { 
                            // 3900 fF VSSA to VREF
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 3900 fF VSSA to 2*VREF
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 1100 fF VSSA to VDDA
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF), 
                            // 1000 fF VSSA to 6*VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF), 
                            // 3900 fF VNEG +/- VREF
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF | DSM_IPCAP1_96FF), 
                            // 2200 fF VNEG +/- 2*VREF
                            (DSM_IPCAP1_1600FF | DSM_IPCAP1_400FF | DSM_IPCAP1_192FF), 
                            // 1000 fF VNEG +/- 6*VREF
                            (DSM_IPCAP1_800FF | DSM_IPCAP1_192FF), 
                            // 6000 fF VNEG +/- VREF/2
                            (DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF | DSM_IPCAP1_400FF), 
                            // 12000 fF VNEG +/- VREF/4
                            (DSM_IPCAP1_6400FF | DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF), 
                            // 17600 fF = 12800 fF + 4800 fF offset VNEG +/- VREF/8
                            (DSM_IPCAP1_12700FF | DSM_IPCAP1_96FFpath), 
                            //17200 fF = 12400 fF + 4800 fF offset VNEG +/- VREF/16
                            (DSM_IPCAP1_6400FF | DSM_IPCAP1_3200FF | DSM_IPCAP1_1600FF | DSM_IPCAP1_800FF | 
                             DSM_IPCAP1_400FF) 
                            };
                                            
        public static uint[] DacCap_16_20 = { 
                            // 4400 fF VSSA to VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4400 fF VSSA to 2*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4896 fF VSSA to VDDA
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF | 
                             DSM_DACCAP_192FF), 
                             // 6000 fF VSSA to 6*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4400 fF VNEG +/- VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 4896 fF VNEG +/- 2*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_96FF), 
                            // 6000 fF VNEG +/- 6*VREF
                            (DSM_DACCAP_3200FF | DSM_DACCAP_1600FF | DSM_DACCAP_800FF | DSM_DACCAP_400FF), 
                            // 3392 fF VNEG +/- VREF/2
                            (DSM_DACCAP_3200FF | DSM_DACCAP_192FF ), 
                            // 3392 fF VNEG +/- VREF/4
                            (DSM_DACCAP_3200FF | DSM_DACCAP_192FF ), 
                            // 2496 fF VNEG +/- VREF/8
                            (DSM_DACCAP_1600FF | DSM_DACCAP_800FF |DSM_DACCAP_96FF), 
                            // 1200 fF VNEG +/- VREF/16
                            (DSM_DACCAP_800FF | DSM_DACCAP_400FF )                             
                            };
                            
            public static uint[] CapOffset_16_20 = { 
                            0x00,                           // VSSA to VREF
                            0x00,                           // VSSA to 2*VREF
                            0x00,                           // VSSA to VDDA
                            0x00,                           // VSSA to 6*VREF
                            0x00,                           // VNEG +/- VREF
                            0x00,                           // VNEG +/- 2*VREF
                            0x00,                           // VNEG +/- 6*VREF
                            0x00,                           // VNEG +/- VREF/2
                            0x00,                           // VNEG +/- VREF/4
                            DSM_IPCAP1OFFSET,               // Add 4800 fF to ipcap VNEG +/- VREF/8
                            DSM_IPCAP1OFFSET                // Add 4800 fF to ipcap VNEG +/- VREF/16
                            };                
        
            public static uint[] SumCap3Fb_8_20 ={
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),  // VSSA to VREF
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),  // VSSA to 2*VREF
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VSSA to VDDA
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VSSA to 6*VREF
                            (DSM_SUMCAP3_250_FF | DSM_SUMCAPFB_500_FF),   // VNEG +/- VREF
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VNEG +/- 2*VREF
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VNEG +/- 6*VREF
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VNEG +/- VREF/2
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_400_FF),   // VNEG +/- VREF/4
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_200_FF),   // VNEG +/- VREF/8
                            (DSM_SUMCAP3_200_FF | DSM_SUMCAPFB_100_FF)    // VNEG +/- VREF/16
                            };

                           
        public static uint[] SumCap12_8_20 ={
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF) ,  // VSSA to VREF
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF) ,  // VSSA to 2*VREF
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VSSA to VDDA
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VSSA to 6*VREF
                            (DSM_SUMCAP1_250_FF | DSM_SUMCAP2_250_FF),   // VNEG +/- VREF
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- 2*VREF
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- 6*VREF
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/2
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/4
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF),   // VNEG +/- VREF/8
                            (DSM_SUMCAP1_200_FF | DSM_SUMCAP2_200_FF)    // VNEG +/- VREF/16
                            };

        
        /// <summary>
        /// ADC_Power Constants
        /// </summary>
        public const uint ADC_LOWPOWER  = 0;
        public const uint ADC_MEDPOWER  = 1;
        public const uint ADC_HIGHPOWER = 2;


        /// <summary>
        /// ADC_Reference Constants
        /// </summary>
        public const uint ADC_INT_REF_NOT_BYPASSED            = 0;
        public const uint ADC_INT_REF_BYPASSED_ON_P03         = 1;
        public const uint ADC_INT_REF_BYPASSED_ON_P32         = 2;
        public const uint ADC_EXT_REF_ON_P03                  = 3;
        public const uint ADC_EXT_REF_ON_P32                  = 4;
        public const uint ADC_INT_REF_VDDA_4                  = 5;
        public const uint ADC_INT_REF_VDDA_4_BYPASSED_ON_P03  = 6;
        public const uint ADC_INT_REF_VDDA_4_BYPASSED_ON_P32  = 7;
        public const uint ADC_INT_REF_VDDA_3                  = 8;
        public const uint ADC_INT_REF_VDDA_3_BYPASSED_ON_P03  = 9;
        public const uint ADC_INT_REF_VDDA_3_BYPASSED_ON_P32  = 0xA;

        /// <summary>
        /// Conversion_Mode Constants
        /// </summary>
        public const uint ADC_CM_SINGLE_SAMPLE = 0;
        public const uint ADC_CM_FAST_FILER    = 1;
        public const uint ADC_CM_CONTINUOUS    = 2;
        public const uint ADC_CM_FAST_FIR      = 3;

        /// <summary>
        /// Input_Buffer_Gain Constants
        /// </summary>
        public const uint ADC_IBG_1X = 0;
        public const uint ADC_IBG_2X = 1;
        public const uint ADC_IBG_4X = 2;
        public const uint ADC_IBG_8X = 3;

        /// <summary>
        /// Start_of_Conversion Constants
        /// </summary>
        public const uint ADC_SOC_SOFTWARE = 0;
        public const uint ADC_SOC_HARDWARE = 1;

        /// <summary>
        /// Constants for SetInputRange() bufmode parameter
        /// </summary>
        public const uint BUF_DIFF_MODE    = 0x00;  // Differential mode 
        public const uint BUF_BYPASS_POS   = 0x04;  // Bypass and power down positive channel 
        public const uint BUF_BYPASS_NEG   = 0x08;  // Bypass and power down negative channel 
        public const uint BUF_RAIL_TO_RAIL = 0x10;  // Enables Rail-to-rail mode 
        public const uint BUF_FILTER_EN    = 0x20;  // Output filter enable 
        public const uint BUF_LOW_PWR      = 0x40;  // Enable  Low power mode 
        
        /// <summary>
        /// Constants for Buffermode parameter
        /// </summary>
        public const uint BUF_MODE_BYPASS_BUFFER = 0x00;  // Bypass buffer mode 
        public const uint BUF_MODE_RAIL_TO_RAIL  = 0x01;  // Rail to Rail buffer mode 
        public const uint BUF_MODE_LEVEL_SHIFT   = 0x02;  // Level Shift buffer mode 
       
        

        //      Register Constants        


        /// <summary>
        /// DSM.CR0 Control Register 0 definitions 
        /// </summary>
        /// 
        // Bit Field  DSM_NONOV                   
        public const uint DSM_NONOV_MASK  = 0x0C;
        public const uint DSM_NONOV_LOW   = 0x00;
        public const uint DSM_NONOV_MED   = 0x04;
        public const uint DSM_NONOV_HIGH  = 0x08;
        public const uint DSM_NONOV_VHIGH = 0x0C;

        // Bit Field  DSM_QLEV                    
        public const uint DSM_QLEV_MASK = 0x03;
        public const uint DSM_QLEV_2  = 0x00;
        public const uint DSM_QLEV_3  = 0x01;
        public const uint DSM_QLEV_9  = 0x02;
        public const uint DSM_QLEV_9x = 0x03;


        /// <summary>
        /// DSM.CR1 Control Register 1 definitions  
        /// </summary>
        public const uint DSM_ODET_TH_MASK = 0x1F;
        public const uint DSM_ODEN         = 0x20;
        public const uint DSM_DPMODE       = 0x40;

        /// <summary>
        /// DSM.CR2 Control Register 2 definitions  
        /// </summary>
 
       // Bit Field  DSM_FCHOP                    
        public const uint DSM_FCHOP_MASK   = 0x07;
        public const uint DSM_FCHOP_DIV2   = 0x00;
        public const uint DSM_FCHOP_DIV4   = 0x01;
        public const uint DSM_FCHOP_DIV8   = 0x02;
        public const uint DSM_FCHOP_DIV16  = 0x03;
        public const uint DSM_FCHOP_DIV32  = 0x04;
        public const uint DSM_FCHOP_DIV64  = 0x05;
        public const uint DSM_FCHOP_DIV128 = 0x06;
        public const uint DSM_FCHOP_DIV256 = 0x07;

        // Bit Field  DSM_MOD_CHOP_EN                 
        public const uint DSM_MOD_CHOP_EN = 0x08;

        // Bit Field  DSM_MX_RESET                    
        public const uint DSM_MX_RESET = 0x80;

        // Bit Field  DSM_RESET1_EN                   
        public const uint DSM_RESET1_EN = 0x10;

        // Bit Field  DSM_RESET2_EN                   
        public const uint DSM_RESET2_EN = 0x20;

        // Bit Field  DSM_RESET3_EN                   
        public const uint DSM_RESET3_EN = 0x40;

        /// <summary>
        /// DSM.CR3 Control Register 3 definitions
        /// </summary>
        
        // Bit Field  DSM_SELECT_MOD_BIT           
        public const uint DSM_MODBITIN_MASK = 0x0F;
        public const uint DSM_MODBITIN_LUT0 = 0x00;
        public const uint DSM_MODBITIN_LUT1 = 0x01;
        public const uint DSM_MODBITIN_LUT2 = 0x02;
        public const uint DSM_MODBITIN_LUT3 = 0x03;
        public const uint DSM_MODBITIN_LUT4 = 0x04;
        public const uint DSM_MODBITIN_LUT5 = 0x05;
        public const uint DSM_MODBITIN_LUT6 = 0x06;
        public const uint DSM_MODBITIN_LUT7 = 0x07;
        public const uint DSM_MODBITIN_UDB  = 0x08;

        // Bit Field  DSM_MODBIT_EN                  
        public const uint DSM_MODBIT_EN = 0x10;

        // Bit Field  DSM_MX_DOUT                    
        public const uint DSM_MX_DOUT_8BIT   = 0x00;
        public const uint DSM_MX_DOUT_2SCOMP = 0x20;

        // Bit Field  DSM_MODBIT  TBD                
        public const uint DSM_MODBIT = 0x40;

        // Bit Field  DSM_SIGN                       
        public const uint DSM_SIGN_NINV = 0x00;
        public const uint DSM_SIGN_INV  = 0x80;


        /// <summary>
        /// DSM.CR4 Control Register 4 definitions 
        /// </summary>
        
        // Bit Field  DSM_SELECT_FCAP_EN             
        public const uint DSM_FCAP1_EN  = 0x80;
        public const uint DSM_FCAP1_DIS = 0x00;

        // Bit Field  DSM_SELECT_FCAP1              
        public const uint DSM_FCAP1_MASK   = 0x7F;
        public const uint DSM_FCAP1_MIN    = 0x00;
        public const uint DSM_FCAP1_MAX    = 0x7F;
        public const uint DSM_FCAP1_100FF  = 0x01;
        public const uint DSM_FCAP1_200FF  = 0x02;
        public const uint DSM_FCAP1_400FF  = 0x04;
        public const uint DSM_FCAP1_800FF  = 0x08;
        public const uint DSM_FCAP1_1600FF = 0x10;
        public const uint DSM_FCAP1_3200FF = 0x20;
        public const uint DSM_FCAP1_6400FF = 0x40;

        /// <summary>
        /// DSM.CR5 Control Register 5 definitions  
        /// </summary>

        // Bit Field  DSM_SELECT_IPCAP_EN             
        public const uint DSM_IPCAP1_EN = 0x80;
        public const uint DSM_IPCAP1_DIS = 0x00;
        public const uint DSM_IPCAP1_96FFpath = 0x80;

        // Bit Field  DSM_SELECT_IPCAP1              
        public const uint DSM_IPCAP1_MASK   = 0x7F;
        public const uint DSM_IPCAP1_MIN    = 0x00;
        public const uint DSM_IPCAP1_MAX    = 0x7F;
        public const uint DSM_IPCAP1_96FF  = 0x01;
        public const uint DSM_IPCAP1_192FF  = 0x02;
        public const uint DSM_IPCAP1_400FF  = 0x04;
        public const uint DSM_IPCAP1_800FF  = 0x08;
        public const uint DSM_IPCAP1_1600FF = 0x10;
        public const uint DSM_IPCAP1_3200FF = 0x20;
        public const uint DSM_IPCAP1_6400FF = 0x40;
        public const uint DSM_IPCAP1_12700FF = 0x7F;


        /// <summary>
        /// DSM.CR6 Control Register 6 definitions  
        /// </summary>

        // Bit Field  DSM_SELECT_DACCAP_EN             
        public const uint DSM_DACCAP_EN  = 0x40;
        public const uint DSM_DACCAP_DIS = 0x00;

        // Bit Field  DSM_SELECT_DACCAP              
        public const uint DSM_DACCAP_MASK   = 0x3F;
        public const uint DSM_DACCAP_MIN    = 0x00;
        public const uint DSM_DACCAP_MAX    = 0x3F;
        public const uint DSM_DACCAP_96FF   = 0x01;
        public const uint DSM_DACCAP_192FF  = 0x02;
        public const uint DSM_DACCAP_400FF  = 0x04;
        public const uint DSM_DACCAP_800FF  = 0x08;
        public const uint DSM_DACCAP_1600FF = 0x10;
        public const uint DSM_DACCAP_3200FF = 0x20;


        /// <summary>
        /// DSM.CR7 Control Register 7 definitions  
        /// </summary>

        // Bit Field  DSM_SELECT_RESCAP_EN             
        public const uint DSM_RESCAP_EN = 0x08;
        public const uint DSM_RESCAP_DIS = 0x00;

        // Bit Field  DSM_SELECT_RESCAP              
        public const uint DSM_RESCAP_MASK = 0x07;
        public const uint DSM_RESCAP_MIN  = 0x00;
        public const uint DSM_RESCAP_MAX  = 0x07;
        public const uint DSM_RESCAP_12FF = 0x00;
        public const uint DSM_RESCAP_24FF = 0x01;
        public const uint DSM_RESCAP_36FF = 0x02;
        public const uint DSM_RESCAP_48FF = 0x03;
        public const uint DSM_RESCAP_60FF = 0x04;
        public const uint DSM_RESCAP_72FF = 0x05;
        public const uint DSM_RESCAP_84FF = 0x06;
        public const uint DSM_RESCAP_96FF = 0x07;

        public const uint DSM_FCAP2_DIS = 0x00;
        public const uint DSM_FCAP2_EN  = 0x80;

        public const uint DSM_FCAP3_DIS = 0x00;
        public const uint DSM_FCAP3_EN  = 0x40;

        public const uint DSM_IPCAP1OFFSET = 0x20;
        public const uint DSM_FPCAP1OFFSET = 0x10;


        /// <summary>
        /// DSM.CR8 Control Register 8 definitions  
        /// </summary>

        public const uint DSM_IPCAP2_EN = 0x80;

        public const uint DSM_IPCAP2_MASK   = 0x70;
        public const uint DSM_IPCAP2_0_FF   = 0x00;
        public const uint DSM_IPCAP2_50_FF  = 0x10;
        public const uint DSM_IPCAP2_100_FF = 0x20;
        public const uint DSM_IPCAP2_150_FF = 0x30;
        public const uint DSM_IPCAP2_200_FF = 0x40;
        public const uint DSM_IPCAP2_250_FF = 0x50;
        public const uint DSM_IPCAP2_300_FF = 0x60;
        public const uint DSM_IPCAP2_350_FF = 0x70;

        public const uint DSM_FCAP2_MASK   = 0x0F;
        public const uint DSM_FCAP2_0_FF   = 0x00;
        public const uint DSM_FCAP2_50_FF  = 0x01;
        public const uint DSM_FCAP2_100_FF = 0x02;
        public const uint DSM_FCAP2_150_FF = 0x03;
        public const uint DSM_FCAP2_200_FF = 0x04;
        public const uint DSM_FCAP2_250_FF = 0x05;
        public const uint DSM_FCAP2_300_FF = 0x06;
        public const uint DSM_FCAP2_350_FF = 0x07;
        public const uint DSM_FCAP2_400_FF = 0x08;
        public const uint DSM_FCAP2_450_FF = 0x09;
        public const uint DSM_FCAP2_500_FF = 0x0A;
        public const uint DSM_FCAP2_550_FF = 0x0B;
        public const uint DSM_FCAP2_600_FF = 0x0C;
        public const uint DSM_FCAP2_650_FF = 0x0D;
        public const uint DSM_FCAP2_700_FF = 0x0E;
        public const uint DSM_FCAP2_750_FF = 0x0F;

        /// <summary>
        /// DSM.CR9 Control Register 9 definitions  
        /// </summary>
       
        public const uint DSM_IPCAP3_EN = 0x80;

        public const uint DSM_IPCAP3_MASK   = 0x70;
        public const uint DSM_IPCAP3_0_FF   = 0x00;
        public const uint DSM_IPCAP3_50_FF  = 0x10;
        public const uint DSM_IPCAP3_100_FF = 0x20;
        public const uint DSM_IPCAP3_150_FF = 0x30;
        public const uint DSM_IPCAP3_200_FF = 0x40;
        public const uint DSM_IPCAP3_250_FF = 0x50;
        public const uint DSM_IPCAP3_300_FF = 0x60;
        public const uint DSM_IPCAP3_350_FF = 0x70;
        
        public const uint DSM_FCAP3_MASK    = 0x0F;
        public const uint DSM_FCAP3_0_FF    = 0x00;
        public const uint DSM_FCAP3_100_FF  = 0x01;
        public const uint DSM_FCAP3_200_FF  = 0x02;
        public const uint DSM_FCAP3_300_FF  = 0x03;
        public const uint DSM_FCAP3_400_FF  = 0x04;
        public const uint DSM_FCAP3_500_FF  = 0x05;
        public const uint DSM_FCAP3_600_FF  = 0x06;
        public const uint DSM_FCAP3_700_FF  = 0x07;
        public const uint DSM_FCAP3_800_FF  = 0x08;
        public const uint DSM_FCAP3_900_FF  = 0x09;
        public const uint DSM_FCAP3_1000_FF = 0x0A;
        public const uint DSM_FCAP3_1100_FF = 0x0B;
        public const uint DSM_FCAP3_1200_FF = 0x0C;
        public const uint DSM_FCAP3_1300_FF = 0x0D;
        public const uint DSM_FCAP3_1400_FF = 0x0E;
        public const uint DSM_FCAP3_1500_FF = 0x0F;

        /// <summary>
        /// DSM.CR10 Control Register 10 definitions  
        /// </summary>

        public const uint DSM_SUMCAP1_EN = 0x80;
        public const uint DSM_SUMCAP2_EN = 0x08;

        public const uint DSM_SUMCAP1_MASK   = 0x70;
        public const uint DSM_SUMCAP1_0_FF   = 0x00;
        public const uint DSM_SUMCAP1_50_FF  = 0x10;
        public const uint DSM_SUMCAP1_100_FF = 0x20;
        public const uint DSM_SUMCAP1_150_FF = 0x30;
        public const uint DSM_SUMCAP1_200_FF = 0x40;
        public const uint DSM_SUMCAP1_250_FF = 0x50;
        public const uint DSM_SUMCAP1_300_FF = 0x60;
        public const uint DSM_SUMCAP1_350_FF = 0x70;

        public const uint DSM_SUMCAP2_MASK   = 0x07;
        public const uint DSM_SUMCAP2_0_FF   = 0x00;
        public const uint DSM_SUMCAP2_50_FF  = 0x01;
        public const uint DSM_SUMCAP2_100_FF = 0x02;
        public const uint DSM_SUMCAP2_150_FF = 0x03;
        public const uint DSM_SUMCAP2_200_FF = 0x04;
        public const uint DSM_SUMCAP2_250_FF = 0x05;
        public const uint DSM_SUMCAP2_300_FF = 0x06;
        public const uint DSM_SUMCAP2_350_FF = 0x07;

        /// <summary>
        /// DSM.CR11 Control Register 11 definitions  
        /// </summary>

        public const uint DSM_SUMCAP3_EN = 0x08;

        public const uint DSM_SUMCAP3_MASK   = 0x70;
        public const uint DSM_SUMCAP3_0_FF   = 0x00;
        public const uint DSM_SUMCAP3_50_FF  = 0x10;
        public const uint DSM_SUMCAP3_100_FF = 0x20;
        public const uint DSM_SUMCAP3_150_FF = 0x30;
        public const uint DSM_SUMCAP3_200_FF = 0x40;
        public const uint DSM_SUMCAP3_250_FF = 0x50;
        public const uint DSM_SUMCAP3_300_FF = 0x60;
        public const uint DSM_SUMCAP3_350_FF = 0x70;

        public const uint DSM_SUMCAPFB_MASK   = 0x07;
        public const uint DSM_SUMCAPFB_0_FF   = 0x00;
        public const uint DSM_SUMCAPFB_50_FF  = 0x01;
        public const uint DSM_SUMCAPFB_100_FF = 0x02;
        public const uint DSM_SUMCAPFB_150_FF = 0x03;
        public const uint DSM_SUMCAPFB_200_FF = 0x04;
        public const uint DSM_SUMCAPFB_250_FF = 0x05;
        public const uint DSM_SUMCAPFB_300_FF = 0x06;
        public const uint DSM_SUMCAPFB_350_FF = 0x07;
        public const uint DSM_SUMCAPFB_400_FF = 0x08;
        public const uint DSM_SUMCAPFB_450_FF = 0x09;
        public const uint DSM_SUMCAPFB_500_FF = 0x0A;
        public const uint DSM_SUMCAPFB_550_FF = 0x0B;
        public const uint DSM_SUMCAPFB_600_FF = 0x0C;
        public const uint DSM_SUMCAPFB_650_FF = 0x0D;
        public const uint DSM_SUMCAPFB_700_FF = 0x0E;
        public const uint DSM_SUMCAPFB_750_FF = 0x0F;

        /// <summary>
        /// DSM.CR12 Control Register 12 definitions  
        /// </summary>

        public const uint DSM_SUMCAPFB_EN = 0x40;
        public const uint DSM_SUMCAPIN_EN = 0x20;

        public const uint DSM_SUMCAPIN_MASK   = 0x1F;
        public const uint DSM_SUMCAPIN_0_FF   = 0x00;
        public const uint DSM_SUMCAPIN_50_FF  = 0x01;
        public const uint DSM_SUMCAPIN_100_FF = 0x02;
        public const uint DSM_SUMCAPIN_150_FF = 0x03;
        public const uint DSM_SUMCAPIN_200_FF = 0x04;
        public const uint DSM_SUMCAPIN_250_FF = 0x05;
        public const uint DSM_SUMCAPIN_300_FF = 0x06;
        public const uint DSM_SUMCAPIN_350_FF = 0x07;
        public const uint DSM_SUMCAPIN_400_FF = 0x08;
        public const uint DSM_SUMCAPIN_450_FF = 0x09;
        public const uint DSM_SUMCAPIN_500_FF = 0x0A;
        public const uint DSM_SUMCAPIN_550_FF = 0x0B;
        public const uint DSM_SUMCAPIN_600_FF = 0x0C;
        public const uint DSM_SUMCAPIN_650_FF = 0x0D;
        public const uint DSM_SUMCAPIN_700_FF = 0x0E;
        public const uint DSM_SUMCAPIN_750_FF = 0x0F;
        public const uint DSM_SUMCAPIN_800_FF = 0x10;
        public const uint DSM_SUMCAPIN_850_FF = 0x11;
        public const uint DSM_SUMCAPIN_900_FF = 0x12;
        public const uint DSM_SUMCAPIN_950_FF = 0x13;
        public const uint DSM_SUMCAPIN_1000_FF = 0x14;
        public const uint DSM_SUMCAPIN_1050_FF = 0x15;
        public const uint DSM_SUMCAPIN_1100_FF = 0x16;
        public const uint DSM_SUMCAPIN_1150_FF = 0x17;
        public const uint DSM_SUMCAPIN_1200_FF = 0x18;
        public const uint DSM_SUMCAPIN_1250_FF = 0x19;
        public const uint DSM_SUMCAPIN_1300_FF = 0x1A;
        public const uint DSM_SUMCAPIN_1350_FF = 0x1B;
        public const uint DSM_SUMCAPIN_1400_FF = 0x1C;
        public const uint DSM_SUMCAPIN_1450_FF = 0x1D;
        public const uint DSM_SUMCAPIN_1500_FF = 0x1E;
        public const uint DSM_SUMCAPIN_1550_FF = 0x15;


        /// <summary>
        /// DSM.CR13 Control Register 13 definitions 
        /// </summary>

        public const uint DSM_CR13_RSVD = 0xFF;

        /// <summary>
        /// DSM.CR14 Control Register 14 definitions 
        /// </summary>
        
        // Bit Field  DSM_POWER1                     
        public const uint DSM_POWER1_MASK = 0x07;

        public const uint DSM_POWER1_0 = 0x00;
        public const uint DSM_POWER1_1 = 0x01;
        public const uint DSM_POWER1_2 = 0x02;
        public const uint DSM_POWER1_3 = 0x03;
        public const uint DSM_POWER1_4 = 0x04;
        public const uint DSM_POWER1_5 = 0x05;
        public const uint DSM_POWER1_6 = 0x06;
        public const uint DSM_POWER1_7 = 0x07;

        public const uint DSM_POWER1_44UA  = 0x00;
        public const uint DSM_POWER1_123UA = 0x01;
        public const uint DSM_POWER1_492UA = 0x02;
        public const uint DSM_POWER1_750UA = 0x03;
        public const uint DSM_POWER1_1MA   = 0x04;

        // Bit Field  DSM_OPAMP1_BW                  
        public const uint DSM_OPAMP1_BW_MASK = 0xF0;
        public const uint DSM_OPAMP1_BW_0 = 0x00;
        public const uint DSM_OPAMP1_BW_1 = 0x10;
        public const uint DSM_OPAMP1_BW_2 = 0x20;
        public const uint DSM_OPAMP1_BW_3 = 0x30;
        public const uint DSM_OPAMP1_BW_4 = 0x40;
        public const uint DSM_OPAMP1_BW_5 = 0x50;
        public const uint DSM_OPAMP1_BW_6 = 0x60;
        public const uint DSM_OPAMP1_BW_7 = 0x70;
        public const uint DSM_OPAMP1_BW_8 = 0x80;
        public const uint DSM_OPAMP1_BW_9 = 0x90;
        public const uint DSM_OPAMP1_BW_A = 0xA0;
        public const uint DSM_OPAMP1_BW_B = 0xB0;
        public const uint DSM_OPAMP1_BW_C = 0xC0;
        public const uint DSM_OPAMP1_BW_D = 0xD0;
        public const uint DSM_OPAMP1_BW_E = 0xE0;
        public const uint DSM_OPAMP1_BW_F = 0xF0;

        /// <summary>
        /// DSM.CR15 Control Register 15 definitions  
        /// </summary>

        // Bit Field  DSM_POWER2_3                   
        public const uint DSM_POWER2_3_MASK = 0x07;

        public const uint DSM_POWER2_3_LOW    = 0x00;
        public const uint DSM_POWER2_3_MED    = 0x01;
        public const uint DSM_POWER2_3_HIGH   = 0x02;
        public const uint DSM_POWER2_3_IP5X   = 0x03;
        public const uint DSM_POWER2_3_2X     = 0x04;
        public const uint DSM_POWER2_3_HIGH_5 = 0x05;
        public const uint DSM_POWER2_3_HIGH_6 = 0x06;
        public const uint DSM_POWER2_3_HIGH_7 = 0x07;

        // Bit Field  DSM_POWER_COMP                 
        public const uint DSM_POWER_COMP_MASK = 0x30;

        public const uint DSM_POWER_VERYLOW = 0x00;
        public const uint DSM_POWER_NORMAL  = 0x10;
        public const uint DSM_POWER_6MHZ    = 0x20;
        public const uint DSM_POWER_12MHZ   = 0x30;

        /// <summary>
        /// DSM.CR16 Control Register 16 definitions 
        /// </summary>

        // Bit Field  DSM_POWER_SUM                  
        public const uint DSM_POWER_SUM_MASK = 0x70;

        public const uint DSM_POWER_SUM_LOW    = 0x00;  
        public const uint DSM_POWER_SUM_MED    = 0x10;
        public const uint DSM_POWER_SUM_HIGH   = 0x20;
        public const uint DSM_POWER_SUM_IP5X   = 0x30;
        public const uint DSM_POWER_SUM_2X     = 0x40;
        public const uint DSM_POWER_SUM_HIGH_5 = 0x50;
        public const uint DSM_POWER_SUM_HIGH_6 = 0x60;
        public const uint DSM_POWER_SUM_HIGH_7 = 0x70;

        public const uint DSM_CP_ENABLE         = 0x08;
        public const uint DSM_CP_PWRCTL_MASK    = 0x07;
        public const uint DSM_CP_PWRCTL_DEFAULT = 0x0A;
        public const uint DSM_CP_PWRCTL_2X      = 0x09;
        public const uint DSM_CP_PWRCTL_TURBO   = 0x08;
        public const uint DSM_CP_PWRCTL_HIGH    = 0x0A;
        public const uint DSM_CP_PWRCTL_MEDIUM  = 0x0B;
                                        
        /// <summary>
        /// DSM.CR17 Control Register 17 definitions  
        /// </summary>

        // Bit Field  DSM_EN_BUF                     
        public const uint DSM_EN_BUF_VREF = 0x01;
        public const uint DSM_EN_BUF_VCM = 0x02;

        public const uint DSM_PWR_CTRL_VREF_MASK = 0x0C;
        public const uint DSM_PWR_CTRL_VREF_0 = 0x00;
        public const uint DSM_PWR_CTRL_VREF_1 = 0x04;
        public const uint DSM_PWR_CTRL_VREF_2 = 0x08;
        public const uint DSM_PWR_CTRL_VREF_3 = 0x0C;

        public const uint DSM_PWR_CTRL_VCM_MASK = 0x30;
        public const uint DSM_PWR_CTRL_VCM_0    = 0x00;
        public const uint DSM_PWR_CTRL_VCM_1    = 0x10;
        public const uint DSM_PWR_CTRL_VCM_2    = 0x20;
        public const uint DSM_PWR_CTRL_VCM_3    = 0x30;

        public const uint DSM_PWR_CTRL_VREF_INN_MASK = 0xC0;
        public const uint DSM_PWR_CTRL_VREF_INN_0    = 0x00;
        public const uint DSM_PWR_CTRL_VREF_INN_1    = 0x40;
        public const uint DSM_PWR_CTRL_VREF_INN_2    = 0x80;
        public const uint DSM_PWR_CTRL_VREF_INN_3    = 0xC0;

        /// <summary>
        /// DSM.REF0 Reference Register 0 definitions  
        /// </summary>

        public const uint DSM_REFMUX_MASK   = 0x07;
        public const uint DSM_REFMUX_NONE   = 0x00;
        
        public const uint DSM_REFMUX_VDAC0_ES3  = 0x03;  // For PSoC3 and PSoC5LP or later
        public const uint DSM_REFMUX_VDAC0  = 0x01;  // For PSoC5A
        
        public const uint DSM_REFMUX_UVCM   = 0x01;  // For PSoC5A         
        public const uint DSM_REFMUX_VDA_4  = 0x02;        
        public const uint DSM_REFMUX_VDA_3  = 0x03;  // For PSoC3 and PSoC5LP or later        
        public const uint DSM_REFMUX_1_024V = 0x04;
        public const uint DSM_REFMUX_1_20V  = 0x05;

        public const uint DSM_EN_BUF_VREF_INN = 0x08;
        public const uint DSM_VREF_RES_DIV_EN = 0x10;
        public const uint DSM_VCM_RES_DIV_EN  = 0x20;
        public const uint DSM_VCMSEL_MASK     = 0xC0;
        public const uint DSM_VCMSEL_NOSEL    = 0x00;
        public const uint DSM_VCMSEL_0_8V     = 0x40;
        public const uint DSM_VCMSEL_0_7V     = 0x80;
        public const uint DSM_VCMSEL_VPWRA_2  = 0xC0;

        /// <summary>
        /// DSM.REF1 Reference Register 1 definitions 
        /// </summary>
        public const uint DSM_REF1_MASK = 0xFF;

        /// <summary>
        /// DSM.REF2 Reference Register 2 definitions  
        /// </summary>

        public const uint DSM_REF2_MASK  = 0xFF;
        public const uint DSM_REF2_NO_SW = 0x00;
        public const uint DSM_REF2_S0_EN = 0x01;
        public const uint DSM_REF2_S1_EN = 0x02;
        public const uint DSM_REF2_S2_EN = 0x04;
        public const uint DSM_REF2_S3_EN = 0x08;
        public const uint DSM_REF2_S4_EN = 0x10;
        public const uint DSM_REF2_S5_EN = 0x20;
        public const uint DSM_REF2_S6_EN = 0x40;
        public const uint DSM_REF2_S7_EN = 0x80;

        /// <summary>
        /// DSM.REF3 Reference Register 3 definitions  
        /// </summary>

        public const uint DSM_REF3_MASK   = 0xFF;
        public const uint DSM_REF3_NO_SW  = 0x00;
        public const uint DSM_REF3_S8_EN  = 0x01;
        public const uint DSM_REF3_S9_EN  = 0x02;
        public const uint DSM_REF3_S10_EN = 0x04;
        public const uint DSM_REF3_S11_EN = 0x08;
        public const uint DSM_REF3_S12_EN = 0x10;
        public const uint DSM_REF3_S13_EN = 0x20;


        /// <summary>
        /// DSM.DEM0 Dynamic Element Matching Register 0 
        /// </summary>

        public const uint DSM_EN_SCRAMBLER0 = 0x01;
        public const uint DSM_EN_SCRAMBLER1 = 0x02;
        public const uint DSM_EN_DEM        = 0x04;
        public const uint DSM_ADC_TEST_EN   = 0x08;
        public const uint DSM_DEMTEST_SRC   = 0x10;

        /// <summary>
        /// DSM.DEM1 Dynamic Element Matching Register 1  
        /// </summary>

        public const uint DSM_DEM1_MASK = 0xFF;


        /// <summary>
        /// DSM.BUF0 Buffer Register 0                
        /// </summary>

        public const uint DSM_ENABLE_P     = 0x01;
        public const uint DSM_BYPASS_P     = 0x02;
        public const uint DSM_RAIL_RAIL_EN = 0x04;

        public const uint DSM_BUFSEL   = 0x08;
        public const uint DSM_BUFSEL_A = 0x00;
        public const uint DSM_BUFSEL_B = 0x08;


        /// <summary>
        /// DSM.BUF1 Buffer Register 1          
        /// </summary>

        public const uint DSM_ENABLE_N  = 0x01;
        public const uint DSM_BYPASS_N  = 0x02;
        public const uint DSM_GAIN_MASK = 0x0C;
        public const uint DSM_GAIN_1X   = 0x00;
        public const uint DSM_GAIN_2X   = 0x04;
        public const uint DSM_GAIN_4X   = 0x08;
        public const uint DSM_GAIN_8X   = 0x0C;

        /// <summary>
        /// DSM.BUF2 Buffer Register 2       
        /// </summary>

        public const uint DSM_LOWPOWER_EN  = 0x01;
        public const uint DSM_ADD_EXTRA_RC = 0x02;

        /// <summary>
        /// DSM.BUF3 Buffer Register 3       
        /// </summary>

        public const uint DSM_BUF_CHOP_EN = 0x08;

        public const uint DSM_BUF_FCHOP_MASK  = 0x07;
        public const uint DSM_BUF_FCHOP_FS2   = 0x00;
        public const uint DSM_BUF_FCHOP_FS4   = 0x01;
        public const uint DSM_BUF_FCHOP_FS8   = 0x02;
        public const uint DSM_BUF_FCHOP_FS16  = 0x03;
        public const uint DSM_BUF_FCHOP_FS32  = 0x04;
        public const uint DSM_BUF_FCHOP_FS64  = 0x05;
        public const uint DSM_BUF_FCHOP_FS128 = 0x06;
        public const uint DSM_BUF_FCHOP_FS256 = 0x07;


        /// <summary>
        /// DSM.MISC Delta Sigma Misc Register     
        /// </summary>

        public const uint DSM_SEL_ICLK_CP = 0x01;
        public const uint DSM_SEL_ECLK_CP = 0x00;
        
        /// <summary>
        /// DSM.REF1 Delta Sigma Reference register           
        /// </summary>

        public const uint DSM_DAC_GND_SEL_EXT = 0x01;
        public const uint DSM_DAC_GND_SEL_INT = 0x00;

        /// <summary>
        /// DSM.CLK Delta Sigma Clock selection Register 
        /// </summary>

        public const uint DSM_CLK_MX_CLK_MSK  = 0x07;
        public const uint DSM_CLK_CLK_EN      = 0x08;
        public const uint DSM_CLK_BYPASS_SYNC = 0x10;


        /// <summary>
        /// DSM.OUT0 Output Register 0 
        /// </summary>

        public const uint DSM_DOUT0 = 0xFF;


        /// <summary>
        /// DSM.OUT1 Output Register 1  
        /// </summary>

        public const uint DSM_DOUT2SCOMP_MASK = 0x0F;
        public const uint DSM_OVDFLAG         = 0x10;
        public const uint DSM_OVDCAUSE        = 0x20;


        /// <summary>
        /// DECIMATOR
        /// </summary>


        /// <summary>
        /// DEC.CR Control Register 0 
        /// </summary>

        public const uint DEC_SAT_EN  = 0x80; // Enable post process offset correction  
        public const uint DEC_FIR_EN  = 0x40; // Post process FIR enable   
        public const uint DEC_OCOR_EN = 0x20; // Offest correction enable  
        public const uint DEC_GCOR_EN = 0x10; // Enable gain correction feature  

        public const uint MODE_MASK          = 0x0C; // Conversion Mode  
        public const uint MODE_SINGLE_SAMPLE = 0x00;
        public const uint MODE_FAST_FILTER   = 0x04;
        public const uint MODE_CONTINUOUS    = 0x08;
        public const uint MODE_FAST_FIR      = 0x0C;

        public const uint DEC_XSTART_EN  = 0x02; // Enables external start signal  
        public const uint DEC_START_CONV = 0x01; // A write to this bit starts a conversion  


        /// <summary>
        /// DEC.SR Status and Control Register 0   
        /// </summary>

        public const uint DEC_CORECLK_DISABLE = 0x20; // Controls gating of the Core clock  
        public const uint DEC_INTR_PULSE      = 0x10; // Controls interrupt mode   
        public const uint DEC_OUT_ALIGN       = 0x08; // Controls 8-bit shift of SAMP registers  
        public const uint DEC_INTR_CLEAR      = 0x04; // A write to this bit clears bit0  
        public const uint DEC_INTR_MASK       = 0x02; // Controls the generation of the conversion comp. INTR  
        public const uint DEC_CONV_DONE       = 0x01; // Bit set if conversion has completed   

        /// <summary>
        /// DEC.SHIFT1 Decimator Input Shift Register 1  
        /// </summary>

        public const uint DEC_SHIFT1_MASK = 0x1F; // Input shift1 control  

        /// <summary>
        /// DEC.SHIFT2 Decimator Input Shift Register 2  
        /// </summary>

        public const uint DEC_SHIFT2_MASK = 0x0F; // Input shift2 control  

        /// <summary>
        /// DEC.DR2 Decimator Decimation Rate of FIR Filter Low Register  
        /// </summary>

        public const uint DEC_DR2_MASK = 0xFF;

        /// <summary>
        /// DEC.DR2H Decimator Decimation Rate of FIR Filter High Register  
        /// </summary>

        public const uint DEC_DR2H_MASK = 0x03;

        /// <summary>
        /// DEC.COHR Decimator Coherency Register    
        /// </summary>

        public const uint DEC_GCOR_KEY_MASK = 0x30;
        public const uint DEC_GCOR_KEY_OFF  = 0x00;
        public const uint DEC_GCOR_KEY_LOW  = 0x10;
        public const uint DEC_GCOR_KEY_MID  = 0x20;
        public const uint DEC_GCOR_KEY_HIGH = 0x30;

        public const uint DEC_OCOR_KEY_MASK = 0x0C;
        public const uint DEC_OCOR_KEY_OFF  = 0x00;
        public const uint DEC_OCOR_KEY_LOW  = 0x04;
        public const uint DEC_OCOR_KEY_MID  = 0x08;
        public const uint DEC_OCOR_KEY_HIGH = 0x0C;

        public const uint DEC_SAMP_KEY_MASK = 0x03;
        public const uint DEC_SAMP_KEY_OFF  = 0x00;
        public const uint DEC_SAMP_KEY_LOW  = 0x01;
        public const uint DEC_SAMP_KEY_MID  = 0x02;
        public const uint DEC_SAMP_KEY_HIGH = 0x03;

        /// <summary>
        /// DSM.SW3 DSM Analog Routing Register 3  
        /// </summary>

        public const uint DSM_VN_AMX      = 0x10;
        public const uint DSM_VN_VREF     = 0x20;
        public const uint DSM_VN_VSSA     = 0x40;
        public const uint DSM_VN_REF_MASK = 0x70; 

        /// <summary>
        /// Decimator GVAL
        /// </summary>

        public const uint DEC_GVAL_MIN = 0x0B;
        public const uint DEC_GVAL_MAX = 0x0F;
    }
}
