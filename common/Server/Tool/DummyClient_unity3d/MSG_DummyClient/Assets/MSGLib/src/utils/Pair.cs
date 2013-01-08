namespace MSG
{
	public class Pair<FirstType, SecondType> {
		private FirstType first;
		private SecondType second;
		
		public FirstType First
		{ 
			get { return first; }
			set { first = value; }
		}
		public SecondType Second
		{ 
			get { return second; }
			set { second = value; }
		}
		
		public Pair(FirstType first, SecondType second)
		{
			this.first = first;
			this.second = second;
		}
		
		public override bool Equals(object obj)
		{
			if(obj == null)
				return false;
			if(obj == this)
				return true;
			
			Pair<FirstType, SecondType> other = obj as Pair<FirstType, SecondType>;
			if(other == null)
				return false;
			
			return ( ((first == null) && (other.first == null)) || (first != null) && first.Equals(other.first) )
				&& ( ((second == null) && (other.second == null)) || (second != null) && second.Equals(other.second) );
		}
		
		public override int GetHashCode()
   	 	{
	        int hashcode = 0;
	        if (first != null)
	            hashcode += first.GetHashCode();
	        if (second != null)
	            hashcode += second.GetHashCode();
	
	        return hashcode;
    	}

	}
}