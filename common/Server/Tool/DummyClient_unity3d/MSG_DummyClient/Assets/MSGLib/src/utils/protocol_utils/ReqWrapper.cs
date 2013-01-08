using System;

namespace MSG
{
	public class ReqWrapper
	{
		public enum ReqType
		{
			NetProtocol,
			InnerProtocol
		}
		
		public ReqType Type {get;set;}
		public Protocol.UReqProtocol NetProtocol {get; set;}
		public AbstractRequest InnerProtocol {get;set;}
		
		public Protocol.UReqProtocol ConvertToNetProtocol( TempData tempData )
		{
			switch(Type)
			{
			case ReqType.NetProtocol:
				return NetProtocol;
			case ReqType.InnerProtocol:
				return InnerProtocol.MakeUReqProtocol(tempData);
			}
			return null;
		}
		
		public ReqWrapper (Protocol.UReqProtocol protocol)
		{
			Type = ReqType.NetProtocol;
			NetProtocol = protocol;
		}
		
		public ReqWrapper(AbstractRequest protocol)
		{
			Type = ReqType.InnerProtocol;
			InnerProtocol = protocol;
		}
	}
}

