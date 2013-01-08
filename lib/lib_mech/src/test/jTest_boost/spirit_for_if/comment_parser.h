//-----------------------------------------------------------------------------
//	コメントパーザ
//-----------------------------------------------------------------------------
#ifndef _COMMENT_PERSER_H_
#define _COMMENT_PERSER_H_

#include <boost/spirit/core.hpp>

struct comment_parser : public boost::spirit::grammar<comment_parser> {

	template<typename S> struct definition {

		boost::spirit::rule<S> comment;

		definition(const comment_parser& self)
		{
			comment		=	"//" >> *(anychar_p - '\n') >> '\n' | 
							"/*" >> *(anychar_p - "*/") >> "*/"	;
		}

		const boost::spirit::rule<S>& start() const { return comment; }
	};
};

#endif