namespace MSG
{
	public interface IKeyValueStorage
	{
		void SetValue(string key, string value);
		string GetValue(string key);
		void Save();
	}
}