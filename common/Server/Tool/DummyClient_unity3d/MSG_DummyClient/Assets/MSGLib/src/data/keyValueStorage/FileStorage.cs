using System;
using System.Collections.Generic;
using System.IO;
namespace MSG
{
	public class FileStorage : IKeyValueStorage
	{
		private const string FileName = "NetTemp.dat";
		private string filePath;
		public string FilePath {get;set;}
		
		private Dictionary<string,string> dic = new Dictionary<string, string>();
		
		public FileStorage()
		{
			string assemblyPath =  System.Reflection.Assembly.GetExecutingAssembly().Location;
			string dir = System.IO.Path.GetDirectoryName(assemblyPath);
			this.filePath = System.IO.Path.Combine(dir,FileName);
			LoadFromFile();
		}
		public FileStorage(string fileDir)
		{	
			this.filePath = System.IO.Path.Combine(fileDir,FileName);
			LoadFromFile();
		}
		
		public void SetValue(string key, string value)
		{
			dic[key] = value;
		}
		public string GetValue(string key)
		{
			try
			{
				return dic[key];
			}
			catch(Exception)
			{
				return null;
			}
		}
		public void Save()
		{
			SaveToFile();
		}
		
		private void LoadFromFile()
		{
			dic.Clear();
			try
			{
				FileStream fs = new FileStream(filePath,FileMode.Open);
				KeyValueList list = ProtoBuf.Serializer.Deserialize<KeyValueList>(fs);
				foreach(KeyValue keyValue in list.list)
				{
					dic[keyValue.key] = keyValue.value;
				}
			}
			catch(Exception)
			{
			}
		}
		private void SaveToFile()
		{
			try
			{
				FileStream fs = new FileStream(filePath, FileMode.Create);
				KeyValueList list = new KeyValueList();
				foreach(string orgkey in dic.Keys)
				{
					KeyValue keyValue = new KeyValue
					{
						key = orgkey,
						value = dic[orgkey]
					};
					list.list.Add(keyValue);
				}
				ProtoBuf.Serializer.Serialize<KeyValueList>(fs, list);
			}
			catch(Exception)
			{
			}
			
		}
	}
}