#include "request_parser.h"

#include <iostream>
#include <iterator>
using namespace std;

int main(int argc, char **argv) {
  // Don't skip the whitespace while reading.
  std::cin >> std::noskipws;
  
  // Use stream iterators to copy the stream to a string.
  istream_iterator<char> it(cin);
  istream_iterator<char> end;
  const string data(it, end);

  try {
    Request request(data);
    cout << "Request(\n"
         << "  method = " << request.method << "\n"
         << "  resource = " << request.resource << "\n"
         << "  version_major = " << request.version_major << "\n"
         << "  version_minor = " << request.version_minor << "\n"
         << "  headers = {\n";
    for (auto header : request.headers) {
      cout << "    " << header.first << ": '" << header.second << "'\n";
    }
    cout << "})\n";
  } catch (BadRequest e) {
    cout << "BadRequest: " << e.what() << "\n";
  }

  return 0;
}
