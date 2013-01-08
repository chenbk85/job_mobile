#ifndef __BASEBALL_GAME_LOGDEF_H__
#define __BASEBALL_GAME_LOGDEF_H__

#include <boost/detail/lightweight_mutex.hpp> 

#include "basekit/log.hpp"

extern MSG::Log<boost::detail::lightweight_mutex,
				boost::detail::lightweight_mutex::scoped_lock> baseball_logger;


//namespace 
//{
//
//class TraceLog
//{
//public:
//	TraceLog(void* obj, const char* function)
//		: obj_(obj), function_(function)
//	{ 
//		std::ostringstream o_stream; o_stream << "--> " << function_ << " ( " << obj_ << ") ";
//		baseball_logger.debug(o_stream.str().c_str()); 
//	}
//
//	~TraceLog()
//	{ 
//		std::ostringstream o_stream; o_stream << "<-- " << function_ << " ( " << obj_ << ") ";
//		baseball_logger.debug(o_stream.str().c_str()); 
//	}
//private:
//	void* obj_;
//	const char* function_;
//};
//
//}

#define FLE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

//#define DINFO(format, arguments...) baseball_logger.info("%s:%d, [%s]\t" format, FLE, __LINE__, __PRETTY_FUNCTION__, ## arguments)//__VA_ARGS__);
//#define DDEBUG(format, arguments...) baseball_logger.debug("%s:%d, [%s]\t" format, FLE, __LINE__, __PRETTY_FUNCTION__, ## arguments)//__VA_ARGS__);
//#define DWARNING(format, arguments...) baseball_logger.warning("%s:%d, [%s]\t" format, FLE, __LINE__, __PRETTY_FUNCTION__, ## arguments)//__VA_ARGS__);
//#define DERROR(format, arguments...) baseball_logger.error("%s:%d, [%s]\t" format, FLE, __LINE__, __PRETTY_FUNCTION__, ## arguments)//__VA_ARGS__);
////#define TRACE_LOG TraceLog __xxxx_trace_log(this, __PRETTY_FUNCTION__)

#define LOG_INFO(log_string) do{ std::ostringstream o_stream; o_stream << FLE << ":" << __LINE__<< ", [" << __PRETTY_FUNCTION__ << "]\t" << log_string; baseball_logger.info(o_stream.str().c_str()); }while(0)
#define LOG_DEBUG(log_string) do{ std::ostringstream o_stream; o_stream << FLE << ":" << __LINE__<< ", [" << __PRETTY_FUNCTION__ << "]\t" << log_string; baseball_logger.debug(o_stream.str().c_str()); }while(0)
#define LOG_WARNING(log_string) do{ std::ostringstream o_stream; o_stream << FLE << ":" << __LINE__<< ", [" << __PRETTY_FUNCTION__ << "]\t" << log_string; baseball_logger.warning(o_stream.str().c_str()); }while(0)
#define LOG_ERROR(log_string) do{ std::ostringstream o_stream; o_stream << FLE << ":" << __LINE__<< ", [" << __PRETTY_FUNCTION__ << "]\t" << log_string; baseball_logger.error(o_stream.str().c_str()); }while(0)
//#define TRACE_LOG TraceLog __xxxx_trace_log(this, __PRETTY_FUNCTION__)


#endif // __BASEBALL_GAME_LOGDEF_H__


