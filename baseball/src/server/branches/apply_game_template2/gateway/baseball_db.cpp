#include "stdafx.h"
#include "baseball_db.h" 

namespace baseball_db 
{
	
const char* to_grade_string(EItemGradeType grade)
{
	switch (grade)
	{
		case eIGT_S: return "S";
		case eIGT_A: return "A";
		case eIGT_B: return "B";
		case eIGT_C: return "C";
		case eIGT_D: return "D";
		case eIGT_E: return "E";
		default:    return "E";
	}
}


const char* to_upgrade_base_lev_string(EItemGradeType grade)
{
	switch (grade)
	{
		case eIGT_S: return "SE";
		case eIGT_A: return "AE";
		case eIGT_B: return "BE";
		case eIGT_C: return "CE";
		case eIGT_D: return "DE";
		case eIGT_E: return "EE";
		default:    return "EE";
	}
}


std::string time_to_string(const boost::posix_time::ptime& time)
{
	try
	{
		return boost::posix_time::to_simple_string(time);
	}
	catch (std::exception&)
	{
		return std::string();
	}
}


boost::posix_time::ptime timetime_to_string(const std::string& time)
{
	try
	{
		return boost::posix_time::time_from_string(time);
	}
	catch (std::exception&)
	{
		return boost::posix_time::ptime(boost::posix_time::not_a_date_time);
	}
}


} /* baseball_db */
