using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace MultAcc_v1_00
{
    [CyCompDevCustomizer()]
    public partial class CyCustomizer : ICyParamEditHook_v1
    {
        private const bool editParamsOnDrop = false;
        private const CyCompDevParamEditorMode mode = CyCompDevParamEditorMode.COMPLETE;
        private MultAccParameters parameters;

        DialogResult ICyParamEditHook_v1.EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery, ICyExpressMgr_v1 mgr)
        {
            parameters = new MultAccParameters(edit);
            CyParamExprDelegate paramChange = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GetParams();
            };

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();

            editor.AddCustomPage("Properties", new MultAccEditingControl(parameters), paramChange, "Properties");

            editor.AddDefaultPage("Built-in", "Built-in");

            parameters.GetParams();

            return editor.ShowDialog();
        }

        bool ICyParamEditHook_v1.EditParamsOnDrop
        {
            get
            {
                return editParamsOnDrop;
            }
        }

        CyCompDevParamEditorMode ICyParamEditHook_v1.GetEditorMode()
        {
            return mode;
        }
    }

    public class MultAccEditingControl : ICyParamEditingControl
    {
        private MultAccControl control;

        public MultAccEditingControl(MultAccParameters parameters)
        {
            control = new MultAccControl(parameters);
            parameters.control = control;
            control.Dock = DockStyle.Fill;
        }

        Control ICyParamEditingControl.DisplayControl
        {
            get { return control; }
        }

        IEnumerable<CyCustErr> ICyParamEditingControl.GetErrors()
        {
            return new CyCustErr[] { };
        }
    }
}