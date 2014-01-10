/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;
using WaveDAC8_v1_70;

namespace WaveDAC8_v1_70
{
    [CyCompDevCustomizer()]
    public class CyCustomizer : ICyParamEditHook_v1
    {
        #region ICyParamEditHook_v1 Members
        CyWaveDacEditingControl WaveDacEditingControl = null;
        CyWaveDacControl m_control = null;

        public DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            //Trace.Assert(Debugger.IsAttached);
            m_control = new CyWaveDacControl(edit, termQuery);
            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            WaveDacEditingControl = new CyWaveDacEditingControl(edit, termQuery, m_control);
            CyParamExprDelegate ExprDelegate = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                m_control.UpdateFormFromParams(edit);
            };
            editor.AddCustomPage("Create Waveforms", WaveDacEditingControl, new CyParamExprDelegate(ExprDelegate),"Basic");            
            editor.AddDefaultPage("Built-in", "Built-in");
            DialogResult result = editor.ShowDialog();
            return result;
        }
        

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public bool UseBigEditor
        {
            get { return true; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }

        #endregion

        //Create a new control to add to a tab
        public class CyWaveDacEditingControl : ICyParamEditingControl
        {
            CyWaveDacControl m_control;
            Panel displayControl = new Panel();

            public CyWaveDacEditingControl(ICyInstEdit_v1 inst, ICyTerminalQuery_v1 termquery, CyWaveDacControl control)
            {
                m_control = control;
                displayControl.Dock = DockStyle.Fill;
                displayControl.AutoScroll = true;
                displayControl.AutoScrollMinSize = m_control.Size;

                m_control.Dock = DockStyle.Fill;
                displayControl.Controls.Add(m_control);
            }

            #region ICyParamEditingControl Members
            public Control DisplayControl
            {
                get { return displayControl; }
            }

            public IEnumerable<CyCustErr> GetErrors()
            {
                return new CyCustErr[] { };    //return an empty array
            }

            #endregion
        }
    }
}
