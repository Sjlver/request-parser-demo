#include "request_parser.h"

using namespace std;

// Creates a Request from the given data
Request::Request(const string& data) : data(data), pos(0) {

  // Parse the HTTP method. We only support GET and POST.
  if (data[pos] == 'G') method = readString("GET");
  else if (data[pos] == 'P') method = readString("POST");
  else throw BadRequest("Unsupported HTTP method");
  readString(" ");

  // Next follows resource and version: "/index.html HTTP/1.1"
  resource = validCharacters(readTo(" "));
  readString("HTTP/");
  version_major = readDigit();
  readString(".");
  version_minor = readDigit();
  readString("\r\n");

  // Read headers of the form "Accept-language: en"
  while (pos < data.size()) {
    string key = validCharacters(readTo(": "));
    string value = validCharacters(readTo("\r\n"));
    headers[key] = value;
  }

  // Check for required headers
  if (version_major == 1 && version_minor == 1 && !headers.count("Host")) {
    throw BadRequest("Host header is required for HTTP/1.1");
  }
}

string Request::readString(const string &s) {
  if (data.substr(pos, s.size()) == s) {
    pos += s.size();
    return s;
  }
  throw BadRequest("Expected '" + s + "'");
}

int Request::readDigit() {
  if (pos < data.size() && data[pos] >= '0' && data[pos] <= '9') {
    int result = atoi(data.substr(pos, 1).c_str());
    pos += 1;
    return result;
  }
  throw BadRequest("Expected a digit");
}

string Request::readTo(const string &delimiter) {
  size_t endpos = data.find(delimiter, pos);
  if (endpos != data.npos) {
    size_t startpos = pos;
    pos = endpos + delimiter.size();
    return data.substr(startpos, endpos - startpos);
  }
  throw BadRequest("Expected the delimiter '" + delimiter + "'");
}

string Request::validCharacters(const string &s) {
  for (auto c : s) {
    if (c < '!' || c > 'z') {
      throw BadRequest("Illegal character in URL");
    }
  }
  return s;
}
