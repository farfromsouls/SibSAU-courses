namespace lab8
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            button1 = new Button();
            button2 = new Button();
            textBox1 = new TextBox();
            dataGridView1 = new DataGridView();
            NameColumn = new DataGridViewTextBoxColumn();
            TypeColumn = new DataGridViewTextBoxColumn();
            PagesColumn = new DataGridViewTextBoxColumn();
            PeriodColumn = new DataGridViewTextBoxColumn();
            AmountColumn = new DataGridViewTextBoxColumn();
            YearColumn = new DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // button1
            // 
            button1.Location = new Point(303, 12);
            button1.Name = "button1";
            button1.Size = new Size(208, 29);
            button1.TabIndex = 1;
            button1.Text = "Сортировка по имени";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(512, 45);
            button2.Name = "button2";
            button2.Size = new Size(94, 29);
            button2.TabIndex = 2;
            button2.Text = "button2";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // textBox1
            // 
            textBox1.Location = new Point(308, 49);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(203, 27);
            textBox1.TabIndex = 3;
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { NameColumn, TypeColumn, PagesColumn, PeriodColumn, AmountColumn, YearColumn });
            dataGridView1.Location = new Point(2, 82);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 51;
            dataGridView1.Size = new Size(816, 309);
            dataGridView1.TabIndex = 4;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;
            // 
            // NameColumn
            // 
            NameColumn.HeaderText = "Name";
            NameColumn.MinimumWidth = 6;
            NameColumn.Name = "NameColumn";
            NameColumn.Width = 125;
            // 
            // TypeColumn
            // 
            TypeColumn.HeaderText = "Type";
            TypeColumn.MinimumWidth = 6;
            TypeColumn.Name = "TypeColumn";
            TypeColumn.Width = 125;
            // 
            // PagesColumn
            // 
            PagesColumn.HeaderText = "Pages";
            PagesColumn.MinimumWidth = 6;
            PagesColumn.Name = "PagesColumn";
            PagesColumn.Width = 125;
            // 
            // PeriodColumn
            // 
            PeriodColumn.HeaderText = "Period";
            PeriodColumn.MinimumWidth = 6;
            PeriodColumn.Name = "PeriodColumn";
            PeriodColumn.Width = 125;
            // 
            // AmountColumn
            // 
            AmountColumn.HeaderText = "Amount";
            AmountColumn.MinimumWidth = 6;
            AmountColumn.Name = "AmountColumn";
            AmountColumn.Width = 125;
            // 
            // YearColumn
            // 
            YearColumn.HeaderText = "Year";
            YearColumn.MinimumWidth = 6;
            YearColumn.Name = "YearColumn";
            YearColumn.Width = 125;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(839, 450);
            Controls.Add(dataGridView1);
            Controls.Add(textBox1);
            Controls.Add(button2);
            Controls.Add(button1);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        private Button button1;
        private Button button2;
        private TextBox textBox1;
        private DataGridView dataGridView1;

        // ПЕРЕИМЕНОВАННЫЕ ПОЛЯ
        private DataGridViewTextBoxColumn NameColumn;
        private DataGridViewTextBoxColumn TypeColumn;
        private DataGridViewTextBoxColumn PagesColumn;
        private DataGridViewTextBoxColumn PeriodColumn;
        private DataGridViewTextBoxColumn AmountColumn;
        private DataGridViewTextBoxColumn YearColumn;
    }
}