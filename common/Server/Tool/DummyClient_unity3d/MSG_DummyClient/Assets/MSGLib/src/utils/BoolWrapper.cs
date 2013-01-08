using UnityEngine;
using System.Collections;

namespace MSG
{
	public class BoolWrapper
	{
		public bool Value { get; set; }
		
		public BoolWrapper(bool val)
		{
			this.Value = val;
		}
		
	}
}