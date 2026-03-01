using System.Diagnostics.Metrics;
using System.Threading;

namespace lab9
{
    public partial class Form1 : Form
    {
        public double x = 0.0;
        public double a = 0.0;

        public Form1()
        {
            InitializeComponent();
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            try
            {
                x = Convert.ToDouble(textBox2.Text);
                textBox1.Text = $"(1+{x})^{a} = ";
            }
            catch
            {
                textBox1.Text = $"(1+x)^{a} = ";
                x = 0.0;
            }

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            try
            {
                a = Convert.ToDouble(textBox3.Text);
                textBox1.Text = $"(1+{x})^{a} = ";
            }
            catch
            {
                textBox1.Text = $"(1+{x})^a = ";
                a = 0.0;
            }
        }

        double factorial(int n)
        {
            if (n == 0) return 1;
            if (n == 1) return 1;
            return n * factorial(n - 1);
        }

        private void countMethod()
        {
            double ans = 0.0;
            int ready_check1 = 0;

            for (int k = 0; k < 1000; k += 1)
            {
                double up = 1;
                for (int i = 0; i < k; i++) 
                {
                    up *= (a - i);
                }

                ans += (up / factorial(k)) * Math.Pow(x, k);
                int ready_check2 = Convert.ToInt32(ans*100000);

                if (ready_check1 == ready_check2)
                {
                    break;
                }
                else
                {
                    ready_check1 = ready_check2;
                }
            }

            ans = Math.Round(ans, 5);
            textBox4.BeginInvoke(new MethodInvoker(() => textBox4.Text = ans.ToString()));
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread newthread = new Thread(new ThreadStart(countMethod));
            newthread.Start();
        }
    }
}
