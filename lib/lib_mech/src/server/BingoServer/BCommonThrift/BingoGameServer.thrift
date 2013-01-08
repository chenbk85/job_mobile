
/**
 * The first thing to know about are types. The available types in Thrift are:
 *
 *  bool        Boolean, one byte
 *  byte        Signed byte
 *  i16         Signed 16-bit integer
 *  i32         Signed 32-bit integer
 *  i64         Signed 64-bit integer
 *  double      64-bit floating point value
 *  string      String
 *  binary      Blob (byte array)
 *  map<t1,t2>  Map from one type to another
 *  list<t1>    Ordered list of one type
 *  set<t1>     Set of unique elements of one type
 *
 * Did you also notice that Thrift supports C style comments?
 */

#include "shared.thrift"

namespace cpp nBingo
namespace csharp nBingo

typedef i64 Tbl_User_id_t
typedef i32 Sys_Error_id_t

/**
const i32 INT32CONSTANT = 9853
const map<string,string> MAPCONSTANT = {'hello':'world', 'goodnight':'moon'}
enum Operation {
  ADD = 1,
  SUBTRACT = 2,
  MULTIPLY = 3,
  DIVIDE = 4
}
*/


struct s_X2LG_LOGIN
{
	1: string id,
	2: binary passwd,
	3: string info,
}
struct s_LG2X_LOGIN
{
	1: Tbl_User_id_t uid,	
	2: Sys_Error_id_t result,
}

exception ServerExeption
{
  1: Sys_Error_id_t what,
  2: string why,
}

service BingoGameServer
{

   s_LG2X_LOGIN X2LG_LOGIN(1:s_X2LG_LOGIN Data),

   ##i32 calculate(1:i32 logid, 2:Work w) throws (1:InvalidOperation ouch),
   ##oneway void zip()

}
