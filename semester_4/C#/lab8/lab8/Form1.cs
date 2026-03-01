using System.Runtime.InteropServices.Swift;
using System.Xml;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace lab8
{
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

    public partial class Form1 : Form
    {
        List<Periodic> periodics = new List<Periodic>();
        public Form1()
        {
            InitializeComponent();
            XmlReader rdr = XmlReader.Create("C:\\Users\\farfromsouls\\Desktop\\ООП\\yan\\lab8\\lab8\\main.xml");
            string name = "0";
            string type = "0";
            int pages = 0;
            int period = 0;
            int amount = 0;
            int year_episodes = 0;

            while (rdr.Read())
            {
                if (rdr.NodeType == XmlNodeType.Element)
                {
                    switch (rdr.Name)
                    {
                        case "NAME":
                            name = rdr.ReadElementContentAsString();
                            listBox1.Items.Add($"{name}");
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
                            break;
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            periodics.Sort();
            listBox1.Items.Clear();
            foreach (Periodic periodic in periodics)
            {
                listBox1.Items.Add(periodic.name);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            foreach (Periodic periodic in periodics)
            {
                if (periodic.year_episodes == Convert.ToInt32(textBox1.Text))
                {
                    listBox1.Items.Add(periodic.name);
                }
            }
        }
    }
}
