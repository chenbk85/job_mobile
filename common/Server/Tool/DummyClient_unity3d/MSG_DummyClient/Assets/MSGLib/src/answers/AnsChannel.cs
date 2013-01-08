using System.Collections.Generic;
namespace MSG
{

	/**  채널 정보에 대한 내용이 ChannelInfo 리스트로 전달됌. */
	/**  @warning 사용자가 ReqConnect를 전송해서 로그인 하지 않았다면 요청을 무시한다. */
	public class AnsChannel
	{
		/**  채널에 대한 정보 리스트. */
		public List<ChannelInfo> ChannelInfo { get; set; }
	}
}