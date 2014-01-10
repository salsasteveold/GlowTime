namespace MultAcc_v1_00
{
    partial class MultAccControl
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
            this.ConversionFunctionGroupbox = new System.Windows.Forms.GroupBox();
            this.HexLabel = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.Q23DecimalLabel = new System.Windows.Forms.Label();
            this.Q23HexInput = new System.Windows.Forms.TextBox();
            this.Q23DecimalInput = new System.Windows.Forms.TextBox();
            this.InputToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.ArraySizeUpDown = new System.Windows.Forms.NumericUpDown();
            this.BlockModeGroupBox = new System.Windows.Forms.GroupBox();
            this.BigEndianCompilerCheckBox = new System.Windows.Forms.CheckBox();
            this.ArraySizelabel = new System.Windows.Forms.Label();
            this.EnableBlockCheckBox = new System.Windows.Forms.CheckBox();
            this.HardwareBlockCompleteCheckBox = new System.Windows.Forms.CheckBox();
            this.ConversionFunctionGroupbox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ArraySizeUpDown)).BeginInit();
            this.BlockModeGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // ConversionFunctionGroupbox
            // 
            this.ConversionFunctionGroupbox.Controls.Add(this.HexLabel);
            this.ConversionFunctionGroupbox.Controls.Add(this.button1);
            this.ConversionFunctionGroupbox.Controls.Add(this.Q23DecimalLabel);
            this.ConversionFunctionGroupbox.Controls.Add(this.Q23HexInput);
            this.ConversionFunctionGroupbox.Controls.Add(this.Q23DecimalInput);
            this.ConversionFunctionGroupbox.Location = new System.Drawing.Point(3, 144);
            this.ConversionFunctionGroupbox.Name = "ConversionFunctionGroupbox";
            this.ConversionFunctionGroupbox.Size = new System.Drawing.Size(271, 64);
            this.ConversionFunctionGroupbox.TabIndex = 2;
            this.ConversionFunctionGroupbox.TabStop = false;
            this.ConversionFunctionGroupbox.Text = "Q0.23 Conversion Calculator";
            // 
            // HexLabel
            // 
            this.HexLabel.AutoSize = true;
            this.HexLabel.Location = new System.Drawing.Point(150, 15);
            this.HexLabel.Name = "HexLabel";
            this.HexLabel.Size = new System.Drawing.Size(26, 13);
            this.HexLabel.TabIndex = 5;
            this.HexLabel.Text = "Hex";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(190, 28);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Calculate";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // Q23DecimalLabel
            // 
            this.Q23DecimalLabel.AutoSize = true;
            this.Q23DecimalLabel.Location = new System.Drawing.Point(6, 16);
            this.Q23DecimalLabel.Name = "Q23DecimalLabel";
            this.Q23DecimalLabel.Size = new System.Drawing.Size(45, 13);
            this.Q23DecimalLabel.TabIndex = 4;
            this.Q23DecimalLabel.Text = "Decimal";
            // 
            // Q23HexInput
            // 
            this.Q23HexInput.Location = new System.Drawing.Point(108, 31);
            this.Q23HexInput.Name = "Q23HexInput";
            this.Q23HexInput.Size = new System.Drawing.Size(68, 20);
            this.Q23HexInput.TabIndex = 2;
            this.Q23HexInput.Text = "0x00000000";
            this.InputToolTip.SetToolTip(this.Q23HexInput, "Hexadecimal input for the Q0.23 calculator.\r\nQ0.23 restricts the numbers between " +
                    "0xFF800000 and 0x007FFFFF\r\nNumbers entered here are automatically truncated to 2" +
                    "4 bits");
            this.Q23HexInput.TextChanged += new System.EventHandler(this.Q23HexInput_TextChanged);
            this.Q23HexInput.Leave += new System.EventHandler(this.Q23HexInput_Leave);
            // 
            // Q23DecimalInput
            // 
            this.Q23DecimalInput.Location = new System.Drawing.Point(9, 31);
            this.Q23DecimalInput.Name = "Q23DecimalInput";
            this.Q23DecimalInput.Size = new System.Drawing.Size(77, 20);
            this.Q23DecimalInput.TabIndex = 0;
            this.Q23DecimalInput.Text = "0.000000000";
            this.InputToolTip.SetToolTip(this.Q23DecimalInput, "Decimal input for the Q0.23 calculator.\r\nQ0.23 restricts the numbers between -1 a" +
                    "nd 0.999999880791\r\nNumbers entered here are automatically converted to the\r\nclos" +
                    "est Q0.23 representation");
            this.Q23DecimalInput.TextChanged += new System.EventHandler(this.Q23DecimalInput_TextChanged);
            this.Q23DecimalInput.Enter += new System.EventHandler(this.Q23DecimalInput_Enter);
            this.Q23DecimalInput.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Q23DecimalInput_KeyPress);
            this.Q23DecimalInput.Leave += new System.EventHandler(this.Q23DecimalInput_Leave);
            // 
            // InputToolTip
            // 
            this.InputToolTip.AutoPopDelay = 15000;
            this.InputToolTip.InitialDelay = 200;
            this.InputToolTip.ReshowDelay = 100;
            this.InputToolTip.Popup += new System.Windows.Forms.PopupEventHandler(this.InputToolTip_Popup);
            // 
            // ArraySizeUpDown
            // 
            this.ArraySizeUpDown.Location = new System.Drawing.Point(6, 32);
            this.ArraySizeUpDown.Maximum = new decimal(new int[] {
            1023,
            0,
            0,
            0});
            this.ArraySizeUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ArraySizeUpDown.Name = "ArraySizeUpDown";
            this.ArraySizeUpDown.Size = new System.Drawing.Size(80, 20);
            this.ArraySizeUpDown.TabIndex = 4;
            this.InputToolTip.SetToolTip(this.ArraySizeUpDown, "The desired number of 32 bit array elements in each block.  Valid inputs are from" +
                    " 1 to 1023.");
            this.ArraySizeUpDown.Value = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.ArraySizeUpDown.ValueChanged += new System.EventHandler(this.ArraySizeUpDown_ValueChanged);
            // 
            // BlockModeGroupBox
            // 
            this.BlockModeGroupBox.Controls.Add(this.HardwareBlockCompleteCheckBox);
            this.BlockModeGroupBox.Controls.Add(this.BigEndianCompilerCheckBox);
            this.BlockModeGroupBox.Controls.Add(this.ArraySizelabel);
            this.BlockModeGroupBox.Controls.Add(this.ArraySizeUpDown);
            this.BlockModeGroupBox.Location = new System.Drawing.Point(3, 3);
            this.BlockModeGroupBox.Name = "BlockModeGroupBox";
            this.BlockModeGroupBox.Size = new System.Drawing.Size(271, 107);
            this.BlockModeGroupBox.TabIndex = 5;
            this.BlockModeGroupBox.TabStop = false;
            this.BlockModeGroupBox.Text = "Block Processing Mode Options";
            // 
            // BigEndianCompilerCheckBox
            // 
            this.BigEndianCompilerCheckBox.AutoSize = true;
            this.BigEndianCompilerCheckBox.Location = new System.Drawing.Point(6, 58);
            this.BigEndianCompilerCheckBox.Name = "BigEndianCompilerCheckBox";
            this.BigEndianCompilerCheckBox.Size = new System.Drawing.Size(177, 17);
            this.BigEndianCompilerCheckBox.TabIndex = 7;
            this.BigEndianCompilerCheckBox.Text = "Compiler uses Big Endian format";
            this.BigEndianCompilerCheckBox.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.InputToolTip.SetToolTip(this.BigEndianCompilerCheckBox, "Checking this box enables Endian swapping on the DMA channels.  The MACC hardware" +
                    " is little endian.");
            this.BigEndianCompilerCheckBox.UseVisualStyleBackColor = true;
            this.BigEndianCompilerCheckBox.CheckedChanged += new System.EventHandler(this.BigEndianCompilerCheckBox_CheckedChanged);
            // 
            // ArraySizelabel
            // 
            this.ArraySizelabel.AutoSize = true;
            this.ArraySizelabel.Location = new System.Drawing.Point(3, 16);
            this.ArraySizelabel.Name = "ArraySizelabel";
            this.ArraySizelabel.Size = new System.Drawing.Size(220, 13);
            this.ArraySizelabel.TabIndex = 6;
            this.ArraySizelabel.Text = "Desired number of elements in the A/B arrays";
            this.ArraySizelabel.Click += new System.EventHandler(this.ArraySizelabel_Click);
            // 
            // EnableBlockCheckBox
            // 
            this.EnableBlockCheckBox.AutoSize = true;
            this.EnableBlockCheckBox.Location = new System.Drawing.Point(3, 214);
            this.EnableBlockCheckBox.Name = "EnableBlockCheckBox";
            this.EnableBlockCheckBox.Size = new System.Drawing.Size(144, 17);
            this.EnableBlockCheckBox.TabIndex = 5;
            this.EnableBlockCheckBox.Text = "Enable Block Processing";
            this.EnableBlockCheckBox.UseVisualStyleBackColor = true;
            this.EnableBlockCheckBox.Visible = false;
            this.EnableBlockCheckBox.CheckedChanged += new System.EventHandler(this.EnableBlockCheckBox_CheckedChanged);
            // 
            // HardwareBlockCompleteCheckBox
            // 
            this.HardwareBlockCompleteCheckBox.AutoSize = true;
            this.HardwareBlockCompleteCheckBox.Location = new System.Drawing.Point(6, 82);
            this.HardwareBlockCompleteCheckBox.Name = "HardwareBlockCompleteCheckBox";
            this.HardwareBlockCompleteCheckBox.Size = new System.Drawing.Size(211, 17);
            this.HardwareBlockCompleteCheckBox.TabIndex = 8;
            this.HardwareBlockCompleteCheckBox.Text = "Enable hardware block complete signal";
            this.InputToolTip.SetToolTip(this.HardwareBlockCompleteCheckBox, "Enables an optional terminal that can be connected to an interrupt or DMA request" +
                    ".  This signal asserts when the MACC is done processing the current block.");
            this.HardwareBlockCompleteCheckBox.UseVisualStyleBackColor = true;
            this.HardwareBlockCompleteCheckBox.CheckedChanged += new System.EventHandler(this.HardwareBlockCompleteCheckBox_CheckedChanged);
            // 
            // MultAccControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.BlockModeGroupBox);
            this.Controls.Add(this.ConversionFunctionGroupbox);
            this.Controls.Add(this.EnableBlockCheckBox);
            this.Name = "MultAccControl";
            this.Size = new System.Drawing.Size(301, 234);
            this.ConversionFunctionGroupbox.ResumeLayout(false);
            this.ConversionFunctionGroupbox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ArraySizeUpDown)).EndInit();
            this.BlockModeGroupBox.ResumeLayout(false);
            this.BlockModeGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox ConversionFunctionGroupbox;
        private System.Windows.Forms.TextBox Q23DecimalInput;
        private System.Windows.Forms.Label HexLabel;
        private System.Windows.Forms.Label Q23DecimalLabel;
        private System.Windows.Forms.TextBox Q23HexInput;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolTip InputToolTip;
        private System.Windows.Forms.NumericUpDown ArraySizeUpDown;
        private System.Windows.Forms.GroupBox BlockModeGroupBox;
        private System.Windows.Forms.Label ArraySizelabel;
        private System.Windows.Forms.CheckBox EnableBlockCheckBox;
        private System.Windows.Forms.CheckBox BigEndianCompilerCheckBox;
        private System.Windows.Forms.CheckBox HardwareBlockCompleteCheckBox;

    }
}
