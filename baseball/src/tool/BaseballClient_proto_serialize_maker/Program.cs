using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

using ProtoBuf;
using ProtoBuf.Meta;
using nPROTO;
using nEXCEL;


namespace BaseballClient_proto_serialize_maker
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                var model = TypeModel.Create();
                {
                    {
                        ArrayList list = excel_baseball_table_db_proto_contract.GetTypes();
                        foreach (object o in list)
                        {
                            System.Type t = (System.Type)o;
                            model.Add(t, true);
                        }
                    }
                    {
                        ArrayList list = PT_BaseballServer_proto_contract.GetTypes();
                        foreach (object o in list)
                        {
                            System.Type t = (System.Type)o;
                            model.Add(t, true);
                        }
                    }
                    {
                        ArrayList list = PT_UserGateServer_proto_contract.GetTypes();
                        foreach (object o in list)
                        {
                            System.Type t = (System.Type)o;
                            model.Add(t, true);
                        }
                    }
                    //----------------------------------------------------------------
                    //- ug.cs
                    model.Add(typeof(nPROTO.Version), true);
                    model.Add(typeof(Error), true);
                    model.Add(typeof(Desc), true);
                    model.Add(typeof(Notice), true);
                    model.Add(typeof(UError), true);
                    model.Add(typeof(UReqConnect), true);
                    model.Add(typeof(UAnsConnect), true);
                    model.Add(typeof(UReqNotice), true);
                    model.Add(typeof(UAnsNotice), true);
                    model.Add(typeof(UReqChannel), true);
                    model.Add(typeof(UAnsChannel), true);
                    model.Add(typeof(UErrChannel), true);
                    model.Add(typeof(UReqStore), true);
                    model.Add(typeof(UAnsStore), true);
                    model.Add(typeof(UReqInfo), true);
                    model.Add(typeof(UAnsInfo), true);
                    model.Add(typeof(UReqAutoJoin), true);
                    model.Add(typeof(UAnsAutoJoin), true);
                    model.Add(typeof(UReqLeaveGame), true);
                    model.Add(typeof(UAnsLeaveGame), true);
                    model.Add(typeof(UReqClose), true);
                    model.Add(typeof(UAnsClose), true);
                    model.Add(typeof(UReqPong), true);
                    model.Add(typeof(UAnsPing), true);
                    model.Add(typeof(UReqPlug), true);
                    model.Add(typeof(UAnsPlug), true);
                    model.Add(typeof(UReqProtocol), true);
                    model.Add(typeof(UAnsProtocol), true);
                    model.Add(typeof(MemberInfo), true);

                    //----------------------------------------------------------------
                    //- db.cs
                    model.Add(typeof(DBIn), true);
                    model.Add(typeof(ReqDB), true);
                    model.Add(typeof(AnsDB), true);

                    //----------------------------------------------------------------
                    //- gameLogic.cs
                    model.Add(typeof(EUserGPS), true);
                    model.Add(typeof(GameUserInfo), true);
                    model.Add(typeof(GameInfo), true);
                    model.Add(typeof(s_game_play_info), true);
                    model.Add(typeof(s_result_round), true);
                    model.Add(typeof(s_result_game), true);
                    model.Add(typeof(GameRoomInfo), true);
                    model.Add(typeof(s_vector3), true);
                    model.Add(typeof(s_vector2), true);
                    model.Add(typeof(s_pitcher_throw_info), true);                
                    model.Add(typeof(s_better_hit_info), true);                
                    model.Add(typeof(GLReqGameProtocol), true);
                    model.Add(typeof(GLAnsGameProtocol), true);
                }

                model.Compile("BaseballClient_proto_Serializer", "BaseballClient_proto_Serializer.dll");
                Console.WriteLine("BaseballClient_proto_Serializer.dll 생성 성공.");
            }
            catch (System.Exception ex)
            {
                Console.WriteLine("BaseballClient_proto_Serializer.dll 생성 에러.");
                Console.WriteLine("{1}", ex.ToString());

            }
        }
    }
}
