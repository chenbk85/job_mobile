using MSG.Protocol;
using System.Collections.Generic;
namespace MSG
{
	/**  공지사항 정보가 들어오는 메시지 <br> */
	/**  위에서 설명한 Notice 자료구조가 반복적으로 들어있다. */
	/**  공지사항이 들어있느 파일이 존재하지 않거나 파싱이 불가능한 경우, */
	/**  notices가 안차있는 메시지라도 무조건 전달된다 */
	
	public class AnsNotice
	{
		/**  공지 리스트. */
		public List<Notice> Notices { get; set; }
	}
}