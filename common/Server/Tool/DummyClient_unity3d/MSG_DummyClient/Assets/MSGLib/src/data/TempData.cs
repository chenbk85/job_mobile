using System;
namespace MSG
{
	public class TempData
	{
		private string name;
		public string Name 
		{ 
			get { return name; }
		}

		public string PlugPassword { get; set; }
		public string PlugIp { get;set; }
		public int PlugPort { get;set; }

		private IKeyValueStorage storage = StorageSingleton.Instance;
		
		public TempData(string name)
		{
			this.name = name;
			PlugPassword = null;
		}
		
		public void LoadTempData()
		{		
			PlugPassword = GetValue("PlugPassword");
			PlugIp = GetValue("PlugIp");
			string plugPortStr = GetValue("PlugPort");
			if( plugPortStr != null && plugPortStr != "" )
				PlugPort = int.Parse(plugPortStr);
		}
		
		public void SaveTempData()
		{
			if(PlugPassword != null)
				SetValue("PlugPassword", PlugPassword);
			if(PlugIp != null)
				SetValue("PlugIp", PlugIp);
			SetValue("PlugPort", PlugPort.ToString());
			storage.Save();
			
		}
		public void CacheAndSaveNecessaryData(Protocol.UAnsProtocol protocol)
		{
			if(protocol.type == Protocol.UAnsProtocol.Type.UANSCONNECT)
			{
				var ans = protocol.ansConnect;
				PlugIp = ans.ip;
				PlugPort = ans.port;
				PlugPassword = ans.passwd;
				SaveTempData();
			}
		}
		
		private void SetValue(string key, string value)
		{
			storage.SetValue(MakeKey(key), value);
		}
		private string GetValue(string key)
		{
			return storage.GetValue(MakeKey(key));
		}
		
		private string MakeKey(string key)
		{
			return Name + "." + key;
		}
	}
}