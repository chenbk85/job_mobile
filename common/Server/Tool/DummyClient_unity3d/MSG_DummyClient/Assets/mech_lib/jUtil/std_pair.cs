
namespace nNWM
{
	public struct pair<T1, T2>
	{
		public T1 first { get; set; }
		public T2 second { get; set; }
	};

	public struct tuple<T1, T2 , T3>
	{
		public tuple(T1 _t1, T2 _t2, T3 _t3)
		{
			this.t1 = _t1;
			this.t2 = _t2;
			this.t3 = _t3;
		}

		public T1 t1{ get; set; }
		public T2 t2{ get; set; }
		public T3 t3{ get; set; }
	};
}