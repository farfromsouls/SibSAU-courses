using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string binaryNumber = textBox1.Text;
            int decimalNumber = Convert.ToInt32(binaryNumber, 2);

            if (radioButton1.Checked)
            {
                textBox2.Text = Convert.ToString(decimalNumber);
            }
            else if (radioButton2.Checked)
            {
                textBox2.Text = Convert.ToString(decimalNumber, 8);
            }
            else if (radioButton3.Checked)
            {
                textBox2.Text = Convert.ToString(decimalNumber, 16);
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
