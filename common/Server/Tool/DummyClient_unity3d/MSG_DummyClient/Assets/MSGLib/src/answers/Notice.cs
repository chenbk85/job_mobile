namespace MSG
{
	/**  공지에 대한 정보를 표현하는 클래스. */
	public class Notice 
	{
		/**  팝업 공지인지 구분. */
		public bool Popup{ get; set; }
		/**  공지의 일렬번호 */
		public int Srl { get; set; }
		/**  공지 내용 */
		public string NoticeContent { get; set; }
	}
}