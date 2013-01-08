using System;
using System.Text;

using Evaluant.Calculator.Domain;
using NUnit.Framework;

using Antlr.Runtime;
using Antlr.Runtime.Tree;

namespace Evaluant.Calculator
{
    [TestFixture]
    public class Tests
    {
        public Tests()
        {
        }

        public CommonTree Parse(string expression)
        {
            ECalcLexer lexer = new ECalcLexer(new ANTLRStringStream(expression));
            ECalcParser parser = new ECalcParser(new CommonTokenStream(lexer));

            return (CommonTree)parser.expression().Tree;
        }

        [Test]
        public void ParserShouldHandleSimpleExpressions()
        {
            ECalcLexer lexer = new ECalcLexer(new ANTLRStringStream("3*(5+2)"));
            ECalcParser parser = new ECalcParser(new CommonTokenStream(lexer));

            parser.expression();
        }

        [Test]
        public void ParserShouldHandleBasExpressions()
        {
            ECalcLexer lexer = new ECalcLexer(new ANTLRStringStream("3*(5+2"));
            ECalcParser parser = new ECalcParser(new CommonTokenStream(lexer));

            try
            {
                parser.expression();
                Assert.Fail();
            }
            catch (Exception e)
            {
                Console.Error.WriteLine("Parser exception: " + e.Message);
            }
        }

        [Test]
        public void ParserShouldHandleTree()
        {
            ECalcLexer lexer = new ECalcLexer(new ANTLRStringStream(" 2 * (3 + 5)"));
            ECalcParser parser = new ECalcParser(new CommonTokenStream(lexer));

            CommonTree tree = (CommonTree)parser.expression().Tree;
            Console.WriteLine(tree.ToStringTree());
        }

        [Test]
        public void LogicalExpressionShouldCreateInteger()
        {
            Value expression = LogicalExpression.Create(Parse("2")) as Value;
            Assert.IsNotNull(expression);
            Assert.AreEqual("2", expression.Text);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(2, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateNot()
        {
            UnaryExpression expression = LogicalExpression.Create(Parse("not true")) as UnaryExpression;
            Assert.IsNotNull(expression);
            Assert.AreEqual(typeof(Value), expression.Expression.GetType());

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(false, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateTimes()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 * 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Times, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(6, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateDiv()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 / 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Div, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(1.5, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateModulo()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 % 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Modulo, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(1, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateMinus()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 - 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Minus, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(1, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreatePlus()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 + 2 + 5")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Plus, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(10, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateLesser()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 < 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Lesser, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(false, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateLesserOrEqual()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 <= 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.LesserOrEqual, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(false, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateGreater()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 > 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.Greater, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(true, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldCreateGreaterOrEqual()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 >= 2")) as BinaryExpresssion;
            Assert.IsNotNull(expression);
            Assert.AreEqual(BinaryExpressionType.GreaterOrEqual, expression.Type);

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(true, visitor.Result);
        }

        [Test]
        public void LogicalExpressionShouldHandlePrecedence()
        {
            BinaryExpresssion expression = LogicalExpression.Create(Parse("3 * (5 + 2)")) as BinaryExpresssion;

            EvaluationVisitor visitor = new EvaluationVisitor();
            visitor.Visit(expression);
            Assert.AreEqual(21, visitor.Result);

            Assert.AreEqual(40, new Expression("5 * 2 ^ 3").Evaluate());
        }

        [Test]
        public void ExpressionShouldEvaluate()
        {
            string[] expressions = new string[]
            {
                "2 + 3 + 5",
                "2 * 3 + 5",
                "2 * (3 + 5)",
                "2 * (2*(2*(2+1)))",
                "10 % 3",
                "true or false",
                "not true",
                "false || not (false and true)",
                "3 > 2 and 1 <= (3-2)",
                "3 % 2 != 10 % 3"
            };

            foreach (string expression in expressions)
                Console.WriteLine("{0} = {1}",
                    expression,
                    new Expression(expression).Evaluate());
        }

        [Test]
        public void ShouldParseValues()
        {
            Assert.AreEqual(123456, new Expression("123456").Evaluate());
            Assert.AreEqual(new DateTime(2001, 01, 01), new Expression("#01/01/2001#").Evaluate());
            Assert.AreEqual(123.456, new Expression("123.456").Evaluate());
            Assert.AreEqual(true, new Expression("true").Evaluate());
            Assert.AreEqual("true", new Expression("'true'").Evaluate());
            Assert.AreEqual("azerty", new Expression("'azerty'").Evaluate());
        }

        [Test]
        public void ShouldHandleUnicode()
        {
            Assert.AreEqual(123456, new Expression("123456").Evaluate());
        }

        [Test]
        public void ShouldEscapeCharacters()
        {
            Assert.AreEqual("'hello'", new Expression(@"'\'hello\''").Evaluate());
            Assert.AreEqual(" ' hel lo ' ", new Expression(@"' \' hel lo \' '").Evaluate());
            Assert.AreEqual("\u0040", new Expression(@"'\u0040'").Evaluate());
        }

        [Test]
        public void ShouldDisplayErrorMessages()
        {
            try
            {
                new Expression("(3 + 2").Evaluate();
                Assert.Fail();
            }
            catch(EvaluationException e)
            {
                Console.WriteLine("Error catched: " + e.Message);
            }
        }

        [Test]
        public void Maths()
        {
            Assert.AreEqual(1, new Expression("Abs(-1)").Evaluate());
            Assert.AreEqual(0, new Expression("Acos(1)").Evaluate());
            Assert.AreEqual(0, new Expression("Asin(0)").Evaluate());
            Assert.AreEqual(0, new Expression("Atan(0)").Evaluate());
            Assert.AreEqual(2, new Expression("Ceiling(1.5)").Evaluate());
            Assert.AreEqual(1, new Expression("Cos(0)").Evaluate());
            Assert.AreEqual(1, new Expression("Exp(0)").Evaluate());
            Assert.AreEqual(1, new Expression("Floor(1.5)").Evaluate());
            Assert.AreEqual(-1, new Expression("IEEERemainder(3,2)").Evaluate());
            Assert.AreEqual(0, new Expression("Log(1,10)").Evaluate());
            Assert.AreEqual(0, new Expression("Log10(1)").Evaluate());
            Assert.AreEqual(9, new Expression("Pow(3,2)").Evaluate());
            Assert.AreEqual(3.22, new Expression("Round(3.222,2)").Evaluate());
            Assert.AreEqual(-1, new Expression("Sign(-10)").Evaluate());
            Assert.AreEqual(0, new Expression("Sin(0)").Evaluate());
            Assert.AreEqual(2, new Expression("Sqrt(4)").Evaluate());
            Assert.AreEqual(0, new Expression("Tan(0)").Evaluate());
        }

        #if NET20
        [Test]
        public void ExpressionShouldEvaluateCustomFunctions()
        {
            Expression e = new Expression("SecretOperation(3, 6)");
            e.EvaluateFunction += delegate(string name, FunctionArgs args)
                {
                    if (name == "SecretOperation")
                        args.Result = (int)args.Parameters[0] + (int)args.Parameters[1];
                };

            Assert.AreEqual(9, e.Evaluate());
        }


        [Test]
		public void ExpressionShouldEvaluateParameters()
		{
			Expression e = new Expression("Round(Pow([Pi], 2) + Pow([Pi2], 2) + [X], 2)");
		    
			e.Parameters["Pi2"] = new Expression("[Pi] * [Pi]");
			e.Parameters["X"] = 10;

			e.EvaluateParameter += delegate(string name, ParameterArgs args)
				{
					if (name == "Pi")
						args.Result = 3.14;
				};

			Assert.AreEqual(117.07, e.Evaluate());
		}
		#endif
    }
}

