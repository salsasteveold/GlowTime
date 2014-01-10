using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace MultAcc_v1_00
{
    public partial class MultAccControl : UserControl
    {
        private MultAccParameters parameters;

        public MultAccControl(MultAccParameters parameters)
        {
            InitializeComponent();
            this.parameters = parameters;
            UpdateForm();
        }

        //private void m_Resistance_SelectedIndexChanged(object sender, EventArgs e)
        //{
        //    parameters.ReferenceResistor = Convert.ToUInt32(m_Resistance.SelectedItem);
        //}

        //Update Form Function
        // Updates form with saved parameters when the GUI is opened.
        public void UpdateForm()
        {
            //m_comboStartDay.SelectedItem = parameters.StartDayOfWeek;

            //m_checkDstEnable.Checked = parameters.DstEnable;

            //m_Resistance.SelectedItem = parameters.ReferenceResistor;

            //ShowOverflowCheckbox.Checked = parameters.ShowOverflow;
            //ShowNotBusyCheckbox.Checked = parameters.ShowNotBusy;
            Q23HexInput.Text = Convert.ToString(String.Format("0x{0:X8}", parameters.CalculatorValue));
            Q23HexInput_Leave(null, null);
            EnableBlockCheckBox.Checked = parameters.EnableBlock;
            BigEndianCompilerCheckBox.Checked = parameters.BigEndianCompiler;
            BigEndianCompilerCheckBox.Enabled = parameters.EnableBlock;
            ArraySizeUpDown.Enabled = parameters.EnableBlock;
            ArraySizeUpDown.Value = Convert.ToDecimal(parameters.ArraySize);
            ArraySizelabel.Enabled = parameters.EnableBlock;
            HardwareBlockCompleteCheckBox.Checked = parameters.ShowBlockDone;
        }

        private void Q23DecimalInput_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void Q23DecimalInput_Leave(object sender, EventArgs e)
        {
            Double temp;

            try
            {

                if (Q23DecimalInput.Text != "")
                {
                    temp = Convert.ToDouble(Q23DecimalInput.Text);
                }
                else
                {
                    temp = 0.0;
                }

                if (temp < -1.0)
                {
                    temp = -1.0;
                }
                else if (temp > (1.0 - (1.0 / (Math.Pow(2, 23)))))
                {
                    temp = (1.0 - (1.0 / (Math.Pow(2, 23))));
                }

                temp = Math.Round(temp * Math.Pow(2, 23));
                Q23HexInput.Text = Convert.ToString(String.Format("0x{0:X8}", Convert.ToInt32(temp)));
                parameters.CalculatorValue = Convert.ToInt32(temp);
                temp = temp / Math.Pow(2, 23);

                Q23DecimalInput.Text = temp.ToString("F9");
            }
            catch(Exception)
            {
                MessageBox.Show("The entered value does not follow the [-]X.XXXXXX format");
                temp = 0;
                Q23DecimalInput.Text = temp.ToString("F9");
                Q23HexInput.Text = Convert.ToString(String.Format("0x{0:X8}", 0));
                parameters.CalculatorValue = Convert.ToInt32(temp);
            }
        }

        //private void ShowOverflowCheckbox_CheckedChanged(object sender, EventArgs e)
        //{
        //    parameters.ShowOverflow = ShowOverflowCheckbox.Checked;
        //}

        //private void ShowNotBusyCheckbox_CheckedChanged(object sender, EventArgs e)
        //{
        //    parameters.ShowNotBusy = ShowNotBusyCheckbox.Checked;
        //}

        private void Q23DecimalInput_Enter(object sender, EventArgs e)
        {
            
        }

        private void Q23DecimalInput_KeyPress(object sender, KeyPressEventArgs e)
        {
            // we only want to handle decimal numbers, with only 1 optional decimal point and negative sign at the beginning only
            // Marking it as "handled" means that no other even processing needs to take place
            // its basically the way to have the key press die here in this method

            // so, if its not a control key (like backspace) and its not a digit, and its not a '.' or '-', then eat it
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && e.KeyChar != '.' && e.KeyChar != '-')
            {
                e.Handled = true;
            }

            // if its a '.' that shows up already in the string
            // eat it
            if (e.KeyChar == '.' && (sender as TextBox).Text.IndexOf('.') > -1)
            {
                e.Handled = true;
            }

            // and if its a '-' and the length of the text is greater than zero (so minus is not the first character)
            // eat it ((sender as TextBox).TextLength > 0)
            // changed it back to "more than one" since the index of greater than zero was a 
            // pain in the ass to use.
            if (e.KeyChar == '-' && (sender as TextBox).Text.IndexOf('-') > -1)
            {
                e.Handled = true;
            }
        }

        private void Q23HexInput_Leave(object sender, EventArgs e)
        {
            String temp;
            double numberDub;
            Int32 numberInt;

            try
            {
                if (Q23HexInput.Text != "")
                {
                    temp = Q23HexInput.Text;

                    if (temp.StartsWith("0x", StringComparison.CurrentCultureIgnoreCase))
                    {
                        temp = temp.Substring(2);
                    }
                    else if (temp.StartsWith("x", StringComparison.CurrentCultureIgnoreCase))
                    {
                        temp = temp.Substring(1);
                    }

                   numberInt = Int32.Parse(temp, System.Globalization.NumberStyles.HexNumber);

                    if(numberInt > (Math.Pow(2, 23)-1))
                    {
                        numberInt = Convert.ToInt32(Math.Pow(2, 23) - 1);
                    }
                    else if (numberInt < -Math.Pow(2, 23))
                    {
                        numberInt = Convert.ToInt32(-Math.Pow(2, 23));
                    }

                    parameters.CalculatorValue = numberInt;

                   Q23HexInput.Text = Convert.ToString(String.Format("0x{0:X8}", numberInt));

                   numberDub = ((double) numberInt) / Math.Pow(2, 23);

                   Q23DecimalInput.Text = numberDub.ToString("F9");
                }
                else
                {
                    numberInt = 0;
                    numberDub = 0;
                    Q23HexInput.Text = Convert.ToString(String.Format("0x{0:X8}", numberInt));
                    Q23DecimalInput.Text = numberDub.ToString("F9");
                    parameters.CalculatorValue = numberInt;
                }
            }
            catch (Exception)
            {
                numberInt = 0;
                numberDub = 0;
                Q23HexInput.Text = Convert.ToString(String.Format("0x{0:X8}", numberInt));
                Q23DecimalInput.Text = numberDub.ToString("F9");
                parameters.CalculatorValue = numberInt;
                MessageBox.Show("The entered value does not follow the 0xYYYYYYYY format");
            }

            

           // Q23DecimalInput.Text = Convert.ToString(temp);
        }

        private void Q23HexInput_TextChanged(object sender, EventArgs e)
        {

        }

        private void InputToolTip_Popup(object sender, PopupEventArgs e)
        {

        }

        private void ArraySizelabel_Click(object sender, EventArgs e)
        {

        }

        private void EnableBlockCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            parameters.EnableBlock = EnableBlockCheckBox.Checked;
            ArraySizeUpDown.Enabled = EnableBlockCheckBox.Checked;
            BigEndianCompilerCheckBox.Enabled = EnableBlockCheckBox.Checked;
            ArraySizelabel.Enabled = EnableBlockCheckBox.Checked;
        }

        private void BigEndianCompilerCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            parameters.BigEndianCompiler = BigEndianCompilerCheckBox.Checked;
        }

        private void ArraySizeUpDown_ValueChanged(object sender, EventArgs e)
        {
            parameters.ArraySize = Convert.ToUInt16(ArraySizeUpDown.Value);
        }

        private void HardwareBlockCompleteCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            parameters.ShowBlockDone = HardwareBlockCompleteCheckBox.Checked;
        }
    }
}
