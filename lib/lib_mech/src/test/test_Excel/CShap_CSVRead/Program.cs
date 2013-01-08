using System;
using System.Collections.Generic;
// using System.Linq;
// using System.Text;
// using System.IO;
using nEXCEL;

/*
namespace nEXCEL
{
    public static class jCSV_Sys_T_Test2_Helper
    {
        public static void FromString(this jCSV This,string s, ref Sys_T_Test2 o)
        {
            if(Char.IsNumber(s[0]))
            {
                CSV_Sys_T_Test2.Find(int.Parse(s));
            }
            else
            {
                CSV_Sys_T_Test2.FindBy_name(s);
            }
        }
    }
}
*/

class Program
{
    static void Main(string[] args)
    {
        nEXCEL.CSV_Sys_T_Test.LoadCSV("./file_Sys_T_Test.csv");
        nEXCEL.CSV_Sys_T_Test2.LoadCSV("./file_Sys_T_Test2.csv");
        nEXCEL.CSV_Sys_T_Test3.LoadCSV("./file_Sys_T_Test3.csv");
        nEXCEL.CSV_Sys_T_Test4.LoadCSV("./file_Sys_T_Test4.csv");
        nEXCEL.nUtil.jCSV.PostParse();


        Sys_T_Test4 o4 = nEXCEL.CSV_Sys_T_Test4.Find(1);
        o4.Print();

        nEXCEL.CSV_Sys_T_Test4.Print();


//         nEXCEL.CSV_Sys_T_Test.Print();
//         nEXCEL.CSV_Sys_T_Test2.Print();
//         nEXCEL.CSV_Sys_T_Test3.Print();


        {
            Console.WriteLine("\n\n---------------------");
            nEXCEL.CSV_Sys_T_Test.Print();
            nEXCEL.Sys_T_Test p = nEXCEL.CSV_Sys_T_Test.Find(nEXCEL.CSV_Sys_T_Test.Count()-1);
            Console.WriteLine("\n\n---------------------");
            if (p != null)
                p.Print();
        }


        List<Sys_T_Test3> listT = nEXCEL.CSV_Sys_T_Test3.FindBy_base_type(EBuildType_test.EBTTT_Sys_T_HQ);
        foreach (Sys_T_Test3 p in listT)
        {
            p.Print();
        }

    }
}
