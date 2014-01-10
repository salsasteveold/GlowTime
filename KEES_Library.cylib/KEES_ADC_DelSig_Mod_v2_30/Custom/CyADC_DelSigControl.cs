/******************************************************************************
* File Name: CyADC_DelSigControl.cs
* ****************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using KEES_ADC_DelSig_Mod_v2_30;


namespace KEES_ADC_DelSig_Mod_v2_30
{
    public partial class CyADC_DelSigControl : UserControl
    {
        #region Enumerated Type String Names
        const string RANGE_VSSA_TO_VDDA = "Vssa to Vdda";
        const string REF_INTERNAL_REF = "Internal 1.024 Volts"; 
        const string BYPASS_BUFFER = "Bypass Buffer";
        const string BYPASS_BUFFER_ENUM = "Bypass_Buffer";
        const string MESSAGE_RANGE = "Range [ " ;
        const string MESSAGE_RANGE_END = " SPS ]";
        const string ERROR_REF_VOLTAGE = "You can choose either 'Internal 1.024 Volts' or 'Internal Vdda/3' "+
                                         "or 'Internal Vdda/4' or ";
        const string PIN_P32 = "P3.2";
        const string PIN_P03 = "P0.3";
        const string INTERNAL = "Internal";
        const string LABEL_VOLTS_VDD = "Volts (Vdd)";
        const string LABEL_VOLTS = "Volts";
        const string INTERNAL_BYPASSED = "Internal Bypassed";

        #region References to Enum Type String Names
        const string REF_EXTERNAL = "External Vref";
        const string INPUT_DIFFERENTIAL = "Diff" ; //"Differential";
        const string INPUT_SINGLE_TYPE = "Vssa";
        const string INPUT_SINGLE = "Single Ended";
        const string INTERNAL_VDDA_4 = "Internal Vdda/4";
        const string INTERNAL_VDDA_3 = "Internal Vdda/3";
        #endregion

        const int TOTAL_SINGLE_MODES = 4;
        const decimal MAX_VDDA3_VALUE= 3.75m;
        const decimal MAX_VREF_VALUE = 1.3M;
        const decimal MIN_VREF_VALUE = 0.9M;
        const decimal VREF_INT_VALUE = 1.024M;
        
        // These are defined such that these are identical to the enums defined in symbol.
        public enum InputRangeValues
        {
            Vssa_to_Vref, Vssa_to_2Vref, Vssa_to_Vdda, Vssa_to_6Vref, Vneg_Vref_Diff, Vneg_2Vref_Diff, Vneg_6Vref_Diff,
            Vneg_Vref2_Diff, Vneg_Vref4_Diff, Vneg_Vref8_Diff, Vneg_Vref16_Diff, NONE
        }

        private string[] InputRangeFormat = {
            "Vssa to {0}V ( 0.0 to Vref )", 
            "Vssa to {0}V ( 0.0 to 2*Vref )", 
            "Vssa to Vdda", 
            "Vssa to {0}V ( 0.0 to 6*Vref )", 
            "+/-{0}V ( -Input +/- Vref )", 
            "+/-{0}V ( -Input +/- 2*Vref )", 
            "+/-{0}V ( -Input +/- 6*Vref )", 
            "+/-{0}V ( -Input +/- Vref/2 )", 
            "+/-{0}V ( -Input +/- Vref/4 )", 
            "+/-{0}V ( -Input +/- Vref/8 )", 
            "+/-{0}V ( -Input +/- Vref/16 )", 
            "NONE",
        };

        private bool m_sRateErr1 = false;
        private bool m_sRateErr2 = false;
        private bool m_sRateErr3 = false;
        private bool m_sRateErr4 = false;
       
        private float[] adcGain = {1, 2, 3, 6, 1, 2, 6, 1/2f, 1/4f, 1/8f, 1/16f };
        #endregion

        public ICyInstEdit_v1 m_Component = null;

        public CyADC_DelSigControl(ICyInstEdit_v1 inst)
        {
            m_Component = inst;
            InitializeComponent();

            // ADC Resolution
            IEnumerable<string> ResolutionEnums = inst.GetPossibleEnumValues(CyADC_DelSigParameters.RESOLUTION);
            foreach (string str in ResolutionEnums)
            {
                m_cbResolution.Items.Add(str);
                m_cbResolutionConfig2.Items.Add(str);
                m_cbResolutionConfig3.Items.Add(str);
                m_cbResolutionConfig4.Items.Add(str);
            }
            // Input Buffer Gain
            IEnumerable<string> InputBufferGainEnums = inst.GetPossibleEnumValues
                                                       (CyADC_DelSigParameters.INPUT_BUFFER_GAIN);
            foreach (string str in InputBufferGainEnums)
            {
                m_cbInputBufferGain.Items.Add(str);
                m_cbInputBufferGain2.Items.Add(str);
                m_cbInputBufferGain3.Items.Add(str);
                m_cbInputBufferGain4.Items.Add(str);
            }

            // Conversion Mode
            IEnumerable<string> ConversionModeEnums = inst.GetPossibleEnumValues
                                                      (CyADC_DelSigParameters.CONVERSION_MODE);
            foreach (string str in ConversionModeEnums)
            {
                m_cbConvMode.Items.Add(str);
                m_cbConvMode2.Items.Add(str);
                m_cbConvMode3.Items.Add(str);
                m_cbConvMode4.Items.Add(str);
            }

            // Reference Mode
            IEnumerable<string> ReferenceEnums = inst.GetPossibleEnumValues(CyADC_DelSigParameters.ADC_REFERENCE);
            foreach (string str in ReferenceEnums)
            {
                m_cbReference.Items.Add(str);
                m_cbReference2.Items.Add(str);
                m_cbReference3.Items.Add(str);
                m_cbReference4.Items.Add(str);
            }

            //Buffer Mode
            IEnumerable<string> BufferModeEnums = inst.GetPossibleEnumValues(CyADC_DelSigParameters.INPUT_BUFFER_MODE);
            foreach (string str in BufferModeEnums)
            {
                m_cbInputBufferMode.Items.Add(str);
                m_cbInputBufferMode2.Items.Add(str);
                m_cbInputBufferMode3.Items.Add(str);
                m_cbInputBufferMode4.Items.Add(str);
            }

            HookAllEvents();
            if (m_Component != null)
            {
                UpdateFormFromParams(inst);
                UpdateADCMode();
                UpdateAllInputRangeList();
            }

        }

        /// <summary>
        /// Hook the events triggered by the controls.
        /// </summary>
        private void HookAllEvents()
        {
            this.m_cbConvMode2.SelectedIndexChanged += new System.EventHandler(this.m_cbConvMode2_SelectedIndexChanged);
            this.m_cbInputBufferMode.SelectedIndexChanged += new System.EventHandler
                                                            (this.m_cbInputBufferMode_SelectedIndexChanged);
            this.m_cbInputBufferGain.SelectedIndexChanged += new System.EventHandler
                                                            (this.m_cbInputBufferGain_SelectedIndexChanged);
            this.m_nudConfig.ValueChanged += new System.EventHandler(this.m_nudConfig_ValueChanged);
            this.m_cbConvMode.SelectedIndexChanged += new System.EventHandler
                                                      (this.m_cbConvMode_SelectedIndexChanged);
            this.m_cbInputBufferMode2.SelectedIndexChanged += new System.EventHandler
                                                      (this.m_cbInputBufferMode2_SelectedIndexChanged);
            this.m_cbReference.SelectedIndexChanged += new System.EventHandler(this.m_cbReference_SelectedIndexChanged);

            this.m_nudRefVoltage.ValueChanged += new System.EventHandler(this.m_nudRefVoltage_ValueChanged);

            this.m_rbModeDifferential.CheckedChanged += new System.EventHandler
                                                        (this.m_rbModeDifferential_CheckedChanged);
            this.m_cbInputRange.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbInputRange_SelectedIndexChanged);
            this.m_cbInputRange2.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbInputRange2_SelectedIndexChanged);
            this.m_cbInputRange3.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbInputRange3_SelectedIndexChanged);
            this.m_cbInputRange4.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbInputRange4_SelectedIndexChanged);

            this.m_nudConvRate.ValueChanged += new EventHandler(m_nudConvRate_ValueChanged);
            this.m_nudConvRate2.ValueChanged += new EventHandler(m_nudConvRate2_ValueChanged);
            this.m_nudConvRate3.ValueChanged += new EventHandler(m_nudConvRate3_ValueChanged);
            this.m_nudConvRate4.ValueChanged += new EventHandler(m_nudConvRate4_ValueChanged);

            this.m_nudRefVoltage2.ValueChanged += new System.EventHandler(this.m_nudRefVoltage2_ValueChanged);
            this.m_cbReference2.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbReference2_SelectedIndexChanged);
            this.m_cbInputBufferGain2.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbInputBufferGain2_SelectedIndexChanged);
            this.m_nudRefVoltage3.ValueChanged += new System.EventHandler(this.m_nudRefVoltage3_ValueChanged);
            this.m_cbReference3.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbReference3_SelectedIndexChanged);
            this.m_cbInputBufferMode3.SelectedIndexChanged += new System.EventHandler
                                                              (this.m_cbInputBufferMode3_SelectedIndexChanged);
            this.m_cbInputBufferGain3.SelectedIndexChanged += new System.EventHandler
                                                              (this.m_cbInputBufferGain3_SelectedIndexChanged);
            this.m_cbConvMode3.SelectedIndexChanged += new System.EventHandler
                                                       (this.m_cbConvMode3_SelectedIndexChanged);
            this.m_nudRefVoltage4.ValueChanged += new System.EventHandler(this.m_nudRefVoltage4_ValueChanged);
            this.m_cbReference4.SelectedIndexChanged += new System.EventHandler
                                                        (this.m_cbReference4_SelectedIndexChanged);
            this.m_cbInputBufferMode4.SelectedIndexChanged += new System.EventHandler
                                                              (this.m_cbInputBufferMode4_SelectedIndexChanged);
            this.m_cbInputBufferGain4.SelectedIndexChanged += new System.EventHandler
                                                              (this.m_cbInputBufferGain4_SelectedIndexChanged);
            this.m_cbConvMode4.SelectedIndexChanged += new System.EventHandler
                                                      (this.m_cbConvMode4_SelectedIndexChanged);
            this.m_cbResolution.SelectedIndexChanged += new EventHandler(m_cbResolution_SelectedIndexChanged);
            this.m_cbResolutionConfig2.SelectedIndexChanged += new System.EventHandler
                                                               (this.m_cbResolutionConfig2_SelectedIndexChanged);
            this.m_cbResolutionConfig3.SelectedIndexChanged += new System.EventHandler
                                                               (this.m_cbResolutionConfig3_SelectedIndexChanged);
            this.m_cbResolutionConfig4.SelectedIndexChanged += new System.EventHandler
                                                               (this.m_cbResolutionConfig4_SelectedIndexChanged);
            
            this.m_cbReference.Validating += new CancelEventHandler(m_cbReference_Validating);
            this.m_cbReference2.Validating += new CancelEventHandler(m_cbReference2_Validating);
            this.m_cbReference3.Validating += new CancelEventHandler(m_cbReference3_Validating);
            this.m_cbReference4.Validating += new CancelEventHandler(m_cbReference4_Validating);

            this.m_rbClockInternal.CheckedChanged += new System.EventHandler(this.m_rbClockInternal_CheckedChanged);
            this.m_rbClockExternal.CheckedChanged += new System.EventHandler(this.m_rbClockExternal_CheckedChanged);
            this.m_cbSocHardware.CheckedChanged += new System.EventHandler(this.m_cbSocHardware_CheckedChanged);
            this.m_cbEnable_Vref_Vss.CheckedChanged += new System.EventHandler
                                                       (this.m_cbEnable_Vref_Vss_CheckedChanged);
        }


        /// <summary>
        /// Unhook the events triggered by the controls.
        /// </summary>
        private void UnhookAllEvents()
        {
            this.m_cbConvMode2.SelectedIndexChanged -= new System.EventHandler
                                                       (this.m_cbConvMode2_SelectedIndexChanged);
            this.m_cbInputBufferMode.SelectedIndexChanged -= new System.EventHandler
                                                             (this.m_cbInputBufferMode_SelectedIndexChanged);
            this.m_cbInputBufferGain.SelectedIndexChanged -= new System.EventHandler
                                                             (this.m_cbInputBufferGain_SelectedIndexChanged);
            this.m_cbInputRange.SelectedIndexChanged -= new System.EventHandler
                                                             (this.m_cbInputRange_SelectedIndexChanged);
            this.m_nudConfig.ValueChanged -= new System.EventHandler(this.m_nudConfig_ValueChanged);
            this.m_cbConvMode.SelectedIndexChanged -= new System.EventHandler(this.m_cbConvMode_SelectedIndexChanged);
            this.m_cbInputBufferMode2.SelectedIndexChanged -= new System.EventHandler 
                                                              (this.m_cbInputBufferMode2_SelectedIndexChanged);
            this.m_cbReference.SelectedIndexChanged -= new System.EventHandler
                                                        (this.m_cbReference_SelectedIndexChanged);

            this.m_nudRefVoltage.ValueChanged -= new System.EventHandler(this.m_nudRefVoltage_ValueChanged);
            this.m_rbModeDifferential.CheckedChanged -= new System.EventHandler
                                                        (this.m_rbModeDifferential_CheckedChanged);

            this.m_nudConvRate.ValueChanged -= new EventHandler(m_nudConvRate_ValueChanged);
            this.m_nudConvRate2.ValueChanged -= new EventHandler(m_nudConvRate2_ValueChanged);
            this.m_nudConvRate3.ValueChanged -= new EventHandler(m_nudConvRate3_ValueChanged);
            this.m_nudConvRate4.ValueChanged -= new EventHandler(m_nudConvRate4_ValueChanged);

            this.m_cbReference.Validating -= new CancelEventHandler(m_cbReference_Validating);
            this.m_cbReference2.Validating -= new CancelEventHandler(m_cbReference2_Validating);
            this.m_cbReference3.Validating -= new CancelEventHandler(m_cbReference3_Validating);
            this.m_cbReference4.Validating -= new CancelEventHandler(m_cbReference4_Validating);

            this.m_cbResolution.SelectedIndexChanged -= new EventHandler(m_cbResolution_SelectedIndexChanged);

            this.m_nudRefVoltage2.ValueChanged -= new System.EventHandler(this.m_nudRefVoltage2_ValueChanged);
            this.m_cbReference2.SelectedIndexChanged -= new System.EventHandler
                                                        (this.m_cbReference2_SelectedIndexChanged);
            this.m_cbInputBufferGain2.SelectedIndexChanged -= new System.EventHandler
                                                             (this.m_cbInputBufferGain2_SelectedIndexChanged);
            this.m_cbInputRange2.SelectedIndexChanged -= new System.EventHandler
                                                         (this.m_cbInputRange2_SelectedIndexChanged);
            this.m_cbResolutionConfig2.SelectedIndexChanged -= new System.EventHandler
                                                               (this.m_cbResolutionConfig2_SelectedIndexChanged);
            this.m_nudRefVoltage3.ValueChanged -= new System.EventHandler(this.m_nudRefVoltage3_ValueChanged);
            this.m_cbReference3.SelectedIndexChanged -= new System.EventHandler
                                                         (this.m_cbReference3_SelectedIndexChanged);
            this.m_cbInputBufferMode3.SelectedIndexChanged -= new System.EventHandler
                                                              (this.m_cbInputBufferMode3_SelectedIndexChanged);
            this.m_cbInputBufferGain3.SelectedIndexChanged -= new System.EventHandler
                                                              (this.m_cbInputBufferGain3_SelectedIndexChanged);
            this.m_cbInputRange3.SelectedIndexChanged -= new System.EventHandler
                                                         (this.m_cbInputRange3_SelectedIndexChanged);
            this.m_cbResolutionConfig3.SelectedIndexChanged -= new System.EventHandler
                                                               (this.m_cbResolutionConfig3_SelectedIndexChanged);
            this.m_cbConvMode3.SelectedIndexChanged -= new System.EventHandler
                                                       (this.m_cbConvMode3_SelectedIndexChanged);
            this.m_nudRefVoltage4.ValueChanged -= new System.EventHandler(this.m_nudRefVoltage4_ValueChanged);
            this.m_cbReference4.SelectedIndexChanged -= new System.EventHandler
                                                        (this.m_cbReference4_SelectedIndexChanged);
            this.m_cbInputBufferMode4.SelectedIndexChanged -= new System.EventHandler
                                                              (this.m_cbInputBufferMode4_SelectedIndexChanged);
            this.m_cbInputBufferGain4.SelectedIndexChanged -= new System.EventHandler
                                                              (this.m_cbInputBufferGain4_SelectedIndexChanged);
            this.m_cbInputRange4.SelectedIndexChanged -= new System.EventHandler
                                                         (this.m_cbInputRange4_SelectedIndexChanged);
            this.m_cbResolutionConfig4.SelectedIndexChanged -= new System.EventHandler
                                                               (this.m_cbResolutionConfig4_SelectedIndexChanged);
            this.m_cbConvMode4.SelectedIndexChanged -= new System.EventHandler
                                                       (this.m_cbConvMode4_SelectedIndexChanged);

            
            this.m_rbClockInternal.CheckedChanged -= new System.EventHandler(this.m_rbClockInternal_CheckedChanged);
            this.m_rbClockExternal.CheckedChanged -= new System.EventHandler(this.m_rbClockExternal_CheckedChanged);
            this.m_cbSocHardware.CheckedChanged -= new System.EventHandler(this.m_cbSocHardware_CheckedChanged);
            this.m_cbEnable_Vref_Vss.CheckedChanged -= new System.EventHandler
                                                       (this.m_cbEnable_Vref_Vss_CheckedChanged);

        }

        void m_cbReference4_Validating(object sender, CancelEventArgs e)
        {
            CheckOtherRefVotageConfig(m_cbReference4);
        }

        void m_cbReference3_Validating(object sender, CancelEventArgs e)
        {
            CheckOtherRefVotageConfig(m_cbReference3);
            CheckOtherRefVotageConfig(m_cbReference4);
        }

        void m_cbReference2_Validating(object sender, CancelEventArgs e)
        {
            CheckOtherRefVotageConfig(m_cbReference2);
            CheckOtherRefVotageConfig(m_cbReference3);
            CheckOtherRefVotageConfig(m_cbReference4);
        }

        void m_cbReference_Validating(object sender, CancelEventArgs e)
        {
            CheckOtherRefVotageConfig(m_cbReference2);
            CheckOtherRefVotageConfig(m_cbReference3);
            CheckOtherRefVotageConfig(m_cbReference4);            
        }


        void m_cbResolutionConfig4_Validating(object sender, CancelEventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                            m_cbResolutionConfig4.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION_CONFIG4, prm, true);
            CheckFreqConfig4(true);
        }

        void m_cbResolutionConfig3_Validating(object sender, CancelEventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                            m_cbResolutionConfig3.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION_CONFIG3, prm, true);
            CheckFreqConfig3(true);
        }

        void m_cbResolutionConfig2_Validating(object sender, CancelEventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                            m_cbResolutionConfig2.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION_CONFIG2, prm, true);
            CheckFreqConfig2(true);
        }

        //Resolution
        void m_cbResolution_Validating(object sender, CancelEventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                            m_cbResolution.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION, prm, true);
            CheckFreqConfig1(true);
        }

        private void m_cbResolutionConfig2_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Update the labels.
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                            m_cbResolutionConfig2.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION_CONFIG2, prm, true);
            CheckFreqConfig2(true);
            DisplayInterruptMessage();
        }

        private void m_cbResolutionConfig3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                            m_cbResolutionConfig3.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION_CONFIG3, prm, true);
            CheckFreqConfig3(true);
            DisplayInterruptMessage();
        }

        void m_cbResolution_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, m_cbResolution.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION, prm, true);
            CheckFreqConfig1(true);
            DisplayInterruptMessage();
        }
        
        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            UnhookAllEvents();
            CyADC_DelSigParameters prms = new CyADC_DelSigParameters(inst);

            #region Config1
            //Set the ADC resolution
            string paramResolution = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.RESOLUTION, 
                prms.m_ADC_Resolution.Expr);
            if (m_cbResolution.Items.Contains(paramResolution))
            {
                m_cbResolution.SelectedItem = paramResolution;
                m_cbResolution.Text = prms.m_ADC_Resolution.Expr;
            }

            // set the ADC mode
            string paramAdcMode = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_INPUT_MODE, 
                prms.m_ADC_Input_Mode.Expr);
            if (!paramAdcMode.Contains(INPUT_DIFFERENTIAL))
            {
                m_rbModeSingle.Checked = true;
            }

            //Set the ADC Input Range
            string paramInputRange = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_RANGE, 
                prms.m_ADC_Input_Range.Expr);
            if (m_cbInputRange.Items.Contains(paramInputRange))
            {
                m_cbInputRange.SelectedItem = paramInputRange;
                m_cbInputRange.Text = prms.m_ADC_Input_Range.Expr;
            }

            //Set the Input Buffer Gain
            string paramInputBufferGain = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_GAIN, 
                prms.m_Input_Buffer_Gain.Expr);
            if (m_cbInputBufferGain.Items.Contains(paramInputBufferGain))
            {
                m_cbInputBufferGain.SelectedItem = paramInputBufferGain;
                m_cbInputBufferGain.Text = prms.m_Input_Buffer_Gain.Expr;
            }

            //Set the Conversion Mode
            string paramConvMode = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.CONVERSION_MODE, 
                prms.m_Conversion_Mode.Expr);
            if (m_cbConvMode.Items.Contains(paramConvMode))
            {
                m_cbConvMode.SelectedItem = paramConvMode;
                m_cbConvMode.Text = prms.m_Conversion_Mode.Expr;
            }

            //Set ADC Reference
            string paramReference = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_REFERENCE, 
                prms.m_ADC_Reference.Expr);
            if (m_cbReference.Items.Contains(paramReference))
            {
                m_cbReference.SelectedItem = paramReference;
                m_cbReference.Text = prms.m_ADC_Reference.Expr;
            }

            //Set ADC Input Buffer Mode
            string paramBufferMode = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_MODE, 
                prms.m_Input_Buffer_Mode.Expr);
            if (m_cbInputBufferMode.Items.Contains(paramBufferMode))
            {
                m_cbInputBufferMode.SelectedItem = paramBufferMode;
                m_cbInputBufferMode.Text = prms.m_Input_Buffer_Mode.Expr;
            }

            //Reference voltage.
            float tempFloat;
            float.TryParse(prms.m_Ref_Voltage.Value, out tempFloat);
            m_nudRefVoltage.Value = (decimal)tempFloat;

            // Conversion/Sample Rate
            int tempSampleRate;
            int.TryParse(prms.m_Sample_Rate.Value, out tempSampleRate);
            m_nudConvRate.Value = (decimal)tempSampleRate;

            // Comment text box
            commentTextBox1.Text = prms.m_Comment_Config1.Value;

            // Config Name text box
            configNameTextBox1.Text = prms.m_Config1_Name.Value;
            nameLabel1.Text = inst.InstanceName + "_" + prms.m_Config1_Name.Value;

            #endregion

            #region Config2
            //Set the ADC resolution
            string paramResolution2 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.RESOLUTION_CONFIG2, 
                prms.m_ADC_Resolution_Config2.Expr);
            if (m_cbResolutionConfig2.Items.Contains(paramResolution2))
            {
                m_cbResolutionConfig2.SelectedItem = paramResolution2;
                m_cbResolutionConfig2.Text = prms.m_ADC_Resolution_Config2.Expr;
            }

            //Set the ADC Input Range
            string paramInputRange2 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_RANGE_CONFIG2, 
                prms.m_ADC_Input_Range_Config2.Expr);
            if (m_cbInputRange2.Items.Contains(paramInputRange2))
            {
                m_cbInputRange2.SelectedItem = paramInputRange2;
                m_cbInputRange2.Text = prms.m_ADC_Input_Range_Config2.Expr;
            }

            //Set the Input Buffer Gain
            string paramInputBufferGain2 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_GAIN, 
                prms.m_Input_Buffer_Gain_Config2.Expr);
            if (m_cbInputBufferGain2.Items.Contains(paramInputBufferGain2))
            {
                m_cbInputBufferGain2.SelectedItem = paramInputBufferGain2;
                m_cbInputBufferGain2.Text = prms.m_Input_Buffer_Gain_Config2.Expr;
            }

            //Set the Conversion Mode
            string paramConvMode2 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.CONVERSION_MODE, 
                prms.m_Conversion_Mode_Config2.Expr);
            if (m_cbConvMode2.Items.Contains(paramConvMode2))
            {
                m_cbConvMode2.SelectedItem = paramConvMode2;
                m_cbConvMode2.Text = prms.m_Conversion_Mode_Config2.Expr;
            }

            //Set ADC Reference
            string paramReference2 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_REFERENCE, 
                prms.m_ADC_Reference_Config2.Expr);
            if (m_cbReference2.Items.Contains(paramReference2))
            {
                m_cbReference2.SelectedItem = paramReference2;
                m_cbReference2.Text = prms.m_ADC_Reference_Config2.Expr;
            }

            //Set ADC Input Buffer Mode
            string paramBufferMode2 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_MODE,
                prms.m_Input_Buffer_Mode_Config2.Expr);
            if (m_cbInputBufferMode2.Items.Contains(paramBufferMode2))
            {
                m_cbInputBufferMode2.SelectedItem = paramBufferMode2;
                m_cbInputBufferMode2.Text = prms.m_Input_Buffer_Mode_Config2.Expr;
            }

            //Reference voltage.
            float.TryParse(prms.m_Ref_Voltage_Config2.Value, out tempFloat);
            m_nudRefVoltage2.Value = (decimal)tempFloat;

            // Conversion/Sample Rate
            int.TryParse(prms.m_Sample_Rate_Config2.Value, out tempSampleRate);
            m_nudConvRate2.Value = (decimal)tempSampleRate;

            // Comment text box
            commentTextBox2.Text = prms.m_Comment_Config2.Value;

            // Config Name text box
            configNameTextBox2.Text = prms.m_Config2_Name.Value;
            nameLabel2.Text = inst.InstanceName + "_" + prms.m_Config2_Name.Value;

            #endregion

            #region Config3
            //Set the ADC resolution
            string paramResolution3 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.RESOLUTION_CONFIG3,
                prms.m_ADC_Resolution_Config3.Expr);
            if (m_cbResolutionConfig3.Items.Contains(paramResolution3))
            {
                m_cbResolutionConfig3.SelectedItem = paramResolution3;
                m_cbResolutionConfig3.Text = prms.m_ADC_Resolution_Config3.Expr;
            }

            //Set the ADC Input Range
            string paramInputRange3 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_RANGE_CONFIG3,
                prms.m_ADC_Input_Range_Config3.Expr);
            if (m_cbInputRange3.Items.Contains(paramInputRange3))
            {
                m_cbInputRange3.SelectedItem = paramInputRange3;
                m_cbInputRange3.Text = prms.m_ADC_Input_Range_Config3.Expr;
            }

            //Set the Input Buffer Gain
            string paramInputBufferGain3 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_GAIN,
                prms.m_Input_Buffer_Gain_Config3.Expr);
            if (m_cbInputBufferGain3.Items.Contains(paramInputBufferGain3))
            {
                m_cbInputBufferGain3.SelectedItem = paramInputBufferGain3;
                m_cbInputBufferGain3.Text = prms.m_Input_Buffer_Gain_Config3.Expr;
            }

            //Set the Conversion Mode
            string paramConvMode3 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.CONVERSION_MODE,
                prms.m_Conversion_Mode_Config3.Expr);
            if (m_cbConvMode3.Items.Contains(paramConvMode3))
            {
                m_cbConvMode3.SelectedItem = paramConvMode3;
                m_cbConvMode3.Text = prms.m_Conversion_Mode_Config3.Expr;
            }

            //Set ADC Reference
            string paramReference3 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_REFERENCE,
                prms.m_ADC_Reference_Config3.Expr);
            if (m_cbReference3.Items.Contains(paramReference3))
            {
                m_cbReference3.SelectedItem = paramReference3;
                m_cbReference3.Text = prms.m_ADC_Reference_Config3.Expr;
            }

            //Set ADC Input Buffer Mode
            string paramBufferMode3 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_MODE,
                prms.m_Input_Buffer_Mode_Config3.Expr);
            if (m_cbInputBufferMode3.Items.Contains(paramBufferMode3))
            {
                m_cbInputBufferMode3.SelectedItem = paramBufferMode3;
                m_cbInputBufferMode3.Text = prms.m_Input_Buffer_Mode_Config3.Expr;
            }

            //Reference voltage.
            float.TryParse(prms.m_Ref_Voltage_Config3.Value, out tempFloat);
            m_nudRefVoltage3.Value = (decimal)tempFloat;

            // Conversion/Sample Rate
            int.TryParse(prms.m_Sample_Rate_Config3.Value, out tempSampleRate);
            m_nudConvRate3.Value = (decimal)tempSampleRate;

            // Comment text box
            commentTextBox3.Text = prms.m_Comment_Config3.Value;

            // Config Name text box
            configNameTextBox3.Text = prms.m_Config3_Name.Value;
            nameLabel3.Text = inst.InstanceName + "_" + prms.m_Config3_Name.Value;

            #endregion

            #region Config4
            //Set the ADC resolution
            string paramResolution4 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.RESOLUTION_CONFIG4,
                prms.m_ADC_Resolution_Config4.Expr);
            if (m_cbResolutionConfig4.Items.Contains(paramResolution4))
            {
                m_cbResolutionConfig4.SelectedItem = paramResolution4;
                m_cbResolutionConfig4.Text = prms.m_ADC_Resolution_Config4.Expr;
            }

            //Set the ADC Input Range
            string paramInputRange4 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_RANGE_CONFIG4,
                prms.m_ADC_Input_Range_Config4.Expr);
            if (m_cbInputRange4.Items.Contains(paramInputRange4))
            {
                m_cbInputRange4.SelectedItem = paramInputRange4;
                m_cbInputRange4.Text = prms.m_ADC_Input_Range_Config4.Expr;
            }

            //Set the Input Buffer Gain
            string paramInputBufferGain4 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_GAIN,
                prms.m_Input_Buffer_Gain_Config4.Expr);
            if (m_cbInputBufferGain4.Items.Contains(paramInputBufferGain4))
            {
                m_cbInputBufferGain4.SelectedItem = paramInputBufferGain4;
                m_cbInputBufferGain4.Text = prms.m_Input_Buffer_Gain_Config4.Expr;
            }

            //Set the Conversion Mode
            string paramConvMode4 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.CONVERSION_MODE,
                prms.m_Conversion_Mode_Config4.Expr);
            if (m_cbConvMode4.Items.Contains(paramConvMode4))
            {
                m_cbConvMode4.SelectedItem = paramConvMode4;
                m_cbConvMode4.Text = prms.m_Conversion_Mode_Config4.Expr;
            }

            //Set ADC Reference
            string paramReference4 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_REFERENCE,
                prms.m_ADC_Reference_Config4.Expr);
            if (m_cbReference4.Items.Contains(paramReference4))
            {
                m_cbReference4.SelectedItem = paramReference4;
                m_cbReference4.Text = prms.m_ADC_Reference_Config4.Expr;
            }

            //Set ADC Input Buffer Mode
            string paramBufferMode4 = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_MODE,
                prms.m_Input_Buffer_Mode_Config4.Expr);
            if (m_cbInputBufferMode4.Items.Contains(paramBufferMode4))
            {
                m_cbInputBufferMode4.SelectedItem = paramBufferMode4;
                m_cbInputBufferMode4.Text = prms.m_Input_Buffer_Mode_Config4.Expr;
            }
            //Reference voltage.
            float.TryParse(prms.m_Ref_Voltage_Config4.Value, out tempFloat);
            m_nudRefVoltage4.Value = (decimal)tempFloat;

            // Conversion/Sample Rate
            int.TryParse(prms.m_Sample_Rate_Config4.Value, out tempSampleRate);
            m_nudConvRate4.Value = (decimal)tempSampleRate;

            // Comment text box
            commentTextBox4.Text = prms.m_Comment_Config4.Value;

            // Config Name text box
            configNameTextBox4.Text = prms.m_Config4_Name.Value;
            nameLabel4.Text = inst.InstanceName + "_" + prms.m_Config4_Name.Value;

            #endregion

            #region Common configuration
            // Clock Source check box
            if (m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_CLOCK, prms.m_ADC_Clock.Expr) == 
                CyADC_DelSigParameters.S_INTERNAL)
            {
                m_rbClockInternal.Checked = true;
                m_rbClockExternal.Checked = false;
            }
            else
            {
                m_rbClockInternal.Checked = false;
                m_rbClockExternal.Checked = true;
            }

            // Start of Conversion check box
            if (m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.START_OF_CONVERSION,
                prms.m_Start_of_Conversion.Expr) == CyADC_DelSigParameters.S_SOFTWARE)
            {
                m_cbSocHardware.Checked = false;
            }
            else
            {
                m_cbSocHardware.Checked = true;
            }

            // Configs
            int temp;
            int.TryParse(prms.m_Configs.Value, out temp);
            m_nudConfig.Value = (decimal)temp;
            UpdateConfigTabs(temp);

            // Enable Vref Vss
            m_cbEnable_Vref_Vss.Checked = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.ADC_nVref,
                prms.m_Enable_Vref_Vss.Expr).Equals(Boolean.TrueString);
            #endregion

            UpdateAllBufferGain();
            CheckAllFreq(false);
            //UpdateRefVoltagesEnable();
            m_cbReference_Validating(this, new CancelEventArgs());
            DisplayInterruptMessage();
            UpdateRefVoltagesEnable();
            UpdateAllInputRangeList();
            HookAllEvents();
            CheckRefVoltage(m_nudRefVoltage, m_cbReference);
            CheckRefVoltage(m_nudRefVoltage2, m_cbReference2);
            CheckRefVoltage(m_nudRefVoltage3, m_cbReference3);
            CheckRefVoltage(m_nudRefVoltage4, m_cbReference4);
        }

        private void UpdateRefVoltagesEnable()
        {
            if (m_cbInputRange.Text == RANGE_VSSA_TO_VDDA)   
            {
                m_cbReference.Enabled = false;
            }
            else
            {
                m_cbReference.Enabled = true;
            }
            if (m_cbInputRange2.Text == RANGE_VSSA_TO_VDDA)
            {
                m_cbReference2.Enabled = false;
            }
            else
            {
                m_cbReference2.Enabled = true;
            }
            if (m_cbInputRange3.Text == RANGE_VSSA_TO_VDDA)
            {
                m_cbReference3.Enabled = false;
            }
            else
            {
                m_cbReference3.Enabled = true;
            }
            if (m_cbInputRange4.Text == RANGE_VSSA_TO_VDDA)
            {
                m_cbReference4.Enabled = false;
            }
            else
            {
                m_cbReference4.Enabled = true;
            }
        }

        private void UpdateConfigTabs(int numberOfTabs)
        {
            // There will be one extra tab for common settings.
            if (numberOfTabs > m_tabConfig.Controls.Count - 1)
            {
                // Remove the common tab and add it later to keep the order
                m_tabConfig.Controls.Remove(m_tabPage5);
                switch (numberOfTabs)
                {
                    case 2:
                        m_tabConfig.Controls.Add(m_tabPage2);
                        break;
                    case 3:
                        m_tabConfig.Controls.Add(m_tabPage3);
                        break;
                    case 4:
                        m_tabConfig.Controls.Add(m_tabPage4);
                        break;
                }
                m_tabConfig.Controls.Add(m_tabPage5);
            }
            else if (numberOfTabs != CyADC_DelSigParameters.MAX_CONFIGS)
            {
                // Remove the tabs 
                if (numberOfTabs <= 3)
                {
                    m_tabConfig.Controls.Remove(m_tabPage4);
                }
                if (numberOfTabs <= 2)
                {
                    m_tabConfig.Controls.Remove(m_tabPage3);
                }
                if (numberOfTabs == 1)
                {
                    m_tabConfig.Controls.Remove(m_tabPage2);
                }
            }            
        }


        void m_nudConvRate4_ValueChanged(object sender, EventArgs e)
        {
            // Check ADC clock frequency range.
            SetAParameter(CyADC_DelSigParameters.SAMPLE_RATE_CONFIG4, m_nudConvRate4.Value.ToString(), false);
            CheckFreqConfig4(true);
        }

        void m_nudConvRate3_ValueChanged(object sender, EventArgs e)
        {
            // Check ADC clock frequency range.
            SetAParameter(CyADC_DelSigParameters.SAMPLE_RATE_CONFIG3, m_nudConvRate3.Value.ToString(), false);
            CheckFreqConfig3(true);
        }

        void m_nudConvRate2_ValueChanged(object sender, EventArgs e)
        {
            // Check ADC clock frequency range.
            SetAParameter(CyADC_DelSigParameters.SAMPLE_RATE_CONFIG2, m_nudConvRate2.Value.ToString(), false);
            CheckFreqConfig2(true);
        }

        void m_nudConvRate_ValueChanged(object sender, EventArgs e)
        {
            // Check ADC clock frequency range.
            SetAParameter(CyADC_DelSigParameters.SAMPLE_RATE, m_nudConvRate.Value.ToString(), false);
            CheckFreqConfig1(true);
        }

        // ADC Input Range
        private void m_cbInputRange_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_RANGE, m_cbInputRange.Text);
            decimal vdda = GetVDDAValue();

            // If "Vssa to Vdda (Single Ended)" is selected then choose refernce to be "Internal Ref"
            if (m_cbInputRange.Text.Equals(RANGE_VSSA_TO_VDDA))
            {
                UnhookAllEvents();
                UnhookAllEvents();

                if (vdda < MAX_VDDA3_VALUE)
                {
                    m_cbReference.SelectedItem = INTERNAL_VDDA_3;
                }
                else
                {
                    m_cbReference.SelectedItem = INTERNAL_VDDA_4;
                }
                HookAllEvents();
                m_cbReference.Enabled = false; 
                prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE, m_cbReference.Text);
                SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE, prm, true);
            }
            else
            {
                m_cbReference.Enabled = true;
            }

            prm = ResolveInputEnumDisplayToId(m_cbInputRange);
            SetAParameter(CyADC_DelSigParameters.INPUT_RANGE, prm, true);
            CheckFreqConfig1(true);

            UpdateRefVoltageEnable(1, m_cbReference, m_cbInputRange, Volts_label, m_nudRefVoltage);
            CheckRefVoltage(m_nudRefVoltage, m_cbReference);
            UnhookAllEvents();
            UpdateInputRangeList(1);
            HookAllEvents();
            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE, m_nudRefVoltage.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE, prm, true);
        }

        // Input Buffer Gain
        private void m_cbInputBufferGain_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_GAIN, 
                                                             m_cbInputBufferGain.Text);
              SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_GAIN, prm, true);
              CheckFreqConfig1(true);
        }

        // Conversion Mode
        private void m_cbConvMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.CONVERSION_MODE, m_cbConvMode.Text);
            SetAParameter(CyADC_DelSigParameters.CONVERSION_MODE, prm, true);
            CheckFreqConfig1(true);
            DisplayInterruptMessage();
        }

        private void DisplayInterruptMessage()
        {
            label_Warning.Visible = false;
            if ((m_cbConvMode.SelectedIndex == 0 && m_cbResolution.SelectedIndex > 8 && m_nudConfig.Value >= 1) 
                || (m_cbConvMode2.SelectedIndex == 0 && m_cbResolutionConfig2.SelectedIndex > 8 && 
                    m_nudConfig.Value >= 2) 
                || (m_cbConvMode3.SelectedIndex == 0 && m_cbResolutionConfig3.SelectedIndex > 8 && 
                    m_nudConfig.Value >= 3)
                || (m_cbConvMode4.SelectedIndex == 0 && m_cbResolutionConfig4.SelectedIndex > 8 && 
                    m_nudConfig.Value == 4))
            {
                label_Warning.Visible = true;
            }
        }
        
        // ADC Reference
        private void m_cbReference_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE, m_cbReference.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE, prm, true);

            CheckOtherRefVotageConfig(m_cbReference2);
            UpdateRefVoltageEnable(1, m_cbReference, m_cbInputRange, Volts_label, m_nudRefVoltage);
            
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage, m_cbReference);
            UpdateInputRangeList(1);
            HookAllEvents();
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE, m_nudRefVoltage.Value.ToString(), false);
        }

        private bool CheckOtherRefVotageConfig(ComboBox parent)
        {
            bool retVal = false;

            // Config1 will be the master tab, if it has set to other than 'Internal Vref' 
            // then it would be taken as the 'only' allowed wiring.
            string masterConfig = REF_INTERNAL_REF;
            if (m_cbReference.Text.Contains(PIN_P03) || m_cbReference.Text.Contains(PIN_P32))
            {
                masterConfig = m_cbReference.Text;
            }
            else if (m_cbReference2.Text.Contains(PIN_P03) || m_cbReference2.Text.Contains(PIN_P32))
            {
                masterConfig = m_cbReference2.Text;
            }
            else if (m_cbReference3.Text.Contains(PIN_P03) || m_cbReference3.Text.Contains(PIN_P32))
            {
                masterConfig = m_cbReference3.Text;
            }
            else if (m_cbReference4.Text.Contains(PIN_P03) || m_cbReference4.Text.Contains(PIN_P32))
            {
                masterConfig = m_cbReference4.Text;
            }

            // The wiring can be same as master config or it should be internal reference .
            if (!(parent.Text.Equals(masterConfig) || parent.Text.Equals(REF_INTERNAL_REF)
                 || parent.Text.Equals(INTERNAL_VDDA_4) || parent.Text.Equals(INTERNAL_VDDA_3)))
            {
                // Set error .
                m_errorProvider.SetError(parent, ERROR_REF_VOLTAGE + masterConfig);
                retVal = true;
            }
            else
            {
                m_errorProvider.SetError(parent, string.Empty);
            }
            return retVal;
        }

        // Clock source radio buttons
        // Internal clock
        private void m_rbClockInternal_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbClockInternal.Checked)
            {
                SetAParameter(CyADC_DelSigParameters.ADC_CLOCK, CyADC_DelSigParameters.S_INTERNAL, true);
            }
        }

        // External clock
        private void m_rbClockExternal_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbClockExternal.Checked)
            {
                SetAParameter(CyADC_DelSigParameters.ADC_CLOCK, CyADC_DelSigParameters.S_EXTERNAL, true);
            }
        }

        // Start of Conversion
        // Hardware/Software
        private void m_cbSocHardware_CheckedChanged(object sender, EventArgs e)
        {
            if (m_cbSocHardware.Checked)
            {
                SetAParameter(CyADC_DelSigParameters.START_OF_CONVERSION, CyADC_DelSigParameters.S_HARDWARE, true);
            }
            else
            {
                SetAParameter(CyADC_DelSigParameters.START_OF_CONVERSION, CyADC_DelSigParameters.S_SOFTWARE, true);
            }
        }

        // Reference Voltage
        private void m_nudRefVoltage_ValueChanged(object sender, EventArgs e)
        {
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage, m_cbReference);
            HookAllEvents();
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE, m_nudRefVoltage.Value.ToString(), false);
            UpdateInputRangeList(1);
        }

        private void CheckRefVoltage(CyNumericUpDown nudRefVoltage, ComboBox cbReference)
        {
            m_errorProvider.SetError(nudRefVoltage, String.Empty);
            decimal retVal = (decimal)GetVDDAValue();
            if (cbReference.Text.Contains(INTERNAL_VDDA_4))
            {
                retVal /= 4;
                nudRefVoltage.Value = retVal;
            }
            else if (cbReference.Text.Contains(INTERNAL_VDDA_3))
            {
                retVal /= 3;
                nudRefVoltage.Value = retVal;
            }
            if (nudRefVoltage.Value > MAX_VREF_VALUE)
            {
                // We will not force the value to be Max value. 
                string errorMessage = string.Format("Error: Parameter should be within value {0}-{1}\n",
                    MIN_VREF_VALUE, MAX_VREF_VALUE);
                m_errorProvider.SetError(nudRefVoltage, errorMessage);
                m_errorProvider.SetIconAlignment(nudRefVoltage, ErrorIconAlignment.MiddleLeft);
            }
            else if (nudRefVoltage.Value < MIN_VREF_VALUE)
            {
                // We will not force the value to be Min value. 
                string errorMessage = string.Format("Error: Parameter should be within value {0}-{1}\n",
                    MIN_VREF_VALUE, MAX_VREF_VALUE);
                m_errorProvider.SetError(nudRefVoltage, errorMessage);
                m_errorProvider.SetIconAlignment(nudRefVoltage, ErrorIconAlignment.MiddleLeft);
            }
        }

        private void SetAParameter(string parameter, string value, bool checkFocus)
        {
            if (this.ContainsFocus || !checkFocus)
            {
                // Verify that the parameter was set correctly.
                m_Component.SetParamExpr(parameter, value);
                m_Component.CommitParamExprs();
                if (m_Component.GetCommittedParam(parameter).ErrorCount != 0)
                {
                    string errors = null;
                    foreach (string err in m_Component.GetCommittedParam(parameter).Errors)
                    {
                        errors = errors + err + "\n";
                    }

                    string errorMessage = string.Format("Error Setting Parameter {0} with value {1}\n\nErrors:\n{2}", 
                        parameter, value, errors);
                    m_errorProvider.SetError(m_nudConfig, errorMessage);
                    MessageBox.Show(errorMessage);
                }
            }
        }

        // Get the ADC clock frequency for the current settings.
        private int GetFreq(uint resolution, uint conversionMode, uint convRate)
        {
            int theFreq;
            theFreq = (int)CyCustomizer.SetClock(resolution, convRate, conversionMode);
            return theFreq;
        }

        // Get the Conversion rate for the current settings.
        private uint GetConvRate(float frequency, bool maximum, int resolution, int conversionMode)
        {
            uint theConvRate;
            theConvRate = (uint)CyCustomizer.GetSampleRate((uint)resolution, frequency, (uint)conversionMode, maximum);
            return theConvRate;
        }

        public bool CheckAllFreq(bool saveValue)
        {
            bool retValue;
            retValue = CheckFreqConfig1(saveValue);
            retValue &= CheckFreqConfig2(saveValue);
            retValue &= CheckFreqConfig3(saveValue);
            retValue &= CheckFreqConfig4(saveValue);
            return retValue;
        }

        // Check the current ADC settings for clock frequencies that are beyond the clock specifications.
        private bool CheckFreqConfig1(bool saveValue)
        {
            bool retValue = CheckFreq(CyADC_DelSigParameters.RESOLUTION, CyADC_DelSigParameters.INPUT_BUFFER_GAIN,
                CyADC_DelSigParameters.SAMPLE_RATE, CyADC_DelSigParameters.CONVERSION_MODE,
                m_cbInputBufferMode, m_nudConvRate, m_cbConvMode, m_cbResolution, m_tbClockFreq,
                m_lbSPSRange, saveValue, CyADC_DelSigParameters.INPUT_RANGE, m_cbInputRange);
            m_sRateErr1 = !retValue;

            // Save Sample rate error status to symbol to generate the DRC error.
            bool value = (m_sRateErr1 | m_sRateErr2 | m_sRateErr3 | m_sRateErr4);
            SetAParameter(CyADC_DelSigParameters.SRATE_ERR, value.ToString(), false);

            return retValue;
        }

        // Check the current ADC settings for clock frequencies that are beyond the clock specifications.
        private bool CheckFreqConfig2(bool saveValue)
        {
            bool retValue = CheckFreq(CyADC_DelSigParameters.RESOLUTION_CONFIG2, 
                CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG2,
                CyADC_DelSigParameters.SAMPLE_RATE_CONFIG2, CyADC_DelSigParameters.CONVERSION_MODE_CONFIG2,
                m_cbInputBufferMode2, m_nudConvRate2, m_cbConvMode2, m_cbResolutionConfig2, m_tbClockFreq2,
                m_lbSPSRange2, saveValue, CyADC_DelSigParameters.INPUT_RANGE_CONFIG2, m_cbInputRange2);
            m_sRateErr2 = !retValue;

            // Save Sample rate error status to symbol to generate the DRC error.
            bool value = (m_sRateErr1 | m_sRateErr2 | m_sRateErr3 | m_sRateErr4);
            SetAParameter(CyADC_DelSigParameters.SRATE_ERR, value.ToString(), false);

            return retValue;
        }

        // Check the current ADC settings for clock frequencies that are beyond the clock specifications.
        private bool CheckFreqConfig3(bool saveValue)
        {
            bool retValue = CheckFreq(CyADC_DelSigParameters.RESOLUTION_CONFIG3, 
                CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG3,
                CyADC_DelSigParameters.SAMPLE_RATE_CONFIG3, CyADC_DelSigParameters.CONVERSION_MODE_CONFIG3,
                m_cbInputBufferMode3, m_nudConvRate3, m_cbConvMode3, m_cbResolutionConfig3, m_tbClockFreq3,
                m_lbSPSRange3, saveValue, CyADC_DelSigParameters.INPUT_RANGE_CONFIG3, m_cbInputRange3);
            m_sRateErr3 = !retValue;

            // Save Sample rate error status to symbol to generate the DRC error.
            bool value = (m_sRateErr1 | m_sRateErr2 | m_sRateErr3 | m_sRateErr4);
            SetAParameter(CyADC_DelSigParameters.SRATE_ERR, value.ToString(), false);

            return retValue;
        }

        // Check the current ADC settings for clock frequencies that are beyond the clock specifications.
        private bool CheckFreqConfig4(bool saveValue)
        {
            bool retValue = CheckFreq(CyADC_DelSigParameters.RESOLUTION_CONFIG4, 
                CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG4,
                CyADC_DelSigParameters.SAMPLE_RATE_CONFIG4, CyADC_DelSigParameters.CONVERSION_MODE_CONFIG4,
                m_cbInputBufferMode4, m_nudConvRate4, m_cbConvMode4, m_cbResolutionConfig4, m_tbClockFreq4,
                m_lbSPSRange4, saveValue, CyADC_DelSigParameters.INPUT_RANGE_CONFIG4, m_cbInputRange4);
            m_sRateErr4 = !retValue;

            // Save Sample rate error status to symbol to generate the DRC error.
            bool value = (m_sRateErr1 | m_sRateErr2 | m_sRateErr3 | m_sRateErr4);
            SetAParameter(CyADC_DelSigParameters.SRATE_ERR, value.ToString(), false);


            return retValue;
        }

        // Check the current ADC settings for clock frequencies that are beyond the clock specifications.
        private bool CheckFreq(string sResolution, string sGain, string sSampleRate, string sConversionMode,
            ComboBox cbInputBufferMode, CyNumericUpDown nudConvRate, ComboBox cbConvMode, ComboBox cbResolution,
            TextBox tbClockFreq, Label lbSPSRange, bool saveValue, string sinputRange, ComboBox cbInputRange)
        {
            float theFreq;
            float theFreqKHz;
            int resolution;
            int gain, conversionMode, inputRange;
            uint minRate, maxRate;
            float TheMaxFreq;
            float TheMinFreq;
            float TheMaxFreqKHz;
            float TheMinFreqKHz;
            string errorMessage;
            bool retVal;
            uint convRate = (uint)nudConvRate.Value;
            

            retVal = true;
            resolution = int.Parse(cbResolution.Text);// int.Parse(m_Component.GetCommittedParam(sResolution).Value);
            //gain = int.Parse(m_Component.GetCommittedParam(sGain).Value);
            string gainValue = m_Component.GetCommittedParam(sGain).Value;
            try
            {
                gain = int.Parse(gainValue);
            }
            catch (Exception)
            {
                gain = 1;
            }
            conversionMode = (int)cbConvMode.SelectedIndex; //m_Component.GetCommittedParam(sConversionMode).Value);
            inputRange = Convert.ToInt32(m_Component.GetCommittedParam(sinputRange).Value);
            if (resolution > 15)
            {
                // If buffer is enabled, for 2x,4x,8x gain, the frequency is halved and 
                // halved and halved respectively

                // Unbuffered Input
                if (cbInputBufferMode.Items[cbInputBufferMode.SelectedIndex].ToString() == BYPASS_BUFFER) 
                    TheMaxFreq = (float)Cyrc.MAX_FREQ_16_20_BITS[inputRange];
                else
                    TheMaxFreq = (float)Cyrc.MAX_FREQ_16_20_BITS[inputRange] / gain;

                TheMinFreq = (float)Cyrc.MIN_FREQ_15_20_BITS;
            }
            else
            {
                // Unbuffered Input
                if (cbInputBufferMode.Items[cbInputBufferMode.SelectedIndex].ToString() == BYPASS_BUFFER) 
                    TheMaxFreq = (float)Cyrc.MAX_FREQ_8_15_BITS[inputRange];
                else
                    TheMaxFreq = (float)Cyrc.MAX_FREQ_8_15_BITS[inputRange] / gain;

                // Minimum frequency is equal to that for 8-14 bit resolution
                TheMinFreq = (float)Cyrc.MIN_FREQ_8_14_BITS;
            }

            theFreq = (float)GetFreq((uint)resolution, (uint)conversionMode, (uint)nudConvRate.Value);
            theFreqKHz = theFreq / (float)1000.0;
            TheMaxFreqKHz = TheMaxFreq / (float)1000.0;
            TheMinFreqKHz = (float)(TheMinFreq / 1000.0);

            maxRate = GetConvRate(TheMaxFreq, true, resolution, conversionMode);
            minRate = GetConvRate(TheMinFreq, false, resolution, conversionMode);

            // Compare to valid value
            if (maxRate < minRate)
            {
                errorMessage = String.Empty;

                if (gain == 8)
                {
                    // 192KHz. And lower limit will be 128KHz.
                    TheMaxFreq = 192000;
                    TheMinFreq = 128000;
                    TheMaxFreqKHz = (float)192;
                    TheMinFreqKHz = (float)128;
                }
                maxRate = GetConvRate(TheMaxFreq, true, resolution, conversionMode);
                minRate = GetConvRate(TheMinFreq, false, resolution, conversionMode);
            }
            
            errorMessage = String.Empty;
            if (theFreq > TheMaxFreq)
            {
                errorMessage = "The sample rate of " + (uint)nudConvRate.Value
                    + " SPS has exceeded the maximum limit of "
                    + maxRate.ToString()
                    + " SPS for the conversion mode, resolution and frequency.";
                m_errorProvider.SetError(nudConvRate, errorMessage);
                m_errorProvider.SetError(cbResolution, errorMessage);
                m_errorProvider.SetError(cbConvMode, errorMessage);
                m_errorProvider.SetError(tbClockFreq, errorMessage);
                retVal = false;
            }
            else if (theFreq < TheMinFreq)
            {
                errorMessage = "The sample rate of " + (uint)nudConvRate.Value + 
                               " SPS has below the minimum limit of "
                    + minRate.ToString()
                    + " SPS for the conversion mode, resolution and frequency.";
                m_errorProvider.SetError(nudConvRate, errorMessage);
                m_errorProvider.SetError(cbResolution, errorMessage);
                m_errorProvider.SetError(cbConvMode, errorMessage);
                m_errorProvider.SetError(tbClockFreq, errorMessage);
                retVal = false;
            }
            else
            {
                m_errorProvider.SetError(cbResolution, String.Empty);
                m_errorProvider.SetError(cbConvMode, String.Empty);
                m_errorProvider.SetError(nudConvRate, String.Empty);
                m_errorProvider.SetError(tbClockFreq, String.Empty);
                retVal = true;
            }

            if (saveValue)
            {
                SetAParameter(sSampleRate, nudConvRate.Value.ToString(), false);
            }
            tbClockFreq.Text = theFreqKHz.ToString("0.000");
            lbSPSRange.Text = MESSAGE_RANGE + minRate.ToString() + " - " + maxRate.ToString() + MESSAGE_RANGE_END;
  
            return retVal;
        }

        // Returns the Reference voltage , indexed by the configuration tab.
        private decimal GetRefVoltage(int refVoltageConfIndex)
        {
            CyADC_DelSigParameters prms = new CyADC_DelSigParameters(m_Component);
            // Reference voltage.
            float tempFloat = 0;
            switch (refVoltageConfIndex)
            {
                case 1:
                    float.TryParse(prms.m_Ref_Voltage.Value, out tempFloat);
                    if (m_cbReference.SelectedItem.ToString().Contains(INTERNAL_BYPASSED) ||
                        m_cbReference.SelectedItem.ToString().Contains(REF_INTERNAL_REF) ||
                        m_cbReference.SelectedItem.ToString().Contains(INTERNAL_VDDA_4) ||
                        m_cbReference.SelectedItem.ToString().Contains(INTERNAL_VDDA_3))
                        tempFloat = (float) m_nudRefVoltage.Value;
                    break;
                case 2:
                    float.TryParse(prms.m_Ref_Voltage_Config2.Value, out tempFloat);
                    if (m_cbReference2.SelectedItem.ToString().Contains(INTERNAL_BYPASSED) ||
                        m_cbReference2.SelectedItem.ToString().Contains(REF_INTERNAL_REF) ||
                        m_cbReference2.SelectedItem.ToString().Contains(INTERNAL_VDDA_4) ||
                        m_cbReference2.SelectedItem.ToString().Contains(INTERNAL_VDDA_3))
                        tempFloat = (float)m_nudRefVoltage2.Value;
                    break;
                case 3:
                    float.TryParse(prms.m_Ref_Voltage_Config3.Value, out tempFloat);
                    if (m_cbReference3.SelectedItem.ToString().Contains(INTERNAL_BYPASSED) ||
                        m_cbReference3.SelectedItem.ToString().Contains(REF_INTERNAL_REF) ||
                        m_cbReference3.SelectedItem.ToString().Contains(INTERNAL_VDDA_4) ||
                        m_cbReference3.SelectedItem.ToString().Contains(INTERNAL_VDDA_3))
                        tempFloat = (float)m_nudRefVoltage3.Value;
                    break;
                case 4:
                    float.TryParse(prms.m_Ref_Voltage_Config4.Value, out tempFloat);
                    if (m_cbReference4.SelectedItem.ToString().Contains(INTERNAL_BYPASSED) ||
                        m_cbReference4.SelectedItem.ToString().Contains(REF_INTERNAL_REF) ||
                        m_cbReference4.SelectedItem.ToString().Contains(INTERNAL_VDDA_4) ||
                        m_cbReference4.SelectedItem.ToString().Contains(INTERNAL_VDDA_3))
                        tempFloat = (float)m_nudRefVoltage4.Value;
                    break;
                default:
                    // Should not fall here, as of now only 4 configuration is supported.
                    tempFloat = -1;
                    break;
            }
            return (decimal)tempFloat;
        }

        // Check what combination of Input Range and Reference is selected
        private void UpdateRefVoltageEnable(int index, Control cbReference, Control cbInputRange, Control label, 
            CyNumericUpDown nudRefVolt)
        {
            UnhookAllEvents();

            nudRefVolt.Enabled = false;
            decimal refVtg = GetRefVoltage(index);
            if (cbReference.Text.Contains(REF_EXTERNAL) || (cbInputRange.Text.Equals(RANGE_VSSA_TO_VDDA)))
            {
                nudRefVolt.Enabled = true;
                if (cbInputRange.Text.Equals(RANGE_VSSA_TO_VDDA))
                {
                    // label_Warning.Text += "r-vda";

                    label.Text = LABEL_VOLTS_VDD;
                    decimal retVal = (decimal)GetVDDAValue();
                    if (retVal < MAX_VDDA3_VALUE)
                    {
                        retVal /= 3;
                    }
                    else
                    {
                        retVal /= 4;
                    }
                    // FOR display purpose and hence this will not be validated.
                    nudRefVolt.Value = retVal;
                    nudRefVolt.Enabled = false;
                }
                else
                {
                    label.Text = LABEL_VOLTS;
                    nudRefVolt.Value = refVtg;
                }
            }
            else
            {
                if (!(cbReference.Text.Contains(INTERNAL_VDDA_4) || cbReference.Text.Contains(INTERNAL_VDDA_3)))
                {
                    label.Text = LABEL_VOLTS;
                    // TODO: This depends on the VDDA values.
                    nudRefVolt.Value = refVtg;
                    nudRefVolt.Value = VREF_INT_VALUE;
                    nudRefVolt.Enabled = false;
                }
            }
            HookAllEvents();
        }

        private void m_cbConvMode2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.CONVERSION_MODE, 
                                                             m_cbConvMode2.Text);
            SetAParameter(CyADC_DelSigParameters.CONVERSION_MODE_CONFIG2, prm, true);
            CheckFreqConfig2(true);
            DisplayInterruptMessage();
        }

        private void m_cbInputBufferMode2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG2, 
                m_cbInputBufferMode2.Text);
            UpdateBufferGain(m_cbInputBufferMode2.Text, m_cbInputBufferGain2);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG2, prm, true);
            CheckFreqConfig2(true);
        }

        private void m_nudConfig_ValueChanged(object sender, EventArgs e)
        {
            int l_Configs = 4;
            int.TryParse(m_nudConfig.Value.ToString(), out l_Configs);

            UpdateConfigTabs(l_Configs);
            UpdateAllInputRangeList();
            SetAParameter(CyADC_DelSigParameters.CONFIGS, m_nudConfig.Value.ToString(), false);
            DisplayInterruptMessage();
        }

        private void UpdateAllBufferGain()
        {
            UpdateBufferGain(m_cbInputBufferMode.Items[m_cbInputBufferMode.SelectedIndex].ToString(), 
                m_cbInputBufferGain);
            UpdateBufferGain(m_cbInputBufferMode2.Items[m_cbInputBufferMode2.SelectedIndex].ToString(), 
                m_cbInputBufferGain2);
            UpdateBufferGain(m_cbInputBufferMode3.Items[m_cbInputBufferMode3.SelectedIndex].ToString(), 
                m_cbInputBufferGain3);
            UpdateBufferGain(m_cbInputBufferMode4.Items[m_cbInputBufferMode4.SelectedIndex].ToString(), 
                m_cbInputBufferGain4);
        }

        private void UpdateBufferGain(string inputBufferMode, Control inputBufferGain)
        {
            // Disable the BufferGain if the Buffer mode is set to Bypass Buffer.
            if (inputBufferMode.Contains(BYPASS_BUFFER) || inputBufferMode.Contains(BYPASS_BUFFER_ENUM))
            {
                inputBufferGain.Enabled = false;
            }
            else
            {
                inputBufferGain.Enabled = true;
            }
        }

        private void m_cbInputBufferMode_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_MODE, 
                m_cbInputBufferMode.Text);
            UpdateBufferGain(m_cbInputBufferMode.Text, m_cbInputBufferGain);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_MODE, prm, true);
            CheckFreqConfig1(true);

        }

        private int ResolveEnumIdOfInputRange(string inputValue)
        {
            int index = 0;
            bool found = false;
            IEnumerable<string> InputRangeEnums = m_Component.GetPossibleEnumValues(CyADC_DelSigParameters.INPUT_RANGE);

            foreach (string str in InputRangeEnums)
            {
                if (inputValue.Equals(str)) {
                    found = true;
                    break;
                }
                index++;
            }
            if (!found)
                index = -1;
            return index;
        }

        //  Returns the actual 
        private string ResolveInputEnumDisplayToId(ComboBox inputRange)
        {
            int index = inputRange.SelectedIndex;
            string strSelected = ""; 
            if (m_rbModeDifferential.Checked)
            {
                index += 4;
            }
            IEnumerable<string> InputRangeEnums = m_Component.GetPossibleEnumValues(
                                                   CyADC_DelSigParameters.INPUT_RANGE);

            foreach (string str in InputRangeEnums)
            {
                if (index == 0)
                {
                    strSelected = str;
                    break;
                }
                index--;
            }                
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_RANGE, strSelected);
            return prm;
        }

        private void UpdateInputModeSelection(ComboBox inputRange, string paramName, string idName)
        {
            string paramInputRange = m_Component.ResolveEnumIdToDisplay(paramName, idName);
            int selectedIndex = ResolveEnumIdOfInputRange(paramInputRange);
            // Only Single modes are listed when the Single Input mode is selcted.
            // So the values stored from the symbol has to calculated with offset.
            if (m_rbModeDifferential.Checked)
            {
                if (selectedIndex < TOTAL_SINGLE_MODES)
                {
                    inputRange.SelectedIndex = 0;
                    // Store the value to symbol
                    string prm = ResolveInputEnumDisplayToId(inputRange);
                    SetAParameter(paramName, prm, true);
                }
                else
                {
                    inputRange.SelectedIndex = selectedIndex - TOTAL_SINGLE_MODES;
                }
            }
            else
            {
                if (selectedIndex < TOTAL_SINGLE_MODES)
                {
                    inputRange.SelectedIndex = selectedIndex;
                }
                else
                {
                    inputRange.SelectedIndex = 0;
                    // Store the value to symbol
                    string prm = ResolveInputEnumDisplayToId(inputRange);
                    SetAParameter(paramName, prm, true);
                }
            }
            CheckAllFreq(false);
        }

        private decimal GetVDDAValue()
        {
            decimal Vdda = Convert.ToDecimal(m_Component.GetCommittedParam(
                            CyADC_DelSigParameters.ADC_Vdda_Value).Value);
            return Vdda;
        }

        private void UpdateInputRangeList(ComboBox list, float vrefValue)
        {

            IEnumerable<string> InputRangeEnums = m_Component.GetPossibleEnumValues(
                                                  CyADC_DelSigParameters.INPUT_RANGE);
            CyADC_DelSigParameters prms = new CyADC_DelSigParameters(m_Component);
            int index = 0;
            string tempStr;
            List<string> modifiedInputRange = new List<string>();
            foreach (string str in InputRangeEnums)
            {
                tempStr = String.Format(InputRangeFormat[index], (vrefValue * adcGain[index]).ToString());
                modifiedInputRange.Add(tempStr);

                index++;
            }

            list.Items.Clear();
            if (m_rbModeDifferential.Checked)
            {
                // ONLY show the differential options in the "Input Range" paramter.
                for (int i = 0; i < modifiedInputRange.Count; i++)
                {
                    string str = modifiedInputRange[i];
                    if (!str.Contains(INPUT_SINGLE_TYPE))// && m_rbModeDifferential.Checked)
                    {
                        list.Items.Add(str);
                    }
                }
            }
            else
            {
                // ONLY show the single options in the "Input Range" paramter.
                for (int i = 0; i < modifiedInputRange.Count; i++)
                {
                    string str = modifiedInputRange[i];
                    if (str.Contains(INPUT_SINGLE_TYPE))
                    {
                        list.Items.Add(str);
                    }
                }
            }
        }

        // Update the ADC mode of all configuration tabs
        private void UpdateInputRangeList(int index)
        {
            float vrefValue;
            CyADC_DelSigParameters prms = new CyADC_DelSigParameters(m_Component);
            vrefValue = (float) GetRefVoltage(index);
            
            switch (index)
            {
                case 1:
                    UpdateInputRangeList(m_cbInputRange, vrefValue);
                    UpdateInputModeSelection(m_cbInputRange, CyADC_DelSigParameters.INPUT_RANGE, 
                        prms.m_ADC_Input_Range.Expr);
                    break;
                case 2:
                    UpdateInputRangeList(m_cbInputRange2, vrefValue);
                    UpdateInputModeSelection(m_cbInputRange2, CyADC_DelSigParameters.INPUT_RANGE_CONFIG2,
                        prms.m_ADC_Input_Range_Config2.Expr);
                    break;
                case 3:
                    UpdateInputRangeList(m_cbInputRange3, vrefValue);
                    UpdateInputModeSelection(m_cbInputRange3, CyADC_DelSigParameters.INPUT_RANGE_CONFIG3,
                        prms.m_ADC_Input_Range_Config3.Expr);
                    break;
                case 4:
                    UpdateInputRangeList(m_cbInputRange4, vrefValue);
                    UpdateInputModeSelection(m_cbInputRange4, CyADC_DelSigParameters.INPUT_RANGE_CONFIG4,
                        prms.m_ADC_Input_Range_Config4.Expr);
                    break;
                default:
                    break;

            }
        }

        private void UpdateAllInputRangeList()
        {   
            UpdateInputRangeList(1);
            UpdateInputRangeList(2);
            UpdateInputRangeList(3);
            UpdateInputRangeList(4);
        }

        private void UpdateADCMode()
        {
            if (m_rbModeDifferential.Checked)
            {
                m_rbModeDifferential2.Checked = true;
                m_rbModeDifferential3.Checked = true;
                m_rbModeDifferential4.Checked = true;
            }
            else
            {
                m_rbModeSingle2.Checked = true;
                m_rbModeSingle3.Checked = true;
                m_rbModeSingle4.Checked = true;
            }
        }
        
        // Update the ADC mode of all configuration tabs.
        private bool UpdateInputRangeList1(bool not)
        {
            float vrefValue;
            string tempStr;
            bool retVal = true;
            IEnumerable<string> InputRangeEnums = m_Component.GetPossibleEnumValues(
                                                   CyADC_DelSigParameters.INPUT_RANGE);
            CyADC_DelSigParameters prms = new CyADC_DelSigParameters(m_Component);
            float.TryParse(prms.m_Ref_Voltage.Value, out vrefValue);

            // Since we dont save the VDDA value in to symbol for input range type VDDA selection 

            int index = 0;

            m_cbInputRange.Items.Clear();
            m_cbInputRange2.Items.Clear();
            m_cbInputRange3.Items.Clear();
            m_cbInputRange4.Items.Clear();

            List<string> modifiedInputRange = new List<string>();
            foreach (string str in InputRangeEnums)
            {
                tempStr = String.Format(InputRangeFormat[index], (vrefValue * adcGain[index]).ToString());
                modifiedInputRange.Add(tempStr);

                index++;
            }

            if (m_rbModeDifferential.Checked)
            {
                m_rbModeDifferential2.Checked = true;
                m_rbModeDifferential3.Checked = true;
                m_rbModeDifferential4.Checked = true;
                // ONLY show the differential options in the "Input Range" paramter.
                for (int i = 0; i < modifiedInputRange.Count; i++)
                {
                    string str = modifiedInputRange[i];
                    if (!str.Contains(INPUT_SINGLE_TYPE))
                    {
                        m_cbInputRange.Items.Add(str);
                        m_cbInputRange2.Items.Add(str);
                        m_cbInputRange3.Items.Add(str);
                        m_cbInputRange4.Items.Add(str);
                    }
                }
            }
            else
            {
                m_rbModeSingle2.Checked = true;
                m_rbModeSingle3.Checked = true;
                m_rbModeSingle4.Checked = true;
                // ONLY show the single options in the "Input Range" paramter.
                for (int i = 0; i < modifiedInputRange.Count; i++)
                {
                    string str = modifiedInputRange[i];
                    if (str.Contains(INPUT_SINGLE_TYPE))
                    {
                        m_cbInputRange.Items.Add(str);
                        m_cbInputRange2.Items.Add(str);
                        m_cbInputRange3.Items.Add(str);
                        m_cbInputRange4.Items.Add(str);
                    }
                }
            }

            UpdateInputModeSelection(m_cbInputRange, CyADC_DelSigParameters.INPUT_RANGE, prms.m_ADC_Input_Range.Expr);
            UpdateInputModeSelection(m_cbInputRange2, CyADC_DelSigParameters.INPUT_RANGE_CONFIG2, 
                prms.m_ADC_Input_Range_Config2.Expr);
            UpdateInputModeSelection(m_cbInputRange3, CyADC_DelSigParameters.INPUT_RANGE_CONFIG3, 
                prms.m_ADC_Input_Range_Config3.Expr);
            UpdateInputModeSelection(m_cbInputRange4, CyADC_DelSigParameters.INPUT_RANGE_CONFIG4, 
                prms.m_ADC_Input_Range_Config4.Expr);

            return retVal;
        }

        // Handle ADC mode.
        // Either m_rbModeSingle, m_rbModeDifferential is allowed.
        private void m_rbModeDifferential_CheckedChanged(object sender, EventArgs e)
        {
            string prm = "";
            if (m_rbModeDifferential.Checked)
            {
                prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_INPUT_MODE,
                    m_rbModeDifferential.Text);
            }
            else
            {
                prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_INPUT_MODE,
                    m_rbModeSingle.Text);
            }

            UnhookAllEvents();
            UpdateADCMode();
            UpdateAllInputRangeList();
            HookAllEvents();
            SetAParameter(CyADC_DelSigParameters.ADC_INPUT_MODE, prm, true);
            UnhookAllEvents();
            UpdateRefVoltagesEnable();
            UpdateRefVoltageEnable(1, m_cbReference, m_cbInputRange, Volts_label, m_nudRefVoltage);
            UpdateRefVoltageEnable(2, m_cbReference2, m_cbInputRange2, Volts_label2, m_nudRefVoltage2);
            UpdateRefVoltageEnable(3, m_cbReference3, m_cbInputRange3, Volts_label3, m_nudRefVoltage3);
            UpdateRefVoltageEnable(4, m_cbReference4, m_cbInputRange4, Volts_label4, m_nudRefVoltage4);
            UpdateAllInputRangeList();
            HookAllEvents();
            CheckAllFreq(true);
        }

        private void m_cbInputRange2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_RANGE_CONFIG2, 
                m_cbInputRange2.Text);
            decimal vdda = GetVDDAValue();

            // If "Vssa to Vdda (Single Ended)" is selected then choose refernce to be "Internal Ref"*/
            if (m_cbInputRange2.Text.Equals(RANGE_VSSA_TO_VDDA))
            {
                UnhookAllEvents();
                UnhookAllEvents();
                if (vdda < MAX_VDDA3_VALUE)
                {
                    m_cbReference2.SelectedItem = INTERNAL_VDDA_3;
                }
                else
                {
                    m_cbReference2.SelectedItem = INTERNAL_VDDA_4;
                }
                HookAllEvents();
                m_cbReference2.Enabled = false; 
                prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2, 
                                                          m_cbReference2.Text);
                SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2, prm, true);
            }
            else
            {
                m_cbReference2.Enabled = true;
            }

            prm = ResolveInputEnumDisplayToId(m_cbInputRange2);
            SetAParameter(CyADC_DelSigParameters.INPUT_RANGE_CONFIG2, prm, true);
            CheckFreqConfig2(true);

            CheckRefVoltage(m_nudRefVoltage2, m_cbReference2);
            UpdateRefVoltageEnable(2, m_cbReference2, m_cbInputRange2, Volts_label2, m_nudRefVoltage2);
            UnhookAllEvents();
            UpdateInputRangeList(2);
            HookAllEvents();
            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, 
                                                     m_nudRefVoltage2.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, prm, true);
        }

        private void m_cbInputBufferGain2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_GAIN, 
                m_cbInputBufferGain2.Text);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG2, prm, true);
            CheckFreqConfig2(true);
        }

        private void m_cbReference2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE, m_cbReference2.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2, prm, true);

            UpdateRefVoltageEnable(2, m_cbReference2, m_cbInputRange2, Volts_label2, m_nudRefVoltage2);
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage2, m_cbReference2);
            UpdateInputRangeList(2);
            HookAllEvents();
            // Save the Reference voltage now, since all events were unhooked it wont get saved.
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, m_nudRefVoltage2.Value.ToString(), false);
        }

        private void m_nudRefVoltage2_ValueChanged(object sender, EventArgs e)
        {
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage2, m_cbReference2);
            HookAllEvents();
            // Set is the upper limit
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, m_nudRefVoltage2.Value.ToString(), false);
            UpdateInputRangeList(2);
        }

        private void m_cbConvMode3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.CONVERSION_MODE, 
                                                             m_cbConvMode3.Text);
            SetAParameter(CyADC_DelSigParameters.CONVERSION_MODE_CONFIG3, prm, true);
            CheckFreqConfig3(true);
            DisplayInterruptMessage();
        }
        
        private void m_cbConvMode4_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.CONVERSION_MODE, 
                                                            m_cbConvMode4.Text);
            SetAParameter(CyADC_DelSigParameters.CONVERSION_MODE_CONFIG4, prm, true);
            CheckFreqConfig4(true);
            DisplayInterruptMessage();
        }

        private void m_cbInputRange3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_RANGE_CONFIG3, 
                m_cbInputRange3.Text);
            decimal vdda = GetVDDAValue();

            // If "Vssa to Vdda (Single Ended)" is selected then choose refernce to be "Internal Ref"
            if (m_cbInputRange3.Text.Equals(RANGE_VSSA_TO_VDDA))
            {
                UnhookAllEvents();
                UnhookAllEvents();
                if (vdda < MAX_VDDA3_VALUE)
                {
                    m_cbReference3.SelectedItem = INTERNAL_VDDA_3;
                }
                else
                {
                    m_cbReference3.SelectedItem = INTERNAL_VDDA_4;
                }
                HookAllEvents();
                m_cbReference3.Enabled = false;
                prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3, 
                                                          m_cbReference3.Text);
                SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3, prm, true);
            }
            else
            {
                m_cbReference3.Enabled = true;
            }

            prm = ResolveInputEnumDisplayToId(m_cbInputRange3);
            SetAParameter(CyADC_DelSigParameters.INPUT_RANGE_CONFIG3, prm, true);
            CheckFreqConfig3(true);

            CheckRefVoltage(m_nudRefVoltage3, m_cbReference3);
            UpdateRefVoltageEnable(3, m_cbReference3, m_cbInputRange3, Volts_label3, m_nudRefVoltage3);
            UnhookAllEvents();
            UpdateInputRangeList(3);
            HookAllEvents();
            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, 
                                                      m_nudRefVoltage3.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, prm, true);
        }

        private void m_cbInputBufferGain3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_GAIN,
                m_cbInputBufferGain3.Text);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG3, prm, true);
            CheckFreqConfig3(true);
        }

        private void m_cbInputBufferMode3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG2,
                m_cbInputBufferMode3.Text);
            UpdateBufferGain(m_cbInputBufferMode3.Text, m_cbInputBufferGain3);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG3, prm, true);
            CheckFreqConfig3(true);
        }

        private void m_cbReference3_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE, m_cbReference3.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3, prm, true);

            UpdateRefVoltageEnable(3, m_cbReference3, m_cbInputRange3, Volts_label3, m_nudRefVoltage3);
            
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage3, m_cbReference3);
            UpdateInputRangeList(3);
            HookAllEvents();
            // Save the Reference voltage now, since all events were unhooked it wont get saved.
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, m_nudRefVoltage3.Value.ToString(), false);
        }

        private void m_nudRefVoltage3_ValueChanged(object sender, EventArgs e)
        {
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage3, m_cbReference3);
            HookAllEvents();

            // Set is the upper limit
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, m_nudRefVoltage3.Value.ToString(), false);
            UpdateInputRangeList(3);
        }

        private void m_cbResolutionConfig4_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.RESOLUTION, 
                                                             m_cbResolutionConfig4.Text);
            SetAParameter(CyADC_DelSigParameters.RESOLUTION_CONFIG4, prm, true);
            CheckFreqConfig4(true);
            DisplayInterruptMessage();
        }

        private void m_cbInputRange4_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_RANGE_CONFIG4,
                m_cbInputRange4.Text);
            decimal vdda = GetVDDAValue();

            // If "Vssa to Vdda (Single Ended)" is selected then choose refernce to be "Internal Ref"
            if (m_cbInputRange4.Text.Equals(RANGE_VSSA_TO_VDDA))
            {
                UnhookAllEvents();
                UnhookAllEvents();
                if (vdda < MAX_VDDA3_VALUE)
                {
                    m_cbReference4.SelectedItem = INTERNAL_VDDA_3;
                }
                else
                {
                    m_cbReference4.SelectedItem = INTERNAL_VDDA_4;
                }
                HookAllEvents();
                m_cbReference4.Enabled = false;
                prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4, 
                                                            m_cbReference4.Text);
                SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4, prm, true);

            }
            else
            {
                m_cbReference4.Enabled = true;
            }

            prm = ResolveInputEnumDisplayToId(m_cbInputRange4);
            SetAParameter(CyADC_DelSigParameters.INPUT_RANGE_CONFIG4, prm, true);
            CheckFreqConfig4(true);

            CheckRefVoltage(m_nudRefVoltage4, m_cbReference4);
            UpdateRefVoltageEnable(4, m_cbReference4, m_cbInputRange4, Volts_label4, m_nudRefVoltage4);
            UnhookAllEvents();
            UpdateInputRangeList(4);
            HookAllEvents();
            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4, 
                                                      m_nudRefVoltage4.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4, prm, true);
        }

        private void m_cbInputBufferGain4_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_GAIN,
                m_cbInputBufferGain4.Text);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_GAIN_CONFIG4, prm, true);
            CheckFreqConfig4(true);            
        }

        private void m_cbInputBufferMode4_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG2,
                m_cbInputBufferMode4.Text);
            UpdateBufferGain(m_cbInputBufferMode4.Text, m_cbInputBufferGain4);
            SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_MODE_CONFIG4, prm, true);
            CheckFreqConfig4(true);
        }

        private void m_cbReference4_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE, m_cbReference4.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4, prm, true);

            UpdateRefVoltageEnable(4, m_cbReference4, m_cbInputRange4, Volts_label4, m_nudRefVoltage4);
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage4, m_cbReference4);
            UpdateInputRangeList(4);
            HookAllEvents();
            //Save the Reference voltage now, since all events were unhooked it wont get saved.
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4, m_nudRefVoltage4.Value.ToString(), false);

        }

        private void m_nudRefVoltage4_ValueChanged(object sender, EventArgs e)
        {
            UnhookAllEvents();
            CheckRefVoltage(m_nudRefVoltage4, m_cbReference4);
            HookAllEvents();

            // Set is the upper limit
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4, m_nudRefVoltage4.Value.ToString(), false);
            UpdateInputRangeList(4);
        }


        private void m_cbEnable_Vref_Vss_CheckedChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.ADC_nVref, m_cbEnable_Vref_Vss.Checked.ToString(), true);
        }

        private void CyADC_DelSigControl_Load(object sender, EventArgs e)
        {
            CyADC_DelSigParameters prms = new CyADC_DelSigParameters(m_Component);
            string paramInputBufferGain = m_Component.ResolveEnumIdToDisplay(CyADC_DelSigParameters.INPUT_BUFFER_GAIN,
                prms.m_Input_Buffer_Gain.Expr);

            string prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE, m_cbReference.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE, prm, false);
            
            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2, 
                                                     m_cbReference2.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG2, prm, false);

            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3, 
                                                      m_cbReference3.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG3, prm, false);

            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4, 
                                                      m_cbReference4.Text);
            SetAParameter(CyADC_DelSigParameters.ADC_REFERENCE_CONFIG4, prm, false);

            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE, m_nudRefVoltage.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE, prm, false);

            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, 
                                                      m_nudRefVoltage2.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG2, prm, false);

            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, 
                                                      m_nudRefVoltage3.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG3, prm, false);

            prm = m_Component.ResolveEnumDisplayToId(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4, 
                                                      m_nudRefVoltage4.Text);
            SetAParameter(CyADC_DelSigParameters.REF_VOLTAGE_CONFIG4, prm, false);

            // Test the input Buffer gain when loading and if not valid input buffer gain found
            // assign the default value
            if (!m_cbInputBufferGain.Items.Contains(paramInputBufferGain))
            {
                m_cbInputBufferGain.SelectedItem = "Gain_1X";
                m_cbInputBufferGain.Text = "1";
                SetAParameter(CyADC_DelSigParameters.INPUT_BUFFER_GAIN, "Gain_1X", false);
            }
        }

        private void configNameTextBox1_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.CONFIG1_NAME, configNameTextBox1.Text, true);
            nameLabel1.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                           "_", configNameTextBox1.Text);
        }

        private void commentTextBox1_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.ADC_COMMENT_CONFIG1, commentTextBox1.Text, true);
        }

        private void commentTextBox2_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.ADC_COMMENT_CONFIG2, commentTextBox2.Text, true);
        }

        private void configNameTextBox2_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.CONFIG2_NAME, configNameTextBox2.Text, true);
            nameLabel2.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox2.Text);
        }

        private void commentTextBox3_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.ADC_COMMENT_CONFIG3, commentTextBox3.Text, true);
        }

        private void configNameTextBox3_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.CONFIG3_NAME, configNameTextBox3.Text, true);
            nameLabel3.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox3.Text);
        }
   
        private void commentTextBox4_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.ADC_COMMENT_CONFIG4, commentTextBox4.Text, true);
        }

        private void configNameTextBox4_TextChanged(object sender, EventArgs e)
        {
            SetAParameter(CyADC_DelSigParameters.CONFIG4_NAME, configNameTextBox4.Text, true);
            nameLabel4.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox4.Text);
        }

        // This is to update the config name label in the customizer whenever
        //  the instance name changes 

        private void timer1_Tick(object sender, EventArgs e)
        {
            nameLabel1.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox1.Text);
            nameLabel2.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox2.Text);
            nameLabel3.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox3.Text);
            nameLabel4.Text = string.Concat(m_Component.GetCommittedParam("INSTANCE_NAME").Value + 
                                                                          "_", configNameTextBox4.Text);
        }
    }

    public class CyNumericUpDown : NumericUpDown
    {
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == Keys.Enter)
            {
                this.ValidateEditText();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }
    }
}
