using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace MultAcc_v1_00
{
    #region Component Parameters Names
    public class CyParamNames
    {
        //public const string DST_ENABLE = "DstEnable";
        //public const string START_OF_WEEK = "StartOfWeek";
        //public const string REFERENCE_RESISTOR = "ReferenceResistor";
        public const string CALCULATOR_VALUE = "CalculatorValue";
        public const string BIG_ENDIAN_COMPILER = "BigEndianCompiler";
        public const string ENABLE_BLOCK = "EnableBlock";
        public const string ARRAY_SIZE = "ArraySize";
        public const string SHOW_BLOCK_DONE = "ShowBlockDone";
    }
    #endregion

    public class MultAccParameters
    {
        private readonly ICyInstEdit_v1 m_edit;
        public MultAccControl control;

        //Local Parameter Variables
        //private bool m_dstEnable;
        //private DayOfWeek m_day;
        //private UInt32 m_RefRes;
        private Int32 m_CalculatorValue;
        private bool m_BigEndianCompiler;
        private bool m_EnableBlock;
        private UInt16 m_ArraySize;
        private bool m_ShowBlockDone;

        //Get Set Function for each parameter
        #region Class Properties
        //public bool DstEnable
        //{
        //    get { return m_dstEnable; }
        //    set
        //    {
        //        m_dstEnable = value;
        //        if (m_edit != null)
        //        {
        //            m_edit.SetParamExpr(CyParamNames.DST_ENABLE, m_dstEnable.ToString().ToLower());
        //            m_edit.CommitParamExprs();
        //        }
        //    }
        //}

        //public UInt32 ReferenceResistor
        //{
        //    get { return m_RefRes; }
        //    set
        //    {
        //        m_RefRes = value;
        //        if (m_edit != null)
        //        {
        //            m_edit.SetParamExpr(CyParamNames.REFERENCE_RESISTOR, m_RefRes.ToString());
        //            m_edit.CommitParamExprs();
        //        }
        //    }
        //}

        //public DayOfWeek StartDayOfWeek
        //{
        //    get { return m_day; }
        //    set
        //    {
        //        m_day = value;
        //        if (m_edit != null)
        //        {
        //            m_edit.SetParamExpr(CyParamNames.START_OF_WEEK, m_day.ToString());
        //            m_edit.CommitParamExprs();
        //        }
        //    }
        //}

        public Int32 CalculatorValue
        {
            get
            {
                return m_CalculatorValue;
            }

            set
            {
                m_CalculatorValue = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.CALCULATOR_VALUE, m_CalculatorValue.ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public bool BigEndianCompiler
        {
            get
            {
                return m_BigEndianCompiler;
            }

            set
            {
                m_BigEndianCompiler = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.BIG_ENDIAN_COMPILER, m_BigEndianCompiler.ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public bool EnableBlock
        {
            get
            {
                return m_EnableBlock;
            }

            set
            {
                m_EnableBlock = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.ENABLE_BLOCK, m_EnableBlock.ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        public UInt16 ArraySize
        {
            get
            {
                return m_ArraySize;
            }

            set
            {
                m_ArraySize = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.ARRAY_SIZE, m_ArraySize.ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }
        
        public bool ShowBlockDone
        {
            get
            {
                return m_ShowBlockDone;
            }

            set
            {
                m_ShowBlockDone = value;
                if (m_edit != null)
                {
                    m_edit.SetParamExpr(CyParamNames.SHOW_BLOCK_DONE, m_ShowBlockDone.ToString());
                    m_edit.CommitParamExprs();
                }
            }
        }

        #endregion


        public MultAccParameters(ICyInstEdit_v1 m_edit)
        {
            this.m_edit = m_edit;
			GetParams();
        }

        //Get Commited Parameters from Customizer
        public void GetParams()
        {
            if (m_edit != null)
            {
                //try
                //{
                //    m_dstEnable = bool.Parse(m_edit.GetCommittedParam(CyParamNames.DST_ENABLE).Value);
                //}
                //catch (Exception) { }
                //try
                //{
                //    m_day = (DayOfWeek)Enum.Parse(typeof(DayOfWeek), Convert.ToString(m_edit.GetCommittedParam(CyParamNames.START_OF_WEEK).Value));
                //}
                //catch (Exception) { }
                //try
                //{
                //    m_RefRes = Convert.ToUInt32(m_edit.GetCommittedParam(CyParamNames.REFERENCE_RESISTOR).Value);//UInt32.Parse(m_edit.GetCommittedParam(CyParamNames.REFERENCE_RESISTOR).Value);
                //}
                //catch (Exception) { }

                try
                {
                    m_CalculatorValue = Convert.ToInt32(m_edit.GetCommittedParam(CyParamNames.CALCULATOR_VALUE).Value);
                }
                catch (Exception) { }

                try
                {
                    m_BigEndianCompiler = Convert.ToBoolean(m_edit.GetCommittedParam(CyParamNames.BIG_ENDIAN_COMPILER).Value);
                }
                catch (Exception) { }

                try
                {
                    m_EnableBlock = Convert.ToBoolean(m_edit.GetCommittedParam(CyParamNames.ENABLE_BLOCK).Value);
                }
                catch (Exception) { }

                try
                {
                    m_ArraySize = Convert.ToUInt16(m_edit.GetCommittedParam(CyParamNames.ARRAY_SIZE).Value);
                }
                catch (Exception) { }

                try
                {
                    m_ShowBlockDone = Convert.ToBoolean(m_edit.GetCommittedParam(CyParamNames.SHOW_BLOCK_DONE).Value);
                }
                catch (Exception) { }
            }
        }

        public void CommitParams()
        {
            if (m_edit != null)
            {
                if (!m_edit.CommitParamExprs())
                {
                    MessageBox.Show("Error in Commiting Parameters");
                }
            }
        }
    }
}