using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace TestCharMethods {
    class Program {
        static int Main() {
            Console.WriteLine("Кол-во книг:");
            int amount = Convert.ToInt32(Console.ReadLine());
            if (amount == 0) {
                return 0;
            }
            Book[] array = new Book[amount];
            for (int i = 0; i < amount; i++) {
                Console.WriteLine("Напишите автора");
                string author = Console.ReadLine();
                Console.WriteLine("Напишите название");
                string name = Console.ReadLine();
                Console.WriteLine("Напишите год");
                int year = Convert.ToInt32(Console.ReadLine());
                array[i] = new Book(author, name, year);
            }

            Console.WriteLine("Книги П.Нортона после 2000г:");
            for (int i = 0; i < amount; i++) {
                if (array[i].author_check("П.Нортон") == true) {
                    if (array[i].year_check(2000, ">") == true) {
                        Console.WriteLine(array[i].name);
                    }
                }
            }

            return 0;
        }
    }
}