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
    public partial class cywaveformeditor : UserControl
    {
        const float L_TEXT_MARGIN = 40.0F;
        const float MARGIN_PERCENT = 0.04F;
        const float MAX_DATA_VALUE = 256F;

        float marginxpercent = 0.0f;
        float marginypercent = 0.0f;
        float leftmargin = 0.0f;
        float rightmargin = 0.0f;
        float topmargin = 0.0f;
        float bottommargin = 0.0f;
        float middlex = 0.0f;
        float tempwidth = 0.0f;


        CyWaveRange ranges = new CyWaveRange(5.0,true);
        double offset = 0.0;
        double sps = 0.0;
        List<byte> values = new List<byte>();
        bool arbitrary = false;
        bool mousedown = false;

        public cywaveformeditor()
        {
            //InitializeComponent();
        }

        public List<byte> DataValues
        {
            get { return values; }
            set { values = value; }
        }

        public bool Arbitrary
        {
            set { arbitrary = value; }
        }

        public double Offset
        {
            get { return offset; }
            set { offset = value; }
        }

        public double SPS
        {
            get { return sps; }
            set { sps = value; }
        }
        
        public CyWaveRange GetWaveRange()
        {
            return (new CyWaveRange(ranges.MaxRange, ranges.Volts));
        }

        public delegate void ArbWaveformChanged(List<byte> data);
        public event ArbWaveformChanged OnArbWaveChange;

        public void SetWaveRange(CyWaveRange WaveRange)
        {
            ranges.MaxRange = WaveRange.MaxRange;
            ranges.Volts = WaveRange.Volts;
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            //base.OnMouseDown(e);
            if(arbitrary && e.Button == MouseButtons.Left)
                AddArbitraryStates(e);
        }

        private void AddArbitraryStates(MouseEventArgs e)
        {
            if (e.X > leftmargin && e.X < middlex && e.Y > topmargin && e.Y < bottommargin)
            {
                //TODO: /* make sure it's not the same region as the last mousedown event */
                /* Calculate X space and Y voltage and re-assign the value */
                float statewidth = ((middlex - leftmargin) / values.Count);
                List<int> states = new List<int>();
                int state = (int)((e.X - leftmargin) / statewidth);
                states.Add(state);
                float tempstatewidth = statewidth;
                while (tempstatewidth < 1.5)
                {
                    state = ++state;
                    states.Add(state);
                    tempstatewidth += statewidth;
                }

                float yval = 256.0f - ((e.Y - topmargin) / ((bottommargin - topmargin) / 256.0f));
                for (int i = 0; i < states.Count; i++)
                {
                    if (states[i] > 0 && states[i] < values.Count)
                        values[states[i]] = (byte)yval;
                }
                this.Invalidate();
                mousedown = true;
            }
            else
                mousedown = false;
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            //base.OnMouseMove(e);
            if (mousedown || e.Button == MouseButtons.Left)
            {
                AddArbitraryStates(e);
            }
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            if(mousedown)
                OnArbWaveChange(DataValues);
            mousedown = false;
            base.OnMouseUp(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            Graphics g = e.Graphics;

            g.FillRectangle(new SolidBrush(Color.White), 0, 0, this.Width, this.Height);

            /* Calculate X and Y margins and */
            marginxpercent = this.Width * MARGIN_PERCENT;
            marginypercent = this.Height * MARGIN_PERCENT;
            leftmargin = L_TEXT_MARGIN + marginxpercent;
            rightmargin = this.Width - marginxpercent;
            topmargin = marginypercent;
            bottommargin = this.Height - marginypercent;
            middlex = leftmargin + (rightmargin - leftmargin) / 2.0F;
            float halfwidth = middlex - leftmargin;
            float heightaftermargins = bottommargin - topmargin;
            float middley = this.Height / 2.0F;

            /* Fill Right half with Grayish Background */
            g.FillRectangle(new SolidBrush(Color.LightGray), middlex, topmargin, halfwidth, heightaftermargins);

            /* Draw Left, Right and Middle Vertical Lines */
            g.DrawLine(new Pen(new SolidBrush(Color.Black), 2), leftmargin, topmargin, leftmargin, bottommargin);
            g.DrawLine(new Pen(new SolidBrush(Color.Black), 2), rightmargin, topmargin, rightmargin, bottommargin);
            g.DrawLine(new Pen(new SolidBrush(Color.Black), 1), middlex, topmargin, middlex, bottommargin);

            /* Draw Center horizontal line */
            //Pen extentspen = new Pen(blkbrush);
            //extentspen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            g.DrawLine(new Pen(new SolidBrush(Color.Gray), 1), leftmargin, middley, rightmargin, middley);

            /* Draw Voltage Strings */
            Font voltfont = new Font("Arial", 9, FontStyle.Regular);
            Brush voltbrush = new SolidBrush(Color.Gray);
            string highvoltstring = String.Format(Convert.ToString(ranges.MaxRange) + (ranges.Volts ? "V" : "mA"),"0.000");
            string midvoltstring = String.Format(Convert.ToString(ranges.MaxRange / 2.0F) + (ranges.Volts ? "V" : "mA"),"0.000");
            string lowvoltstring = String.Format(Convert.ToString(0.0) + (ranges.Volts ? "V" : "mA"), "0.000");
            SizeF highvoltsize = g.MeasureString(highvoltstring, voltfont);
            SizeF midvoltsize = g.MeasureString(midvoltstring, voltfont);
            SizeF lowvoltsize = g.MeasureString(lowvoltstring, voltfont);
            RectangleF highvoltrect = new RectangleF(new PointF(leftmargin - highvoltsize.Width - 2, topmargin), highvoltsize);
            RectangleF midvoltrect = new RectangleF(new PointF(leftmargin - midvoltsize.Width - 2, middley - (midvoltsize.Height / 2.0F) - 1), midvoltsize);
            RectangleF lowvoltrect = new RectangleF(new PointF(leftmargin - lowvoltsize.Width - 2, bottommargin - lowvoltsize.Height), lowvoltsize);

            g.DrawString(highvoltstring, voltfont, voltbrush, highvoltrect);
            g.DrawString(midvoltstring, voltfont, voltbrush, midvoltrect);
            g.DrawString(lowvoltstring, voltfont, voltbrush, lowvoltrect);

            voltbrush.Dispose();

            Bitmap imgwaveform = new Bitmap((int)halfwidth, (int)heightaftermargins);// TODO: ??? Why Five?
            Graphics igw = Graphics.FromImage(imgwaveform);
			
            if (values.Count != 0)
            {
                /* Draw the Waveform */
                float ymult = heightaftermargins / MAX_DATA_VALUE;
                tempwidth = halfwidth / values.Count;
                float xwidth = tempwidth;
                int normalizer = 1;
                while (xwidth <= 1.5)
                {
                    xwidth += tempwidth;
                    normalizer++;
                }
                float prevy = heightaftermargins - (values[values.Count-1] * ymult); ;
                int j = 0;
                int lastpoint = 0;
                Pen wavepen = new Pen(new SolidBrush(Color.Red), 1);
                float prevx = (j * xwidth);
                for (int i = 0; i < values.Count; i+=normalizer)
                {
                    float startx = (j * xwidth);
                    float endx = startx + xwidth;
                    float y = heightaftermargins - (values[i] * ymult);
                    float tempy1 = 0;
                    float tempy2 = 0;
                    if (tempwidth > 1.0)  /* if a state is wider than 1 pixel draw a vertical line from previous Y to current Y
                                             * then a straight horizontal line at Y. 
                                             */
                    {
                        prevy = (prevy < 0) ? 0 : (prevy > heightaftermargins - 2) ? heightaftermargins - 2 : prevy;
                        y = (y < 0) ? 0 : (y > heightaftermargins - 2) ? heightaftermargins - 2 : y;
                        igw.DrawLine(wavepen, startx, prevy, startx, y);
                        igw.DrawLine(wavepen, startx, y, endx, y);
                    }                    
                    else /* if a state is less than 1 pixels then cover all possible values of that state */
                    {
                        /* Line needs to be drawn with representation of skipped bits */
                        int z = lastpoint;
                        byte min = values[z];
                        byte max = values[z];
                        for (z = lastpoint+1; z <= i; z++)
                        {
                            min = Math.Min(min, values[z]);
                            max = Math.Max(max, values[z]);
                        }
                        tempy1 = heightaftermargins - (min * ymult);
                        tempy2 = heightaftermargins - (max * ymult);
                        tempy1 = (tempy1 < 0) ? 0 : (tempy1 > heightaftermargins-2) ? heightaftermargins-2 : tempy1;
                        tempy2 = (tempy2 < 0) ? 0 : (tempy2 > heightaftermargins-2) ? heightaftermargins-2 : tempy2;
                        if (tempy1 == tempy2)
                            igw.DrawLine(wavepen, startx, tempy1, startx, tempy1 + 1);
                        else
                            igw.DrawLine(wavepen, startx, tempy1, startx, tempy2);
                    }
                    j++;
                    prevy = y;
                    prevx = endx;
                    lastpoint = i;
                }
                wavepen.Dispose();

                g.DrawImage(imgwaveform,new PointF(leftmargin,topmargin));
                g.DrawImage(imgwaveform,new PointF(middlex,topmargin));
                imgwaveform.Dispose();
                if (sps != 0)
                {
                    /* Draw the frequency/Period Label  */
                    /* Left Margin to Middle X = 1 period */
                    double Period = values.Count * (1.0/Convert.ToDouble(sps));
                    double Frequency = 1.0 / Period;
                    String PeriodStr = "Period: " + ConvertToReadableSeconds(Period);
                    String FrequencyStr = "Frequency: " + ConvertToReadableFrequency(Frequency);
                    SizeF pstrsize = g.MeasureString(PeriodStr, voltfont);
                    SizeF fstrsize = g.MeasureString(FrequencyStr, voltfont);

                    Brush br = new SolidBrush(Color.Green);
                    double halftopmargin = topmargin / 2.0;

                    /* Draw Left Arrow */
                    PointF[] ptsL1 = new PointF[3];
                    ptsL1[0] = new PointF((float)leftmargin, (float)halftopmargin);
                    ptsL1[1] = new PointF(leftmargin + topmargin, 0);
                    ptsL1[2] = new PointF(leftmargin + topmargin, topmargin);
                    g.FillPolygon(br,ptsL1);

                    /* Draw Left Arrow */
                    PointF[] ptsL2 = new PointF[3];
                    ptsL2[0] = new PointF((float)middlex, (float)halftopmargin);
                    ptsL2[1] = new PointF(middlex + topmargin, 0);
                    ptsL2[2] = new PointF(middlex + topmargin, topmargin);
                    g.FillPolygon(br, ptsL2);

                    /* Draw Right Arrow */
                    PointF[] ptsR1 = new PointF[3];
                    ptsR1[0] = new PointF((float)middlex, (float)halftopmargin);
                    ptsR1[1] = new PointF(middlex - topmargin, 0);
                    ptsR1[2] = new PointF(middlex - topmargin, topmargin);
                    g.FillPolygon(br, ptsR1);

                    /* Draw Right Arrow */
                    PointF[] ptsR2 = new PointF[3];
                    ptsR2[0] = new PointF((float)rightmargin, (float)halftopmargin);
                    ptsR2[1] = new PointF(rightmargin - topmargin, 0);
                    ptsR2[2] = new PointF(rightmargin - topmargin, topmargin);
                    g.FillPolygon(br, ptsR2);

                    PointF perstrpt = new PointF((float)(leftmargin + (halfwidth / 2.0) - (pstrsize.Width / 2.0)), 0);
                    PointF freqstrpt = new PointF((float)(rightmargin - (halfwidth / 2.0) - (fstrsize.Width / 2.0)), 0);
                    g.DrawString(PeriodStr,voltfont,br,perstrpt);
                    g.DrawString(FrequencyStr, voltfont, br, freqstrpt);
                    g.DrawLine(new Pen(br), ptsL1[0], new PointF((float)(perstrpt.X - topmargin), (float)halftopmargin));
                    g.DrawLine(new Pen(br), new PointF((float)(perstrpt.X + pstrsize.Width + topmargin), (float)halftopmargin), ptsR1[0]);
                    g.DrawLine(new Pen(br), ptsL2[0], new PointF((float)(freqstrpt.X - topmargin), (float)halftopmargin));
                    g.DrawLine(new Pen(br), new PointF((float)(freqstrpt.X + fstrsize.Width + topmargin), (float)halftopmargin), ptsR2[0]);

                    br.Dispose();
                }
                voltfont.Dispose();
            }
        }

        String ConvertToReadableFrequency(double value)
        {
            string retval = "0.0Hz";
            if (value > 1000000)   /*MHz*/
                retval = String.Format("{0}MHz", (value / 1000000.0).ToString("0.000"));
            else if (value > 1000)   /*KHz*/
                retval = String.Format("{0}KHz", (value / 1000.0).ToString("0.000"));
            else   /*Hz*/
                retval = String.Format("{0}Hz", (value).ToString("0.000"));
            return retval;
        }

        String ConvertToReadableSeconds(double value)
        {
            string retval = "0.0ms";
            if (value < 0.000001)   /*ns*/
                retval = String.Format("{0}ns", (value * 1000000000.0).ToString("0.000"));
            else if (value < 0.001)   /*us*/
                retval = String.Format("{0}us", (value * 1000000.0).ToString("0.000"));
            else   /*ms*/
                retval = String.Format("{0}ms", (value * 1000.0).ToString("0.000"));
            return retval;
        }
    }

    public class CyWaveRange
    {
        double maxrange = 5.0;
        bool volts = true;

        public CyWaveRange(double MaxRange, bool Volts)
        {
            maxrange = MaxRange;
            volts = Volts;
        }
        public CyWaveRange()
        {
            maxrange = 5.0;
            volts = true;
        }

        public double MaxRange
        {
            get { return maxrange; }
            set { maxrange = value; }
        }
        
        public bool Volts
        {

            get { return volts; }
            set { volts = value; }
        }
    }
}
