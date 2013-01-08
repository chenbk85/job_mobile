/**
	@mainpage MSG C# Client Network Library {version}
	@section intro 소개
	네오위즈 모바일의 룸 기반 서버 플랫폼인 MSG와 통신하는 C# 클라이언트 라이브러리입니다. <br>
	MSGClient 통해서 Request 오브젝트를 보내고, MSGClient의 PopEvent로 모든 이벤트를 받아오도록 설계되었습니다. <br>
	현재는 유니티 클라이언트에서 사용될 것을 중점적으로 고려하여 개발되었습니다. <br>
*/

using System;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;
using System.Collections.Generic;

using MSG.Protocol;

namespace MSG
{
/**
	@class MSGClient
	@brief MSG 클라이언트 클래스
	@warning 같은 이름의 클라이언트는 동시에 존재하지 않도록 한다.
*/	
	public class MSGClient 
	{
		public static LoggerOption DEFAULT_OPTION = new LoggerOption
        {
            isPrintEnabled = true,
            isWriteEnabled = true,
            type = LogDirectoryType.Persistent,
           	initTime = string.Format("{0:yy_MM_dd_hh-mm}.txt",System.DateTime.Now)
        };
		
		#region Constants
		private const int DEFAULT_MSG_QUEUE_SIZE = 100;
		
		private const int READ_BUFFER_SIZE = 1024;
		private const int WRITE_BUFFER_SIZE = 1024;
		
		private const int HEAD_SIZE = 4; 				/**  데이터 헤더 사이즈. */

        


		#endregion

		#region Enums
		private enum Status
		{
			Init,				/**  기본 상태 */
			Connecting,			/**  접속 중 */
			Connected,			/**  접속 되어 있음. */
			Disconnecting		/**  연결 끊는 중. */
		}
		
		/**  Close를 호출할 때 바뀌는 닫는 상태.  */
		private enum ClosingStatus
		{
			NotClosing,						/**  닫는 중이 아님. */
			SendingMsgBeforeClosing,		/**  닫기전에 메시지 보내는 중. */
			Closing 						/**  닫는 중 */
		}
		#endregion
		
		#region Members
		private int readBufferSize;
		private int writeBufferSize;
		
		private TempData tempData;			/**  임시 데이터가 들어가는 저장소. */
		private string name;				/**  클라이언트 이름. */
		
		private string ipOrUrl;				/**  현재 접속 중인 url */
		private int port;					/**  현재 접속 중인 port */

		private Socket socket;				 
		
		private MSGEventQueue eventQueue;	/**  받은 이벤트가 보관되는 이벤트 큐 */
		private Queue<ReqWrapper> sendQueue = new Queue<ReqWrapper>();	/**  보낼 메시지가 보관되는 큐 */
				
		private Status status;
		private ClosingStatus closingStatus = ClosingStatus.NotClosing;
		private MSGDisconnected.ReasonEnum disconnectReason;	/**  접속이 끊어질 때, 끊어진 이유. */

		private Thread recvThread;
		private Thread sendThread;
		private Thread connectThread;

		private Logger logger;
		public Logger Logger
		{
			get{return logger;}
		}
		
		private AutoResetEvent msgPopEvent = new AutoResetEvent(false);		/** 메시지가 pop 될 때 Set하는 이벤트. */
		private AutoResetEvent sendMsgEvent = new AutoResetEvent(false);	/** 메시지를 send할 때 Set하는 이벤트. */


		#	region Thread Locks
		private object threadLock = new object();
		private object addressLock = new object();
		private object statusLock = new object();
		private object closingStatusLock = new object();
		private object sendQueueLock = new object();
		private object eventQueueLock = new object();
		private object tempDataLock = new object();
		private object disconnectLock = new object();
		
		#	endregion
		#endregion
		
		#region Config
		
		private float connectionTimeOutSeconds = 5.0f;
		private ThreadPriority threadPriority = ThreadPriority.Lowest;
		
		/**  접속 타임 아웃 시간. 초 단위로 표현함. */
		/**  지정한 시간이 초과되면 접속에 실패함. <br> */
		/**  기본값: 5 seconds */
		public float ConfigConnectionTimeOutSeconds
		{
			get{ return connectionTimeOutSeconds; }
			set{ connectionTimeOutSeconds = value;}
		}
		
		/**  Receive Queue 사이즈. */
		/**  메시지 큐가 꽉 차면 더이상 메시지를 받지 않음. <br> */
		/**  기본값: 100 */
		public int ConfigReceiveQueueSize
		{
			get
			{ 
				lock(eventQueueLock)
					return eventQueue.MaxMsgCount;
			}
			set
			{
				lock(eventQueueLock)
					eventQueue.MaxMsgCount = value;
			}
		}		
		
		/**  쓰레드 우선순위 <br> */
		/**  기본값: ThreadPriority.Lowest */
			public ThreadPriority NetThreadPriority
		{
			get { return threadPriority; }
			set 
			{ 
				threadPriority = value; 
				if(this.recvThread != null)
					this.recvThread.Priority = value;
				if(this.sendThread != null)
					this.sendThread.Priority = value;
			}
		}
		
		/**  로고 기록 레벨. <br> */
		/**  기본값 : LogLevel.None */
		public LogLevel LogLevel
		{
			get { return logger.LogLevel; }
			set { logger.LogLevel = value; }
		}
		
		#endregion
		
		
		#region Public Properties
		/**  Client의 이름. */
		public string Name { get { return name; } }

		/**  @return 현재 접속 중이면 true, 아니면 false */
		public bool IsConnected
		{
			get { return status == Status.Connected; }
		}
		#endregion

		#region Private Properties
		private Status SafeStatus
		{
			get { lock(statusLock) return status; }
			set { lock(statusLock) status = value; }
		}
		private ClosingStatus SafeClosingStatus
		{
			get { lock(closingStatusLock) return closingStatus; }
			set { lock(closingStatusLock)closingStatus = value;	}
		}

		private bool SafeIsSendQueueEmpty
		{
			get { lock(sendQueueLock) return sendQueue.Count == 0; }
		}
		#endregion
				
		
		
		#region Constructor & Destructor
		/**  MSGClient의 생성자. */
		/**  @param name client의 이름. 해당 이름은 client가 필요한 데이터를 보조 기억 장치에 캐싱할 때 사용한다. 각 MSGClient는 유니크한 name을 지녀야한다. */
		/** 	@warning 유니티 엔진 사용 시, MSGClient 클래스의 생성은 유니티 메인 쓰레드에서 이루어져야합니다. */
		public MSGClient (string name)
		{
			Initialize(name, null,READ_BUFFER_SIZE,WRITE_BUFFER_SIZE);
		}
		/**  MSGClient의 생성자. */
		/**  @param name client의 이름. 해당 이름은 client가 필요한 데이터를 보조 기억 장치에 캐싱할 때 사용한다. 각 MSGClient는 유니크한 name을 지녀야한다. */
		/**  @param logger logging에 사용할 logger를 지정한다. Logger를 상속하여 커스텀 logger를 만들어 사용할 수 있다. */
		/** 	@warning 유니티 엔진 사용 시, MSGClient 클래스의 생성은 유니티 메인 쓰레드에서 이루어져야합니다. */
		public MSGClient (string name, Logger logger)
		{
			Initialize(name, logger,READ_BUFFER_SIZE,WRITE_BUFFER_SIZE);
		}
		/**  MSGClient의 생성자. */
		/**  @param name client의 이름. 해당 이름은 client가 필요한 데이터를 보조 기억 장치에 캐싱할 때 사용한다. 각 MSGClient는 유니크한 name을 지녀야한다. */
		/**  @param logger logging에 사용할 logger를 지정한다. Logger를 상속하여 커스텀 logger를 만들어 사용할 수 있다. */
		/**  @param bufferSize read/write 버퍼의 사이즈. 기본은 1024 byte이다. */
		/** 	@warning 유니티 엔진 사용 시, MSGClient 클래스의 생성은 유니티 메인 쓰레드에서 이루어져야합니다. */
		public MSGClient (string name, Logger logger, int bufferSize)
		{
			Initialize(name, logger,bufferSize,bufferSize);
		}
		/**  MSGClient의 생성자. */
		/**  @param name client의 이름. 해당 이름은 client가 필요한 데이터를 보조 기억 장치에 캐싱할 때 사용한다. 각 MSGClient는 유니크한 name을 지녀야한다. */
		/**  @param logger logging에 사용할 logger를 지정한다. Logger를 상속하여 커스텀 logger를 만들어 사용할 수 있다. */
		/**  @param readBufferSize read 버퍼의 사이즈. 기본은 1024 byte이다. */
		/**  @param writeBufferSize write 버퍼의 사이즈. 기본은 1024 byte이다. */
		/** 	@warning 유니티 엔진 사용 시, MSGClient 클래스의 생성은 유니티 메인 쓰레드에서 이루어져야합니다. */
		public MSGClient (string name, Logger logger, int readBufferSize, int writeBufferSize)
		{
			Initialize(name, logger,readBufferSize,writeBufferSize);
		}
		~MSGClient()
		{
			if(socket != null)
				socket.Close();
			
		}
		#endregion
		
		#region Public Methods
		/**  지정한 주소와 포트에 TCP 연결을 한다.  */
		/**  접속은 비동기적으로 처리되며, 접속이 실패한 경우 PopEvent로 ErrorConnect 이벤트를 받아볼 수 있다. */
		/**  @param ipOrUrl 접속할 ip 혹은 url. */
		/**  @param port 접속할 포트 */
		/**  @return 접속이 불가능한 상태라면 false를, 접속이 가능하다면 true를 리턴한다. true를 리턴했다고 반드시 접속에 성공하는 것은 아니다. */
		public bool Connect(string ipOrUrl, int port)
		{
			if(this.status == Status.Init)
			{
				InitializeSocket();
				logger.d("Connect Called");
				logger.d("Setting url and port");
				
				SafeStatus = Status.Connecting;
				lock(addressLock)
				{
					this.ipOrUrl = ipOrUrl;
					this.port = port;
				}
			
				connectThread = new Thread(this.ConnectRun);
				connectThread.Start();

				logger.d("Connect Thread Start");
				
				return true;
			}
			return false;
		}
		/**  이전 Login때 Plug를 위해 캐싱한 ip와 port로 Connect한다. */
		/**  MSG의 Plug 기능을 위한 메소드. */
		/**  @return 접속이 불가능한 상태이거나 캐시된 ip/port가 없다면 false를, 접속이 가능하다면 true를 리턴한다. true를 리턴했다고 반드시 접속에 성공하는 것은 아니다. */
		public bool PlugConnect()
		{
			if(tempData.PlugIp == null)
			{
				logger.i("No cached plug ip");
				return false;
			}
			return Connect (tempData.PlugIp,tempData.PlugPort);
		}
		
		/**  MSGClient에서 발생하는 모든 이벤트(메시지, 에러, 상태 변화 등등)를 받아오는 메소드. */
		/**  MSGClient 내부에 쌓인 이벤트를 순서대로 하나씩 받아온다.  */
		/**  @param e 이벤트 객체를 받을 레퍼런스. */
		/**  @return 받아올 이벤트가 있어 받아왔다면 true, 이벤트가 없어 받아오지 못했다면 false. */
		public bool PopEvent(out MSGEvent e)
		{
			lock(eventQueueLock)
			{
				e = eventQueue.Dequeue();
			}
			
			msgPopEvent.Set();
			
			if( e == default(MSGEvent) )
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		/**  Requst를 서버에 보내기 위한 메소드.  */
		/**  비동기 메소드로, SendQueue에 Request가 추가되며 실제로 서버로 보내는 것은 Send Thread가 한다. */
		/**  @param req 보낼 Request. */
		/**  @return 서버에 접속이 되어있어 보내가가 가능할 경우 true, 접속이 안되어있어 보내가기 불가능할 경우 falae를 리턴한다. */
		/**  @warning true를 리턴했다고 보내기에 성공한 것은 아니다. */
		public bool Send(AbstractRequest req)
		{
			if(req == null)
				return false;
			return Send (new ReqWrapper(req));
			
		}
		private bool Send(Protocol.UReqProtocol req)
		{
			if(req == null)
				return false;
			return Send (new ReqWrapper(req));
		}
		private bool Send(ReqWrapper req)
		{
			if(req == null)
				return false;
			if( IsConnected )
			{
				lock(sendQueueLock)
				{
					sendQueue.Enqueue(req);
				}
				sendMsgEvent.Set();
				return true;
			}
			else
			{
				return false;
			}
		}
		
		/**  오브젝트 풀링을 위한 메소드.  */
		/**  네트워크 라이브러리가 가비지 컬렉션에 의한 렉을 유발할 경우 사용한다. */
		/**  @param e 사용이 끝나, 풀링할 이벤트 오브젝트. */
		public void InsertEventToRecyclingPool(MSGEvent e)
		{
			MSGEventQueue.InsertEventToRecyclingPool(e);
		}


		/**  서버와의 TCP 접속을 종료한다. */
		/**  @param graceful true일 경우, SendQueue에 쌓여있는 메시지를 최대한 보내도록 노력한 뒤 접속을 종료한다. false이면 즉시 접속을 종료한다. */
		public void Close(bool graceful)
		{

			if(SafeStatus == Status.Init)
				return;
							
			if(!graceful || SafeIsSendQueueEmpty)
			{	
				SafeClosingStatus = ClosingStatus.Closing;
				DisconnectSocket(MSGDisconnected.ReasonEnum.ByClient);
			}
			else
			{
				SafeClosingStatus = ClosingStatus.SendingMsgBeforeClosing;
			}
		}
		#endregion

		#region Private Methods
		private void InitializeSocket()
		{
			this.socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			this.socket.NoDelay = true;
		}
		/** name과 logger와 함께 Initialize한다. logger가 null이면 자동으로 기본 로거가 지정된다. */
		private void Initialize(string name, Logger logger, int readBufferSize, int writeBufferSize)
		{
            if (logger == null)
                this.logger = LoggerFactory.MakeLogger(MSGClient.DEFAULT_OPTION);
            else
                this.logger = logger;
			this.readBufferSize = readBufferSize;
			this.writeBufferSize = writeBufferSize;
			this.status = Status.Init;
			this.name = name;
			this.eventQueue = new MSGEventQueue(DEFAULT_MSG_QUEUE_SIZE, this.logger);
			this.logger.LogLevel = LogLevel.None;
			this.tempData = new TempData(name);
			this.tempData.LoadTempData();
		}

		private void StartRecvAndSendThreads()
		{
			lock(threadLock)
			{
				if(recvThread != null)
					recvThread.Abort();
				if(sendThread != null)
					sendThread.Abort();

				recvThread = new Thread(this.ReceiveRun);
				sendThread = new Thread(this.SendRun);

				recvThread.Priority = threadPriority;
				sendThread.Priority = threadPriority;

				recvThread.Start();
				sendThread.Start();
			}
		}
		private void ConnectRun()
		{
			IPAddress[] ips = null;
			try
			{
				
				logger.d("Getting IPs....");
				lock(addressLock)
				{
					ips = Dns.GetHostAddresses(this.ipOrUrl);
					foreach(IPAddress ip in ips)
					{
						logger.i("IP: " + ip.ToString());
					}
				}
				
				logger.d("Start Connecting");
				
				var socketResult = socket.BeginConnect(ips, port, null, null);
				
				TimeSpan timeout = TimeSpan.FromSeconds(connectionTimeOutSeconds);
				bool success = socketResult.AsyncWaitHandle.WaitOne(timeout, true);
				if(success)
				{
					socket.EndConnect(socketResult);
				}
				else
				{
					socket.EndConnect(socketResult);
					socket.Close();
					throw  new SocketException(10060);
				}
				
				IPEndPoint remoteIpEndPoint = socket.RemoteEndPoint as IPEndPoint;
				lock(eventQueueLock)
					eventQueue.EnqueueConnectEvent(remoteIpEndPoint.Address.ToString(), remoteIpEndPoint.Port);
				logger.d( "Connected");
				
				
				SafeStatus = Status.Connected;					
				
				StartRecvAndSendThreads();					
			}
			catch(Exception ex)
			{
				logger.e( "Connect Exception => " + ex.ToString()); 
				
				if(SafeStatus != Status.Disconnecting && SafeStatus != Status.Init)
					lock(eventQueueLock)
						eventQueue.EnqueueConnectException(ex);
				
				DisconnectSocket(MSGDisconnected.ReasonEnum.ByError);
				
				return;
			}

		}
		
		private void ReceiveRun()
		{
			byte[] buffer = new byte[this.readBufferSize];
			
			try
			{
				while( true)
				{
					if(SafeStatus != Status.Connected )
						break;
				
					bool isMsgFull;
					lock(eventQueueLock)
						isMsgFull = eventQueue.IsMsgFull;
					
					if( isMsgFull)
					{
						msgPopEvent.WaitOne();
						continue;
					}
					
					logger.d( "Reading header from socket....");
					
					if( !Recevie(buffer, HEAD_SIZE) )
					{
						DisconnectSocket(MSGDisconnected.ReasonEnum.ByServer);
						break;
					}
					
					int size = BitConverter.ToInt32 (buffer, 0);
	
					if( size == 0 )
						continue;
					
					logger.d( "Reading body from socket....(size : " + size + ")");
					
					if(!Recevie(buffer, size))
					{
						DisconnectSocket(MSGDisconnected.ReasonEnum.ByServer);
						break;
					}
					
					MemoryStream memStream = new MemoryStream(buffer,0,size);
					
					UAnsProtocol protocol = ProtoBuf.Serializer.Deserialize<UAnsProtocol>(memStream);
					ProccessReceivedProtocol(protocol);				
					Thread.Sleep(1);
				}
			}
			catch(Exception ex)
			{
				logger.e( "Receive Exception : " + ex.ToString());
								
				if(SafeStatus != Status.Disconnecting)
				{
					lock(eventQueueLock)
						eventQueue.EnqueueReceiveException(ex);	
					DisconnectSocket(MSGDisconnected.ReasonEnum.ByError);
				}
				
			}
			
			logger.i("Receive thread is finished");
			
		}
		private void SendRun()
		{
			byte[] buffer = new byte[this.writeBufferSize];
			try
			{
				while(true)
				{
					if(SafeStatus != Status.Connected )
						break;
					
					if( SafeIsSendQueueEmpty)
					{
						if(SafeClosingStatus == ClosingStatus.SendingMsgBeforeClosing)
						{
							DisconnectSocket(MSGDisconnected.ReasonEnum.ByClient);
							break;
						}
						else
						{
							sendMsgEvent.WaitOne();
							continue;
						}
					}
					
					
					ReqWrapper req = null;
					logger.d( "Dequeue Req");
					
					lock(sendQueueLock)
					{
						req = sendQueue.Dequeue();
					}
										
					UReqProtocol reqProtocol = null;
					lock(tempDataLock)
						reqProtocol = req.ConvertToNetProtocol(tempData);
					
					logger.d( "Serialize Req");

					MemoryStream memStream = new MemoryStream(buffer,0,WRITE_BUFFER_SIZE);
					ProtoBuf.Serializer.SerializeWithLengthPrefix<UReqProtocol>(memStream, reqProtocol,ProtoBuf.PrefixStyle.Fixed32);
					
					logger.d( "Send Req => Length:"+ BitConverter.ToInt32(buffer,0));
					
					int size = socket.Send(buffer, (int)memStream.Position, SocketFlags.None);
										
					logger.d( "Send Req Succeed => size:" + size );
					Thread.Sleep(1);
				}
			}
			catch(Exception ex)
			{
				logger.e( "Send Exception : " + ex.ToString());
				
				if(SafeStatus != Status.Disconnecting)
				{
					lock(eventQueueLock)
						eventQueue.EnqueueSendException(ex);
					DisconnectSocket(MSGDisconnected.ReasonEnum.ByError);
				}
			}
			
			logger.i("Send thread is finished");
		}
		private void DisconnectSocket(MSGDisconnected.ReasonEnum reason )
		{
			lock(disconnectLock)
			{
				Status status = SafeStatus;
	
				if(status == Status.Disconnecting || status == Status.Init)
					return;
	
				logger.d( "Disconnecting");
				SafeStatus = Status.Disconnecting;
				disconnectReason = reason;
							
				SafeStatus = Status.Disconnecting;
				sendMsgEvent.Set();
				Thread disconnectThread = new Thread(this.RefreshStatusForDisconnectRun);
				disconnectThread.Priority = ThreadPriority.Lowest;
				disconnectThread.Start();
				
			}
		}
		
		/** check and change status and closingStatus for disconnect. */
		private void RefreshStatusForDisconnectRun()
		{	
			if(SafeStatus != Status.Disconnecting)
				return;
			
			logger.d( "Socket Shutdown");
			try
			{
				socket.Shutdown(SocketShutdown.Both);
			}catch(Exception){}

			logger.d( "Socket Close");
			socket.Close();
			logger.d( "Join Threads");
			if(this.connectThread != null)
				this.connectThread.Join();
			if(this.recvThread != null)
				this.recvThread.Join();
			if(this.sendThread != null)
				this.sendThread.Join();
			
			SafeStatus = Status.Init;
			
			if(SafeClosingStatus != ClosingStatus.NotClosing)
			{
				SafeClosingStatus = ClosingStatus.NotClosing;
				lock(sendQueueLock)
					sendQueue.Clear();
				lock(eventQueueLock)
					eventQueue.EnqueueDisconnectEvent(MSGDisconnected.ReasonEnum.ByClient);
				logger.d( "Closed");
			}
			else
			{
				lock(eventQueueLock)
					eventQueue.EnqueueDisconnectEvent(disconnectReason);
			}
			
			
			logger.d( "Disconnecting Thread Finished");
		}
		
		private void ProccessReceivedProtocol(UAnsProtocol ans)
		{
			lock(tempDataLock)
				tempData.CacheAndSaveNecessaryData(ans);
			
			AnswerMessage msg = AnsProtocolConverter.Convert(ans);
			
			if(msg != null)
			{
				lock(eventQueueLock)
					eventQueue.EnqueueRecvMessageEvent(msg);
				
				logger.d( "Message Received : " + msg.ToString());
			}
			else
			{
				if(ans.type == UAnsProtocol.Type.UANSPING)
				{
					SendPong(ans.ansPing.seq);
					logger.d( "Message Received : Ping");
				}
				else
				{
					logger.d( "Unknown Message Received : " + ans.type.ToString());	
				}
			}
		}
		private void SendPong(int sequence)
		{
			var req = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQPONG,
				reqPong = new UReqPong
				{
					seq = sequence
				}
			};
			logger.d( "Send Pong");
			Send(req);
		}
		
		//EOF 시 false 리턴.
		private bool Recevie(byte[] buffer, int size)
		{
			for(int recvSize = 0; recvSize < size;)
			{
				int tmpSize = socket.Receive(buffer, recvSize, size - recvSize, SocketFlags.None);
				if( tmpSize  == 0)
					return false;
				recvSize += tmpSize;
			}
			return true;
		}
		
		#endregion
		
	}

}