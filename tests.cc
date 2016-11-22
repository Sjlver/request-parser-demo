#include "request_parser.h"

#include <gtest/gtest.h>
using namespace std;

TEST(RequestParserTest, HandlesSampleGetRequest) {
  const string data =
    "GET /index.html HTTP/1.0\r\n"
    "Host: www.example.com\r\n"
    "Accept-Language: en\r\n";

  Request request(data);
  EXPECT_EQ("GET", request.method);
  EXPECT_EQ("/index.html", request.resource);
  EXPECT_EQ(1, request.version_major);
  EXPECT_EQ(0, request.version_minor);
  map<string, string> expected_headers = {{"Host", "www.example.com"}, {"Accept-Language", "en"}};
  EXPECT_EQ(expected_headers, request.headers);
}
