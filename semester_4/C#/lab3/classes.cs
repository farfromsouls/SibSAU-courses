using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

class Document {
    public string name;   
    public string date;
    public int money;

    public void zaverit() {
        Console.WriteLine(name, " - заверен");
    }
    public void sign() {
        Console.WriteLine(name, " - подписан");
    }
    public void destroy() {
        Console.WriteLine(name, " - разорван");
    }
}

class Kvitanciya : Document {
    public string adress;

    public Kvitanciya(string n, string d, int m, string a) {
        name = n;
        date = d;
        money = m;
        adress = a;
    }

    public void pay(){
        Console.WriteLine(name, " - оплачена");
    }
}

class Nakladnaya : Document {
    public List<string> positions;

    public Nakladnaya(string n, string d, int m, List<string> p) {
        name = n;
        date = d;
        money = m;
        positions = p;
    }

    public void apply(){
        Console.WriteLine(name, " - подтверждена");
    }
}

class Check : Document {
    public List<string> patches;

    public Check(string n, string d, int m, List<string> p) {
        name = n;
        date = d;
        money = m;
        patches = p;
    }

    public void pay(){
        Console.WriteLine(name, " - оплачен");
    }
}