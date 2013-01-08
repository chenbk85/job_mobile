//
// jReply.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at jHttp://www.boost.org/LICENSE_1_0.txt)
//

#include "reply.hpp"
#include <string>
#include <boost/lexical_cast.hpp>

namespace jHttp {
namespace jServer {

namespace status_strings {

const std::string ok =
  "HTTP/1.0 200 OK\r\n";
const std::string e_created =
  "HTTP/1.0 201 Created\r\n";
const std::string e_accepted =
  "HTTP/1.0 202 Accepted\r\n";
const std::string e_no_content =
  "HTTP/1.0 204 No Content\r\n";
const std::string e_multiple_choices =
  "HTTP/1.0 300 Multiple Choices\r\n";
const std::string e_moved_permanently =
  "HTTP/1.0 301 Moved Permanently\r\n";
const std::string e_moved_temporarily =
  "HTTP/1.0 302 Moved Temporarily\r\n";
const std::string e_not_modified =
  "HTTP/1.0 304 Not Modified\r\n";
const std::string e_bad_request =
  "HTTP/1.0 400 Bad Request\r\n";
const std::string e_unauthorized =
  "HTTP/1.0 401 Unauthorized\r\n";
const std::string e_forbidden =
  "HTTP/1.0 403 Forbidden\r\n";
const std::string e_not_found =
  "HTTP/1.0 404 Not Found\r\n";
const std::string e_internal_server_error =
  "HTTP/1.0 500 Internal Server Error\r\n";
const std::string e_not_implemented =
  "HTTP/1.0 501 Not Implemented\r\n";
const std::string e_bad_gateway =
  "HTTP/1.0 502 Bad Gateway\r\n";
const std::string e_service_unavailable =
  "HTTP/1.0 503 Service Unavailable\r\n";

boost::asio::const_buffer to_buffer(jReply::EStatusType status)
{
  switch (status)
  {
  case jReply::eST_ok:
    return boost::asio::buffer(ok);
  case jReply::e_created:
    return boost::asio::buffer(e_created);
  case jReply::e_accepted:
    return boost::asio::buffer(e_accepted);
  case jReply::e_no_content:
    return boost::asio::buffer(e_no_content);
  case jReply::e_multiple_choices:
    return boost::asio::buffer(e_multiple_choices);
  case jReply::e_moved_permanently:
    return boost::asio::buffer(e_moved_permanently);
  case jReply::e_moved_temporarily:
    return boost::asio::buffer(e_moved_temporarily);
  case jReply::e_not_modified:
    return boost::asio::buffer(e_not_modified);
  case jReply::e_bad_request:
    return boost::asio::buffer(e_bad_request);
  case jReply::e_unauthorized:
    return boost::asio::buffer(e_unauthorized);
  case jReply::e_forbidden:
    return boost::asio::buffer(e_forbidden);
  case jReply::e_not_found:
    return boost::asio::buffer(e_not_found);
  case jReply::e_internal_server_error:
    return boost::asio::buffer(e_internal_server_error);
  case jReply::e_not_implemented:
    return boost::asio::buffer(e_not_implemented);
  case jReply::e_bad_gateway:
    return boost::asio::buffer(e_bad_gateway);
  case jReply::e_service_unavailable:
    return boost::asio::buffer(e_service_unavailable);
  default:
    return boost::asio::buffer(e_internal_server_error);
  }
}

} // namespace status_strings

namespace misc_strings {

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

} // namespace misc_strings

std::vector<boost::asio::const_buffer> jReply::to_buffers()
{
  std::vector<boost::asio::const_buffer> buffers;
  buffers.push_back(status_strings::to_buffer(status));
  for (std::size_t i = 0; i < headers.size(); ++i)
  {
    jHeader& h = headers[i];
    buffers.push_back(boost::asio::buffer(h.name));
    buffers.push_back(boost::asio::buffer(misc_strings::name_value_separator));
    buffers.push_back(boost::asio::buffer(h.value));
    buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  }
  buffers.push_back(boost::asio::buffer(misc_strings::crlf));
  buffers.push_back(boost::asio::buffer(content));
  return buffers;
}

namespace stock_replies {

const char ok[] = "";
const char e_created[] =
  "<html>"
  "<head><title>Created</title></head>"
  "<body><h1>201 Created</h1></body>"
  "</html>";
const char e_accepted[] =
  "<html>"
  "<head><title>Accepted</title></head>"
  "<body><h1>202 Accepted</h1></body>"
  "</html>";
const char e_no_content[] =
  "<html>"
  "<head><title>No Content</title></head>"
  "<body><h1>204 Content</h1></body>"
  "</html>";
const char e_multiple_choices[] =
  "<html>"
  "<head><title>Multiple Choices</title></head>"
  "<body><h1>300 Multiple Choices</h1></body>"
  "</html>";
const char e_moved_permanently[] =
  "<html>"
  "<head><title>Moved Permanently</title></head>"
  "<body><h1>301 Moved Permanently</h1></body>"
  "</html>";
const char e_moved_temporarily[] =
  "<html>"
  "<head><title>Moved Temporarily</title></head>"
  "<body><h1>302 Moved Temporarily</h1></body>"
  "</html>";
const char e_not_modified[] =
  "<html>"
  "<head><title>Not Modified</title></head>"
  "<body><h1>304 Not Modified</h1></body>"
  "</html>";
const char e_bad_request[] =
  "<html>"
  "<head><title>Bad Request</title></head>"
  "<body><h1>400 Bad Request</h1></body>"
  "</html>";
const char e_unauthorized[] =
  "<html>"
  "<head><title>Unauthorized</title></head>"
  "<body><h1>401 Unauthorized</h1></body>"
  "</html>";
const char e_forbidden[] =
  "<html>"
  "<head><title>Forbidden</title></head>"
  "<body><h1>403 Forbidden</h1></body>"
  "</html>";
const char e_not_found[] =
  "<html>"
  "<head><title>Not Found</title></head>"
  "<body><h1>404 Not Found</h1></body>"
  "</html>";
const char e_internal_server_error[] =
  "<html>"
  "<head><title>Internal Server Error</title></head>"
  "<body><h1>500 Internal Server Error</h1></body>"
  "</html>";
const char e_not_implemented[] =
  "<html>"
  "<head><title>Not Implemented</title></head>"
  "<body><h1>501 Not Implemented</h1></body>"
  "</html>";
const char e_bad_gateway[] =
  "<html>"
  "<head><title>Bad Gateway</title></head>"
  "<body><h1>502 Bad Gateway</h1></body>"
  "</html>";
const char e_service_unavailable[] =
  "<html>"
  "<head><title>Service Unavailable</title></head>"
  "<body><h1>503 Service Unavailable</h1></body>"
  "</html>";

std::string to_string(jReply::EStatusType status)
{
  switch (status)
  {
  case jReply::eST_ok:
    return ok;
  case jReply::e_created:
    return e_created;
  case jReply::e_accepted:
    return e_accepted;
  case jReply::e_no_content:
    return e_no_content;
  case jReply::e_multiple_choices:
    return e_multiple_choices;
  case jReply::e_moved_permanently:
    return e_moved_permanently;
  case jReply::e_moved_temporarily:
    return e_moved_temporarily;
  case jReply::e_not_modified:
    return e_not_modified;
  case jReply::e_bad_request:
    return e_bad_request;
  case jReply::e_unauthorized:
    return e_unauthorized;
  case jReply::e_forbidden:
    return e_forbidden;
  case jReply::e_not_found:
    return e_not_found;
  case jReply::e_internal_server_error:
    return e_internal_server_error;
  case jReply::e_not_implemented:
    return e_not_implemented;
  case jReply::e_bad_gateway:
    return e_bad_gateway;
  case jReply::e_service_unavailable:
    return e_service_unavailable;
  default:
    return e_internal_server_error;
  }
}

} // namespace stock_replies

jReply jReply::stock_reply(jReply::EStatusType status)
{
  jReply rep;
  rep.status = status;
  rep.content = stock_replies::to_string(status);
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<std::string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "text/html";
  return rep;
}

} // namespace jServer
} // namespace jHttp
