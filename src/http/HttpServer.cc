#include "HttpServer.h"

#include <memory>

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpContext.h"

/**
 * 默认的http回调函数
 * 设置响应状态码，响应信息并关闭连接
 */
void DefaultHttpCallback(const HttpRequest&, HttpResponse* resp) {
  resp->SetStatusCode(HttpResponse::k404NotFound);
  resp->SetStatusMessage("Not Found");
  resp->SetCloseConnection(true);
}

HttpServer::HttpServer(EventLoop *loop,
                      const InetAddress &listenAddr,
                      const std::string &name,
                      TcpServer::Option option)
    : server_(loop, listenAddr, name, option),
      httpCallback_(DefaultHttpCallback) {
  server_.SetConnectionCallback(
    std::bind(&HttpServer::OnConnection, this, std::placeholders::_1));
  server_.SetMessageCallback(
    std::bind(&HttpServer::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  server_.SetThreadNum(4);
}

void HttpServer::Start() {
  LOG_INFO << "HttpServer[" << server_.Name().c_str() << "] starts listening on " << server_.IpPort().c_str();
  server_.Start();
}

void HttpServer::OnConnection(const TcpConnectionPtr& conn) {
  if (conn->Connected()) {
    LOG_INFO << "new Connection arrived";
  } else {
    LOG_INFO << "Connection closed";
  }
}

// 有消息到来时的业务处理
void HttpServer::OnMessage(const TcpConnectionPtr& conn,
                           Buffer* buf,
                           Timestamp receiveTime) {
  // LOG_INFO << "HttpServer::onMessage";
  std::unique_ptr<HttpContext> Context(new HttpContext);

#if 0
  // 打印请求报文
  std::string request = buf->GetBufferAllAsString();
  std::cout << request << std::endl;
#endif

  // 进行状态机解析
  // 错误则发送 BAD REQUEST 半关闭
  if (!Context->ParseRequest(buf, receiveTime)) {
    LOG_INFO << "parseRequest failed!";
    conn->Send("HTTP/1.1 400 Bad Request\r\n\r\n");
    conn->Shutdown();
  }

  // 如果成功解析
  if (Context->GotAll()) {
    LOG_INFO << "parseRequest success!";
    OnRequest(conn, Context->Request());
    Context->Reset();
  }
}

void HttpServer::OnRequest(const TcpConnectionPtr& conn, const HttpRequest& req) {
  const std::string& connection = req.GetHeader("Connection");

  // 判断长连接还是短连接
  bool close = connection == "close" ||
      (req.version() == HttpRequest::kHttp10 && connection != "Keep-Alive");
  // TODO:这里有问题，但是强制改写了
  close = true;
  // 响应信息
  HttpResponse response(close);
  // httpCallback_ 由用户传入，怎么写响应体由用户决定
  // 此处初始化了一些response的信息，比如响应码，回复OK
  httpCallback_(req, &response);
  Buffer buf;
  response.AppendToBuffer(&buf);
  // TODO:需要重载 TcpConnection::send 使其可以接收一个缓冲区
  conn->Send(&buf);
  if (response.CloseConnection()) {
    conn->Shutdown();
  }
}