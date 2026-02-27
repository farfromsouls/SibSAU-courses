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
            char[] ch = "aeiuo".ToCharArray();

            StreamReader f = new StreamReader("words.txt");
            string s;
            
            while ((s = f.ReadLine()) != null) 
            {
                string[] words = s.Split(' ');
                
                foreach (string word in words)
                {
                    if (string.IsNullOrEmpty(word))
                        continue;
                    
                    string lowerWord = word.ToLower();
                    if (ch.Contains(lowerWord[0]) && ch.Contains(lowerWord[lowerWord.Length-1]))
                    {
                        Console.WriteLine(word);
                    }
                }
            }
            f.Close();
        }
    }
}