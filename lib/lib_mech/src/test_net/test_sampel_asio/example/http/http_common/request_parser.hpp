//
// request_parser.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_PARSER_HPP
#define HTTP_REQUEST_PARSER_HPP

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace jHttp {
namespace jServer {

struct jRequest;

/// Parser for incoming requests.
class jRequest_parser
{
public:
  /// Construct ready to parse the jRequest e_method.
  jRequest_parser();

  /// Reset to initial parser state.
  void reset();

  /// Parse some data. The tribool return value is true when a complete jRequest
  /// has been parsed, false if the data is invalid, indeterminate when more
  /// data is required. The InputIterator return value indicates how much of the
  /// input has been consumed.
  template <typename InputIterator>
  boost::tuple<boost::tribool, InputIterator> parse(jRequest& req,
      InputIterator begin, InputIterator end)
  {
    while (begin != end)
    {
      boost::tribool result = consume(req, *begin++);
      if (result || !result)
        return boost::make_tuple(result, begin);
    }
    boost::tribool result = boost::indeterminate;
    return boost::make_tuple(result, begin);
  }

private:
  /// Handle the next character of input.
  boost::tribool consume(jRequest& req, char input);

  /// Check if a byte is an HTTP character.
  static bool is_char(int c);

  /// Check if a byte is an HTTP control character.
  static bool is_ctl(int c);

  /// Check if a byte is defined as an HTTP tspecial character.
  static bool is_tspecial(int c);

  /// Check if a byte is a digit.
  static bool is_digit(int c);

  /// The current state of the parser.
  enum EState
  {
    e_method_start,
    e_method,
    e_uri_start,
    e_uri,
    e_http_version_h,
    e_http_version_t_1,
    e_http_version_t_2,
    e_http_version_p,
    e_http_version_slash,
    e_http_version_major_start,
    e_http_version_major,
    e_http_version_minor_start,
    e_http_version_minor,
    e_expecting_newline_1,
    e_header_line_start,
    e_header_lws,
    e_header_name,
    e_space_before_e_header_value,
    e_header_value,
    e_expecting_newline_2,
    e_expecting_newline_3
  } state_;
};

} // namespace jServer
} // namespace jHttp

#endif // HTTP_REQUEST_PARSER_HPP
