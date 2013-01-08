using System;
using System.Text;

namespace Evaluant.Calculator
{
    public delegate void EvaluateFunctionHandler(string name, FunctionArgs args);
    public delegate void EvaluateParameterHandler(string name, ParameterArgs args);
    public class EvaluationException : ApplicationException
    {
        public EvaluationException(string message)
            : base(message)
        {
        }

        public EvaluationException(string message, Exception innerException)
            : base(message, innerException)
        {
        }

    }
    public class ParameterArgs : EventArgs
    {
        public ParameterArgs()
        {
        }

        private object result;

        public object Result
        {
            get { return result; }
            set { result = value; }
        }
    }

}
