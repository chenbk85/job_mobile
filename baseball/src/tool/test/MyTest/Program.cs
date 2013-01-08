using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

using ProtoTest;

namespace MyTest
{

    class Program
    {
        public static MyModel myNewModel = null;
        public static MySerializer mySerializer = null;
        public static void file_save_test()
        {
            try
            {
                myNewModel = new MyModel();
                myNewModel.enum1 = TestEnum.walk;
                myNewModel.intList = new List<int>();
                myNewModel.stringList = new List<string>();
                myNewModel.int2 = 4321;
                for (int i = 0; i < 5; i++)
                {
                    myNewModel.intList.Add(i);
                    myNewModel.stringList.Add("string : " + i.ToString());
                }

                mySerializer = new MySerializer();
                using (var file = File.Create("MyModel.bin.data"))
                {
                    mySerializer.Serialize(file, myNewModel);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}", e.ToString());
                throw new Exception(e.ToString());
            }
        }

        static void Main(string[] args)
        {
            file_save_test();
        }
    }
}
