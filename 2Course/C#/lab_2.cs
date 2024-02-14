using System; 
using System.Collections.Generic; 
using System.IO; 
using System.Linq; 
 
namespace C_sharp_1 
{ 
    interface IPerson 
    { 
        string Name { get; } 
        string Patronomic { get; } 
        string Lastname { get; } 
        DateTime Date { get; } 
        int Age { get; } 
    } 
 
    public class Student : IPerson 
    { 
        public string Name { get; } 
        public string Patronomic { get; } 
        public string Lastname { get; } 
        public DateTime Date { get; } 
        public int Age 
        { 
            get 
            { 
                DateTime now = DateTime.Now; 
                if (now.Month > Date.Month) 
                    return now.Year - Date.Year; 
                else 
                    if (now.Month == Date.Month) 
                { 
                    if (now.Day >= Date.Day) 
                        return now.Year - Date.Year; 
                    else 
                        return now.Year - Date.Year - 1; 
                } 
                else 
                    return now.Year - Date.Year - 1; 
            } 
        } 
 
        public int Course { get; } 
        public string Group { get; set; } 
        public float Avr_point { get; } 
 
        public Student(string name, string patronomic, string lastname, DateTime date, int course, string group, float avr_point) 
        { 
            Name = name; 
            Patronomic = patronomic; 
            Lastname = lastname; 
            Date = date; 
            Course = course; 
            Group = group; 
            Avr_point = avr_point; 
        } 
        override public String ToString() 
        { 
            return $"Name: {Name} {Patronomic} {Lastname}, Date:{Date: dd-MM-yyyy}, Age:{Age}, Course:{Course}, Group: {Group}, Avr_point: {Avr_point}"; 
        } 
 
        public static Student Parse(string text) 
        { 
            string[] attributes = text.Split(new char[] { ' ' }); 
            DateTime date = Convert.ToDateTime(attributes[3]); 
            int age = Convert.ToInt32(attributes[4]); 
            int course = Convert.ToInt32(attributes[5]); 
            float avr_point = Convert.ToSingle(attributes[7]); 
            Student temp = new Student(attributes[0], attributes[1], attributes[2], date, course, attributes[6], avr_point); 
            return temp; 
        } 
    } 
 
    public class Teacher : IPerson 
    { 
        public string Name { get; } 
        public string Patronomic { get; } 
        public string Lastname { get; } 
        public DateTime Date { get; } 
        public int Age { get; } 
 
        public string Department { get; } 
        int Exp { get; } 
        public enum Post 
        { 
            Зав_Кафедрой, Профессор, Доцент, 
            Старший_Преподаватель 
        } 
 
        public Teacher(string name, string patronomic, string lastname, DateTime date, int age, string department, int exp) 
        { 
            Name = name; 
            Patronomic = patronomic; 
            Lastname = lastname; 
            Date = date; 
            Age = age; 
            Department = department; 
            Exp = exp; 
        } 
        override public String ToString() 
        { 
            return $"Name: {Name} {Patronomic} {Lastname}, Date:{Date: dd-MM-yyyy}, Age: {Age}, Department: {Department}, Exp: {Exp}"; 
        } 
 
        public static Teacher Parse(string text) 
        { 
            string[] attributes = text.Split(new char[] { ' ' }); 
            DateTime date = Convert.ToDateTime(attributes[3]); 
            int age = Convert.ToInt32(attributes[4]); 
            int exp = Convert.ToInt32(attributes[6]); 
            Teacher temp = new Teacher(attributes[0], attributes[1], attributes[2], date, age, attributes[5], exp); 
            return temp; 
        } 
    } 
 
    interface IUniversity 
    { 
        IEnumerable<IPerson> Persons { get; } 
        IEnumerable<Student> Students { get; } 
        IEnumerable<Teacher> Teachers { get; } 
 
        void Add(IPerson person); 
        void Remove(IPerson person); 
 
        IEnumerable<IPerson> FindByLastName(string lastName); 
 
        IEnumerable<Teacher> FindByDepartment(string text); 
    } 
 
    class University : IUniversity 
    { 
        public List<IPerson> persons { get; } //Список всех людей университета 
        public List<Student> students { get; } //Список студентов 
        public List<Teacher> teachers { get; } //Список преподавателей 
        public University() //Конструктор 
        { 
            persons = new List<IPerson>(); 
            students = new List<Student>(); 
            teachers = new List<Teacher>(); 
        } 
        public IEnumerable<IPerson> Persons { get => persons.OrderBy(p => p.Age); } //Сортировка людей по возрасту 
        public IEnumerable<Student> Students { get => persons.OfType<Student>().OrderBy(p => p.Age); } //Сортировка студентов по возрасту 
        public IEnumerable<Teacher> Teachers { get => persons.OfType<Teacher>().OrderBy(p => p.Age); }//Сортировка преподавателей по возрасту 
        public void Add(IPerson person) //Добавить человека 
        { 
            persons.Add(person); 
            if (person is Student student) //Если он студент 
                students.Add(student); 
            if (person is Teacher teacher) //Если он преподаватель 
                teachers.Add(teacher); 
        } 
        public void Remove(IPerson person) //Удалить человека 
        { 
            persons.Remove(person); 
            if (person is Student student) 
                students.Remove(student);   //Если он студент 
            if (person is Teacher teacher) 
                teachers.Remove(teacher);   //Если он преподаватель 
        } 
 
        public IEnumerable<IPerson> FindByLastName(string lastName) 
        { 
            var selectedPersons = from p in Persons  
                                  where p.Lastname == lastName  
                                  orderby p 
                                  select p; 
            return selectedPersons; 
        } 
 
        public IEnumerable<Teacher> FindByDepartment(string text) 
        { 
            return teachers.Where(x => x.Department == text).OrderBy(x => x.Post).ToList(); 
        } 
    } 
 
    static class Program 
    { 
 
        static void Upload_Students(University NSTU) 
        { 
            string[] text = File.ReadAllLines(@"D:\SomeDir2\input_student.txt"); 
            foreach (string i in text) 
            { 
                Student temp = Student.Parse(i); 
                NSTU.students.Add(temp); 
            } 
        } 
 
        static void Upload_Teachers(University NSTU) 
        { 
            string[] text = File.ReadAllLines(@"D:\SomeDir2\input_teacher.txt"); 
            foreach (string i in text) 
            { 
                Teacher temp = Teacher.Parse(i); 
                NSTU.teachers.Add(temp); 
            } 
        } 
 
        static void Main() 
        { 
            University NSTU = new University(); 
            bool showMenu = true; 
            while (showMenu) 
            { 
                showMenu = MainMenu(NSTU); 
            } 
        } 
        private static bool MainMenu(University temp) 
        { 
            Student student; 
            Teacher teacher; 
            IEnumerable<IPerson> lastN; 
            Console.Clear(); 
            Console.WriteLine("Choose an option:"); 
            Console.WriteLine("1) Upload students"); 
            Console.WriteLine("2) Upload teachers"); 
            Console.WriteLine("3) Add student"); 
            Console.WriteLine("4) Add teacher"); 
            Console.WriteLine("5) Remove student"); 
            Console.WriteLine("6) Remove teacher"); 
            Console.WriteLine("7) Search by Lastname"); 
            Console.WriteLine("8) Search by Department"); 
            Console.WriteLine("S) Save"); 
            Console.WriteLine("0) Exit"); 
            Console.Write("\r\nSelect an option: "); 
            while (true) 
            { 
                switch (Console.ReadLine()) 
                { 
                case "1": 
                    Upload_Students(temp); 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "2": 
                    Upload_Teachers(temp); 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "3": 
                    student = Student.Parse(Console.ReadLine()); 
                    temp.Add(student); 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "4": 
                    teacher = Teacher.Parse(Console.ReadLine()); 
                    temp.Add(teacher); 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "5": 
                    student = Student.Parse(Console.ReadLine()); 
                    temp.Remove(student); 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "6": 
                    teacher = Teacher.Parse(Console.ReadLine()); 
                    temp.Remove(teacher); 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "7": 
                    lastN = temp.FindByLastName(Console.ReadLine()); 
                    foreach (IPerson S in lastN) 
                    { 
                        Console.WriteLine(S.ToString()); 
                    } 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "8": 
                        lastN = temp.FindByDepartment(Console.ReadLine()); 
                        foreach (IPerson T in lastN) 
                        { 
                            Console.WriteLine(T.ToString()); 
                        } 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "S": 
                    File.OpenWrite(@"D:\SomeDir2\input_teacher.txt"); 
                    foreach (Teacher T in temp.Teachers) 
                    { 
                        File.WriteAllText(@"D:\SomeDir2\input_teacher.txt", T.ToString()); 
                    } 
                    File.OpenWrite(@"D:\SomeDir2\input_student.txt"); 
                    foreach (Student S in temp.Students) 
                    { 
                        File.WriteAllText(@"D:\SomeDir2\input_student.txt", S.ToString()); 
                    } 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "s": 
                    File.OpenWrite(@"D:\SomeDir2\input_teacher.txt"); 
                    foreach (Teacher T in temp.Teachers) 
                    { 
                        File.WriteAllText(@"D:\SomeDir2\input_teacher.txt", T.ToString()); 
                    } 
                    File.OpenWrite(@"D:\SomeDir2\input_student.txt"); 
                    foreach (Student S in temp.Students) 
                    { 
                        File.WriteAllText(@"D:\SomeDir2\input_student.txt", S.ToString()); 
                    } 
                        Console.Write("\r\nSelect an option: "); 
                        break; 
                case "0": 
                    return true; 
                default: 
                    Console.Write("\r\nSelect an option: "); 
                    return false; 
                } 
            } 
        } 
    } 
} 
