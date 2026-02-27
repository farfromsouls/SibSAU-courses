using System.IO;

namespace lab7
{
    public partial class Form1 : Form
    {
        public string saved_dir = "";
        int saved_dir_index = 999;

        public void writeDrives()
        { 
            listBox1.Items.Clear();
            DriveInfo[] drives = DriveInfo.GetDrives();
            foreach (DriveInfo drive in drives)
            {
                string d1 = drive.Name;
                string d2 = drive.DriveFormat;
                long d3 = drive.TotalFreeSpace / 1024 / 1024 / 1024;
                long d4 = drive.TotalSize / 1024 / 1024 / 1024;
                listBox1.Items.Add($"{d1} {d2} занято: {d4 - d3}GB/{d4}GB\n");
            }
        }

        public void showFileData(FileInfo file)
        {
            richTextBox1.Text = "";
            richTextBox1.Text += $"расположение: {file.Directory}\n";
            richTextBox1.Text += $"имя: {file.Name}\n";
            richTextBox1.Text += $"дата создания: {file.CreationTime}\n";
            richTextBox1.Text += $"дата изменения: {file.LastWriteTime}\n";
            richTextBox1.Text += $"Размер: {Math.Round(file.Length / 1024.0 / 1024.0, 2)}МБ\n";
        }

        public void update_lists()
        { 
            string path = textBox1.Text;
            if (path == "")
            {
                writeDrives();
                listBox2.Items.Clear();
                saved_dir = "";
                saved_dir_index = 999;
                textBox1.Text = "";
                return;
            }
            try
            {
                DirectoryInfo dir = new DirectoryInfo(path);
                FileInfo file = new FileInfo(path);
                saved_dir += $"{dir.Name}\\";
                saved_dir_index = 999;

                listBox1.Items.Clear();
                listBox2.Items.Clear();
                foreach (DirectoryInfo inner_dir in dir.GetDirectories())
                {
                    listBox1.Items.Add(inner_dir.Name);
                }
                foreach (FileInfo inner_file in dir.GetFiles())
                {
                    listBox2.Items.Add(inner_file.Name);
                }

                if (file.Exists)
                {
                    showFileData(file);
                }

                saved_dir = dir.FullName;
                if (!saved_dir.EndsWith(Path.DirectorySeparatorChar.ToString()))
                    saved_dir += Path.DirectorySeparatorChar;

                saved_dir_index = 999;
            }
            catch (Exception ex)
            {
                writeDrives();
                listBox2.Items.Clear();
                richTextBox1.Text = ex.ToString();
                saved_dir = "";
                saved_dir_index = 999;
                textBox1.Text = ""; 
            }
        }

        public Form1()
        {
            InitializeComponent();
            writeDrives();
        }

        private void оПрограммеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("О программа:\n");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string newName = textBox2.Text.Trim();
            if (string.IsNullOrEmpty(newName))
            {
                MessageBox.Show("Введите имя");
                return;
            }

            if (newName.StartsWith("\\"))
            {
                string folderName = newName.Substring(1);
                if (string.IsNullOrEmpty(folderName))
                {
                    MessageBox.Show("Некорректное имя папки");
                    return;
                }
                string fullPath = Path.Combine(textBox1.Text, folderName);
                Directory.CreateDirectory(fullPath);
            }
            else
            {
                
                string fullPath = Path.Combine(textBox1.Text, newName);
                using (File.Create(fullPath)) { } 
            }
            update_lists();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                File.Copy($"{textBox1.Text}\\{listBox2.Text}", $"{textBox1.Text}\\copy_{listBox2.Text}");
                update_lists();
            } catch
            {
                return;
            }
          
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try { 
                File.Move($"{textBox1.Text}\\{listBox2.Text}", $"{textBox1.Text}\\{textBox2.Text}");
                update_lists();
            }
            catch
            {
                return;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            { 
                File.Move($"{textBox1.Text}\\{listBox2.Text}", $"{textBox2.Text}\\{listBox2.Text}");
                update_lists();
            }
            catch
            {
                return;
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            update_lists();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedIndex == saved_dir_index) return; 

            if (saved_dir == "")
            {
                string driveName = listBox1.Text.Split()[0]; 
                textBox1.Text = driveName;
            }
            else
            {
                string dirName = listBox1.Text;
                textBox1.Text = Path.Combine(textBox1.Text, dirName);
            }
            saved_dir_index = listBox1.SelectedIndex;
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            string filePath = Path.Combine(textBox1.Text, listBox2.Text);
            FileInfo file = new FileInfo(filePath);
            try
            {
                showFileData(file);
            } catch
            {
                return;
            }
        }
    }
}
