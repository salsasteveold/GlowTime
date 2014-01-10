namespace KEES_ADC_SAR_v2_0
{
    partial class CySARADCControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.gbModes = new System.Windows.Forms.GroupBox();
            this.lblActualConversionRate = new System.Windows.Forms.Label();
            this.lblConversionRateLabel = new System.Windows.Forms.Label();
            this.lblNoRate = new System.Windows.Forms.Label();
            this.lblNoFreq = new System.Windows.Forms.Label();
            this.tbClockFreq = new System.Windows.Forms.TextBox();
            this.numSampleRate = new System.Windows.Forms.NumericUpDown();
            this.Convertsion_label = new System.Windows.Forms.Label();
            this.Clock_label = new System.Windows.Forms.Label();
            this.cbResolution = new System.Windows.Forms.ComboBox();
            this.ADC_Resolution_label = new System.Windows.Forms.Label();
            this.m_gbClockSource = new System.Windows.Forms.GroupBox();
            this.rbExternal = new System.Windows.Forms.RadioButton();
            this.rbInternal = new System.Windows.Forms.RadioButton();
            this.m_gbSOC = new System.Windows.Forms.GroupBox();
            this.m_rbHardwareTrigerr = new System.Windows.Forms.RadioButton();
            this.rbSoftwareTrigerr = new System.Windows.Forms.RadioButton();
            this.rbFreeRunning = new System.Windows.Forms.RadioButton();
            this.cbReference = new System.Windows.Forms.ComboBox();
            this.cbInputRange = new System.Windows.Forms.ComboBox();
            this.gbInput = new System.Windows.Forms.GroupBox();
            this.numRefVoltage = new System.Windows.Forms.NumericUpDown();
            this.Volts_label = new System.Windows.Forms.Label();
            this.External_Ref_label = new System.Windows.Forms.Label();
            this.Reference_label = new System.Windows.Forms.Label();
            this.ADC_Input_Range_label = new System.Windows.Forms.Label();
            this.errorProvider = new System.Windows.Forms.ErrorProvider(this.components);
            this.chbNextOut = new System.Windows.Forms.CheckBox();
            this.gbModes.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSampleRate)).BeginInit();
            this.m_gbClockSource.SuspendLayout();
            this.m_gbSOC.SuspendLayout();
            this.gbInput.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numRefVoltage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).BeginInit();
            this.SuspendLayout();
            // 
            // gbModes
            // 
            this.gbModes.Controls.Add(this.lblActualConversionRate);
            this.gbModes.Controls.Add(this.lblConversionRateLabel);
            this.gbModes.Controls.Add(this.lblNoRate);
            this.gbModes.Controls.Add(this.lblNoFreq);
            this.gbModes.Controls.Add(this.tbClockFreq);
            this.gbModes.Controls.Add(this.numSampleRate);
            this.gbModes.Controls.Add(this.Convertsion_label);
            this.gbModes.Controls.Add(this.Clock_label);
            this.gbModes.Controls.Add(this.cbResolution);
            this.gbModes.Controls.Add(this.ADC_Resolution_label);
            this.gbModes.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbModes.Location = new System.Drawing.Point(13, 3);
            this.gbModes.Name = "gbModes";
            this.gbModes.Size = new System.Drawing.Size(276, 143);
            this.gbModes.TabIndex = 0;
            this.gbModes.TabStop = false;
            this.gbModes.Text = "Modes";
            // 
            // lblActualConversionRate
            // 
            this.lblActualConversionRate.AutoSize = true;
            this.lblActualConversionRate.Location = new System.Drawing.Point(148, 79);
            this.lblActualConversionRate.Name = "lblActualConversionRate";
            this.lblActualConversionRate.Size = new System.Drawing.Size(35, 13);
            this.lblActualConversionRate.TabIndex = 19;
            this.lblActualConversionRate.Text = "label2";
            // 
            // lblConversionRateLabel
            // 
            this.lblConversionRateLabel.AutoSize = true;
            this.lblConversionRateLabel.Location = new System.Drawing.Point(17, 79);
            this.lblConversionRateLabel.Name = "lblConversionRateLabel";
            this.lblConversionRateLabel.Size = new System.Drawing.Size(121, 13);
            this.lblConversionRateLabel.TabIndex = 18;
            this.lblConversionRateLabel.Text = "Actual conv. rate (SPS):";
            // 
            // lblNoRate
            // 
            this.lblNoRate.AutoSize = true;
            this.lblNoRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblNoRate.Location = new System.Drawing.Point(146, 51);
            this.lblNoRate.Name = "lblNoRate";
            this.lblNoRate.Size = new System.Drawing.Size(109, 13);
            this.lblNoRate.TabIndex = 17;
            this.lblNoRate.Text = "UNKNOWN RATE";
            // 
            // lblNoFreq
            // 
            this.lblNoFreq.AutoSize = true;
            this.lblNoFreq.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblNoFreq.Location = new System.Drawing.Point(146, 106);
            this.lblNoFreq.Name = "lblNoFreq";
            this.lblNoFreq.Size = new System.Drawing.Size(109, 13);
            this.lblNoFreq.TabIndex = 16;
            this.lblNoFreq.Text = "UNKNOWN FREQ";
            // 
            // tbClockFreq
            // 
            this.errorProvider.SetIconAlignment(this.tbClockFreq, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.tbClockFreq.Location = new System.Drawing.Point(150, 103);
            this.tbClockFreq.Name = "tbClockFreq";
            this.tbClockFreq.ReadOnly = true;
            this.tbClockFreq.Size = new System.Drawing.Size(85, 20);
            this.tbClockFreq.TabIndex = 3;
            this.tbClockFreq.Visible = false;
            this.tbClockFreq.TextChanged += new System.EventHandler(this.tbClockFreq_TextChanged);
            // 
            // numSampleRate
            // 
            this.errorProvider.SetIconAlignment(this.numSampleRate, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.numSampleRate.Location = new System.Drawing.Point(150, 49);
            this.numSampleRate.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numSampleRate.Name = "numSampleRate";
            this.numSampleRate.Size = new System.Drawing.Size(85, 20);
            this.numSampleRate.TabIndex = 2;
            this.numSampleRate.Value = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            // 
            // Convertsion_label
            // 
            this.Convertsion_label.AutoSize = true;
            this.Convertsion_label.Location = new System.Drawing.Point(24, 51);
            this.Convertsion_label.Name = "Convertsion_label";
            this.Convertsion_label.Size = new System.Drawing.Size(114, 13);
            this.Convertsion_label.TabIndex = 12;
            this.Convertsion_label.Text = "Conversion rate (SPS):";
            // 
            // Clock_label
            // 
            this.Clock_label.AutoSize = true;
            this.Clock_label.Location = new System.Drawing.Point(23, 106);
            this.Clock_label.Name = "Clock_label";
            this.Clock_label.Size = new System.Drawing.Size(115, 13);
            this.Clock_label.TabIndex = 9;
            this.Clock_label.Text = "Clock frequency (kHz):";
            // 
            // cbResolution
            // 
            this.cbResolution.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbResolution.FormattingEnabled = true;
            this.errorProvider.SetIconAlignment(this.cbResolution, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.cbResolution.Location = new System.Drawing.Point(150, 22);
            this.cbResolution.Name = "cbResolution";
            this.cbResolution.Size = new System.Drawing.Size(86, 21);
            this.cbResolution.TabIndex = 1;
            this.cbResolution.SelectedIndexChanged += new System.EventHandler(this.m_cbResolution_SelectedIndexChanged);
            // 
            // ADC_Resolution_label
            // 
            this.ADC_Resolution_label.AutoSize = true;
            this.ADC_Resolution_label.Location = new System.Drawing.Point(53, 25);
            this.ADC_Resolution_label.Name = "ADC_Resolution_label";
            this.ADC_Resolution_label.Size = new System.Drawing.Size(85, 13);
            this.ADC_Resolution_label.TabIndex = 7;
            this.ADC_Resolution_label.Text = "Resolution (bits):";
            // 
            // m_gbClockSource
            // 
            this.m_gbClockSource.Controls.Add(this.rbExternal);
            this.m_gbClockSource.Controls.Add(this.rbInternal);
            this.m_gbClockSource.ForeColor = System.Drawing.SystemColors.ControlText;
            this.m_gbClockSource.Location = new System.Drawing.Point(295, 91);
            this.m_gbClockSource.Name = "m_gbClockSource";
            this.m_gbClockSource.Size = new System.Drawing.Size(114, 55);
            this.m_gbClockSource.TabIndex = 3;
            this.m_gbClockSource.TabStop = false;
            this.m_gbClockSource.Text = "Clock source";
            // 
            // rbExternal
            // 
            this.rbExternal.AutoSize = true;
            this.rbExternal.Location = new System.Drawing.Point(6, 34);
            this.rbExternal.Name = "rbExternal";
            this.rbExternal.Size = new System.Drawing.Size(63, 17);
            this.rbExternal.TabIndex = 1;
            this.rbExternal.Text = "External";
            this.rbExternal.UseVisualStyleBackColor = true;
            // 
            // rbInternal
            // 
            this.rbInternal.AutoSize = true;
            this.rbInternal.Location = new System.Drawing.Point(6, 14);
            this.rbInternal.Name = "rbInternal";
            this.rbInternal.Size = new System.Drawing.Size(60, 17);
            this.rbInternal.TabIndex = 0;
            this.rbInternal.Text = "Internal";
            this.rbInternal.UseVisualStyleBackColor = true;
            this.rbInternal.CheckedChanged += new System.EventHandler(this.rbInternal_CheckedChanged);
            // 
            // m_gbSOC
            // 
            this.m_gbSOC.Controls.Add(this.m_rbHardwareTrigerr);
            this.m_gbSOC.Controls.Add(this.rbSoftwareTrigerr);
            this.m_gbSOC.Controls.Add(this.rbFreeRunning);
            this.m_gbSOC.ForeColor = System.Drawing.SystemColors.ControlText;
            this.m_gbSOC.Location = new System.Drawing.Point(295, 3);
            this.m_gbSOC.Name = "m_gbSOC";
            this.m_gbSOC.Size = new System.Drawing.Size(114, 83);
            this.m_gbSOC.TabIndex = 2;
            this.m_gbSOC.TabStop = false;
            this.m_gbSOC.Text = "Sample mode";
            // 
            // m_rbHardwareTrigerr
            // 
            this.m_rbHardwareTrigerr.AutoSize = true;
            this.m_rbHardwareTrigerr.Location = new System.Drawing.Point(6, 61);
            this.m_rbHardwareTrigerr.Name = "m_rbHardwareTrigerr";
            this.m_rbHardwareTrigerr.Size = new System.Drawing.Size(103, 17);
            this.m_rbHardwareTrigerr.TabIndex = 2;
            this.m_rbHardwareTrigerr.TabStop = true;
            this.m_rbHardwareTrigerr.Text = "Hardware trigger";
            this.m_rbHardwareTrigerr.UseVisualStyleBackColor = true;
            this.m_rbHardwareTrigerr.CheckedChanged += new System.EventHandler(this.sampleMode_CheckedChanged);
            // 
            // rbSoftwareTrigerr
            // 
            this.rbSoftwareTrigerr.AutoSize = true;
            this.rbSoftwareTrigerr.Location = new System.Drawing.Point(6, 38);
            this.rbSoftwareTrigerr.Name = "rbSoftwareTrigerr";
            this.rbSoftwareTrigerr.Size = new System.Drawing.Size(99, 17);
            this.rbSoftwareTrigerr.TabIndex = 1;
            this.rbSoftwareTrigerr.Text = "Software trigger";
            this.rbSoftwareTrigerr.UseVisualStyleBackColor = true;
            this.rbSoftwareTrigerr.CheckedChanged += new System.EventHandler(this.sampleMode_CheckedChanged);
            // 
            // rbFreeRunning
            // 
            this.rbFreeRunning.AutoSize = true;
            this.rbFreeRunning.Location = new System.Drawing.Point(6, 15);
            this.rbFreeRunning.Name = "rbFreeRunning";
            this.rbFreeRunning.Size = new System.Drawing.Size(84, 17);
            this.rbFreeRunning.TabIndex = 0;
            this.rbFreeRunning.Text = "Free running";
            this.rbFreeRunning.UseVisualStyleBackColor = true;
            this.rbFreeRunning.CheckedChanged += new System.EventHandler(this.sampleMode_CheckedChanged);
            // 
            // cbReference
            // 
            this.cbReference.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbReference.FormattingEnabled = true;
            this.errorProvider.SetIconAlignment(this.cbReference, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.cbReference.Location = new System.Drawing.Point(124, 42);
            this.cbReference.Name = "cbReference";
            this.cbReference.Size = new System.Drawing.Size(204, 21);
            this.cbReference.TabIndex = 1;
            this.cbReference.SelectedIndexChanged += new System.EventHandler(this.cbReference_SelectedIndexChanged);
            // 
            // cbInputRange
            // 
            this.cbInputRange.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbInputRange.FormattingEnabled = true;
            this.errorProvider.SetIconAlignment(this.cbInputRange, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.cbInputRange.Location = new System.Drawing.Point(124, 15);
            this.cbInputRange.Name = "cbInputRange";
            this.cbInputRange.Size = new System.Drawing.Size(249, 21);
            this.cbInputRange.TabIndex = 0;
            this.cbInputRange.SelectedIndexChanged += new System.EventHandler(this.cbInputRange_SelectedIndexChanged);
            // 
            // gbInput
            // 
            this.gbInput.Controls.Add(this.numRefVoltage);
            this.gbInput.Controls.Add(this.Volts_label);
            this.gbInput.Controls.Add(this.External_Ref_label);
            this.gbInput.Controls.Add(this.cbReference);
            this.gbInput.Controls.Add(this.cbInputRange);
            this.gbInput.Controls.Add(this.Reference_label);
            this.gbInput.Controls.Add(this.ADC_Input_Range_label);
            this.gbInput.ForeColor = System.Drawing.SystemColors.ControlText;
            this.gbInput.Location = new System.Drawing.Point(13, 149);
            this.gbInput.Name = "gbInput";
            this.gbInput.Size = new System.Drawing.Size(396, 97);
            this.gbInput.TabIndex = 4;
            this.gbInput.TabStop = false;
            this.gbInput.Text = "Input";
            // 
            // numRefVoltage
            // 
            this.numRefVoltage.DecimalPlaces = 4;
            this.errorProvider.SetIconAlignment(this.numRefVoltage, System.Windows.Forms.ErrorIconAlignment.MiddleLeft);
            this.numRefVoltage.Increment = new decimal(new int[] {
            1,
            0,
            0,
            196608});
            this.numRefVoltage.Location = new System.Drawing.Point(124, 69);
            this.numRefVoltage.Maximum = new decimal(new int[] {
            1500,
            0,
            0,
            196608});
            this.numRefVoltage.Name = "numRefVoltage";
            this.numRefVoltage.Size = new System.Drawing.Size(84, 20);
            this.numRefVoltage.TabIndex = 2;
            this.numRefVoltage.Value = new decimal(new int[] {
            1024,
            0,
            0,
            196608});
            // 
            // Volts_label
            // 
            this.Volts_label.AutoSize = true;
            this.Volts_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.Volts_label.Location = new System.Drawing.Point(214, 71);
            this.Volts_label.Name = "Volts_label";
            this.Volts_label.Size = new System.Drawing.Size(30, 13);
            this.Volts_label.TabIndex = 13;
            this.Volts_label.Text = "Volts";
            // 
            // External_Ref_label
            // 
            this.External_Ref_label.AutoSize = true;
            this.External_Ref_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.External_Ref_label.Location = new System.Drawing.Point(14, 71);
            this.External_Ref_label.Name = "External_Ref_label";
            this.External_Ref_label.Size = new System.Drawing.Size(94, 13);
            this.External_Ref_label.TabIndex = 14;
            this.External_Ref_label.Text = "Voltage reference:";
            // 
            // Reference_label
            // 
            this.Reference_label.AutoSize = true;
            this.Reference_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.Reference_label.Location = new System.Drawing.Point(48, 45);
            this.Reference_label.Name = "Reference_label";
            this.Reference_label.Size = new System.Drawing.Size(60, 13);
            this.Reference_label.TabIndex = 4;
            this.Reference_label.Text = "Reference:";
            // 
            // ADC_Input_Range_label
            // 
            this.ADC_Input_Range_label.AutoSize = true;
            this.ADC_Input_Range_label.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.ADC_Input_Range_label.Location = new System.Drawing.Point(44, 18);
            this.ADC_Input_Range_label.Name = "ADC_Input_Range_label";
            this.ADC_Input_Range_label.Size = new System.Drawing.Size(64, 13);
            this.ADC_Input_Range_label.TabIndex = 9;
            this.ADC_Input_Range_label.Text = "Input range:";
            // 
            // errorProvider
            // 
            this.errorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.errorProvider.ContainerControl = this;
            // 
            // chbNextOut
            // 
            this.chbNextOut.AutoSize = true;
            this.chbNextOut.Location = new System.Drawing.Point(13, 252);
            this.chbNextOut.Name = "chbNextOut";
            this.chbNextOut.Size = new System.Drawing.Size(117, 17);
            this.chbNextOut.TabIndex = 5;
            this.chbNextOut.Text = "Enable EOS output";
            this.chbNextOut.UseVisualStyleBackColor = true;
            this.chbNextOut.CheckedChanged += new System.EventHandler(this.chbNextOut_CheckedChanged);
            // 
            // CySARADCControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.Controls.Add(this.chbNextOut);
            this.Controls.Add(this.gbInput);
            this.Controls.Add(this.m_gbSOC);
            this.Controls.Add(this.m_gbClockSource);
            this.Controls.Add(this.gbModes);
            this.Name = "CySARADCControl";
            this.Size = new System.Drawing.Size(437, 276);
            this.Load += new System.EventHandler(this.CySARADCControl_Load);
            this.gbModes.ResumeLayout(false);
            this.gbModes.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSampleRate)).EndInit();
            this.m_gbClockSource.ResumeLayout(false);
            this.m_gbClockSource.PerformLayout();
            this.m_gbSOC.ResumeLayout(false);
            this.m_gbSOC.PerformLayout();
            this.gbInput.ResumeLayout(false);
            this.gbInput.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numRefVoltage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gbModes;
        private System.Windows.Forms.Label ADC_Resolution_label;
        private System.Windows.Forms.ComboBox cbResolution;
        private System.Windows.Forms.GroupBox m_gbClockSource;
        private System.Windows.Forms.RadioButton rbExternal;
        private System.Windows.Forms.RadioButton rbInternal;
        private System.Windows.Forms.GroupBox m_gbSOC;
        private System.Windows.Forms.RadioButton rbFreeRunning;
        private System.Windows.Forms.RadioButton rbSoftwareTrigerr;
        private System.Windows.Forms.Label Clock_label;
        private System.Windows.Forms.Label Convertsion_label;
        private System.Windows.Forms.ComboBox cbReference;
        private System.Windows.Forms.ComboBox cbInputRange;
        private System.Windows.Forms.GroupBox gbInput;
        private System.Windows.Forms.Label Volts_label;
        private System.Windows.Forms.Label External_Ref_label;
        private System.Windows.Forms.Label Reference_label;
        private System.Windows.Forms.Label ADC_Input_Range_label;
        private System.Windows.Forms.TextBox tbClockFreq;
        private System.Windows.Forms.NumericUpDown numSampleRate;
        private System.Windows.Forms.NumericUpDown numRefVoltage;
        private System.Windows.Forms.Label lblNoFreq;
        private System.Windows.Forms.ErrorProvider errorProvider;
        private System.Windows.Forms.Label lblNoRate;
        private System.Windows.Forms.CheckBox chbNextOut;
        private System.Windows.Forms.Label lblActualConversionRate;
        private System.Windows.Forms.Label lblConversionRateLabel;
        private System.Windows.Forms.RadioButton m_rbHardwareTrigerr;
    }
}
