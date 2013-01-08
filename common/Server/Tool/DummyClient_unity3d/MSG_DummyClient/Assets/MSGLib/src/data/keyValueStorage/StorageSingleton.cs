
namespace MSG
{
	public class StorageSingleton 
	{
		private static IKeyValueStorage instance = null;
		public static IKeyValueStorage Instance
		{
			get
			{
				if( instance == null)
					instance = MakeKeyValueStorage();
				return instance;
			}

		}
		private static IKeyValueStorage MakeKeyValueStorage()
		{
#if UNITY_3_0 || UNITY_3_0_0 || UNITY_3_1 || UNITY_3_2 || UNITY_3_3 || UNITY_3_4 || UNITY_3_5 || UNITY_4_0 || UNITY_4_1 || UNITY_4_2
			return new FileStorage(UnityEngine.Application.temporaryCachePath);
#else
			return new FileStorage();
#endif
		}

	}
}