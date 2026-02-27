using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace TestCharMethods
{
    class Program
    {
        static void Main()
        {
            List<Kvitanciya> x1 = new List<Kvitanciya>();
            for (int i = 0; i < 5; i++){
                Kvitanciya newdoc = new Kvitanciya("квинтанция "+i, "01.01.2000", 1000+i, "красраб 151");
                x1.Add(newdoc);
            }
            List<Nakladnaya> x2 = new List<Nakladnaya>();
            for (int i = 0; i < 5; i++){
                Nakladnaya newdoc = new Nakladnaya("накладная "+i, "01.01.2000", 1000+i, new List<string> {"первая поз.", "вторая поз."});
                x2.Add(newdoc);
            }
            List<Check> x3 = new List<Check>();
            for (int i = 0; i < 5; i++){
                Check newdoc = new Check("Чек "+i, "01.01.2000", 1000+i,  new List<string> {"первый товар", "второй товар"});
                x3.Add(newdoc);
            }

            foreach (Kvitanciya i in x1) {
                Console.WriteLine(i.name);
            }
            foreach (Nakladnaya i in x2) {
                Console.WriteLine(i.name);
            }
            foreach (Check i in x3) {
                Console.WriteLine(i.name);
            }
        }
    }
}