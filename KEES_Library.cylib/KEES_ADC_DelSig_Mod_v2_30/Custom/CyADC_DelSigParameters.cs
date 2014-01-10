/*******************************************************************************
* File Name: CyADC_DelSigParameters.cs
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;

namespace KEES_ADC_DelSig_Mod_v2_30
{
    class CyADC_DelSigParameters
    {
        public const uint MAX_CONFIGS = 4;

        #region Param Name Constants
        public const string ADC_CLOCK = "ADC_Clock";
        public const string INPUT_RANGE = "ADC_Input_Range";
        public const string INPUT_RANGE_CONFIG2 = "ADC_Input_Range_Config2";
        public const string INPUT_RANGE_CONFIG3 = "ADC_Input_Range_Config3";
        public const string INPUT_RANGE_CONFIG4 = "ADC_Input_Range_Config4";
        public const string ADC_REFERENCE = "ADC_Reference";
        public const string ADC_REFERENCE_CONFIG2 = "ADC_Reference_Config2";
        public const string ADC_REFERENCE_CONFIG3 = "ADC_Reference_Config3";
        public const string ADC_REFERENCE_CONFIG4 = "ADC_Reference_Config4";
        public const string RESOLUTION = "ADC_Resolution";
        public const string RESOLUTION_CONFIG2 = "ADC_Resolution_Config2";
        public const string RESOLUTION_CONFIG3 = "ADC_Resolution_Config3";
        public const string RESOLUTION_CONFIG4 = "ADC_Resolution_Config4";
        public const string CONVERSION_MODE = "Conversion_Mode";
        public const string CONVERSION_MODE_CONFIG2 = "Conversion_Mode_Config2";
        public const string CONVERSION_MODE_CONFIG3 = "Conversion_Mode_Config3";
        public const string CONVERSION_MODE_CONFIG4 = "Conversion_Mode_Config4";
        public const string INPUT_BUFFER_GAIN = "Input_Buffer_Gain";
        public const string INPUT_BUFFER_GAIN_CONFIG2 = "Input_Buffer_Gain_Config2";
        public const string INPUT_BUFFER_GAIN_CONFIG3 = "Input_Buffer_Gain_Config3";
        public const string INPUT_BUFFER_GAIN_CONFIG4 = "Input_Buffer_Gain_Config4";
        public const string INPUT_BUFFER_MODE = "Input_Buffer_Mode";
        public const string INPUT_BUFFER_MODE_CONFIG2 = "Input_Buffer_Mode_Config2";
        public const string INPUT_BUFFER_MODE_CONFIG3 = "Input_Buffer_Mode_Config3";
        public const string INPUT_BUFFER_MODE_CONFIG4 = "Input_Buffer_Mode_Config4";
        public const string SAMPLE_RATE = "Sample_Rate";
        public const string SAMPLE_RATE_CONFIG2 = "Sample_Rate_Config2";
        public const string SAMPLE_RATE_CONFIG3 = "Sample_Rate_Config3";
        public const string SAMPLE_RATE_CONFIG4 = "Sample_Rate_Config4";
        public const string REF_VOLTAGE = "Ref_Voltage";
        public const string REF_VOLTAGE_CONFIG2 = "Ref_Voltage_Config2";
        public const string REF_VOLTAGE_CONFIG3 = "Ref_Voltage_Config3";
        public const string REF_VOLTAGE_CONFIG4 = "Ref_Voltage_Config4";
        public const string CLOCK_FREQUENCY = "Clock_Frequency";
        public const string START_OF_CONVERSION = "Start_of_Conversion";
        public const string CONFIGS = "Configs";
        public const string ADC_CHARGE_PUMP_CLOCK = "ADC_Charge_Pump_Clock";
        public const string ADC_INPUT_MODE = "ADC_Input_Mode";
        public const string INPUT_MODE = "Input_Mode";
        public const string INPUT_MODE_CONFIG2 = "ADC_Input_Mode_Config2";
        public const string INPUT_MODE_CONFIG3 = "ADC_Input_Mode_Config3";
        public const string INPUT_MODE_CONFIG4 = "ADC_Input_Mode_Config4";
        public const string INPUT_RANGEVALUE = "ADC_Input_RangeValue";
        public const string INPUT_RANGEVALUE_CONFIG2 = "ADC_Input_RangeValue_Config2";
        public const string INPUT_RANGEVALUE_CONFIG3 = "ADC_Input_RangeValue_Config3";
        public const string INPUT_RANGEVALUE_CONFIG4 = "ADC_Input_RangeValue_Config4";
        public const string ADC_nVref = "Enable_Vref_Vss";
        public const string ADC_Vdda_Value = "Vdda_Value";

        public const string ADC_COMMENT_CONFIG1 = "Comment_Config1";
        public const string ADC_COMMENT_CONFIG2 = "Comment_Config2";
        public const string ADC_COMMENT_CONFIG3 = "Comment_Config3";
        public const string ADC_COMMENT_CONFIG4 = "Comment_Config4";

        public const string CONFIG1_NAME = "Config1_Name";
        public const string CONFIG2_NAME = "Config2_Name";
        public const string CONFIG3_NAME = "Config3_Name";
        public const string CONFIG4_NAME = "Config4_Name";

        public const string S_SOFTWARE = "Software";
        public const string S_INTERNAL = "Internal";
        public const string S_HARDWARE = "Hardware";
        public const string S_EXTERNAL = "External";
        public const string SRATE_ERR = "sRate_Err";
        
        

        #endregion


        // Member variables. Note: Some of these can be made an array. 
        public CyCompDevParam m_ADC_Clock = null;
        public CyCompDevParam m_ADC_Input_Range = null;
        public CyCompDevParam m_ADC_Input_Range_Config2 = null;
        public CyCompDevParam m_ADC_Input_Range_Config3 = null;
        public CyCompDevParam m_ADC_Input_Range_Config4 = null;
        public CyCompDevParam m_ADC_Reference = null;
        public CyCompDevParam m_ADC_Reference_Config2 = null;
        public CyCompDevParam m_ADC_Reference_Config3 = null;
        public CyCompDevParam m_ADC_Reference_Config4 = null;
        public CyCompDevParam m_ADC_Resolution = null;
        public CyCompDevParam m_ADC_Resolution_Config2 = null;
        public CyCompDevParam m_ADC_Resolution_Config3 = null;
        public CyCompDevParam m_ADC_Resolution_Config4 = null;
        public CyCompDevParam m_Conversion_Mode = null;
        public CyCompDevParam m_Conversion_Mode_Config2 = null;
        public CyCompDevParam m_Conversion_Mode_Config3 = null;
        public CyCompDevParam m_Conversion_Mode_Config4 = null;
        public CyCompDevParam m_Input_Buffer_Gain = null;
        public CyCompDevParam m_Input_Buffer_Gain_Config2 = null;
        public CyCompDevParam m_Input_Buffer_Gain_Config3 = null;
        public CyCompDevParam m_Input_Buffer_Gain_Config4 = null;
        public CyCompDevParam m_Input_Buffer_Mode = null;
        public CyCompDevParam m_Input_Buffer_Mode_Config2 = null;
        public CyCompDevParam m_Input_Buffer_Mode_Config3 = null;
        public CyCompDevParam m_Input_Buffer_Mode_Config4 = null;
        public CyCompDevParam m_Sample_Rate = null;
        public CyCompDevParam m_Sample_Rate_Config2 = null;
        public CyCompDevParam m_Sample_Rate_Config3 = null;
        public CyCompDevParam m_Sample_Rate_Config4 = null;
        public CyCompDevParam m_Ref_Voltage = null;
        public CyCompDevParam m_Ref_Voltage_Config2 = null;
        public CyCompDevParam m_Ref_Voltage_Config3 = null;
        public CyCompDevParam m_Ref_Voltage_Config4 = null;
        public CyCompDevParam m_Clock_Frequency = null;
        public CyCompDevParam m_Start_of_Conversion = null;
        public CyCompDevParam m_Configs = null;
        public CyCompDevParam m_ADC_Charge_Pump_Clock = null;
        public CyCompDevParam m_ADC_Input_Mode = null;
        public CyCompDevParam m_Enable_Vref_Vss = null;
        public CyCompDevParam m_Comment_Config1 = null;
        public CyCompDevParam m_Comment_Config2 = null;
        public CyCompDevParam m_Comment_Config3 = null;
        public CyCompDevParam m_Comment_Config4 = null;

        public CyCompDevParam m_Config1_Name = null;
        public CyCompDevParam m_Config2_Name = null;
        public CyCompDevParam m_Config3_Name = null;
        public CyCompDevParam m_Config4_Name = null;
        
        public CyCompDevParam m_ADC_ExVref_Num = null;

        public CyCompDevParam m_Vdda_Value = null;

        public CyADC_DelSigParameters(ICyInstEdit_v1 inst)
        {
            GetParams(inst);
        }

        // Get parameter values
        private void GetParams(ICyInstEdit_v1 inst)
        {
            m_ADC_Clock = inst.GetCommittedParam(ADC_CLOCK);

            m_ADC_Input_Range = inst.GetCommittedParam(INPUT_RANGE);
            m_ADC_Input_Range_Config2 = inst.GetCommittedParam(INPUT_RANGE_CONFIG2);
            m_ADC_Input_Range_Config3 = inst.GetCommittedParam(INPUT_RANGE_CONFIG3);
            m_ADC_Input_Range_Config4 = inst.GetCommittedParam(INPUT_RANGE_CONFIG4);

            m_ADC_Reference = inst.GetCommittedParam(ADC_REFERENCE);
            m_ADC_Reference_Config2 = inst.GetCommittedParam(ADC_REFERENCE_CONFIG2);
            m_ADC_Reference_Config3 = inst.GetCommittedParam(ADC_REFERENCE_CONFIG3);
            m_ADC_Reference_Config4 = inst.GetCommittedParam(ADC_REFERENCE_CONFIG4);

            m_ADC_Resolution = inst.GetCommittedParam(RESOLUTION);
            m_ADC_Resolution_Config2 = inst.GetCommittedParam(RESOLUTION_CONFIG2);
            m_ADC_Resolution_Config3 = inst.GetCommittedParam(RESOLUTION_CONFIG3);
            m_ADC_Resolution_Config4 = inst.GetCommittedParam(RESOLUTION_CONFIG4);

            m_Conversion_Mode = inst.GetCommittedParam(CONVERSION_MODE);
            m_Conversion_Mode_Config2 = inst.GetCommittedParam(CONVERSION_MODE_CONFIG2);
            m_Conversion_Mode_Config3 = inst.GetCommittedParam(CONVERSION_MODE_CONFIG3);
            m_Conversion_Mode_Config4 = inst.GetCommittedParam(CONVERSION_MODE_CONFIG4);
            m_Input_Buffer_Gain = inst.GetCommittedParam(INPUT_BUFFER_GAIN);
            m_Input_Buffer_Gain_Config2 = inst.GetCommittedParam(INPUT_BUFFER_GAIN_CONFIG2);
            m_Input_Buffer_Gain_Config3 = inst.GetCommittedParam(INPUT_BUFFER_GAIN_CONFIG3);
            m_Input_Buffer_Gain_Config4 = inst.GetCommittedParam(INPUT_BUFFER_GAIN_CONFIG4);
            m_Input_Buffer_Mode = inst.GetCommittedParam(INPUT_BUFFER_MODE);
            m_Input_Buffer_Mode_Config2 = inst.GetCommittedParam(INPUT_BUFFER_MODE_CONFIG2);
            m_Input_Buffer_Mode_Config3 = inst.GetCommittedParam(INPUT_BUFFER_MODE_CONFIG3);
            m_Input_Buffer_Mode_Config4 = inst.GetCommittedParam(INPUT_BUFFER_MODE_CONFIG4);

            m_Sample_Rate = inst.GetCommittedParam(SAMPLE_RATE);
            m_Sample_Rate_Config2 = inst.GetCommittedParam(SAMPLE_RATE_CONFIG2);
            m_Sample_Rate_Config3 = inst.GetCommittedParam(SAMPLE_RATE_CONFIG3);
            m_Sample_Rate_Config4 = inst.GetCommittedParam(SAMPLE_RATE_CONFIG4);
            m_Ref_Voltage = inst.GetCommittedParam(REF_VOLTAGE);
            m_Ref_Voltage_Config2 = inst.GetCommittedParam(REF_VOLTAGE_CONFIG2);
            m_Ref_Voltage_Config3 = inst.GetCommittedParam(REF_VOLTAGE_CONFIG3);
            m_Ref_Voltage_Config4 = inst.GetCommittedParam(REF_VOLTAGE_CONFIG4);

            m_Clock_Frequency = inst.GetCommittedParam(CLOCK_FREQUENCY);
            m_Start_of_Conversion = inst.GetCommittedParam(START_OF_CONVERSION);
            m_Configs = inst.GetCommittedParam(CONFIGS);
            m_ADC_Charge_Pump_Clock = inst.GetCommittedParam(ADC_CHARGE_PUMP_CLOCK);
            m_ADC_Input_Mode = inst.GetCommittedParam(ADC_INPUT_MODE);
            m_Enable_Vref_Vss = inst.GetCommittedParam(ADC_nVref);

            m_Comment_Config1 = inst.GetCommittedParam(ADC_COMMENT_CONFIG1);
            m_Comment_Config2 = inst.GetCommittedParam(ADC_COMMENT_CONFIG2);
            m_Comment_Config3 = inst.GetCommittedParam(ADC_COMMENT_CONFIG3);
            m_Comment_Config4 = inst.GetCommittedParam(ADC_COMMENT_CONFIG4);

            m_Config1_Name = inst.GetCommittedParam(CONFIG1_NAME);
            m_Config2_Name = inst.GetCommittedParam(CONFIG2_NAME);
            m_Config3_Name = inst.GetCommittedParam(CONFIG3_NAME);
            m_Config4_Name = inst.GetCommittedParam(CONFIG4_NAME);

            m_ADC_ExVref_Num = inst.GetCommittedParam("ADC_ExVref_Num");

            m_Vdda_Value = inst.GetCommittedParam(ADC_Vdda_Value);

        }
        
        private void SetParam(ICyInstEdit_v1 inst, string ParamName, string value)
        {

        }

        private void CommitParams(ICyInstEdit_v1 inst)
        {
            inst.CommitParamExprs();
        }
    }
}