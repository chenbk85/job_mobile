using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

using ProtoBuf;
using ProtoBuf.Meta;
using ProtoTest;

namespace MySerializer
{
    class Program
    {
        static void Main(string[] args)
        {

            var model = TypeModel.Create();
            ArrayList list = ProtoTest.Regist_MyModel.GetTypes();

            foreach (object o in list)
            {
                System.Type t = (System.Type)o;
                model.Add(t, true);
            }
            model.Compile("MySerializer", "MySerializer.dll");

            
        }
    }
}
