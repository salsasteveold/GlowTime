/*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided. 
********************************************************************************/

using System;
using System.Collections.Generic;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Diagnostics;

namespace KEES_ADC_SAR_v2_0
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1, ICyDRCProvider_v1, ICyInstValidateHook_v1, ICyAPICustomize_v1
    {
        public const string CONFIGURE_TAB_NAME = "Configure";
        public string m_instanceName;

        #region ICyParamEditHook_v1 Members
        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            m_instanceName = edit.InstanceName;
            CySARADCParameters parameters = new CySARADCParameters(edit, termQuery);

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.LoadParameters();
            };

            editor.AddCustomPage(Resources.ConfigureTabCaption, new CySARADCControl(parameters, edit.DeviceQuery),
                ExprDelegate, CONFIGURE_TAB_NAME);
            editor.AddDefaultPage(Resources.BuiltInTabCaption, "Built-in");

            edit.NotifyWhenDesignUpdates(new CyDesignUpdated_v1(parameters.UpdateClock));

            parameters.LoadParameters();
            parameters.m_globalEditMode = true;
            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return false;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            CySARADCParameters parameters = new CySARADCParameters(args.InstQueryV1, args.TermQueryV1);
            CyCustErr err;

            // These verifications depend on silicon and cannot be calculated when silicon is unknown
            if (CySARADCParameters.IsArchMemberAvailable)
            {
                err = VerifyClock(args.InstQueryV1.DesignQuery, args.TermQueryV1, parameters.AdcClockSource,
                    parameters.InstanceName);
                if (err.IsOk == false)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

                err = VerifyExternalClock(args.TermQueryV1, parameters.AdcClockSource);
                if (err.IsOk == false)
                    yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
            }

            err = VerifyVoltage(args.InstQueryV1, parameters.RefVoltage, parameters.AdcReference,
                parameters.AdcInputRange);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyReference(parameters.AdcReference, parameters.AdcClockSource, parameters.AdcSampleRate,
                parameters.AdcInputRange);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyNextOut(args.DeviceQueryV1, parameters.EnableNextOut);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);

            err = VerifyVDACExternalRef(parameters);
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
        }

        CyCustErr VerifyClock(ICyDesignQuery_v1 designQuery, ICyTerminalQuery_v1 termQuery,
            CyEAdcClockSrcType adcClock, string instanceName)
        {
            double clockFrequency;
            string clockName = string.Empty;
            string clockID = string.Empty;
            if (adcClock == CyEAdcClockSrcType.Internal)
            {
                clockName = instanceName + CyClockReader.INTERNAL_CLK;
                clockID = CyClockReader.GetClockID(designQuery, clockName);
                clockFrequency = CyClockReader.GetInternalClockInHz(designQuery, instanceName);
            }
            else
            {
                List<string> clockIDsList = termQuery.GetClockIds(CyClockReader.EXTERNAL_CLK, 0);
                if (clockIDsList.Count > 0)
                    clockID = clockIDsList[0];
                clockFrequency = CyClockReader.GetExternalClockInKHz(termQuery) * 1000;
            }

            if (clockFrequency >= 0)
            {
                // Ten to the six power for converting Hz to MHz
                const int POW6 = 1000000;
                const int POW9 = 1000000000;
                // Converting clock name to clock ID for accuracy getting function
                //string clockID = CyClockReader.GetClockID(designQuery, clockName);
                // Get accuracy prcent with negative sign
                double plusAccuracyPercent = designQuery.GetClockPlusAccuracyPercent(clockID);
                // Get accuracy prcent with plus sign
                double minusAccuracyPercent = designQuery.GetClockMinusAccuracyPercent(clockID);
                // Minimum clock value with plus accuracy percent
                double minClockPlusAccuracy = CyParamRange.ClockFreqMinHz + (CyParamRange.ClockFreqMinHz
                    * plusAccuracyPercent / 100);
                // Maximum clock value with negative accuracy percent
                double maxClockMinusAccuracy = CyParamRange.ClockFreqMaxHz - (CyParamRange.ClockFreqMaxHz
                    * minusAccuracyPercent / 100);

                if (clockFrequency < minClockPlusAccuracy || clockFrequency > maxClockMinusAccuracy)
                {
                    return new CyCustErr(string.Format(Resources.DRCInternalClockFreqMsg,
                        CyParamRange.ClockFreqMinMHz, plusAccuracyPercent, minClockPlusAccuracy / POW6,
                        CyParamRange.ClockFreqMaxMHz, minusAccuracyPercent, maxClockMinusAccuracy / POW6));
                }
                else
                {
                    double pulseWidth = GetPulseWidth(designQuery, clockFrequency, clockID) * POW9;
                    if (pulseWidth < CyParamRange.MinimumPulseWidth)
                        return new CyCustErr(string.Format(Resources.DRCMinimumPulseWidthMsg,
                            CyParamRange.MinimumPulseWidth));
                    else
                        return CyCustErr.OK;
                }
            }
            return CyCustErr.OK;
        }

        private double GetPulseWidth(ICyDesignQuery_v1 designQuery, double clockFrequency, string clockID)
        {
            double pulseWidth = -1;
            uint clockDivider = 0;
            try
            {
                if (string.IsNullOrEmpty(clockID) == false)
                    clockDivider = designQuery.GetClockDivider(clockID);
                else
                    throw new Exception("Invalid clock ID.");

                if (clockDivider == 1)
                    pulseWidth = (1 / clockFrequency) / 2;
                else
                    pulseWidth = (1 / clockFrequency) * Math.Floor((double)clockDivider / 2) / clockDivider;
            }
            catch (Exception)
            {
                Debug.Assert(false);
            }

            return pulseWidth;
        }

        CyCustErr VerifyExternalClock(ICyTerminalQuery_v1 termQuery, CyEAdcClockSrcType clockSource)
        {
            if (clockSource == CyEAdcClockSrcType.External)
            {
                double externalClockInKHz = CyClockReader.GetExternalClockInKHz(termQuery);
                if (externalClockInKHz > 0)
                {
                    if (externalClockInKHz < CyParamRange.ClockFreqMinKHz ||
                        externalClockInKHz > CyParamRange.ClockFreqMaxKHz)
                    {
                        return new CyCustErr(string.Format(Resources.ClockFrequencyErrorMsg,
                            CyParamRange.ClockFreqMinMHz, CyParamRange.ClockFreqMaxMHz));
                    }
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyVoltage(ICyInstQuery_v1 instQuery, double refVoltage, CyEAdcRefType reference,
            CyEAdcInputRangeType inputRange)
        {
            double vdda = 0;

            try
            {
                vdda = Convert.ToDouble(Math.Round(instQuery.VoltageQuery.VDDA, 4));
            }
            catch
            {
                vdda = 0;
            }
            if (vdda > 0)
            {
                double maxVoltage;
                string message;
                // External voltage reference should be limited to Vdda/2 for "Vssa to Vdda(Single)" 
                // and "0.0 +/- Vdda/2(Differential)" input ranges

                if (reference == CyEAdcRefType.Ext_Ref && (inputRange == CyEAdcInputRangeType.Vssa_to_Vdda ||
                    inputRange == CyEAdcInputRangeType.Vneg_Vdda_2_Diff))
                {
                    maxVoltage = vdda / 2;
                    message = Resources.VoltageReferenceErrorMsgVddaDiv2;
                }
                else
                {
                    maxVoltage = vdda;
                    message = Resources.VoltageReferenceErrorMsg;
                }

                if (refVoltage < CyParamRange.REF_VOLTAGE_MIN || refVoltage > maxVoltage)
                {
                    return new CyCustErr(message, CyParamRange.REF_VOLTAGE_MIN, maxVoltage);
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyReference(CyEAdcRefType reference, CyEAdcClockSrcType clockSource, uint sampleRate,
            CyEAdcInputRangeType inputRange)
        {
            if (reference == CyEAdcRefType.Int_Ref_Not_Bypassed && inputRange != CyEAdcInputRangeType.Vneg_Vdda_Diff &&
                clockSource == CyEAdcClockSrcType.Internal && sampleRate > CyParamRange.CONVERSION_RATE_INT_VREF_MAX)
                return new CyCustErr(Resources.InvalidReferenceErrorMsg);
            else
                return CyCustErr.OK;
        }

        CyCustErr VerifyVDACExternalRef(CySARADCParameters parameters)
        {
            if (parameters.AdcReference == CyEAdcRefType.Ext_Ref &&
                (parameters.AdcInputRange == CyEAdcInputRangeType.Vneg_VDAC_Diff ||
               parameters.AdcInputRange == CyEAdcInputRangeType.Vssa_to_VDAC))
            {
                string currentInputRange = CyDictParser.GetDictValue(parameters.m_dnDict, parameters.AdcInputRange);
                return new CyCustErr(string.Format(Resources.VDACExternalRefErrorMsg, currentInputRange.Substring(0,
                    currentInputRange.IndexOf('(') - 1)));
            }
            else
                return CyCustErr.OK;
        }

        CyCustErr VerifyNextOut(ICyDeviceQuery_v1 deviceQuery, bool nextOutEnabled)
        {
            if (deviceQuery.ArchFamilyMember == CySARADCParameters.PSOC_5A && nextOutEnabled)
                return new CyCustErr(Resources.NextOutErrorMsg);
            else
                return CyCustErr.OK;
        }
        #endregion

        #region ICyInstValidateHook_v1 Members
        public void ValidateParams(ICyInstValidate_v1 instVal)
        {
            CySARADCParameters parameters = new CySARADCParameters(instVal);
            if (CySARADCParameters.IsArchMemberAvailable)
            {
                // Conversion rate validation
                if (parameters.AdcClockSource == CyEAdcClockSrcType.Internal &&
                    (parameters.AdcSampleRate < parameters.GetMinSampleRate() ||
                    parameters.AdcSampleRate > parameters.GetMaxSampleRate()))
                {
                    CyCustErr err = new CyCustErr(string.Format(Resources.DRCConversionRate,
                        CyParamRange.ClockFreqMinMHz, CyParamRange.ClockFreqMaxMHz));
                    instVal.AddError(CyParamNames.SAMPLE_RATE, err);
                }
            }
        }
        #endregion

        #region ICyAPICustomize_v1 Members
        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery,
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> customizers = new List<CyAPICustomizer>(apis);
            Dictionary<string, string> paramDict = new Dictionary<string, string>();

            if (customizers.Count > 0) paramDict = customizers[0].MacroDictionary;

            CySARADCParameters parameters = new CySARADCParameters(query, termQuery);
            double clockFrequency;
            double pulseWidth = 0;
            string clockName = string.Empty;
            string clockID = string.Empty;
            if (parameters.AdcClockSource == CyEAdcClockSrcType.Internal)
            {
                clockName = query.InstanceName + CyClockReader.INTERNAL_CLK;
                clockID = CyClockReader.GetClockID(query.DesignQuery, clockName);
                clockFrequency = CyClockReader.GetInternalClockInHz(query.DesignQuery, query.InstanceName);
            }
            else
            {
                List<string> clockIDsList = termQuery.GetClockIds(CyClockReader.EXTERNAL_CLK, 0);
                if (clockIDsList.Count > 0)
                    clockID = clockIDsList[0];
                clockFrequency = CyClockReader.GetExternalClockInKHz(termQuery) * 1000;
            }

            if (clockFrequency >= 0)
            {
                pulseWidth = GetPulseWidth(query.DesignQuery, clockFrequency, clockID) * 1000000000;
            }

            paramDict.Add("HighPowerPulse", (pulseWidth > CyParamRange.HIGH_POWER_PULSE_WIDTH ? 1 : 0).ToString());
            paramDict.Add("NominalClockFrequency", Convert.ToInt32(clockFrequency >= 0 ? clockFrequency :
                -1).ToString());

            for (int i = 0; i < customizers.Count; i++)
            {
                customizers[i].MacroDictionary = paramDict;
            }

            return customizers;
        }
        #endregion
    }
}
