//
// jRequest_parser.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#include "request_parser.hpp"
#include "request.hpp"

namespace jHttp {
namespace jServer {

jRequest_parser::jRequest_parser()
  : state_(e_method_start)
{
}

void jRequest_parser::reset()
{
  state_ = e_method_start;
}

boost::tribool jRequest_parser::consume(jRequest& req, char input)
{
  switch (state_)
  {
  case e_method_start:
    if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      state_ = e_method;
      req.e_method.push_back(input);
      return boost::indeterminate;
    }
  case e_method:
    if (input == ' ')
    {
      state_ = e_uri;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.e_method.push_back(input);
      return boost::indeterminate;
    }
  case e_uri_start:
    if (is_ctl(input))
    {
      return false;
    }
    else
    {
      state_ = e_uri;
      req.uri.push_back(input);
      return boost::indeterminate;
    }
  case e_uri:
    if (input == ' ')
    {
      state_ = e_http_version_h;
      return boost::indeterminate;
    }
    else if (is_ctl(input))
    {
      return false;
    }
    else
    {
      req.uri.push_back(input);
      return boost::indeterminate;
    }
  case e_http_version_h:
    if (input == 'H')
    {
      state_ = e_http_version_t_1;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_t_1:
    if (input == 'T')
    {
      state_ = e_http_version_t_2;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_t_2:
    if (input == 'T')
    {
      state_ = e_http_version_p;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_p:
    if (input == 'P')
    {
      state_ = e_http_version_slash;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_slash:
    if (input == '/')
    {
      req.e_http_version_major = 0;
      req.e_http_version_minor = 0;
      state_ = e_http_version_major_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_major_start:
    if (is_digit(input))
    {
      req.e_http_version_major = req.e_http_version_major * 10 + input - '0';
      state_ = e_http_version_major;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_major:
    if (input == '.')
    {
      state_ = e_http_version_minor_start;
      return boost::indeterminate;
    }
    else if (is_digit(input))
    {
      req.e_http_version_major = req.e_http_version_major * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_minor_start:
    if (is_digit(input))
    {
      req.e_http_version_minor = req.e_http_version_minor * 10 + input - '0';
      state_ = e_http_version_minor;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_http_version_minor:
    if (input == '\r')
    {
      state_ = e_expecting_newline_1;
      return boost::indeterminate;
    }
    else if (is_digit(input))
    {
      req.e_http_version_minor = req.e_http_version_minor * 10 + input - '0';
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_expecting_newline_1:
    if (input == '\n')
    {
      state_ = e_header_line_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_header_line_start:
    if (input == '\r')
    {
      state_ = e_expecting_newline_3;
      return boost::indeterminate;
    }
    else if (!req.headers.empty() && (input == ' ' || input == '\t'))
    {
      state_ = e_header_lws;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.headers.push_back(jHeader());
      req.headers.back().name.push_back(input);
      state_ = e_header_name;
      return boost::indeterminate;
    }
  case e_header_lws:
    if (input == '\r')
    {
      state_ = e_expecting_newline_2;
      return boost::indeterminate;
    }
    else if (input == ' ' || input == '\t')
    {
      return boost::indeterminate;
    }
    else if (is_ctl(input))
    {
      return false;
    }
    else
    {
      state_ = e_header_value;
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case e_header_name:
    if (input == ':')
    {
      state_ = e_space_before_e_header_value;
      return boost::indeterminate;
    }
    else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
    {
      return false;
    }
    else
    {
      req.headers.back().name.push_back(input);
      return boost::indeterminate;
    }
  case e_space_before_e_header_value:
    if (input == ' ')
    {
      state_ = e_header_value;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_header_value:
    if (input == '\r')
    {
      state_ = e_expecting_newline_2;
      return boost::indeterminate;
    }
    else if (is_ctl(input))
    {
      return false;
    }
    else
    {
      req.headers.back().value.push_back(input);
      return boost::indeterminate;
    }
  case e_expecting_newline_2:
    if (input == '\n')
    {
      state_ = e_header_line_start;
      return boost::indeterminate;
    }
    else
    {
      return false;
    }
  case e_expecting_newline_3:
    return (input == '\n');
  default:
    return false;
  }
}

bool jRequest_parser::is_char(int c)
{
  return c >= 0 && c <= 127;
}

bool jRequest_parser::is_ctl(int c)
{
  return (c >= 0 && c <= 31) || (c == 127);
}

bool jRequest_parser::is_tspecial(int c)
{
  switch (c)
  {
  case '(': case ')': case '<': case '>': case '@':
  case ',': case ';': case ':': case '\\': case '"':
  case '/': case '[': case ']': case '?': case '=':
  case '{': case '}': case ' ': case '\t':
    return true;
  default:
    return false;
  }
}

bool jRequest_parser::is_digit(int c)
{
  return c >= '0' && c <= '9';
}

} // namespace jServer
} // namespace jHttp
