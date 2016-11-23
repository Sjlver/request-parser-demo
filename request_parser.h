#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H

#include <exception>
#include <map>
#include <string>

struct Request {
  Request(const std::string &data);

  std::string method;    // HTTP method (GET, POST, ...)
  std::string resource;  // The resource being accessed (/index.html)
  int version_major;     // HTTP major version (the 1 in HTTP 1.0)
  int version_minor;     // HTTP minor version (the 0 in HTTP 1.0)

  // HTTP headers (e.g., {"Accept-language": "en"})
  std::map<std::string, std::string> headers;

private:
  const std::string data;  // Textual request data
  size_t pos;              // How much of the request data we've consumed so far

  // Reads a constant and returns it. Throws BadRequest if the constant is not present.
  std::string readString(const std::string &s);
  
  // Reads a digit and returns it. Throws BadRequest if there is no digit.
  int readDigit();

  // Reads to the given delimiter and returns the result (without the
  // delimiter). Consumes the delimiter. Throws BadRequest if the delimiter is
  // not found.
  std::string readTo(const std::string &delimiter);

  // Returns `s` if it contains only valid characters, else throws BadRequest
  std::string validCharacters(const std::string &s);
};

struct BadRequest: public std::exception {
  BadRequest(const std::string &reason) : reason(reason) {}
  virtual ~BadRequest() {}

  virtual const char *what() const throw() override { return reason.c_str(); }

private:
  std::string reason;
};

#endif
