using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using WaveDAC8_v1_70;

namespace WaveDAC8_v1_70
{
    partial class CyWaveDacControl
    {
        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CyWaveDacControl));
            this.m_cbImplementation = new System.Windows.Forms.ComboBox();
            this.m_lblDCOff2 = new System.Windows.Forms.Label();
            this.m_lblAmp2 = new System.Windows.Forms.Label();
            this.m_cbWave2Type = new System.Windows.Forms.ComboBox();
            this.m_nudDCOffset2 = new WaveDAC8_v1_70.CyNumericUpDown();
            this.m_lblNumSamp2 = new System.Windows.Forms.Label();
            this.m_nudNumSamples2 = new WaveDAC8_v1_70.CyNumericUpDown();
            this.m_nudAmplitude2 = new WaveDAC8_v1_70.CyNumericUpDown();
            this.m_lblDCOff1 = new System.Windows.Forms.Label();
            this.m_lblAmp1 = new System.Windows.Forms.Label();
            this.m_cbWave1Type = new System.Windows.Forms.ComboBox();
            this.m_nudDCOffset1 = new WaveDAC8_v1_70.CyNumericUpDown();
            this.m_lblNumSamp1 = new System.Windows.Forms.Label();
            this.m_nudNumSamples1 = new WaveDAC8_v1_70.CyNumericUpDown();
            this.m_nudAmplitude1 = new WaveDAC8_v1_70.CyNumericUpDown();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.m_nudSPS = new WaveDAC8_v1_70.CyNumericUpDown();
            this.m_rbInternalClock = new System.Windows.Forms.RadioButton();
            this.m_rbExternalClock = new System.Windows.Forms.RadioButton();
            this.m_cywave2 = new WaveDAC8_v1_70.cywaveformeditor();
            this.m_cywave1 = new WaveDAC8_v1_70.cywaveformeditor();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDCOffset2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumSamples2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudAmplitude2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDCOffset1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumSamples1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudAmplitude1)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSPS)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_cbImplementation
            // 
            this.m_cbImplementation.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.m_cbImplementation.FormattingEnabled = true;
            this.m_cbImplementation.Location = new System.Drawing.Point(3, 33);
            this.m_cbImplementation.Name = "m_cbImplementation";
            this.m_cbImplementation.Size = new System.Drawing.Size(288, 24);
            this.m_cbImplementation.TabIndex = 36;
            // 
            // m_lblDCOff2
            // 
            this.m_lblDCOff2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblDCOff2.AutoSize = true;
            this.m_lblDCOff2.Location = new System.Drawing.Point(427, 74);
            this.m_lblDCOff2.Name = "m_lblDCOff2";
            this.m_lblDCOff2.Size = new System.Drawing.Size(69, 13);
            this.m_lblDCOff2.TabIndex = 35;
            this.m_lblDCOff2.Text = "DC Offset (V)";
            // 
            // m_lblAmp2
            // 
            this.m_lblAmp2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblAmp2.AutoSize = true;
            this.m_lblAmp2.Location = new System.Drawing.Point(427, 48);
            this.m_lblAmp2.Name = "m_lblAmp2";
            this.m_lblAmp2.Size = new System.Drawing.Size(69, 13);
            this.m_lblAmp2.TabIndex = 34;
            this.m_lblAmp2.Text = "Amplitude (V)";
            // 
            // m_cbWave2Type
            // 
            this.m_cbWave2Type.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cbWave2Type.FormattingEnabled = true;
            this.m_cbWave2Type.Location = new System.Drawing.Point(299, 19);
            this.m_cbWave2Type.Name = "m_cbWave2Type";
            this.m_cbWave2Type.Size = new System.Drawing.Size(121, 21);
            this.m_cbWave2Type.TabIndex = 33;
            // 
            // m_nudDCOffset2
            // 
            this.m_nudDCOffset2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudDCOffset2.DecimalPlaces = 3;
            this.m_nudDCOffset2.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudDCOffset2.Location = new System.Drawing.Point(299, 72);
            this.m_nudDCOffset2.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudDCOffset2.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            -2147483648});
            this.m_nudDCOffset2.Name = "m_nudDCOffset2";
            this.m_nudDCOffset2.Size = new System.Drawing.Size(121, 20);
            this.m_nudDCOffset2.TabIndex = 32;
            // 
            // m_lblNumSamp2
            // 
            this.m_lblNumSamp2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblNumSamp2.AutoSize = true;
            this.m_lblNumSamp2.Location = new System.Drawing.Point(427, 100);
            this.m_lblNumSamp2.Name = "m_lblNumSamp2";
            this.m_lblNumSamp2.Size = new System.Drawing.Size(47, 13);
            this.m_lblNumSamp2.TabIndex = 31;
            this.m_lblNumSamp2.Text = "Samples";
            // 
            // m_nudNumSamples2
            // 
            this.m_nudNumSamples2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudNumSamples2.Location = new System.Drawing.Point(299, 98);
            this.m_nudNumSamples2.Maximum = new decimal(new int[] {
            64535,
            0,
            0,
            0});
            this.m_nudNumSamples2.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.m_nudNumSamples2.Name = "m_nudNumSamples2";
            this.m_nudNumSamples2.Size = new System.Drawing.Size(120, 20);
            this.m_nudNumSamples2.TabIndex = 30;
            this.m_nudNumSamples2.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            // 
            // m_nudAmplitude2
            // 
            this.m_nudAmplitude2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudAmplitude2.DecimalPlaces = 3;
            this.m_nudAmplitude2.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudAmplitude2.Location = new System.Drawing.Point(299, 46);
            this.m_nudAmplitude2.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.m_nudAmplitude2.Name = "m_nudAmplitude2";
            this.m_nudAmplitude2.Size = new System.Drawing.Size(121, 20);
            this.m_nudAmplitude2.TabIndex = 29;
            this.m_nudAmplitude2.Value = new decimal(new int[] {
            40,
            0,
            0,
            65536});
            // 
            // m_lblDCOff1
            // 
            this.m_lblDCOff1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblDCOff1.AutoSize = true;
            this.m_lblDCOff1.Location = new System.Drawing.Point(420, 74);
            this.m_lblDCOff1.Name = "m_lblDCOff1";
            this.m_lblDCOff1.Size = new System.Drawing.Size(69, 13);
            this.m_lblDCOff1.TabIndex = 28;
            this.m_lblDCOff1.Text = "DC Offset (V)";
            // 
            // m_lblAmp1
            // 
            this.m_lblAmp1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblAmp1.AutoSize = true;
            this.m_lblAmp1.Location = new System.Drawing.Point(420, 48);
            this.m_lblAmp1.Name = "m_lblAmp1";
            this.m_lblAmp1.Size = new System.Drawing.Size(69, 13);
            this.m_lblAmp1.TabIndex = 27;
            this.m_lblAmp1.Text = "Amplitude (V)";
            // 
            // m_cbWave1Type
            // 
            this.m_cbWave1Type.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cbWave1Type.FormattingEnabled = true;
            this.m_cbWave1Type.Location = new System.Drawing.Point(292, 19);
            this.m_cbWave1Type.Name = "m_cbWave1Type";
            this.m_cbWave1Type.Size = new System.Drawing.Size(121, 21);
            this.m_cbWave1Type.TabIndex = 26;
            // 
            // m_nudDCOffset1
            // 
            this.m_nudDCOffset1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudDCOffset1.DecimalPlaces = 3;
            this.m_nudDCOffset1.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudDCOffset1.Location = new System.Drawing.Point(292, 72);
            this.m_nudDCOffset1.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.m_nudDCOffset1.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            -2147483648});
            this.m_nudDCOffset1.Name = "m_nudDCOffset1";
            this.m_nudDCOffset1.Size = new System.Drawing.Size(121, 20);
            this.m_nudDCOffset1.TabIndex = 25;
            // 
            // m_lblNumSamp1
            // 
            this.m_lblNumSamp1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_lblNumSamp1.AutoSize = true;
            this.m_lblNumSamp1.Location = new System.Drawing.Point(420, 100);
            this.m_lblNumSamp1.Name = "m_lblNumSamp1";
            this.m_lblNumSamp1.Size = new System.Drawing.Size(47, 13);
            this.m_lblNumSamp1.TabIndex = 24;
            this.m_lblNumSamp1.Text = "Samples";
            // 
            // m_nudNumSamples1
            // 
            this.m_nudNumSamples1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudNumSamples1.Location = new System.Drawing.Point(293, 98);
            this.m_nudNumSamples1.Maximum = new decimal(new int[] {
            64535,
            0,
            0,
            0});
            this.m_nudNumSamples1.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.m_nudNumSamples1.Name = "m_nudNumSamples1";
            this.m_nudNumSamples1.Size = new System.Drawing.Size(120, 20);
            this.m_nudNumSamples1.TabIndex = 23;
            this.m_nudNumSamples1.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // m_nudAmplitude1
            // 
            this.m_nudAmplitude1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.m_nudAmplitude1.DecimalPlaces = 3;
            this.m_nudAmplitude1.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.m_nudAmplitude1.Location = new System.Drawing.Point(292, 46);
            this.m_nudAmplitude1.Maximum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.m_nudAmplitude1.Name = "m_nudAmplitude1";
            this.m_nudAmplitude1.Size = new System.Drawing.Size(121, 20);
            this.m_nudAmplitude1.TabIndex = 22;
            this.m_nudAmplitude1.Value = new decimal(new int[] {
            40,
            0,
            0,
            65536});
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.m_nudSPS);
            this.groupBox2.Controls.Add(this.m_rbInternalClock);
            this.groupBox2.Controls.Add(this.m_rbExternalClock);
            this.groupBox2.Location = new System.Drawing.Point(299, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(229, 66);
            this.groupBox2.TabIndex = 40;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Clocking - Sample Rate";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(150, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "SPS";
            // 
            // m_nudSPS
            // 
            this.m_nudSPS.Location = new System.Drawing.Point(126, 39);
            this.m_nudSPS.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.m_nudSPS.Name = "m_nudSPS";
            this.m_nudSPS.Size = new System.Drawing.Size(86, 20);
            this.m_nudSPS.TabIndex = 2;
            this.m_nudSPS.ValueChanged += new System.EventHandler(this.m_nudSPS_ValueChanged);
            // 
            // m_rbInternalClock
            // 
            this.m_rbInternalClock.AutoSize = true;
            this.m_rbInternalClock.Location = new System.Drawing.Point(7, 39);
            this.m_rbInternalClock.Name = "m_rbInternalClock";
            this.m_rbInternalClock.Size = new System.Drawing.Size(97, 17);
            this.m_rbInternalClock.TabIndex = 1;
            this.m_rbInternalClock.TabStop = true;
            this.m_rbInternalClock.Text = "Internal Source";
            this.m_rbInternalClock.UseVisualStyleBackColor = true;
            this.m_rbInternalClock.CheckedChanged += new System.EventHandler(this.m_rbInternalClock_CheckedChanged);
            // 
            // m_rbExternalClock
            // 
            this.m_rbExternalClock.AutoSize = true;
            this.m_rbExternalClock.Location = new System.Drawing.Point(7, 16);
            this.m_rbExternalClock.Name = "m_rbExternalClock";
            this.m_rbExternalClock.Size = new System.Drawing.Size(100, 17);
            this.m_rbExternalClock.TabIndex = 0;
            this.m_rbExternalClock.TabStop = true;
            this.m_rbExternalClock.Text = "External Source";
            this.m_rbExternalClock.UseVisualStyleBackColor = true;
            this.m_rbExternalClock.CheckedChanged += new System.EventHandler(this.m_rbExternalClock_CheckedChanged);
            // 
            // m_cywave2
            // 
            this.m_cywave2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cywave2.DataValues = ((System.Collections.Generic.List<byte>)(resources.GetObject("m_cywave2.DataValues")));
            this.m_cywave2.Location = new System.Drawing.Point(7, 17);
            this.m_cywave2.Name = "m_cywave2";
            this.m_cywave2.Offset = 0;
            this.m_cywave2.Size = new System.Drawing.Size(281, 163);
            this.m_cywave2.SPS = 0;
            this.m_cywave2.TabIndex = 38;
            // 
            // m_cywave1
            // 
            this.m_cywave1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.m_cywave1.DataValues = ((System.Collections.Generic.List<byte>)(resources.GetObject("m_cywave1.DataValues")));
            this.m_cywave1.Location = new System.Drawing.Point(6, 19);
            this.m_cywave1.Name = "m_cywave1";
            this.m_cywave1.Offset = 0;
            this.m_cywave1.Size = new System.Drawing.Size(275, 163);
            this.m_cywave1.SPS = 0;
            this.m_cywave1.TabIndex = 37;
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(88, 4);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(112, 17);
            this.label2.TabIndex = 41;
            this.label2.Text = "Range Selection";
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.m_cywave2);
            this.groupBox3.Controls.Add(this.m_cbWave2Type);
            this.groupBox3.Controls.Add(this.m_nudAmplitude2);
            this.groupBox3.Controls.Add(this.m_nudNumSamples2);
            this.groupBox3.Controls.Add(this.m_lblNumSamp2);
            this.groupBox3.Controls.Add(this.m_nudDCOffset2);
            this.groupBox3.Controls.Add(this.m_lblDCOff2);
            this.groupBox3.Controls.Add(this.m_lblAmp2);
            this.groupBox3.Location = new System.Drawing.Point(3, 272);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(525, 187);
            this.groupBox3.TabIndex = 42;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Waveform 2";
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(427, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(63, 13);
            this.label3.TabIndex = 39;
            this.label3.Text = "Wave Type";
            // 
            // groupBox4
            // 
            this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Controls.Add(this.m_cywave1);
            this.groupBox4.Controls.Add(this.m_cbWave1Type);
            this.groupBox4.Controls.Add(this.m_nudAmplitude1);
            this.groupBox4.Controls.Add(this.m_nudDCOffset1);
            this.groupBox4.Controls.Add(this.m_nudNumSamples1);
            this.groupBox4.Controls.Add(this.m_lblAmp1);
            this.groupBox4.Controls.Add(this.m_lblNumSamp1);
            this.groupBox4.Controls.Add(this.m_lblDCOff1);
            this.groupBox4.Location = new System.Drawing.Point(9, 77);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(518, 187);
            this.groupBox4.TabIndex = 43;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Waveform 1";
            // 
            // label4
            // 
            this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(420, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(63, 13);
            this.label4.TabIndex = 40;
            this.label4.Text = "Wave Type";
            // 
            // CyWaveDacControl
            // 
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.m_cbImplementation);
            this.Name = "CyWaveDacControl";
            this.Size = new System.Drawing.Size(541, 475);
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDCOffset2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumSamples2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudAmplitude2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudDCOffset1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudNumSamples1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudAmplitude1)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_nudSPS)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
        #endregion
        private ComboBox m_cbImplementation;
        private Label m_lblDCOff2;
        private Label m_lblAmp2;
        private ComboBox m_cbWave2Type;
        private CyNumericUpDown m_nudDCOffset2;
        private Label m_lblNumSamp2;
        private CyNumericUpDown m_nudNumSamples2;
        private CyNumericUpDown m_nudAmplitude2;
        private Label m_lblDCOff1;
        private Label m_lblAmp1;
        private ComboBox m_cbWave1Type;
        private CyNumericUpDown m_nudDCOffset1;
        private Label m_lblNumSamp1;
        private CyNumericUpDown m_nudNumSamples1;
        private CyNumericUpDown m_nudAmplitude1;
        private cywaveformeditor m_cywave1;
        private cywaveformeditor m_cywave2;
        private GroupBox groupBox2;
        private CyNumericUpDown m_nudSPS;
        private RadioButton m_rbInternalClock;
        private RadioButton m_rbExternalClock;
        private Label label1;
        private Label label2;
        private GroupBox groupBox3;
        private Label label3;
        private GroupBox groupBox4;
        private Label label4;
    }
}
