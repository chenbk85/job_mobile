namespace MSG
{

	/**  요청의 최상위 추상 클래스. */
	public abstract class AbstractRequest
	{
		public abstract Protocol.UReqProtocol MakeUReqProtocol(TempData tmpData);
	}
}