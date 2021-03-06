// HttpRequest/HttpResponse classes
// TODO: Basically everything needs to be fixed.  :-)

#include "server.h"
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>

namespace obsequi {

// TODO: This class is really ugly at this point. Just don't even look.
class HttpRequest {
 public:
  HttpRequest() {}
  HttpRequest(const std::string& method, const std::string& request_uri,
              const std::string& http_version,
              const std::vector<std::string> headers,
              const char* content, const int content_length)
    : method_(method),
      request_uri_(request_uri),
      http_version_(http_version),
      headers_(headers),
      content_(content, content_length) {}

  void Print();

  static HttpRequest parse(int fd);

  const std::string method_;
  const std::string request_uri_;
  const std::string http_version_;
  const std::vector<std::string> headers_;  // should be a map
  const std::string content_;
};

// TODO: This class is really ugly at this point. Just don't even look.
class HttpResponse {
 public:
  HttpResponse() {}
  
  std::string content;
  std::string type;

  void SetHtmlContent(const std::string& contentx) {
    this->content = contentx;
    this->type = "text/html";
  }

  void SetJsonContent(const std::string& contentx) {
    this->content = contentx;
    this->type = "application/json";
  }

  void SetJsContent(const std::string& contentx) {
    this->content = contentx;
    this->type = "application/javascript";
  }

  void Send(int fd);
};

}  // namespace obsequi
