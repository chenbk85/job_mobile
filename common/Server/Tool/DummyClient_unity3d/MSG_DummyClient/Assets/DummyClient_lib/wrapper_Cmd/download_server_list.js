//#pragma strict


public var url : String = "http://nwmsvn.nwinet.co.kr/images/5/51/Server_list_xml.txt";

function Start () {
    var www : WWW = new WWW (url);
    yield www;
    
    var sc = GetComponent ("CmdEventManager");
    if(www.error!=null)
    {
        sc.SendMessage("SetServerListURL",url);
        sc.SendMessage("LoadServerList",null);
        //sc.LoadServerList(null,url);
        return;
    }
    sc.SendMessage("SetServerListURL",url);
    sc.SendMessage("LoadServerList",www.text);
    //sc.LoadServerList(www.text,url);
}

