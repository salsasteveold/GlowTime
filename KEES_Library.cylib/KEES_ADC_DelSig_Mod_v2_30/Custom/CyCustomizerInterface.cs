/*******************************************************************************
* File Name: CyCustomizerInterface.cs
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/
using System;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using System.Windows.Forms;
using System.Collections.Generic;
using KEES_ADC_DelSig_Mod_v2_30;

namespace KEES_ADC_DelSig_Mod_v2_30
{
    public partial class CyCustomizer : ICyParamEditHook_v1, ICyExprEval_v2, ICyDRCProvider_v1
    {
        public const string PSOC5A = "PSoC5A";
        private bool m_editParamOnDrop = false;
        const string BasicTabName = "Basic";
        const string BuiltinTabName = "Built-in";
        const string ConfigureTabName = "Configure";
        const string ADC_VDDA_3_REFERENCE = "8";
        const string ADC_VDDA_3_REFERENCE_BYPASSED_P03 = "9";
        const string ADC_VDDA_3_REFERENCE_BYPASSED_P32 = "10";
        const string ADC_VDDA_4_REFERENCE = "5";
        const string ADC_VDDA_4_REFERENCE_BYPASSED_P03 = "6";
        const string ADC_VDDA_4_REFERENCE_BYPASSED_P32 = "7";
        const string ADC_IR_VSSA_TO_VDDA = "2";
        const string EXTERNAL_VREF_P03 = "3";
        const string EXTERNAL_VREF_P32 = "4";
        const double VDDA3_LOWERLIMIT = 2.7;
        const double VDDA3_UPPERLIMIT = 3.9;
        const double VDDA4_LOWERLIMIT = 3.6;
        const double VDDA4_UPPERLIMIT = 5.2;
        const int ADC_BUFFER_GAIN = 1;
        const string ADC_IR_VSSA_TO_2VREF = "1";

        CyADC_DelSigControl m_control;
        CyADC_EditingControl m_editingControl;

        #region ICyParamEditHook_v1 Members

        System.Windows.Forms.DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, 
                                                                         ICyTerminalQuery_v1 termQuery, 
                                                                         ICyExpressMgr_v1 mgr)
        {
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            m_control = new CyADC_DelSigControl(edit);
            m_editingControl = new CyADC_EditingControl(edit, m_control, BasicTabName);
            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_control.UpdateFormFromParams(edit);
            };

            editor.AddCustomPage(ConfigureTabName, m_editingControl, ExprDelegate, BasicTabName);
            editor.AddDefaultPage(BuiltinTabName, BuiltinTabName);
            editor.UseBigEditor = true;
            DialogResult result = editor.ShowDialog();
            
            // Place calculations here *****************************************************************************
        
            edit.CommitParamExprs();

            return result;
        }

        #region ICyDRCProvider_v1 Members
        public IEnumerable<CyDRCInfo_v1> GetDRCs(ICyDRCProviderArgs_v1 args)
        {
            string ADC_nVrefValue = args.InstQueryV1.GetCommittedParam(CyADC_DelSigParameters.ADC_nVref).Value;
            string ADC_Reference = args.InstQueryV1.GetCommittedParam(CyADC_DelSigParameters.ADC_REFERENCE).Value;
            string ADC_Reference_Config2 = args.InstQueryV1.GetCommittedParam
                                           (CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2).Value;
            string ADC_Reference_Config3 = args.InstQueryV1.GetCommittedParam
                                           (CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3).Value;
            string ADC_Reference_Config4 = args.InstQueryV1.GetCommittedParam
                                           (CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4).Value;
            string ADC_InputRange = args.InstQueryV1.GetCommittedParam
                                           (CyADC_DelSigParameters.INPUT_RANGE).Value;
            string ADC_InputRange_Config2 = args.InstQueryV1.GetCommittedParam
                                           (CyADC_DelSigParameters.INPUT_RANGE_CONFIG2).Value;
            string ADC_InputRange_Config3 = args.InstQueryV1.GetCommittedParam
                                           (CyADC_DelSigParameters.INPUT_RANGE_CONFIG3).Value;
            string ADC_InputRange_Config4 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.INPUT_RANGE_CONFIG4).Value;
            string ADC_RefVoltage = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.REF_VOLTAGE).Value;
            string ADC_RefVoltage_Config2 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2).Value;
            string ADC_RefVoltage_Config3 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3).Value;
            string ADC_RefVoltage_Config4 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4).Value;

            string ADC_Config1_Name = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.CONFIG1_NAME).Value;
            string ADC_Config2_Name = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.CONFIG2_NAME).Value;
            string ADC_Config3_Name = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.CONFIG3_NAME).Value;
            string ADC_Config4_Name = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.CONFIG4_NAME).Value;
            string sRate_Err = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.SRATE_ERR).Value;
            string ADC_Buffer_Gain1 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.INPUT_BUFFER_GAIN).Value;
            string ADC_Buffer_Gain2 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG2).Value;
            string ADC_Buffer_Gain3 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG3).Value;
            string ADC_Buffer_Gain4 = args.InstQueryV1.GetCommittedParam
                                            (CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG4).Value;

            CyCustErr err1 = VerifyReferenceSelection(args, args.InstQueryV1.VoltageQuery, ADC_Reference,
                                                      ADC_Reference_Config2, ADC_Reference_Config3,
                                                      ADC_Reference_Config4, ADC_InputRange, ADC_InputRange_Config2, 
                                                      ADC_InputRange_Config3, ADC_InputRange_Config4);

            CyCustErr err = VerifyVrefValue(args, args.InstQueryV1.VoltageQuery, ADC_Reference, ADC_Reference_Config2,
                                            ADC_Reference_Config3, ADC_Reference_Config4, ADC_InputRange,
                                             ADC_InputRange_Config2, ADC_InputRange_Config3, ADC_InputRange_Config4,
                                             ADC_RefVoltage, ADC_RefVoltage_Config2, ADC_RefVoltage_Config3, 
                                             ADC_RefVoltage_Config4);

            CyCustErr err2 = VerifynVrefSelection(args, ADC_nVrefValue);

            CyCustErr configErr = VerifyConfigNames(args, ADC_Config1_Name, ADC_Config2_Name, ADC_Config3_Name, 
                                                    ADC_Config4_Name);
            CyCustErr sRateErr = VerifySampleRate(args, sRate_Err);
            CyCustErr bufferGainErr = VerifyBufferGain(args, ADC_InputRange, ADC_InputRange_Config2,
                                                       ADC_InputRange_Config3, ADC_InputRange_Config4,
                                                       ADC_Buffer_Gain1, ADC_Buffer_Gain2,
                                                       ADC_Buffer_Gain3, ADC_Buffer_Gain4);
                        
            if (err.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err.Message);
            
            if (err1.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err1.Message);
            
            if (err2.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, err2.Message);

            if (configErr.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, configErr.Message);

            if (sRateErr.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Error, sRateErr.Message);

            if (bufferGainErr.IsOk == false)
                yield return new CyDRCInfo_v1(CyDRCInfo_v1.CyDRCType_v1.Warning, bufferGainErr.Message);

        }

        CyCustErr VerifyReferenceSelection(ICyDRCProviderArgs_v1 drcQuery, ICyVoltageQuery_v1 voltage, 
                                           string ADC_Reference, string ADC_Reference_Config2, 
                                           string ADC_Reference_Config3, string ADC_Reference_Config4, 
                                           string ADC_InputRange, string ADC_InputRange_Config2, 
                                           string ADC_InputRange_Config3, string ADC_InputRange_Config4)
        {
            double vdda = Convert.ToDouble(voltage.VDDA);
            if (drcQuery.DeviceQueryV1.ArchFamilyMember == PSOC5A && drcQuery.DeviceQueryV1.IsPSoC5 == true)
            {
                bool isADCRerence_Vdda3 = 
                    (((ADC_Reference.Equals(ADC_VDDA_3_REFERENCE) || 
                       ADC_Reference.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                       ADC_Reference.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                       (!ADC_InputRange.Equals(ADC_IR_VSSA_TO_VDDA))) ||
                     ((ADC_Reference_Config2.Equals(ADC_VDDA_3_REFERENCE) || 
                       ADC_Reference_Config2.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                       ADC_Reference_Config2.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                      (!ADC_InputRange_Config2.Equals(ADC_IR_VSSA_TO_VDDA))) ||
                     ((ADC_Reference_Config3.Equals(ADC_VDDA_3_REFERENCE) || 
                       ADC_Reference_Config3.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                       ADC_Reference_Config3.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                      (!ADC_InputRange_Config3.Equals(ADC_IR_VSSA_TO_VDDA))) ||
                     ((ADC_Reference_Config4.Equals(ADC_VDDA_3_REFERENCE) || 
                       ADC_Reference_Config4.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                       ADC_Reference_Config4.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                      (!ADC_InputRange_Config4.Equals(ADC_IR_VSSA_TO_VDDA))));

                if (isADCRerence_Vdda3)
                {
                    return new CyCustErr(Resource.VerifySelectedReferenceErrorMsg);
                }

                if ((vdda < MAX_VDDA3_VALUE) && 
                    (ADC_InputRange.Equals(ADC_IR_VSSA_TO_VDDA) ||
                     ADC_InputRange_Config2.Equals(ADC_IR_VSSA_TO_VDDA) || 
                     ADC_InputRange_Config3.Equals(ADC_IR_VSSA_TO_VDDA) || 
                     ADC_InputRange_Config4.Equals(ADC_IR_VSSA_TO_VDDA)))
                {
                    return new CyCustErr(Resource.VerifyVssaToVddaSelectedReference);
                }
            }
            return CyCustErr.OK;
        }
        
        CyCustErr VerifynVrefSelection(ICyDRCProviderArgs_v1 drcQuery, string ADC_nVrefValue)
        {
            if (drcQuery.DeviceQueryV1.ArchFamilyMember == PSOC5A && drcQuery.DeviceQueryV1.IsPSoC5 == true)
            {
                
                if (ADC_nVrefValue.Equals(Resource.TrueText))
                {
                    return new CyCustErr(Resource.VerifynVrefSelectionErrorMsg);
                }
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyConfigNames(ICyDRCProviderArgs_v1 drcQuery, string ADC_Config1_Name, string ADC_Config2_Name,
                                    string ADC_Config3_Name, string ADC_Config4_Name)
        {
            if ((ADC_Config1_Name == ADC_Config2_Name) || (ADC_Config1_Name == ADC_Config3_Name) ||
                (ADC_Config1_Name == ADC_Config4_Name) || (ADC_Config2_Name == ADC_Config3_Name) ||
                (ADC_Config2_Name == ADC_Config4_Name) || (ADC_Config3_Name == ADC_Config4_Name))
            {
                return new CyCustErr(Resource.VerifyConfigNamesErrMsg);
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifySampleRate(ICyDRCProviderArgs_v1 drcQuery, string sRateErr)
        {
            if (sRateErr.Equals(Resource.TrueText))
            {
                return new CyCustErr(Resource.VerifysRateErrMsg);
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyBufferGain(ICyDRCProviderArgs_v1 drcQuery, string ADC_InputRange1, string ADC_InputRange2,
                                   string ADC_InputRange3, string ADC_InputRange4, string ADC_BufferGain1, 
                                   string ADC_BufferGain2, string ADC_BufferGain3, string ADC_BufferGain4)
        {
            int bufferGain1 = Convert.ToInt32(ADC_BufferGain1);
            int bufferGain2 = Convert.ToInt32(ADC_BufferGain2);
            int bufferGain3 = Convert.ToInt32(ADC_BufferGain3);
            int bufferGain4 = Convert.ToInt32(ADC_BufferGain4);

            if (((ADC_InputRange1.Equals(ADC_IR_VSSA_TO_2VREF) || ADC_InputRange1.Equals(ADC_IR_VSSA_TO_VDDA)) &&
                (bufferGain1 > ADC_BUFFER_GAIN)) ||
                ((ADC_InputRange2.Equals(ADC_IR_VSSA_TO_2VREF) || ADC_InputRange2.Equals(ADC_IR_VSSA_TO_VDDA)) &&
                (bufferGain2 > ADC_BUFFER_GAIN)) ||
                ((ADC_InputRange3.Equals(ADC_IR_VSSA_TO_2VREF) || ADC_InputRange3.Equals(ADC_IR_VSSA_TO_VDDA)) &&
                (bufferGain3 > ADC_BUFFER_GAIN)) ||
                ((ADC_InputRange4.Equals(ADC_IR_VSSA_TO_2VREF) || ADC_InputRange4.Equals(ADC_IR_VSSA_TO_VDDA)) &&
                (bufferGain4 > ADC_BUFFER_GAIN)))
            {
                return new CyCustErr(Resource.VerifyBufferGainErrMsg);
            }
            return CyCustErr.OK;
        }

        CyCustErr VerifyVrefValue(ICyDRCProviderArgs_v1 drcQuery, ICyVoltageQuery_v1 voltage, string ADC_Reference, 
                                  string ADC_Reference_Config2, string ADC_Reference_Config3, 
                                  string ADC_Reference_Config4, string ADC_InputRange, string ADC_InputRange_Config2,
                                  string ADC_InputRange_Config3, string ADC_InputRange_Config4, string ADC_RefVoltage, 
                                  string ADC_RefVoltage_Config2, string ADC_RefVoltage_Config3, 
                                  string ADC_RefVoltage_Config4)
        {
            double vdda = Convert.ToDouble(voltage.VDDA);
            double Vref = Convert.ToDouble (ADC_RefVoltage);
            double Vref_Config2 = Convert.ToDouble (ADC_RefVoltage_Config2);
            double Vref_Config3 = Convert.ToDouble (ADC_RefVoltage_Config3);
            double Vref_Config4 = Convert.ToDouble (ADC_RefVoltage_Config4);

            bool isADCRerence_Vdda3 = (((ADC_Reference.Equals(ADC_VDDA_3_REFERENCE) || 
                                         ADC_Reference.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                                         ADC_Reference.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                                        (!(ADC_InputRange.Equals(ADC_IR_VSSA_TO_VDDA)))) ||
                                        ((ADC_Reference_Config2.Equals(ADC_VDDA_3_REFERENCE) || 
                                          ADC_Reference_Config2.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                                          ADC_Reference_Config2.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                                        (!(ADC_InputRange_Config2.Equals(ADC_IR_VSSA_TO_VDDA)))) || 
                                        ((ADC_Reference_Config3.Equals(ADC_VDDA_3_REFERENCE) || 
                                          ADC_Reference_Config3.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                                          ADC_Reference_Config3.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                                        (!(ADC_InputRange_Config3.Equals(ADC_IR_VSSA_TO_VDDA)))) || 
                                        ((ADC_Reference_Config4.Equals(ADC_VDDA_3_REFERENCE) || 
                                          ADC_Reference_Config4.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P03) ||
                                          ADC_Reference_Config4.Equals(ADC_VDDA_3_REFERENCE_BYPASSED_P32)) && 
                                        (!(ADC_InputRange_Config4.Equals(ADC_IR_VSSA_TO_VDDA)))));

            bool isADCReference_Vdda4 = (((ADC_Reference.Equals(ADC_VDDA_4_REFERENCE) || 
                                           ADC_Reference.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P03) ||
                                           ADC_Reference.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P32)) && 
                                          (!(ADC_InputRange.Equals(ADC_IR_VSSA_TO_VDDA)))) ||
                                         ((ADC_Reference_Config2.Equals(ADC_VDDA_4_REFERENCE) || 
                                           ADC_Reference_Config2.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P03) ||
                                           ADC_Reference_Config2.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P32))&& 
                                          (!(ADC_InputRange_Config2.Equals(ADC_IR_VSSA_TO_VDDA)))) ||
                                         ((ADC_Reference_Config3.Equals(ADC_VDDA_4_REFERENCE) || 
                                           ADC_Reference_Config3.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P03) ||
                                           ADC_Reference_Config3.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P32)) && 
                                          (!(ADC_InputRange_Config3.Equals(ADC_IR_VSSA_TO_VDDA)))) ||
                                         ((ADC_Reference_Config4.Equals(ADC_VDDA_4_REFERENCE) || 
                                           ADC_Reference_Config4.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P03) ||
                                           ADC_Reference_Config4.Equals(ADC_VDDA_4_REFERENCE_BYPASSED_P32)) && 
                                          (!(ADC_InputRange_Config4.Equals(ADC_IR_VSSA_TO_VDDA)))));

            bool isADCInputRage_Vssa_to_Vdda = (ADC_InputRange.Equals(ADC_IR_VSSA_TO_VDDA) || 
                                                ADC_InputRange_Config2.Equals(ADC_IR_VSSA_TO_VDDA) || 
                                                ADC_InputRange_Config3.Equals(ADC_IR_VSSA_TO_VDDA) || 
                                                ADC_InputRange_Config4.Equals(ADC_IR_VSSA_TO_VDDA));

            bool isVrefforExterna_Ref = (((((VDDA3_LOWERLIMIT / 3) > Vref) || (Vref > (VDDA3_UPPERLIMIT / 3))) && 
                                         ((ADC_Reference.Equals(EXTERNAL_VREF_P03)) || 
                                          (ADC_Reference.Equals(EXTERNAL_VREF_P32)))) ||
                                         ((((VDDA3_LOWERLIMIT / 3) > Vref_Config2) || 
                                            (Vref_Config2 > (VDDA3_UPPERLIMIT / 3))) && 
                                         ((ADC_Reference_Config2.Equals(EXTERNAL_VREF_P03)) || 
                                          (ADC_Reference_Config2.Equals(EXTERNAL_VREF_P32)))) ||
                                         ((((VDDA3_LOWERLIMIT / 3) > Vref_Config3) || 
                                            (Vref_Config3 > (VDDA3_UPPERLIMIT / 3))) && 
                                         ((ADC_Reference_Config3.Equals(EXTERNAL_VREF_P03)) || 
                                          (ADC_Reference_Config3.Equals(EXTERNAL_VREF_P32)))) ||
                                         ((((VDDA3_LOWERLIMIT / 3) > Vref_Config4) || 
                                            (Vref_Config4 > (VDDA3_UPPERLIMIT / 3))) && 
                                         ((ADC_Reference_Config4.Equals(EXTERNAL_VREF_P03)) || 
                                          (ADC_Reference_Config4.Equals(EXTERNAL_VREF_P32)))));
                

            if ((isADCRerence_Vdda3 && ((VDDA3_LOWERLIMIT > vdda) || (vdda > VDDA3_UPPERLIMIT))) || 
                (isADCReference_Vdda4 && ((VDDA4_LOWERLIMIT > vdda) || (vdda > VDDA4_UPPERLIMIT))))
            {
                return new CyCustErr(Resource.ReferenceVrefValueError);
            }
            if ((isADCInputRage_Vssa_to_Vdda && ((VDDA3_LOWERLIMIT > vdda) || (vdda > VDDA4_UPPERLIMIT))))
            {
                return new CyCustErr(Resource.InputRangeVrefValueError);
            }
            if (isVrefforExterna_Ref) 
            {
                return new CyCustErr(Resource.ExtRefVrefValueError);
            }

            return CyCustErr.OK;
        }
        #endregion

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return m_editParamOnDrop;
            }
        }

        bool UseBigEditor
        {
            get { return true; }
        }


        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

      

        #endregion



        #region ICyExprEval_v2 Members

        CyExprEvalFuncEx ICyExprEval_v2.GetFunction(string exprFuncName)
        {
            switch (exprFuncName)
            {
                case "AdcClockFrequency":
                    return new CyExprEvalFuncEx(AdcClockFrequency);

                case "GetVDDA":
                    return new CyExprEvalFuncEx(GetVDDA);

                default:
                    return null;
            }
        }

        /// <summary>
        /// Calculate the ADC clock frequency as a expression evaluator method.
        /// </summary>
        /// <param name="exprFuncName">Name of the function.</param>
        /// <param name="args">arguments to the function</param>
        /// <param name="typeConverter">Converts types to strings</param>
        /// <returns></returns>
        object AdcClockFrequency(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs, 
                                 ICyExprTypeConverter typeConverter)
        {
            if (args.Length != 3) // How many args do you have? 
            {
                // TODO :new CyCustErr("The method "+ exprFuncName + " requires __ paramters");
                return 30720000;
            }
            else
            {
             
                uint resolution = typeConverter.GetAsUInt(args[0]);
                uint sampleRate = typeConverter.GetAsUInt(args[1]);
                uint conversionMode = typeConverter.GetAsUInt(args[2]);

                // Call the actual frequency with the given parameters
                uint theFreq = SetClock(resolution, sampleRate, conversionMode);
                return theFreq;
            }
        }

        object GetVDDA(string exprFuncName, object[] args, ICyExprEvalArgs_v2 custArgs,
                       ICyExprTypeConverter typeConverter)
        {
            double m_systemVdda = 5.0;
            try
            {
                if (custArgs.InstQuery != null)
                {
                    if (custArgs.InstQuery.VoltageQuery != null)
                    {
                        m_systemVdda = custArgs.InstQuery.VoltageQuery.VDDA;
                    }
                }
            }
            catch
            {
                m_systemVdda = 5.0;
            }
            return m_systemVdda;
        }

        #endregion
    }

    public class CyADC_EditingControl : ICyParamEditingControl
    {
        CyADC_DelSigControl ADC_Control;
        ICyInstEdit_v1 m_instEdit;
        List<string> m_tabNames;

        public CyADC_EditingControl(ICyInstEdit_v1 inst, CyADC_DelSigControl userControl, params string[] tabNames)
        {
            m_instEdit = inst;
            m_tabNames = new List<string>(tabNames);
            ADC_Control = userControl;// new CyADC_DelSigControl(inst);
            ADC_Control.Dock = DockStyle.Fill;
            ADC_Control.AutoScroll = true;
        }

        #region ICyParamEditingControl Members

        Control ICyParamEditingControl.DisplayControl
        {
            get
            {
                return ADC_Control;
            }
        }

        System.Collections.Generic.IEnumerable<CyCustErr> ICyParamEditingControl.GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();

            foreach (string paramName in m_instEdit.GetParamNames())
            {
                CyCompDevParam param = m_instEdit.GetCommittedParam(paramName);
                if (m_tabNames.Contains(param.TabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            errs.Add(new CyCustErr(errMsg));
                        }
                    }
                }
            }

            return errs;
        }

        #endregion
    }

}
