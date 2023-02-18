#ifndef HTTP_HTTPRESPONSE_H
#define HTTP_HTTPRESPONSE_H

#include <unordered_map>

class Buffer;
class HttpResponse {
 public:
  // 响应状态码
  enum HttpStatusCode {
    kUnknown,
    k200Ok = 200,
    k301MovedPermanently = 301,
    k400BadRequest = 400,
    k404NotFound = 404,
  };  

  explicit HttpResponse(bool close)
      : statusCode_(kUnknown),
        closeConnection_(close) {
  }   

  void SetStatusCode(HttpStatusCode code) { statusCode_ = code; } 

  void SetStatusMessage(const std::string& message) { statusMessage_ = message; }   

  void SetCloseConnection(bool on) { closeConnection_ = on; }  

  bool CloseConnection() const { return closeConnection_; }  

  void SetContentType(const std::string& contentType) { AddHeader("Content-Type", contentType); } 

  void AddHeader(const std::string& key, const std::string& value) { headers_[key] = value; }  

  void SetBody(const std::string& body) { body_ = body; }   

  void AppendToBuffer(Buffer* output) const;

 private:
  std::unordered_map<std::string, std::string> headers_;
  HttpStatusCode statusCode_;
  // FIXME: add http version
  std::string statusMessage_;
  bool closeConnection_;
  std::string body_;
};

#endif // HTTP_HTTPRESPONSE_H