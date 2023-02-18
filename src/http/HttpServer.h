#ifndef HTTP_HTTPSERVER_H
#define HTTP_HTTPSERVER_H

#include <string>

#include "TcpServer.h"
#include "noncopyable.h"
#include "Logging.h"

class HttpRequest;
class HttpResponse;

class HttpServer : noncopyable {
 public:
  using HttpCallback = std::function<void (const HttpRequest&, HttpResponse*)>;

  HttpServer(EventLoop *loop,
          const InetAddress& listenAddr,
          const std::string& name,
          TcpServer::Option option = TcpServer::kNoReusePort);
  
  EventLoop* GetLoop() const { return server_.GetLoop(); }

  void SetHttpCallback(const HttpCallback& cb) {
    httpCallback_ = cb;
  }
  
  void Start();

 private:
  void OnConnection(const TcpConnectionPtr& conn);
  void OnMessage(const TcpConnectionPtr &conn,
                  Buffer *buf,
                  Timestamp receiveTime);
  void OnRequest(const TcpConnectionPtr&, const HttpRequest&);

  TcpServer server_;
  HttpCallback httpCallback_;
};

#endif // HTTP_HTTPSERVER_H