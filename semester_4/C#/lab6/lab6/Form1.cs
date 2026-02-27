namespace lab6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        Bitmap b;
        Graphics g;
        Point startPoint;

        private void Form1_Load(object sender, EventArgs e)
        {
            this.b = new Bitmap(this.pictureBox1.Size.Width,
                                this.pictureBox1.Size.Height);
            this.g = Graphics.FromImage(this.b);
            this.pictureBox1.Image = b;
            this.g.Clear(Color.White);
            this.listBox1.SelectedIndex = 0;
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            this.startPoint = new Point(e.X, e.Y);
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            int x = Math.Min(this.startPoint.X, e.X);
            int y = Math.Min(this.startPoint.Y, e.Y);
            int width = Math.Abs(e.X - this.startPoint.X);
            int height = Math.Abs(e.Y - this.startPoint.Y);

            switch (this.listBox1.SelectedIndex)
            {
                case 0:
                    this.g.DrawLine(new Pen(this.pictureBox2.BackColor,
                                            (float)this.numericUpDown1.Value),
                                            this.startPoint,
                                            new Point(e.X, e.Y));
                    break;
                case 1:
                    this.g.DrawRectangle(new Pen(this.pictureBox2.BackColor,
                                                 (float)this.numericUpDown1.Value),
                                                 x, y, width, height);
                    if (this.checkBox1.Checked)
                    {
                        this.g.FillRectangle(new SolidBrush(this.pictureBox2.BackColor),
                                             x, y, width, height);
                    }
                    break;
                case 2:
                    this.g.DrawEllipse(new Pen(this.pictureBox2.BackColor,
                                                 (float)this.numericUpDown1.Value),
                                                 x, y, width, height);
                    if (this.checkBox1.Checked)
                    {
                        this.g.FillEllipse(new SolidBrush(this.pictureBox2.BackColor),
                                             x, y, width, height);
                    }
                    break;


            }
            this.pictureBox1.Invalidate();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                pictureBox2.BackColor = colorDialog1.Color;
            }
        }

        private void оПрограммеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Слева от рабочей области есть набор инструментов\nон содержит:\n - заливка\n - выбор цвета\n - толщина\n - выбор кисти/фигуры");
        }

        private void новыйХолстToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.g.Clear(Color.White);
            this.pictureBox1.Invalidate();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                this.b.Save(this.saveFileDialog1.FileName, System.Drawing.Imaging.ImageFormat.Jpeg);
            }
        }

        private void loadImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                this.g.Clear(Color.White);
                this.g.DrawImage(Image.FromFile(this.openFileDialog1.FileName), new Point(0, 0));
                this.pictureBox1.Invalidate();
            }
        }
    }
}
