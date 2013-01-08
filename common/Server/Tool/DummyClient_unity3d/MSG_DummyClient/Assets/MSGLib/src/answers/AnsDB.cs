using System;

namespace MSG
{
	/** 디비 응답 메시지 */
	public class AnsDB
	{
		/**  쿼리의 시퀀스 번호 */
		public int Seq { get; set; }
		/**  쿼리 정보 */
		public string Query { get; set; }
		/**  디비 처리 결과 코드 */
		public int ReturnCode { get; set; }
		/**  디비 응답 결과를 시리얼라이즈해서 저장 */
		public byte[] Result { get; set; }
	}
}

