using System.Diagnostics.Metrics;
using System.Reflection;
using System.Runtime.InteropServices.Swift;
using System.Xml;
using System.Xml.Linq;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace lab8
{

    public partial class Form1 : Form
    {
        List<Periodic> periodics = new List<Periodic>();
        public Form1()
        {
            InitializeComponent();
            XmlReader rdr = XmlReader.Create("C:\\Users\\farfromsouls\\Documents\\GitHub\\SibSAU-courses\\semester_4\\C#\\lab8\\lab8\\main.xml");
            string name = "0";
            string type = "0";
            int pages = 0;
            int period = 0;
            int amount = 0;
            int year_episodes = 0;
            int counter = 0;

            while (rdr.Read())
            {
                if (rdr.NodeType == XmlNodeType.Element)
                {
                    switch (rdr.Name)
                    {
                        case "NAME":
                            name = rdr.ReadElementContentAsString();
                            break;
                        case "TYPE":
                            type = rdr.ReadElementContentAsString();
                            break;
                        case "PAGES":
                            pages = rdr.ReadElementContentAsInt();
                            break;
                        case "PERIOD":
                            period = rdr.ReadElementContentAsInt();
                            break;
                        case "AMOUNT":
                            amount = rdr.ReadElementContentAsInt();
                            break;
                        case "YEAR_EPISODES":
                            year_episodes = rdr.ReadElementContentAsInt();
                            periodics.Add(new Periodic(name, type, pages, period, amount, year_episodes));
                            dataGridView1.Rows.Add();
                            dataGridView1["NameColumn", counter].Value = name;
                            dataGridView1["TypeColumn", counter].Value = type;
                            dataGridView1["PagesColumn", counter].Value = pages;
                            dataGridView1["PeriodColumn", counter].Value = period;
                            dataGridView1["AmountColumn", counter].Value = amount;
                            dataGridView1["YearColumn", counter].Value = year_episodes;
                            counter++;
                            break;
                    }
                }
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            periodics.Sort();
            dataGridView1.Rows.Clear();
            int counter = 0;
            foreach (Periodic periodic in periodics)
            {
                dataGridView1.Rows.Add();
                dataGridView1["NameColumn", counter].Value = periodic.name;
                dataGridView1["TypeColumn", counter].Value = periodic.type;
                dataGridView1["PagesColumn", counter].Value = periodic.pages;
                dataGridView1["PeriodColumn", counter].Value = periodic.period;
                dataGridView1["AmountColumn", counter].Value = periodic.amount;
                dataGridView1["YearColumn", counter].Value = periodic.year_episodes;
                counter++;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            int counter = 0;
            foreach (Periodic periodic in periodics)
            {
                if (periodic.year_episodes == Convert.ToInt32(textBox1.Text))
                {
                    dataGridView1.Rows.Add();
                    dataGridView1["NameColumn", counter].Value = periodic.name;
                    dataGridView1["TypeColumn", counter].Value = periodic.type;
                    dataGridView1["PagesColumn", counter].Value = periodic.pages;
                    dataGridView1["PeriodColumn", counter].Value = periodic.period;
                    dataGridView1["AmountColumn", counter].Value = periodic.amount;
                    dataGridView1["YearColumn", counter].Value = periodic.year_episodes;
                    counter++;
                }
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }

    public class Periodic : IComparable<Periodic>
    {
        public string name;
        public string type;
        public int pages;
        public int period;
        public int amount;
        public int year_episodes;

        public Periodic(string name, string type, int pages, int period, int amount, int year_episodes)
        {
            this.name = name;
            this.type = type;
            this.pages = pages;
            this.period = period;
            this.amount = amount;
            this.year_episodes = year_episodes;
        }

        public int CompareTo(Periodic other)
        {
            return name.CompareTo(other.name);
        }
    }
}
