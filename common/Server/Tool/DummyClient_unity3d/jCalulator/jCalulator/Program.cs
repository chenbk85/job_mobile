using System;

namespace Evaluant.Calculator.Play
{
    /// <summary>
    /// Summary description for Program.
    /// </summary>
    public class Program
    {
        public static void Main(string[] args)
        {
            string[] expressions = new string[]
			{
				"2 + 3 + 5",
				"2 * 3 + 5",
				"2 * (3 + 5)",
				"2 * (2*(2*(2+1)))",
				"10 % 3",
				"true or false",
				"false || not (false and true)",
				"3 > 2 and 1 <= (3-2)",
				"3 % 2 != 10 % 3",
			};

            Expression ex;
            foreach (string expression in expressions)
            {
                ex = new Expression(expression);
                Object eval = ex.Evaluate();
                decimal d = (decimal)ex.Evaluate();
                float f = (float)d;
                Console.WriteLine("{0} = {1}", expression, eval.ToString());
            }
        }
    }
}
