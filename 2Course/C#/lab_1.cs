using System; 
using System.Collections.Generic; 
using System.IO; 
using System.Threading; 
using System.Threading.Tasks; 
 
namespace C_sharp_1 
{ 
    public class Person 
    { 
        public string Name { get; } 
        public string Surname { get; } 
        public string Lastname { get; } 
        public DateTime BirthDate { get; } 
        public float Weight { get; } 
        public bool Sex{ get; } 
        public Person(string Surname, string Name, string Lastname, bool Sex, DateTime BirthDate, float Weight) 
        { 
            this.Name = Name; 
            this.Surname = Surname; 
            this.Lastname = Lastname; 
            this.Sex = Sex; 
            this.BirthDate = BirthDate; 
            this.Weight = Weight; 
        } 
        override public String ToString() 
        { 
            return $"Name: {Surname} {Name} {Lastname}, Sex: {Sex_char}, BirthDate:{BirthDate: dd-MM-yyyy}, Age:{Age}, Weight: {Weight:E4}"; 
        } 
 
        public char Sex_char 
        { 
            get 
            { 
                if (Sex == true) 
                    return 'm'; 
                else 
                    return 'f'; 
            } 
        } 
        public int Age 
        { 
            get 
            { 
                DateTime dn = DateTime.Now; 
                if (dn.Month > BirthDate.Month) 
                    return (dn.Year - BirthDate.Year); 
                else if (dn.Month < BirthDate.Month) 
                    return (dn.Year - BirthDate.Year - 1); 
                else 
                { 
                    if (dn.Day >= BirthDate.Day) 
                        return (dn.Year - BirthDate.Year); 
                    else return (dn.Year - BirthDate.Year - 1); 
                } 
            } 
        } 
       
    } 
 
    class Program 
    { 
        public static Person Parse(string text) 
        { 
            string[] attributes = text.Split(new char[] { ' ' }); 
            bool Sex = false; 
            if (attributes[3] == "m") 
                Sex = true; 
            float Weight = Convert.ToSingle(attributes[5]); 
            DateTime BirthDate = Convert.ToDateTime(attributes[4]); 
            Person temp = new Person(attributes[0], attributes[1], attributes[2], Sex, BirthDate, Weight); 
            return temp; 
        } 
 
        static void Main() 
        { 
            string[] text = File.ReadAllLines(@"D:\SomeDir2\input.txt"); 
            Console.WriteLine("Sort 1 or 0"); 
            string choice = Console.ReadLine(); 
            List<Person> persons = new List<Person>(); 
            foreach (string i in text) 
            { 
                Person temp = Parse(i); 
                persons.Add(temp); 
            } 
 
            if (choice == "1") 
                persons.Sort((x, y) => x.BirthDate.CompareTo(y.BirthDate)); 
            else 
                persons.Sort((x, y) => y.BirthDate.CompareTo(x.BirthDate)); 
 
            using (StreamWriter w = File.CreateText(@"D:\SomeDir2\output.txt")) 
            { 
                foreach (Person var in persons) 
                { 
                    w.WriteLine(var); 
                } 
            } 
        } 
    } 
} 
