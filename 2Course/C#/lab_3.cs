using System; 
using System.Collections.Generic; 
 
namespace Lab_С_sharp_3 
{ 
    interface IExpr 
    { 
        double Compute(IReadOnlyDictionary<string, double> variableValues); 
        IEnumerable<string> Variables { get; } 
        bool IsConstant { get; } 
        bool IsPolynom { get; } 
    } 
    abstract class UnaryOperation 
    { 
        public Variable X { get; set; } 
        public Variable Result { get; } 
    } 
    abstract class Function : Variable 
    { 
        public Variable X { get; set; } 
        public Variable Y { get; set; } 
        Constant C { get; } 
    } 
    class Variable 
    { 
        public string Name { set; get; } 
        public double Value { set; get; } 
        public static Variable operator +(Variable A, Variable B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value + B.Value; 
            return C; 
        } 
        public static Variable operator -(Variable A, Variable B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value - B.Value; 
            return C; 
        } 
        public static Variable operator *(Variable A, Variable B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value * B.Value; 
            return C; 
        } 
        public static Variable operator /(Variable A, Variable B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value / B.Value; 
            return C; 
        } 
        public static Variable operator +(Variable A, Constant B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value + B.value; 
            return C; 
        } 
        public static Variable operator -(Variable A, Constant B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value - B.value; 
            return C; 
        } 
        public static Variable operator *(Variable A, Constant B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value * B.value; 
            return C; 
        } 
        public static Variable operator /(Variable A, Constant B) 
        { 
            Variable C = new Variable { Name = "c" }; 
            C.Value = A.Value / B.value; 
            return C; 
        } 
    } 
    abstract class BinaryOperation : Variable 
    { 
        public Variable X { get; set; } 
        public Variable Y { get; set; } 
        public Variable Result { set; get; } 
    } 
    class Constant 
    { 
        public readonly double value; 
        public Constant(double Value) 
        { 
            value = Value; 
        } 
        public static Constant operator +(Constant A, Constant B) 
        { 
            return new Constant(A.value + B.value); 
        } 
        public static Constant operator -(Constant A, Constant B) 
        { 
            return new Constant(A.value - B.value); 
        } 
        public static Constant operator *(Constant A, Constant B) 
        { 
            return new Constant(A.value * B.value); 
        } 
        public static Constant operator /(Constant A, Constant B) 
        { 
            return new Constant(A.value / B.value); 
        } 
    } 
    class U_minus : UnaryOperation 
    { 
        U_minus(Variable A) 
        { 
            X = A; 
        } 
        override public String ToString() 
        { 
            return "(-" + X.Name + ')'; 
        } 
    } 
    class Add : BinaryOperation 
    { 
        public Add(Variable A, Variable B) 
        { 
            Value = A.Value + B.Value; 
        } 
        override public String ToString() 
        { 
            return '(' + X.Name + '+' + Y.Name + ')'; 
        } 
    } 
    class Sub : BinaryOperation 
    { 
        Sub(Variable A, Variable B) 
        { 
            X = A; 
            Y = B; 
        } 
        override public String ToString() 
        { 
            return '(' + X.Name + '-' + Y.Name + ')'; 
        } 
    } 
    class Mult : BinaryOperation 
    { 
        public Mult(Variable A, Variable B) 
        { 
            X = A; 
            Y = B; 
            Value = A.Value * B.Value; 
        } 
        public Mult(Variable A, Constant B) 
        { 
            X = A; 
            Y.Value = B.value; 
        } 
        override public String ToString() 
        { 
            return '(' + X.Name + '*' + Y.Name + ')'; 
        } 
    } 
    class Divide : BinaryOperation 
    { 
        public Divide(Variable A, Variable B) 
        { 
            X = A; 
            Y = B; 
        } 
        public Divide(Variable A, Constant B) 
        { 
            Value = A.Value / B.value; 
        } 
        override public String ToString() 
        { 
            return '(' + X.Name + '/' + Y.Name + ')'; 
        } 
    } 
    class SinFunc : Function 
    { 
        public SinFunc(Variable A) 
        { 
            Value = Math.Sin(A.Value); 
        } 
    } 
    class Program 
    { 
        public static Constant Sin(Variable A) 
        { 
            return new Constant(Math.Sin(A.Value)); 
        } 
        static void Main() 
        { 
            var a = new Variable { Name = "a" }; 
            var b = new Variable { Name = "b" }; 
            var c = new Constant(2); 
            a.Value = Convert.ToSingle(Console.ReadLine()); 
            b.Value = Convert.ToSingle(Console.ReadLine()); 
            var expr0 = new Mult(new Add(a, b), new SinFunc(new Divide(a, new Constant(2)))); 
            var expr = (a + b) * Sin(a / c); 
            Console.WriteLine(expr.Value); 
            Console.WriteLine(expr0.Value); 
        } 
    } 
} 
