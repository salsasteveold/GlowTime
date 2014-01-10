/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Diagnostics;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using WaveDAC8_v1_70;

namespace WaveDAC8_v1_70
{
    public partial class CyWaveDacControl : UserControl
    {
        public ICyInstEdit_v1 m_Component = null;
        public ICyTerminalQuery_v1 m_TermQuery = null;

        public CyWaveDacControl(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termquery)
        {
            m_Component = inst;
            m_TermQuery = termquery;
            //Trace.Assert(Debugger.IsAttached);
            InitializeComponent();

            InitializeFormComponents(inst);
            UpdateFormFromParams(inst);
        }

        /// <summary>
        /// 
        /// </summary>
        protected override void OnCreateControl()
        {
            base.OnCreateControl();
            this.ParentForm.FormClosing += new FormClosingEventHandler(ParentForm_FormClosing);
        }

        protected override void OnResize(EventArgs e)
        {
            base.OnResize(e);
            m_cywave1.Invalidate();
            m_cywave2.Invalidate();
        }

        void ParentForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if (((Form)sender).DialogResult == DialogResult.Cancel)
            //{
            //    return;
            //}
            //if (ep_Errors.GetError(m_numPeriod) != "")
            //{
            //    m_numPeriod.Focus();
            //    e.Cancel = true;
            //}
            //if(ep_Errors.GetError(m_numCompare1) != "")
            //{
            //    m_numCompare1.Focus();
            //    e.Cancel = true;
            //}
            //if (!m_cbPWMMode.Text.Equals("One Output") && !m_cbPWMMode.Text.Equals("Center Align"))
            //{
            //    if (ep_Errors.GetError(m_numCompare2) != "")
            //    {
            //        m_numCompare2.Focus();
            //        e.Cancel = true;
            //    }
            //}
            //if (ep_Errors.GetError(m_numDeadBandCounts) != "")
            //{
            //    m_numDeadBandCounts.Focus();
            //    e.Cancel = true;
            //}
        }

        #region Form Initialization
        public void InitializeFormComponents(ICyInstEdit_v1 inst)
        {
            /* Set the WaveType Combo Boxes from Enums */
            IEnumerable<string> Wave1_TypeEnums = inst.GetPossibleEnumValues("Wave1_Type");
            foreach (string str in Wave1_TypeEnums)
            {
                m_cbWave1Type.Items.Add(str);
            }

            IEnumerable<string> Wave2_TypeEnums = inst.GetPossibleEnumValues("Wave2_Type");
            foreach (string str in Wave2_TypeEnums)
            {
                m_cbWave2Type.Items.Add(str);
            }

            /* Set the DAC Range Combo Box from Enums */
            IEnumerable<string> DacRangeEnums = inst.GetPossibleEnumValues("DAC_Range");
            foreach (string str in DacRangeEnums)
            {
                m_cbImplementation.Items.Add(str);
            }

            m_cywave1.OnArbWaveChange += new cywaveformeditor.ArbWaveformChanged(m_cywave1_OnArbWaveChange);
            m_cywave2.OnArbWaveChange += new cywaveformeditor.ArbWaveformChanged(m_cywave2_OnArbWaveChange);
        }

        private void ConfigureNumerics(string prm)
        {
            switch (prm)
            {
                case "Range_1_Volt":
                    ((CyNumericUpDown)m_nudAmplitude1).Increment = Convert.ToDecimal(1.020 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude2).Increment = Convert.ToDecimal(1.020 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset1).Increment = Convert.ToDecimal(1.020 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Increment = Convert.ToDecimal(1.020 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude1).Maximum = Convert.ToDecimal(1.020);
                    ((CyNumericUpDown)m_nudAmplitude2).Maximum = Convert.ToDecimal(1.020);
                    ((CyNumericUpDown)m_nudDCOffset1).Maximum = Convert.ToDecimal(1.020);
                    ((CyNumericUpDown)m_nudDCOffset1).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Maximum = Convert.ToDecimal(1.020);
                    ((CyNumericUpDown)m_nudDCOffset2).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset1).DecimalPlaces = 3;
                    ((CyNumericUpDown)m_nudDCOffset2).DecimalPlaces = 3;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 3;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 3;
                    ((Label)m_lblAmp1).Text = "Amplitude (Vpp)";
                    ((Label)m_lblAmp2).Text = "Amplitude (Vpp)";
                    ((Label)m_lblDCOff1).Text = "Offset (V)";
                    ((Label)m_lblDCOff2).Text = "Offset (V)";
                    break;
                case "Range_4_Volt":
                    ((CyNumericUpDown)m_nudAmplitude1).Increment = Convert.ToDecimal(4.080 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude2).Increment = Convert.ToDecimal(4.080 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset1).Increment = Convert.ToDecimal(4.080 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Increment = Convert.ToDecimal(4.080 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude1).Maximum = Convert.ToDecimal(4.080);
                    ((CyNumericUpDown)m_nudAmplitude2).Maximum = Convert.ToDecimal(4.080);
                    ((CyNumericUpDown)m_nudDCOffset1).Maximum = Convert.ToDecimal(4.080);
                    ((CyNumericUpDown)m_nudDCOffset1).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Maximum = Convert.ToDecimal(4.080);
                    ((CyNumericUpDown)m_nudDCOffset2).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset1).DecimalPlaces = 3;
                    ((CyNumericUpDown)m_nudDCOffset2).DecimalPlaces = 3;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 3;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 3;
                    ((Label)m_lblAmp1).Text = "Amplitude (Vpp)";
                    ((Label)m_lblAmp2).Text = "Amplitude (Vpp)";
                    ((Label)m_lblDCOff1).Text = "Offset (V)";
                    ((Label)m_lblDCOff2).Text = "Offset (V)";
                    break;
                case "ISink_2040_uA":
                case "ISource_2040_uA":
                    ((CyNumericUpDown)m_nudAmplitude1).Increment = Convert.ToDecimal(2.040 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude2).Increment = Convert.ToDecimal(2.040 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset1).Increment = Convert.ToDecimal(2.040 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Increment = Convert.ToDecimal(2.040 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude1).Maximum = Convert.ToDecimal(2.040);
                    ((CyNumericUpDown)m_nudAmplitude2).Maximum = Convert.ToDecimal(2.040);
                    ((CyNumericUpDown)m_nudDCOffset1).Maximum = Convert.ToDecimal(2.04);
                    ((CyNumericUpDown)m_nudDCOffset1).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Maximum = Convert.ToDecimal(1.04);
                    ((CyNumericUpDown)m_nudDCOffset2).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset1).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudDCOffset2).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 6;
                    ((Label)m_lblAmp1).Text = "Amplitude (mApp)";
                    ((Label)m_lblAmp2).Text = "Amplitude (mApp)";
                    ((Label)m_lblDCOff1).Text = "Offset (mA)";
                    ((Label)m_lblDCOff2).Text = "Offset (mA)";
                    break;
                case "ISink_256_uA":
                case "ISource_256_uA":
                    ((CyNumericUpDown)m_nudAmplitude1).Increment = Convert.ToDecimal(0.256 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude2).Increment = Convert.ToDecimal(0.256 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset1).Increment = Convert.ToDecimal(0.256 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Increment = Convert.ToDecimal(0.256 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude1).Maximum = Convert.ToDecimal(0.256);
                    ((CyNumericUpDown)m_nudAmplitude2).Maximum = Convert.ToDecimal(0.256);
                    ((CyNumericUpDown)m_nudDCOffset1).Maximum = Convert.ToDecimal(0.256);
                    ((CyNumericUpDown)m_nudDCOffset1).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Maximum = Convert.ToDecimal(0.256);
                    ((CyNumericUpDown)m_nudDCOffset2).Minimum = Convert.ToDecimal(0.0);
                    ((CyNumericUpDown)m_nudDCOffset1).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudDCOffset2).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 6;
                    ((Label)m_lblAmp1).Text = "Amplitude (mApp)";
                    ((Label)m_lblAmp2).Text = "Amplitude (mApp)";
                    ((Label)m_lblDCOff1).Text = "Offset (mA)";
                    ((Label)m_lblDCOff2).Text = "Offset (mA)";
                    break;
                case "ISink_32_uA":
                case "ISource_32_uA":
                    ((CyNumericUpDown)m_nudAmplitude1).Increment = Convert.ToDecimal(0.032 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude2).Increment = Convert.ToDecimal(0.032 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset1).Increment = Convert.ToDecimal(0.032 / 256.0);
                    ((CyNumericUpDown)m_nudDCOffset2).Increment = Convert.ToDecimal(0.032 / 256.0);
                    ((CyNumericUpDown)m_nudAmplitude1).Maximum = Convert.ToDecimal(0.032);
                    ((CyNumericUpDown)m_nudAmplitude2).Maximum = Convert.ToDecimal(0.032);
                    ((CyNumericUpDown)m_nudDCOffset1).Maximum = Convert.ToDecimal(0.032);
                    ((CyNumericUpDown)m_nudDCOffset1).Minimum = Convert.ToDecimal(0.00);
                    ((CyNumericUpDown)m_nudDCOffset2).Maximum = Convert.ToDecimal(0.032);
                    ((CyNumericUpDown)m_nudDCOffset2).Minimum = Convert.ToDecimal(0.00);
                    ((CyNumericUpDown)m_nudDCOffset1).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudDCOffset2).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 6;
                    ((CyNumericUpDown)m_nudAmplitude1).DecimalPlaces = 6;
                    ((Label)m_lblAmp1).Text = "Amplitude (mApp)";
                    ((Label)m_lblAmp2).Text = "Amplitude (mApp)";
                    ((Label)m_lblDCOff1).Text = "Offset (mA)";
                    ((Label)m_lblDCOff2).Text = "Offset (mA)";
                    break;
            }
        } 
        #endregion

        void UnhookUpdateEvents()
        {
            m_cbWave1Type.SelectedIndexChanged -= m_cbWave1Type_SelectedIndexChanged;
            m_cbWave2Type.SelectedIndexChanged -= m_cbWave2Type_SelectedIndexChanged;
            m_nudAmplitude1.ValueChanged -= m_nudAmplitude1_ValueChanged;
            m_nudAmplitude2.ValueChanged -= m_nudAmplitude2_ValueChanged;
            m_nudDCOffset1.ValueChanged -= m_nudDCOffset1_ValueChanged;
            m_nudDCOffset2.ValueChanged -= m_nudDCOffset2_ValueChanged;
            m_nudNumSamples1.ValueChanged -= m_nudNumSamples1_ValueChanged;
            m_nudNumSamples2.ValueChanged -= m_nudNumSamples2_ValueChanged;
            m_nudSPS.ValueChanged -= m_nudSPS_ValueChanged;
            m_cbImplementation.SelectedIndexChanged -= m_cbImplementation_SelectedIndexChanged;
            m_nudDCOffset2.KeyUp -= m_nudDCOffset2_KeyUp;
            m_rbExternalClock.CheckedChanged -= m_rbExternalClock_CheckedChanged;
            m_rbInternalClock.CheckedChanged -= m_rbInternalClock_CheckedChanged;
        }

        void HookupUpdateEvents()
        {
            m_cbWave1Type.SelectedIndexChanged += m_cbWave1Type_SelectedIndexChanged;
            m_cbWave2Type.SelectedIndexChanged += m_cbWave2Type_SelectedIndexChanged;
            m_nudAmplitude1.ValueChanged += m_nudAmplitude1_ValueChanged;
            m_nudAmplitude2.ValueChanged += m_nudAmplitude2_ValueChanged;
            m_nudDCOffset1.ValueChanged += m_nudDCOffset1_ValueChanged;
            m_nudDCOffset2.ValueChanged += m_nudDCOffset2_ValueChanged;
            m_nudNumSamples1.ValueChanged += m_nudNumSamples1_ValueChanged;
            m_nudNumSamples2.ValueChanged += m_nudNumSamples2_ValueChanged;
            m_nudSPS.ValueChanged += m_nudSPS_ValueChanged;
            m_cbImplementation.SelectedIndexChanged += m_cbImplementation_SelectedIndexChanged;
            m_nudDCOffset2.KeyUp += m_nudDCOffset2_KeyUp;
            m_rbExternalClock.CheckedChanged += m_rbExternalClock_CheckedChanged;
            m_rbInternalClock.CheckedChanged += m_rbInternalClock_CheckedChanged;
        }

        void m_cywave1_OnArbWaveChange(List<byte> data)
        {
            SetAParameter("Wave1_Data", DataToString(data), false);
        }
        void m_cywave2_OnArbWaveChange(List<byte> data)
        {
            SetAParameter("Wave2_Data", DataToString(data), false);
        }

        public void MyUpdate()
        {
            UpdateFormFromParams(m_Component);
        }

        public void UpdateFormFromParams(ICyInstEdit_v1 inst)
        {
            UnhookUpdateEvents();
            CyWaveDACParameters prms = new CyWaveDACParameters(inst);           
            
            IEnumerable<string> DacRangeEnums = inst.GetPossibleEnumValues("DAC_Range");
            bool DACRangeFound = false;
            foreach (string str in DacRangeEnums)
            {
                if (!DACRangeFound)
                {
                    string paramcompare = m_Component.ResolveEnumIdToDisplay("DAC_Range", prms.DAC_Range.Expr);
                    if (paramcompare == str)
                    {
                        m_cbImplementation.SelectedItem = paramcompare;
                        DACRangeFound = true;
                    }
                }
            }
            if (!DACRangeFound)
            {
                m_cbImplementation.Text = prms.DAC_Range.Expr;
            }

            IEnumerable<string> Wave1TypeEnums = inst.GetPossibleEnumValues("Wave1_Type");
            bool WaveType1Found = false;
            foreach (string str in Wave1TypeEnums)
            {
                if (!WaveType1Found)
                {
                    string paramcompare = m_Component.ResolveEnumIdToDisplay("Wave1_Type", prms.Wave1_Type.Expr);
                    if (paramcompare == str)
                    {
                        m_cbWave1Type.SelectedItem = paramcompare;
                        WaveType1Found = true;
                    }
                }
            }
            if (!WaveType1Found)
            {
                m_cbWave1Type.Text = prms.Wave1_Type.Expr;
            }

            m_cywave1.Arbitrary = m_cbWave1Type.Text.Contains("Arbit");

            
            IEnumerable<string> Wave2TypeEnums = inst.GetPossibleEnumValues("Wave2_Type");
            bool WaveType2Found = false;
            foreach (string str in Wave2TypeEnums)
            {
                if (!WaveType2Found)
                {
                    string paramcompare = m_Component.ResolveEnumIdToDisplay("Wave2_Type", prms.Wave2_Type.Expr);
                    if (paramcompare == str)
                    {
                        m_cbWave2Type.SelectedItem = paramcompare;
                        WaveType2Found = true;
                    }
                }
            }
            if (!WaveType2Found)
            {
                m_cbWave2Type.Text = prms.Wave2_Type.Expr;
            }

            m_cywave2.Arbitrary = m_cbWave2Type.Text.Contains("Arbit");

            if (m_cbWave1Type.Text.Contains("Arbit"))
            {
                m_nudAmplitude1.Enabled = false;
                m_nudDCOffset1.Enabled = false;
            }

            if (m_cbWave2Type.Text.Contains("Arbit"))
            {
                m_nudAmplitude2.Enabled = false;
                m_nudDCOffset2.Enabled = false;
            }


            string prm = m_Component.ResolveEnumDisplayToId("DAC_Range", m_cbImplementation.Text);
            ConfigureNumerics(prm);

            m_nudNumSamples1.Value = Convert.ToInt16(prms.Wave1_Length.Expr);
            m_nudNumSamples2.Value = Convert.ToInt16(prms.Wave2_Length.Expr);
            m_nudAmplitude1.Value = Convert.ToDecimal(prms.Wave1_Amplitude.Expr);
            m_nudAmplitude2.Value = Convert.ToDecimal(prms.Wave2_Amplitude.Expr);
            m_nudDCOffset1.Value = Convert.ToDecimal(prms.Wave1_DCOffset.Expr);
            m_nudDCOffset2.Value = Convert.ToDecimal(prms.Wave2_DCOffset.Expr);

            m_rbExternalClock.Checked = prms.Clock_SRC.Expr.Contains("Exter");
            m_rbInternalClock.Checked = prms.Clock_SRC.Expr.Contains("Inter");
            m_nudSPS.Value = Convert.ToDecimal(prms.Sample_Clock_Freq.Expr);

            if (prms.Clock_SRC.Expr.Contains("Inter"))
            {
                m_cywave1.SPS = Convert.ToDouble(prms.Sample_Clock_Freq.Expr);
                m_cywave2.SPS = Convert.ToDouble(prms.Sample_Clock_Freq.Expr);
                m_nudSPS.Enabled = true;
            }
            else
            {
                m_cywave1.SPS = 0.0;
                m_cywave2.SPS = 0.0;
                m_nudSPS.Enabled = false;
            }

            UpdateDrawing();

            HookupUpdateEvents();
        }

        private void UpdateDrawing()
        {
            UpdateDrawing1();
            UpdateDrawing2();
        }

        private void UpdateDrawing1()
        {
            CyWaveDACParameters prms = new CyWaveDACParameters(m_Component);
            m_cywave1.SetWaveRange(GetMaxVolage(prms.DAC_Range.Expr));
            m_cywave1.Offset = Convert.ToDouble(prms.Wave1_DCOffset.Expr);
            m_cywave1.DataValues = GetDataValues(prms.Wave1_Data.Expr);
            m_cywave1.Invalidate();
        }
        private void UpdateDrawing2()
        {
            CyWaveDACParameters prms = new CyWaveDACParameters(m_Component);
            m_cywave2.SetWaveRange(GetMaxVolage(prms.DAC_Range.Expr));
            m_cywave2.Offset = Convert.ToDouble(prms.Wave2_DCOffset.Expr);
            m_cywave2.DataValues = GetDataValues(prms.Wave2_Data.Expr);
            m_cywave2.Invalidate();
        }

        private List<byte> GetDataValues(String datastring)
        {
            List<byte> data = new List<byte>();
            string[] split = datastring.Split(',');
            foreach (string str in split)
            {
                data.Add(Convert.ToByte(str));
            }
            return data;
        }

        private CyWaveRange GetMaxVolage(string DAC_Range)
        {
            CyWaveRange cywr = new CyWaveRange();
            if(DAC_Range.Contains("Range_1_Volt")) {cywr.MaxRange = 1.020; cywr.Volts = true;}
            else if(DAC_Range.Contains("Range_4_Volt")) {cywr.MaxRange = 4.080; cywr.Volts = true;}
            else if(DAC_Range.Contains("ISink_2040_uA")) {cywr.MaxRange = 2.040; cywr.Volts = false;}
            else if(DAC_Range.Contains("ISink_256_uA")) {cywr.MaxRange = 0.255; cywr.Volts = false;}
            else if(DAC_Range.Contains("ISink_32_uA")) {cywr.MaxRange = 0.032; cywr.Volts = false;}
            else if (DAC_Range.Contains("ISource_2040_uA")) {cywr.MaxRange = 2.040; cywr.Volts = false;}
            else if (DAC_Range.Contains("ISource_256_uA")) {cywr.MaxRange = 0.255; cywr.Volts = false;}
            else if (DAC_Range.Contains("ISource_32_uA")) {cywr.MaxRange = 0.032; cywr.Volts = false;}
            return cywr;
        }

        private void SetAParameter(string parameter, string value, bool CheckFocus)
        {
            if (this.ContainsFocus || !CheckFocus)
            {
                m_Component.SetParamExpr(parameter, value);
                m_Component.CommitParamExprs();
                if (m_Component.GetCommittedParam(parameter).ErrorCount != 0)
                {
                    string errors = null;
                    foreach (string err in m_Component.GetCommittedParam(parameter).Errors)
                    {
                        errors = errors + err + "\n";
                    }
                    MessageBox.Show(string.Format("Error Setting Parameter {0} with value {1}\n\nErrors:\n{2}", parameter, value, errors),
                        "Error Setting Parameter", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void m_cbWave1Type_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId("Wave1_Type", m_cbWave1Type.Text);
            SetAParameter("Wave1_Type", prm, false);
            if (prm.Contains("Arbit"))
            {
                m_nudAmplitude1.Enabled = false;
                m_nudDCOffset1.Enabled = false;
                m_cywave1.Arbitrary = true;                
                return;
            }
            else
            {
                m_nudAmplitude1.Enabled = true;
                m_nudDCOffset1.Enabled = true;
                m_cywave1.Arbitrary = false;                
            }
            CreateWaveform1();
        }

        private void CreateWaveform1()
        {
            CyWaveDACParameters prms = new CyWaveDACParameters(m_Component);
            double MaxVoltage = GetMaxVolage(prms.DAC_Range.Expr).MaxRange;
            int NumSamples = Convert.ToInt16(prms.Wave1_Length.Expr);
            double Amplitude = Convert.ToDouble(prms.Wave1_Amplitude.Expr);
            double DCOffset = Convert.ToDouble(prms.Wave1_DCOffset.Expr);
            List<byte> data = new List<byte>();
            switch (m_cbWave1Type.Text)
            {
                case "Sine":                
                    data = CreateSineWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Triangle":
                    data = CreateTriangleWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Sawtooth":
                    data = CreateSawtoothWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Square":
                    data = CreateSquareWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Arbitrary":
                    data = m_cywave1.DataValues;
                    break;
                default:
                    break;
            }
            SetAParameter("Wave1_Data", DataToString(data), false);
            UpdateDrawing1();
        }

        private string DataToString(List<byte> data)
        {
            string datastring = null;
            for(int i=0;i<data.Count;i++)
            {
                datastring += ((i == 0 ? ' ' : ',') + data[i].ToString("0"));
            }
            return datastring;
        }

        private void m_cbWave2Type_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId("Wave2_Type", m_cbWave2Type.Text);
            SetAParameter("Wave2_Type", prm, false);
            if (prm.Contains("Arbit"))
            {
                m_nudAmplitude2.Enabled = false;
                m_nudDCOffset2.Enabled = false;
                m_cywave2.Arbitrary = true;                
                return;
            }
            else
            {
                m_nudAmplitude2.Enabled = true;
                m_nudDCOffset2.Enabled = true;
                m_cywave2.Arbitrary = false;                
            }
            CreateWaveform2();
        }

        private void CreateWaveform2()
        {
            CyWaveDACParameters prms = new CyWaveDACParameters(m_Component);
            double MaxVoltage = GetMaxVolage(prms.DAC_Range.Expr).MaxRange;
            int NumSamples = Convert.ToInt16(prms.Wave2_Length.Expr);
            double Amplitude = Convert.ToDouble(prms.Wave2_Amplitude.Expr);
            double DCOffset = Convert.ToDouble(prms.Wave2_DCOffset.Expr);
            List<byte> data = new List<byte>();
            switch (m_cbWave2Type.Text)
            {
                case "Sine":
                    data = CreateSineWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Triangle":
                    data = CreateTriangleWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Sawtooth":
                    data = CreateSawtoothWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Square":
                    data = CreateSquareWaveform(NumSamples, MaxVoltage, Amplitude, DCOffset);
                    break;
                case "Arbitrary":
                    data = m_cywave2.DataValues;
                    break;
                default:
                    break;
            }
            SetAParameter("Wave2_Data", DataToString(data), false);
            UpdateDrawing2();
        }

        private List<byte> CreateSineWaveform(int NumSamples, double MaxVoltage, double Amplitude, double DCOffset)
        {
            /* Create a Sine Wave */
            List<byte> data = new List<byte>();


            double fullScale = Convert.ToDouble(MaxVoltage);  // Full Scale amplitude
            double amp_pp = Convert.ToDouble(Amplitude);      // Signal amplitude peak-to-peak
            double dc_offset = Convert.ToDouble(DCOffset);    // Signal DC offset w/respect to full scale
	    	double samples   = Convert.ToDouble(NumSamples);

            double tempval = 0;
	    	double sinIndex = 0;
	   	 	byte value;

            for (int i = 0; i < NumSamples; i++)
            {
				sinIndex = i;
                tempval = (amp_pp/2.0) * Math.Sin( (sinIndex/samples) * (Math.PI*2.0) );
				tempval = tempval + dc_offset;                 // Add DC offset
				tempval = (tempval/fullScale) * 255.0;         // Scale 0 to 255
                value = Convert.ToByte((tempval >= 255) ? 255 : (tempval <= 0) ? 0 : tempval);
                data.Add(value);
            }
            return data;
        }

        private List<byte> CreateTriangleWaveform(int NumSamples, double MaxVoltage, double Amplitude, double DCOffset)
        {
            /* Create a Triangle Wave */
            List<byte> data = new List<byte>();
            double fullScale = Convert.ToDouble(MaxVoltage);  // Full Scale amplitude
            double amp_pp = Convert.ToDouble(Amplitude);      // Signal amplitude peak-to-peak
            double dc_offset = Convert.ToDouble(DCOffset);    // Signal DC offset w/respect to full scale
            double onequarter = NumSamples * 0.25;
            double onehalf = NumSamples * 0.5;
            double threequarter = NumSamples * 0.75;

            double tempval = 0;
	    	byte value;

	    	for (int i = 0; i < NumSamples; i++)
            {
                if (i < onequarter)
                {
		    		tempval = (((amp_pp/2.0)/onequarter)*i);  // First quarter of triangle wave
                }
                else if (i < threequarter)
                {
		    		tempval = (amp_pp - (((amp_pp/2.0)/onequarter)*(i-onequarter))) - (amp_pp/2.0) ;  // Second and third quarters
                }
                else
                {
		    		tempval = (((amp_pp/2.0)/onequarter)*(i-threequarter)) - (amp_pp/2);  // last quarter of triangle wave
                }

				tempval = tempval + dc_offset;                 // Add DC offset
				tempval = (tempval/fullScale) * 255.0;         // Scale 0 to 255
                value = Convert.ToByte((tempval >= 255) ? 255 : (tempval <= 0) ? 0 : tempval); // Clip Values
                data.Add(value);
            }
            return data;
        }

        private List<byte> CreateSawtoothWaveform(int NumSamples, double MaxVoltage, double Amplitude, double DCOffset)
        {
            /* Create a Sawtooth Wave */
            List<byte> data = new List<byte>();
            double fullScale = Convert.ToDouble(MaxVoltage);  // Full Scale amplitude
            double amp_pp = Convert.ToDouble(Amplitude);      // Signal amplitude peak-to-peak
            double dc_offset = Convert.ToDouble(DCOffset);    // Signal DC offset w/respect to full scale

            double tempval = 0;
	    	byte value;

	    	for (int i = 0; i < NumSamples; i++)
        	{
				tempval = ((amp_pp/(NumSamples-1))*i)-(amp_pp/2);  // Create Triangle at amplitude at zero offset
				tempval = tempval + dc_offset;                 // Add DC offset
				tempval = (tempval/fullScale) * 255.0;         // Scale 0 to 255
            	value = Convert.ToByte((tempval >= 255) ? 255 : (tempval <= 0) ? 0 : tempval); // Clip Values
            	data.Add(value);
        	}
            return data;
        }

        private List<byte> CreateSquareWaveform(int NumSamples, double MaxVoltage, double Amplitude, double DCOffset)
        {
            /* Create a Square Wave */
            List<byte> data = new List<byte>();
            double fullScale = Convert.ToDouble(MaxVoltage);  // Full Scale amplitude
            double amp_pp = Convert.ToDouble(Amplitude);      // Signal amplitude peak-to-peak
            double dc_offset = Convert.ToDouble(DCOffset);    // Signal DC offset w/respect to full scale

            double tempval = 0;
	    	byte value;

	    	for (int i = 0; i < NumSamples; i++)
            {
                if (i < (NumSamples / 2.0))
				{
		   			tempval = amp_pp/2.0;  // Positive half of square wave
				}
				else
				{
		   			tempval = -amp_pp/2.0;  // Negative half of square wave

				}
				tempval = tempval + dc_offset;                 // Add DC offset
				tempval = (tempval/fullScale) * 255.0;         // Scale 0 to 255
            	value = Convert.ToByte((tempval >= 255) ? 255 : (tempval <= 0) ? 0 : tempval); // Clip Values
                data.Add(value);
            }
            return data;
        }

        private void m_nudNumSamples1_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Wave1_Length", Convert.ToString(m_nudNumSamples1.Value), false);
            if (m_cbWave1Type.Text.Contains("Arbit"))
            {
                List<byte> bytes = m_cywave1.DataValues;
                if (m_nudNumSamples1.Value > bytes.Count)
                {
                    int i = (int)m_nudNumSamples1.Value - bytes.Count;
                    while (i-- > 0)
                        bytes.Add((byte)0);
                }
                else
                {
                    int i =  bytes.Count - (int)m_nudNumSamples1.Value;
                    while (i-- > 0)
                    bytes.RemoveAt(bytes.Count - 1);
                }
                SetAParameter("Wave1_Data", DataToString(bytes), false);
            }
            CreateWaveform1();
        }

        private void m_nudNumSamples2_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Wave2_Length", Convert.ToString(m_nudNumSamples2.Value), false);
            if (m_cbWave2Type.Text.Contains("Arbit"))
            {
                List<byte> bytes = m_cywave2.DataValues;
                if (m_nudNumSamples2.Value > bytes.Count)
                {
                    int i = (int)m_nudNumSamples2.Value - bytes.Count;
                    while (i-- > 0)
                        bytes.Add((byte)0);
                }
                else
                {
                    int i = bytes.Count - (int)m_nudNumSamples2.Value;
                    while (i-- > 0)
                        bytes.RemoveAt(bytes.Count - 1);
                }
                SetAParameter("Wave2_Data", DataToString(bytes), false);
            }
            CreateWaveform2();

        }

        private void m_nudAmplitude1_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Wave1_Amplitude", Convert.ToString(m_nudAmplitude1.Value), false);
            CreateWaveform1();

        }

        private void m_nudAmplitude2_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Wave2_Amplitude", Convert.ToString(m_nudAmplitude2.Value), false);
            CreateWaveform2();
        }

        private void m_nudDCOffset1_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Wave1_DCOffset", Convert.ToString(m_nudDCOffset1.Value), false);
            CreateWaveform1();
        }

        private void m_nudDCOffset2_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Wave2_DCOffset", Convert.ToString(m_nudDCOffset2.Value), false);
            CreateWaveform2();
        }

        private void m_nudDCOffset2_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                e.Handled = true;
                e.SuppressKeyPress = true;
            }
        }

        private void m_cbImplementation_SelectedIndexChanged(object sender, EventArgs e)
        {
            string prm = m_Component.ResolveEnumDisplayToId("DAC_Range", m_cbImplementation.Text);
            SetAParameter("DAC_Range", prm, false);
            CyWaveDACParameters prms = new CyWaveDACParameters(m_Component);
            m_cywave1.SetWaveRange(GetMaxVolage(prms.DAC_Range.Expr));
            m_cywave2.SetWaveRange(GetMaxVolage(prms.DAC_Range.Expr));
            ConfigureNumerics(prm);
            CreateWaveform1();
            CreateWaveform2();
            UpdateDrawing();
        }

        private void m_nudSPS_ValueChanged(object sender, EventArgs e)
        {
            SetAParameter("Sample_Clock_Freq", Convert.ToString(m_nudSPS.Value), false);
            m_cywave1.SPS = Convert.ToDouble(m_nudSPS.Value);
            m_cywave2.SPS = Convert.ToDouble(m_nudSPS.Value);
            UpdateDrawing();
        }

        private void m_rbExternalClock_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbExternalClock.Checked)
            {
                SetAParameter("Clock_SRC", "External_Clk", false);
                m_nudSPS.Enabled = false;
                m_cywave1.SPS = 0.0;    //TODO: Clock Query
                m_cywave2.SPS = 0.0;
                UpdateDrawing();
            }
        }

        private void m_rbInternalClock_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbInternalClock.Checked)
            {
                SetAParameter("Clock_SRC", "Internal_Clk", false);
                m_nudSPS.Enabled = true;
                m_cywave1.SPS = Convert.ToDouble(m_nudSPS.Value);
                m_cywave2.SPS = Convert.ToDouble(m_nudSPS.Value);
                UpdateDrawing();
            }
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


