using System;
namespace nNWM
{
    public class jString
    {
        public static string[] jSplit(string val, string token)
        {
            char[] dele = new char[token.Length];
            int i=0;
            foreach (var c in token)
            {
                dele[i++] = c;
            }
            return val.Split(dele);
        }

    }
}