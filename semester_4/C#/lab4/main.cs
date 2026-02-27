using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace TestCharMethods {
    class Program {

        public static void display(Book[] arr){
            foreach(Book a in arr)
                Console.WriteLine(a.name, a.year);
        }

        static int Main() {
            Console.WriteLine("Кол-во книг:");
            int amount = Convert.ToInt32(Console.ReadLine());
            compare cmp = new compare();

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

            Console.WriteLine("Сортировка по году:");
            
            Array.Sort(array, cmp);
            display(array);
            
            Console.WriteLine("Сортировка по названию:");
            
            Array.Sort(array);
            display(array);

            return 0;
        }
    }
}