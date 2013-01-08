using System.Collections.Generic;
namespace MSG
{
	public class CountingQueue<T>
	{			
		private static Queue<Pair<T,BoolWrapper>> pairRecyclingPool = new Queue<Pair<T,BoolWrapper>>(); /** To avoid gc lag */
		private static object recyclingPoolLock = new object();
		
		private Queue<Pair<T,BoolWrapper>> queue; /** item and isDropableItem */
		private int count;
		
		private int maxCount;
		public int MaxCount
		{
			get { return maxCount; }
			set { maxCount = value; }
		}
		
		private object thisLock = new object();
		
		
		public int Count
		{
			get{ return queue.Count; }
		}
		
		public bool IsCountFull
		{
			get{ return count >= maxCount; }
		}
		
		
		public CountingQueue(int maxCount)
		{
			lock(thisLock)
			{
				this.maxCount = maxCount;
				queue = new Queue<Pair<T,BoolWrapper>>(maxCount);		
			}
		}
				
		public void Clear()
		{
			lock(thisLock)
			{
				queue.Clear();
			}
		}
		
		public T Dequeue()
		{
			lock(thisLock)
			{
				if( queue.Count == 0 )
					return default(T);
			}
	
			Pair<T,BoolWrapper> pair;
			T item;
			
			lock(thisLock)
			{
				pair = queue.Dequeue();
				if(pair.Second.Value)
					count--;
			}
			
			item = pair.First;
			pair.First = default(T);
			pair.Second.Value = false;
			
			lock(recyclingPoolLock)
			{
				pairRecyclingPool.Enqueue(pair);								
			}
			
			return item;
		}
		public void Enqueue(T item)
		{
			Enqueue(item, false);
		}
		public void Enqueue(T item, bool isCountable)
		{
			ReallyEnqueue(item, isCountable);
		}	
		private void ReallyEnqueue(T item, bool isCountable)
		{
			Pair<T,BoolWrapper> pair = null;
			
			lock(recyclingPoolLock)
			{
				if(pairRecyclingPool.Count > 0)
					pair = pairRecyclingPool.Dequeue();
			}
			
			if(pair == null)
			{
				pair = new Pair<T, BoolWrapper>(item, new BoolWrapper(isCountable));
			}
			else
			{
				pair.First = item;
				pair.Second.Value = isCountable;
			}
			
			lock(thisLock)
			{
				queue.Enqueue(pair);				
				if(isCountable)
					count++;
			}
		}
		
		
		
	}
}