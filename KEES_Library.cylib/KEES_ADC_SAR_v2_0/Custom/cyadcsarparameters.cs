/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System;

namespace KEES_ADC_SAR_v2_0
{
    #region Symbol Parameter Names
    public class CyParamNames
    {
        // Formal parameters
        public const string ADC_RESOLUTION = "ADC_Resolution";
        public const string ADC_CLOCK = "ADC_Clock";
        public const string ADC_SAMPLE_MODE = "ADC_SampleMode";
        public const string ADC_INPUT_RANGE = "ADC_Input_Range";
        public const string ADC_REFERENCE = "ADC_Reference";
        public const string SAMPLE_RATE = "Sample_Rate";
        public const string REF_VOLTAGE = "Ref_Voltage";
        public const string SAMPLE_PRECHARGE = "Sample_Precharge";
        public const string ENABLE_NEXT_OUT = "Enable_next_out";

        // Local parameters
        public const string ADC_CLOCK_FREQUENCY = "ADC_Clock_Frequency";
        public const string SAMPLE_RATE_DEFAULT = "Sample_Rate_def";
        public const string INSTANCE_NAME = "INSTANCE_NAME";
    }
    #endregion

    #region Symbol Types
    public enum CyEAdcSampleModeType { Free_Running, Software_Trigger, Hardware_Trigger };
    public enum CyEAdcClockSrcType { External, Internal };
    public enum CyEAdcResolution { Bits_8 = 8, Bits_10 = 10, Bits_12 = 12 };
    public enum CyEAdcInputRangeType
    {
        Vss_to_Vref,
        Vssa_to_Vdda,
        Vssa_to_VDAC,
        Vneg_Vref_Diff,
        Vneg_Vdda_Diff,
        Vneg_Vdda_2_Diff,
        Vneg_VDAC_Diff
    };
    public enum CyEAdcRefType { Int_Ref_Not_Bypassed, Int_Ref_Bypass, Ext_Ref };
    #endregion

    #region Parameter Ranges
    public class CyParamRange
    {
        public const uint SAMPLE_RATE_MIN = 0;

        public static readonly uint ClockFreqMinMHz = 1;
        public static uint ClockFreqMaxMHz;
        public static double MinimumPulseWidth;

        public static uint ClockFreqMinHz
        {
            get
            {
                return ClockFreqMinMHz * 1000000;
            }
        }
        public static uint ClockFreqMaxHz
        {
            get
            {
                return ClockFreqMaxMHz * 1000000;
            }
        }
        public static uint ClockFreqMinKHz
        {
            get
            {
                return ClockFreqMinMHz * 1000;
            }
        }
        public static uint ClockFreqMaxKHz
        {
            get
            {
                return ClockFreqMaxMHz * 1000;
            }
        }

        public const uint MAX_FREQ_PSOC5A = 14;
        public const uint MAX_FREQ_PSOC5LP = 18;

        // minimum pulse width value = 1/14Mhz = 71.43ns / 2 = 35.71ns - some margin (~+-4% CDT 91247) = 33ns.
        // minimum pulse width value = 1/18Mhz = 55.55ns / 2 = 27.77ns - some margin (~+-4% CDT 91247) = 25.5ns.
        public const double MINIMUM_PULSE_WIDTH_PSOC5A = 33;
        public const double MINIMUM_PULSE_WIDTH_PSOC5LP = 25.5;
        public const double HIGH_POWER_PULSE_WIDTH = 50;

        public const double REF_VOLTAGE_MIN = 0.8;
        public const double REF_VOLTAGE_MAX = 5.5;

        public const uint CONVERSION_RATE_INT_VREF_MAX = 100000;

        public const int SAMPLE_PER_CHARGE_PSOC5A = 7;
        public const int SAMPLE_PER_CHARGE_PSOC5LP = 6;
        public const byte RESOLUTION_PSOC5A = 12;
    }
    #endregion

    public class CySARADCParameters
    {
        public const string PSOC_5A = "PSoC5A";
        public ICyInstQuery_v1 m_inst;
        ICyInstValidate_v1 m_instVal;
        public string m_instanceName;
        /// <summary>
        /// During first getting of parameters this variable is false, what means that assigning
        /// values to form controls will not immediatly overwrite parameters with the same values.
        /// </summary>
        public bool m_globalEditMode = false;
        public CySARADCControl m_control = null;
        public double m_externalClockInKHz;
        public double m_systemVdda;

        // Lists contain display names of types taken from symbol,
        // lists are used to fill comboboxes
        public List<string> m_resolutionList;
        public List<string> m_inputRangeList;
        public List<string> m_referenceList;
        // Dictionary is used to keep display names of types taken from symbol,
        // and associate them with the enum fields to simplify access to diaplay names
        public Dictionary<object, string> m_dnDict = new Dictionary<object, string>();

        public static bool IsArchMemberAvailable = false;
        public static string ArchFamilyMemberName;
        public int m_samplePercharge;
        public byte m_actualResolution;

        #region Constructor(s)
        public CySARADCParameters(ICyInstValidate_v1 instVal)
        {
            m_instVal = instVal;
            ArchFamilyMemberName = instVal.ArchFamilyMember;
            InitializeSiliconDependentVariables(ArchFamilyMemberName);
        }

        public CySARADCParameters(ICyInstQuery_v1 inst, ICyTerminalQuery_v1 termQuery)
        {
            this.m_inst = inst;
            ArchFamilyMemberName = m_inst.DeviceQuery.ArchFamilyMember;
            m_instanceName = m_inst.InstanceName;
            InitializeSiliconDependentVariables(ArchFamilyMemberName);

            m_resolutionList = new List<string>(inst.GetPossibleEnumValues(CyParamNames.ADC_RESOLUTION));
            m_inputRangeList = new List<string>(inst.GetPossibleEnumValues(CyParamNames.ADC_INPUT_RANGE));
            m_referenceList = new List<string>(inst.GetPossibleEnumValues(CyParamNames.ADC_REFERENCE));
            m_externalClockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);

            try
            {
                m_systemVdda = System.Math.Round(inst.VoltageQuery.VDDA, 4);
            }
            catch
            {
                m_systemVdda = 5;
            }

            // Adding display names to the dictionary to easily operate with enums
            CyDictParser.FillDictionary(ref m_dnDict, typeof(CyEAdcInputRangeType), m_inputRangeList);
            CyDictParser.FillDictionary(ref m_dnDict, typeof(CyEAdcRefType), m_referenceList);
        }

        private void InitializeSiliconDependentVariables(string archFamilyMemberName)
        {
            if (string.IsNullOrEmpty(archFamilyMemberName))
            {
                IsArchMemberAvailable = false;
            }
            else
            {
                IsArchMemberAvailable = true;
                if (archFamilyMemberName == PSOC_5A)
                {
                    CyParamRange.ClockFreqMaxMHz = CyParamRange.MAX_FREQ_PSOC5A;
                    CyParamRange.MinimumPulseWidth = CyParamRange.MINIMUM_PULSE_WIDTH_PSOC5A;
                    m_samplePercharge = CyParamRange.SAMPLE_PER_CHARGE_PSOC5A;
                    m_actualResolution = CyParamRange.RESOLUTION_PSOC5A;
                }
                else
                {
                    CyParamRange.ClockFreqMaxMHz = CyParamRange.MAX_FREQ_PSOC5LP;
                    CyParamRange.MinimumPulseWidth = CyParamRange.MINIMUM_PULSE_WIDTH_PSOC5LP;
                    m_samplePercharge = CyParamRange.SAMPLE_PER_CHARGE_PSOC5LP;
                    m_actualResolution = (byte)this.AdcResolution;
                }
            }
        }
        #endregion

        #region Class properties
        public CyEAdcResolution AdcResolution
        {
            get
            {
                return GetValue<CyEAdcResolution>(CyParamNames.ADC_RESOLUTION);
            }
            set
            {
                SetValue(CyParamNames.ADC_RESOLUTION, value);
                if (ArchFamilyMemberName != PSOC_5A)
                    m_actualResolution = (byte)value;
            }
        }

        public CyEAdcClockSrcType AdcClockSource
        {
            get
            {
                return GetValue<CyEAdcClockSrcType>(CyParamNames.ADC_CLOCK);
            }
            set
            {
                SetValue(CyParamNames.ADC_CLOCK, value);
            }
        }

        public CyEAdcSampleModeType AdcSampleMode
        {
            get
            {
                return GetValue<CyEAdcSampleModeType>(CyParamNames.ADC_SAMPLE_MODE);
            }
            set
            {
                SetValue(CyParamNames.ADC_SAMPLE_MODE, value);
            }
        }

        public CyEAdcInputRangeType AdcInputRange
        {
            get
            {
                return GetValue<CyEAdcInputRangeType>(CyParamNames.ADC_INPUT_RANGE);
            }
            set
            {
                SetValue(CyParamNames.ADC_INPUT_RANGE, value);
            }
        }

        public CyEAdcRefType AdcReference
        {
            get
            {
                return GetValue<CyEAdcRefType>(CyParamNames.ADC_REFERENCE);
            }
            set
            {
                SetValue(CyParamNames.ADC_REFERENCE, value);
            }
        }

        public uint AdcSampleRate
        {
            get
            {
                return GetValue<uint>(CyParamNames.SAMPLE_RATE);
            }
            set
            {
                SetValue(CyParamNames.SAMPLE_RATE, value);
            }
        }

        public double RefVoltage
        {
            get
            {
                return GetValue<double>(CyParamNames.REF_VOLTAGE);
            }
            set
            {
                SetValue(CyParamNames.REF_VOLTAGE, value);
            }
        }

        public uint SampleRateDefault
        {
            get
            {
                return GetValue<uint>(CyParamNames.SAMPLE_RATE_DEFAULT);
            }
        }

        public string InstanceName
        {
            get
            {
                return GetValue<string>(CyParamNames.INSTANCE_NAME);
            }
        }

        public bool EnableNextOut
        {
            get
            {
                return GetValue<bool>(CyParamNames.ENABLE_NEXT_OUT);
            }
            set
            {
                SetValue(CyParamNames.ENABLE_NEXT_OUT, value);
            }
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            CyCompDevParam param = null;
            T value;

            if (m_inst != null)
                param = m_inst.GetCommittedParam(paramName);
            else if (m_instVal != null)
                param = m_instVal.GetCommittedParam(paramName);

            CyCustErr err = param.TryGetValueAs<T>(out value);
            if (err.IsOK)
            {
                return value;
            }
            else
            {
                m_control.ShowError(paramName, err);
                return default(T);
            }
        }

        public void LoadParameters()
        {
            m_globalEditMode = false;
            m_control.UpdateUI();
            m_globalEditMode = true;
        }
        #endregion

        #region Getting Internal Frequency and External Sample Rate
        // Get the ADC clock frequency for the current settings in kHz.
        public double GetInternalFreq()
        {
            return (double)(AdcSampleRate * ((double)m_actualResolution +
                m_samplePercharge)) / 1000;
        }

        public uint GetExternalSampleRate()
        {
            if (m_externalClockInKHz >= 0)
                return GetSampleRate(m_externalClockInKHz);
            else
                return 0;
        }

        public uint GetSampleRate(double clockFrequencyInKHz)
        {
            if (clockFrequencyInKHz >= 0)
                return (uint)Math.Round((clockFrequencyInKHz * 1000) / ((double)m_actualResolution +
                    m_samplePercharge));
            else return 0;
        }

        public uint GetMaxSampleRate()
        {
            return (uint)Math.Round((double)CyParamRange.ClockFreqMaxHz / ((double)m_actualResolution +
                m_samplePercharge));
        }

        public uint GetMinSampleRate()
        {
            return (uint)Math.Round((double)CyParamRange.ClockFreqMinHz / ((double)m_actualResolution +
                m_samplePercharge));
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_globalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }
        #endregion

        #region External Clock Updating
        public void UpdateClock(ICyInstQuery_v1 edit, ICyTerminalQuery_v1 termQuery)
        {
            m_externalClockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);
            m_control.UpdateClockData();
            m_control.UpdateSampleRateData();
        }
        #endregion
    }
}
