/*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/



using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;

namespace WaveDAC8_v1_70
{
    public class CyWaveDACParameters
    {
        public CyCompDevParam Clock_SRC = null;
        public CyCompDevParam DAC_Range = null;
        public CyCompDevParam Sample_Clock_Freq = null;
        public CyCompDevParam Wave1_Amplitude = null;
        public CyCompDevParam Wave1_Data = null;
        public CyCompDevParam Wave1_DCOffset = null;
        public CyCompDevParam Wave1_Length = null;
        public CyCompDevParam Wave1_Type = null;
        public CyCompDevParam Wave2_Amplitude = null;
        public CyCompDevParam Wave2_Data = null;
        public CyCompDevParam Wave2_DCOffset = null;
        public CyCompDevParam Wave2_Length = null;
        public CyCompDevParam Wave2_Type = null;

        public CyWaveDACParameters(ICyInstEdit_v1 inst)
        {
            GetParams(inst);
        }

        private void GetParams(ICyInstEdit_v1 inst)
        {
            Clock_SRC = inst.GetCommittedParam("Clock_SRC");
            DAC_Range = inst.GetCommittedParam("DAC_Range");
            Sample_Clock_Freq = inst.GetCommittedParam("Sample_Clock_Freq");
            Wave1_Amplitude = inst.GetCommittedParam("Wave1_Amplitude");
            Wave1_Data = inst.GetCommittedParam("Wave1_Data");
            Wave1_DCOffset = inst.GetCommittedParam("Wave1_DCOffset");
            Wave1_Length = inst.GetCommittedParam("Wave1_Length");
            Wave1_Type = inst.GetCommittedParam("Wave1_Type");
            Wave2_Amplitude = inst.GetCommittedParam("Wave2_Amplitude");
            Wave2_Data = inst.GetCommittedParam("Wave2_Data");
            Wave2_DCOffset = inst.GetCommittedParam("Wave2_DCOffset");
            Wave2_Length = inst.GetCommittedParam("Wave2_Length");
            Wave2_Type = inst.GetCommittedParam("Wave2_Type");
        }
    }
}

