using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;
using nEXCEL;
using System.IO;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using ProtoBuf;
using nPROTO;

class BaseballClientNetworkDLL
{
    [DllImport("BaseballClientNetworkDLL.dll")]
    public static extern void DisplayHelloFromDLL();

    public static void Main_test1()
    {
        Console.WriteLine("This is C# program");
        DisplayHelloFromDLL();

    }



    public struct typeTest
    {
        //문자열 124
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public String strTest;

        //숫자형
        public int intTest;

        //바이트 배열
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] byteTest;

        //유니트형 배열
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public UInt32[] uintTest;
    }

    [DllImport("BaseballClientNetworkDLL.dll")]
    extern public static void OnTest1();

    [DllImport("BaseballClientNetworkDLL.dll")]
    extern public static int intOnTest2(int intTemp);

    [DllImport("BaseballClientNetworkDLL.dll")]
    extern public static string strOnTest3(string strTemp);

    [DllImport("BaseballClientNetworkDLL.dll")]
    extern public static void OnTest4(ref typeTest testTemp);

    [DllImport("BaseballClientNetworkDLL.dll")]
    extern public static void OnTest5(int[] intTemp);

    public static void Main_test2()
    {
        OnTest1();
        typeTest testTemp = new typeTest();

        testTemp.byteTest = new byte[64];
        testTemp.uintTest = new uint[4];

        testTemp.strTest = "aaa";
        testTemp.intTest = 1234;
        testTemp.byteTest[0] = 3;
        testTemp.uintTest[0] = 33;


        OnTest4(ref testTemp);

        Console.WriteLine("{1} {2} {3}", testTemp.intTest, testTemp.strTest, testTemp.byteTest[0]);

    }

}



namespace ClientSocket
{
    class ClientClass
    {
        public static Socket m_Socket;
        public static byte[] getbyte = new byte[1024];
        public static byte[] setbyte = new byte[1024];

        static void Load_CSV()
        {

            nEXCEL.nUtil.jCSV.Load_CSV();

            //             Sys_T_Test4 o4 = nEXCEL.CSV_Sys_T_Test4.Find(1);
            //             o4.Print();
            //             nEXCEL.CSV_Sys_T_Test4.Print();

            //nEXCEL.CSV_Sys_SubItemAbility.Print();

            //         nEXCEL.CSV_Sys_T_Test.Print();
            //         nEXCEL.CSV_Sys_T_Test2.Print();
            //         nEXCEL.CSV_Sys_T_Test3.Print();

            {
                //                 Console.WriteLine("\n\n---------------------");
                //                 nEXCEL.CSV_Sys_T_Test.Print();
                //                 nEXCEL.Sys_T_Test p = nEXCEL.CSV_Sys_T_Test.Find(nEXCEL.CSV_Sys_T_Test.Count - 1);
                //                 Console.WriteLine("\n\n---------------------");
                //                 if (p != null)
                //                     p.Print();
            }

            //             List<Sys_T_Test3> listT = nEXCEL.CSV_Sys_T_Test3.FindBy_base_type(EBuildType_test.EBTTT_Sys_T_HQ);
            //             foreach (Sys_T_Test3 p in listT)
            //             {
            //                 p.Print();
            //             }

            Console.WriteLine("csv로딩 OK");


        }
        static void Test_UReqConnect()
        {
            //UReqConnect 테스트

            UReqConnect sd = nPROTO.ug.Make_UReqConnect(0, 1001, 0
                                    , nPROTO.ug.Make_Version()
                                    , nPROTO.ug.Make_MemberInfo(1001, "avartar_url_test", "버스추월", true
                                    )
                                );

            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.reqConnect = sd;
            sendMsg.type = (UReqProtocol.Type.UREQCONNECT);

            byte[] sendSocketData = util.EncodingSize_To_Data(ug.Serialize(sendMsg));

            {
                //파일로 저장.
                using (var file = File.Create("d:\\UReqConnect.bin"))
                {
                    int iLen = sendSocketData.Length;
                    file.Write(sendSocketData, 0,iLen);
                }
            }


            nPROTO.UReqProtocol recvData = new nPROTO.UReqProtocol();
            ug.Decoding_FromSocketData(ref recvData , sendSocketData);

            if (recvData.type != nPROTO.UReqProtocol.Type.UREQCONNECT)
                throw new nPROTO.jException("ERROR : not recv UReqProtocol");
            nPROTO.UReqConnect rd = recvData.reqConnect;

            Console.WriteLine("UAnsConnect : {0}", rd.ToString());
        }



        private static void ConnectToServer_by_DummyClient()
        {


            //IPAddress serverIP = IPAddress.Parse("10.25.20.115");
            //int sPort = 2010;
            // icandoit 맥   IPAddress serverIP = IPAddress.Parse("10.25.21.104"); int sPort = 12000;
            // 이용운               IPAddress serverIP = IPAddress.Parse("10.25.20.37"); int sPort = 12000;
            // QA서버               IPAddress serverIP = IPAddress.Parse("182.162.130.57"); int sPort = 15200;
            IPAddress serverIP = IPAddress.Parse("10.25.21.104"); int sPort = 12000;

            int pp_id = 9001;

            IPEndPoint serverEndPoint = new IPEndPoint(serverIP, sPort);

            m_Socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            Console.WriteLine("-----------------------------------------------\n");
            Console.WriteLine("서버로 접속을 시작합니다. [ 엔터를 입력하세요. ]\n");
            Console.WriteLine("-----------------------------------------------\n");
            //Console.ReadLine();

            m_Socket.Connect(serverEndPoint);

            if (!m_Socket.Connected)
            {
                Console.WriteLine("연결 실패.\n");
                return;
            }
            Console.WriteLine("정상적으로 연결 되었습니다.\n");


            {
                //UReqConnect호출

                nPROTO.ug.Send(m_Socket
                                    , nPROTO.ug.Make_UReqConnect(0, pp_id, 0
                                        , nPROTO.ug.Make_Version()
                                        , nPROTO.ug.Make_MemberInfo(pp_id, "avartar_url_test", pp_id.ToString(), true
                                        )
                                    )
                                );


                //UAnsConnect 받기.^
                nPROTO.UAnsProtocol r = nPROTO.ug.Recv_UAnsProtocol(m_Socket);
                if (r.type != nPROTO.UAnsProtocol.Type.UANSCONNECT)
                    throw new nPROTO.jException("ERROR : not recv UAnsConnect");

                Console.WriteLine("UAnsConnect : {0}", r.ansConnect.ToString());
            }

            {
                ug.Send(m_Socket, ug.Make_UReqInfo());

                //UANSINFO 받기.^
                nPROTO.UAnsProtocol r = nPROTO.ug.Recv_UAnsProtocol(m_Socket);
                if (r.type != nPROTO.UAnsProtocol.Type.UANSINFO)
                    throw new nPROTO.jException("ERROR : not recv UANSINFO");

                Console.WriteLine("UANSINFO : {0}", r.ansInfo.ToString());
            }

            {
                string[] m_tables = {
                                      "tbl_user"
                                  };

                for (int i = 0; i < m_tables.Length; ++i)
                {
                    ug.Send(m_Socket, ug.Make_UReqGameInfo(i + 1, m_tables[i]));

                    nPROTO.UAnsProtocol r = nPROTO.ug.Recv_UAnsProtocol(m_Socket);
                    if (r.type != nPROTO.UAnsProtocol.Type.UANSDB)
                        throw new nPROTO.jException("ERROR : not recv UANSDB");

                    Console.WriteLine("UANSDB : {0}", r.ansDB.ToString());

                }

            }

            {
                //UReqAutoJoin호출
                nPROTO.ug.Send(m_Socket, nPROTO.ug.Make_UReqAutoJoin(0, 0));

                //UAnsAutoJoin 받기.
                nPROTO.UAnsProtocol r = nPROTO.ug.Recv_UAnsProtocol(m_Socket);
                if (r.type != nPROTO.UAnsProtocol.Type.UANSAUTOJOIN)
                    throw new nPROTO.jException("ERROR : not recv UAnsAutoJoin");

                //                 GameRoomInfo gri = GameRoomInfo.CreateBuilder().MergeFrom(r.AnsAutoJoin.GameRoomInfo).Build();
                //                 Console.WriteLine("UAnsAutoJoin : {0} ", gri.RoomId);
            }

            {
                //GLReqGameProtocal호출
                nPROTO.ug.Send(m_Socket, PT_BaseballServer.Build_x2bs_echo(2345, "x2bs_echo msg",1234));

                //UAnsAutoJoin 받기.
                UAnsProtocol r = nPROTO.ug.Recv_UAnsProtocol(m_Socket);
                if (r.type != UAnsProtocol.Type.GLANSGAMEPROTOCOL)
                    throw new nPROTO.jException("ERROR : not recv GLANSGAMEPROTOCOL");

                BaseballServer_Client r2 = new BaseballServer_Client();
                ug.Recv(ref r2, r);
                if (r2.type != BaseballServer_Client.Type.bs2x_echo)
                    throw new nPROTO.jException("ERROR : not recv bs2x_echo");

                Console.WriteLine("bs2x_echo : {0} ", r2.m_bs2x_echo.ToString());
            }


            /*

            {
                nPROTO.ug.Send(m_Socket, PT_BaseballServer.Build_req_timer_start(5, "req_timer_start msg"));
                while (true)
                {
                    try
                    {
                        UAnsProtocol r = nPROTO.ug.Recv_UAnsProtocol(m_Socket);

                        if (r.type != UAnsProtocol.Type.GLANSGAMEPROTOCOL)
                        {
                            continue;
                        }

                        BaseballServer_Client r2;
                        nPROTO.ug.Recv(ref r2, r);
                        if (r2.type != BaseballServer_Client.Type.ans_timer_start)
                            throw new nPROTO.jException("ERROR : not recv ans_timer_start");

                        Console.WriteLine("ans_timer_start : {0} ", r2.m_ans_timer_start.ToString());
                    }
                    catch (System.Exception ex)
                    {
                        Console.WriteLine("[WARN]ans_timer_start : {0} ", ex.ToString());


                    }
                }
            }
 * 
 */
        }//private static void ConnectToServer_by_DummyClient()


        static void Main(string[] args)
        {

            //BaseballClientNetworkDLL.Main_test1();
            //BaseballClientNetworkDLL.Main_test2();

            Load_CSV();
            return;

            ConnectToServer_by_DummyClient();

            //{// 테스트 코드 : UAnsConnect를 만들어서 인코딩 /디코딩하여 확인해봄.
            //    nPROTO.UAnsConnect ans = nPROTO.nTest.Make_UAnsConnect(1, 2, 3, "ipip", 456, "pwd");
            //    byte[] sendBuffer = nPROTO.nTest.Encoding_ToSocketData(ans);

            //    nPROTO.UAnsProtocol ans2 = new nPROTO.UAnsProtocol();
            //    nPROTO.ug.Decoding_FromSocketData(ref ans2, sendBuffer);
            //    nPROTO.UAnsProtocol.Type type = ans2.type;
            //    Console.WriteLine("type = {0}", type.ToString());
            //    if (type != nPROTO.UAnsProtocol.Type.UANSCONNECT)
            //    {
            //        throw new nPROTO.jException("type != nPROTO.UAnsProtocol.Type.UANSCONNECT");
            //    }

            //}
            
            return;

        }
    }
}



