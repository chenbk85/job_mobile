using System.Collections.Generic;
using MSG.Protocol;

namespace MSG
{
	/**  디비 파라미터 정보를 저장하는 자료구조  */

	public class DBIn
	{
		public enum TypeEnum
		{
			Int,
			Int64,
			Str
		}
		/**  파라미터의 형식 */
		public TypeEnum Type { get; set; }
		/**  파라미터의 값 정보를 문자열로 변환하여 저장 */
		public string Value { get; set; }
		
		public DBIn(){}
		public DBIn(TypeEnum type, string val)
		{
			Type = type;
			Value = val;
			
		}
	}
	/**  @brief 디비 요청 메시지 */

	public class ReqDB : AbstractRequest
	{
		/**  쿼리의 시퀀스 번호 */
		public int Seq { get; set; }
		/**  쿼리 정보 */
		public string Query { get; set;}
		private List<DBIn> _params = null;
		/**  쿼리의 파라미터 정보 리스트 */
		public List<DBIn> Params
		{ 
			get { return _params; } 
		}
		/** 부가 정보가 들어있는 필드 */
		public byte[] Options { get; set; }

		public ReqDB()
		{
			_params = new List<DBIn>();
		}
		public ReqDB(int seq, string query, List<DBIn> paramList, byte[] option)
		{
			Seq = seq;
			Query = query;
			_params = paramList;
			Options = option;
		}
		public override UReqProtocol MakeUReqProtocol(TempData tmpData)
		{
			UReqProtocol request = new UReqProtocol
			{
				type = UReqProtocol.Type.UREQDB,
				reqDB = new Protocol.ReqDB
				{
					seq = Seq,
					query = Query,
					options = Options,
					
				}
			};
						
			foreach( DBIn dbin in _params )
			{
				Protocol.DBIn.Type dbtype = Protocol.DBIn.Type.INT;
				
				switch(dbin.Type)
				{
				case DBIn.TypeEnum.Int:
					dbtype = Protocol.DBIn.Type.INT;
					break;
				case DBIn.TypeEnum.Int64:
					dbtype = Protocol.DBIn.Type.INT64;
					break;
				case DBIn.TypeEnum.Str:
					dbtype = Protocol.DBIn.Type.STR;
					break;
				}
				Protocol.DBIn tmp = new Protocol.DBIn
				{
					type = dbtype,
					val = dbin.Value
				};
				request.reqDB.@params.Add(tmp);
			}
			
						
			return request;
		}
	}
}