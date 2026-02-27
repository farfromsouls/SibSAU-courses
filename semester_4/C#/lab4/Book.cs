using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Collections;


public class Book : IComparable<Book> {
    public string author;   
    public string name; 
    public int year; 
    public Book(){author = "None"; name = "None"; year = 0;}
    public Book(string a, string n, int y){author = a; name = n; year = y;}

    public bool year_check(int y, string con) {
        if (con == ">") {
            if (year > y) {
                return true;
            } else {
                return false;
            }
        } else if (con == "<") {
            if (year < y) {
                return true;
            } else {
                return false;
            }
        } else if (con == "=") {
            if (year == y) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    public bool author_check(string a) {
        if (author == a) {
            return true;
        } else {
            return false;
        }
    }

    public int CompareTo(Book other) { 
        return name.CompareTo(other.name);  
    }  
}

class compare : IComparer<Book> {
    public int Compare(Book x, Book y) {
        return x.year.CompareTo(y.year);
    }
}