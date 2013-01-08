using System;
using System.Collections.Generic;
using System.Net.Sockets;
namespace MSG
{
	public class MSGEventQueue
	{
		
		private static Queue<MSGEvent> eventRecyclingPool = new Queue<MSGEvent>();
		private static object recyclingPoolLock = new object();
		
		private CountingQueue<MSGEvent> queue;
		private Logger logger = null;
		
		private delegate void InitEventFuc(MSGEvent e);
		
		public int MaxMsgCount
		{
			get { return queue.MaxCount; }
			set { queue.MaxCount = value; }
		}
		
		public int MsgCount
		{
			get { return queue.MaxCount;}
		}
		
		public bool IsMsgFull
		{
			get { return queue.IsCountFull; }
		}
		
		public MSGEventQueue (int maxMsgCount, Logger logger)
		{
			queue = new CountingQueue<MSGEvent>(maxMsgCount);
			MaxMsgCount = maxMsgCount;
			this.logger = logger;
		}
		
		public void Clear()
		{
			queue.Clear();
		}
		
		public MSGEvent Dequeue()
		{
			return queue.Dequeue();
		}
		
		
		public void EnqueueConnectEvent(string ip, int port)
		{
			EnqueueEvent(
				(e) => e.InitToConnected(ip,port)
				);
		}
		public void EnqueueDisconnectEvent(MSGDisconnected.ReasonEnum reason)
		{
			EnqueueEvent(
				(e) => e.InitToDisconnected(reason)
				);
		}		
		public void EnqueueRecvMessageEvent(AnswerMessage ans)
		{
			EnqueueEvent(
				(e) => e.InitToRecvMessage(ans)
				);
		}
		public void EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum errType, int errCode, string errMsg)
		{
			EnqueueEvent(
				(e) => e.InitToErrorRecv(errType, errCode, errMsg)
				);
		}
		public void EnqueueErrorSendEvent(MSGError.ErrorTypeEnum errType, int errCode, string errMsg)
		{
			EnqueueEvent(
				(e) => e.InitToErrorSend(errType, errCode, errMsg)
				);
		}
		public void EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum errType, int errCode, string errMsg)
		{
			EnqueueEvent(
				(e) => e.InitToErrorConnect(errType, errCode, errMsg)
				);
		}
		private void EnqueueEvent(InitEventFuc initFuc)
		{
			MSGEvent e = NewOrDequeueFromPoolNetEvent();
			initFuc(e);
			queue.Enqueue(e);
			logger.d("Event Logged =>" + e.EventType.ToString());
			
		}


		public void EnqueueConnectException(Exception exception)
		{
			try
			{
				throw exception;
			}
			catch(ArgumentOutOfRangeException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.InvalidIpOrUrlOrPort, 0, ex.Message);
			}
			catch(ArgumentNullException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.InvalidIpOrUrlOrPort, 0, ex.Message);
			}
			catch(ArgumentException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.InvalidIpOrUrlOrPort, 0, ex.Message);
			}
			catch(SocketException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.ErrorFromSocket, ex.ErrorCode, ex.Message);
			}
			catch(ObjectDisposedException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.SocketHasBeenClosed, 0, ex.Message);
			}
			catch(NotSupportedException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.SocketNotSupported, 0, ex.Message);
			}
			catch(InvalidOperationException ex)
			{
				EnqueueErrorConnectEvent(MSGError.ErrorTypeEnum.InvalidSocketStatus, 0, ex.Message);
			}
		}
		public void EnqueueReceiveException(Exception exception)
		{
			try
			{
				throw exception;
			}
			catch(ArgumentNullException ex)
			{
				EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum.BufferError,0,ex.ToString());
			}
			catch(ArgumentOutOfRangeException ex)
			{
				EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum.BufferError, 0, ex.ToString());
			}
			catch(SocketException ex)
			{
				EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum.ErrorFromSocket, ex.ErrorCode, ex.ToString());
			}
			catch(ObjectDisposedException ex)
			{
				EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum.SocketHasBeenClosed, 0, ex.Message);
			}
			catch(System.Security.SecurityException ex)
			{
				EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum.NoPermission, 0, ex.Message);
			}
			catch(global::ProtoBuf.ProtoException ex)
			{
				EnqueueErrorRecvEvent(MSGError.ErrorTypeEnum.ProtoBufException, 0, ex.Message);
			}
		}
		public void EnqueueSendException(Exception exception)
		{
			try
			{
				throw exception;
			}
			catch(ArgumentNullException ex)
			{
				EnqueueErrorSendEvent(MSGError.ErrorTypeEnum.BufferError, 0, ex.ToString());
			}
			catch(ArgumentOutOfRangeException ex)
			{
				EnqueueErrorSendEvent(MSGError.ErrorTypeEnum.BufferError, 0, ex.ToString());
			}
			catch(SocketException ex)
			{
				EnqueueErrorSendEvent(MSGError.ErrorTypeEnum.ErrorFromSocket, ex.ErrorCode, ex.ToString());
			}
			catch(ObjectDisposedException ex)
			{
				EnqueueErrorSendEvent(MSGError.ErrorTypeEnum.SocketHasBeenClosed, 0, ex.ToString());
			}
			catch(global::ProtoBuf.ProtoException ex)
			{
				EnqueueErrorSendEvent(MSGError.ErrorTypeEnum.ProtoBufException, 0, ex.Message);
			}
			catch(NotSupportedException ex)
			{
				EnqueueErrorSendEvent(MSGError.ErrorTypeEnum.MemoryStreamException, 0, ex.Message);
			}
		}

		private static MSGEvent NewOrDequeueFromPoolNetEvent()
		{
			lock(recyclingPoolLock)
			{
				if(eventRecyclingPool.Count > 0)
					return eventRecyclingPool.Dequeue();
			}
			
			return new MSGEvent();
		}
		public static void InsertEventToRecyclingPool(MSGEvent e)
		{
			lock(recyclingPoolLock)
			{
				eventRecyclingPool.Enqueue(e);
			}
		}
	}
}
