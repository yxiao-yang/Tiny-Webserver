#include "TcpConnection.h"

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/tcp.h>
#include <functional>
#include <string>

#include "Logging.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

static EventLoop *CheckLoopNotNull(EventLoop *loop) {
  // 如果传入EventLoop没有指向有意义的地址则出错
  // 正常来说在 TcpServer::start 这里就生成了新线程和对应的EventLoop
  if (loop == nullptr) {
    LOG_FATAL << "mainLoop is null!";
  }
  return loop;
}

TcpConnection::TcpConnection(EventLoop *loop,
                            const std::string &nameArg,
                            int sockfd,
                            const InetAddress &localAddr,
                            const InetAddress &peerAddr)
    : loop_(CheckLoopNotNull(loop)), 
      name_(nameArg),
      state_(kConnecting),
      reading_(true),
      socket_(new Socket(sockfd)),
      channel_(new Channel(loop, sockfd)),
      localAddr_(localAddr),
      peerAddr_(peerAddr),
      highWaterMark_(64 * 1024 * 1024) { // 64M 避免发送太快对方接受太慢
  // 下面给channel设置相应的回调函数 poller给channel通知感兴趣的事件发生了 channel会回调相应的回调函数
  channel_->SetReadCallback(
    std::bind(&TcpConnection::HandleRead, this, std::placeholders::_1));
  channel_->SetWriteCallback(
    std::bind(&TcpConnection::HandleWrite, this));
  channel_->SetCloseCallback(
    std::bind(&TcpConnection::HandleClose, this));
  channel_->SetErrorCallback(
    std::bind(&TcpConnection::HandleError, this));

  LOG_INFO << "TcpConnection::ctor[" << name_.c_str() << "] at fd =" << sockfd;
  socket_->SetKeepAlive(true);
}

TcpConnection::~TcpConnection() {
    LOG_INFO << "TcpConnection::dtor[" << name_.c_str() << "] at fd=" << channel_->fd() << " state=" << static_cast<int>(state_);
}


// 发送数据
void TcpConnection::Send(const std::string &buf) {
  if (state_ == kConnected) {
    if (loop_->IsInLoopThread()) {
      SendInLoop(buf.c_str(), buf.size());
    } else {
      // 遇到重载函数的绑定，可以使用函数指针来指定确切的函数
      void(TcpConnection::*fp)(const void* data, size_t len) = &TcpConnection::SendInLoop;
      loop_->RunInLoop(std::bind(fp, this, buf.c_str(), buf.size()));
    }
  }
}

void TcpConnection::Send(Buffer *buf) {
  if (state_ == kConnected) {
    if (loop_->IsInLoopThread()) {
      SendInLoop(buf->Peek(), buf->ReadableBytes());
      buf->RetrieveAll();
    } else {
      // sendInLoop有多重重载，需要使用函数指针确定
      void (TcpConnection::*fp)(const std::string& message) = &TcpConnection::SendInLoop;
      loop_->RunInLoop(std::bind(fp, this, buf->RetrieveAllAsString()));
    }
  }
}

void TcpConnection::SendInLoop(const std::string& message) {
  SendInLoop(message.data(), message.size());
}

/**
 * 发送数据 应用写的快 而内核发送数据慢 需要把待发送数据写入缓冲区，而且设置了水位回调
 **/
void TcpConnection::SendInLoop(const void* data, size_t len) {
  ssize_t nwrote = 0;
  size_t remaining = len;
  bool faultError = false;

  // 之前调用过connection得shutdown，不能再进行发送了
  if (state_ == kDisconnected) {
    LOG_ERROR << "disconnected, give up writing";
    return;
  }

  // channel第一次写数据，且缓冲区没有待发送数据
  if (!channel_->IsWriting() && outputBuffer_.ReadableBytes() == 0) {
    nwrote = ::write(channel_->fd(), data, len);
    if (nwrote >= 0) {
      // 判断有没有一次性写完
      remaining = len - nwrote;
      if (remaining == 0 && writeCompleteCallback_) {
        // 既然一次性发送完事件就不用让channel对epollout事件感兴趣了
        loop_->QueueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
      }
    } else {
      // nwrote = 0
      nwrote = 0;
      if (errno != EWOULDBLOCK) {
        LOG_ERROR << "TcpConnection::sendInLoop";
        if (errno == EPIPE || errno == ECONNRESET) {
          // SIGPIPE
          faultError = true;
        }
      }
    }

  }

  // 说明一次性并没有发送完数据，剩余数据需要保存到缓冲区中，且需要改channel注册写事件
  if (!faultError && remaining > 0) {
    size_t oldLen = outputBuffer_.ReadableBytes();
    if (oldLen + remaining >= highWaterMark_ && 
        oldLen < highWaterMark_ && 
        highWaterMarkCallback_) {
      // TODO
      loop_->QueueInLoop(std::bind(
      highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
    }
    outputBuffer_.Append((char *)data + nwrote, remaining);
    if (!channel_->IsWriting()) {
      channel_->EnableWriting(); // 这里一定要注册channel的写事件 否则poller不会给channel通知epollout
    }
  }
}

// 关闭连接 
void TcpConnection::Shutdown() {
  if (state_ == kConnected) {
    SetState(kDisconnecting);
    loop_->RunInLoop(std::bind(&TcpConnection::ShutdownInLoop, this));
  }
}

void TcpConnection::ShutdownInLoop() {
  if (!channel_->IsWriting()) {
    // 说明当前outputBuffer_的数据全部向外发送完成
    socket_->ShutdownWrite();
  }
}

// 连接建立
void TcpConnection::ConnectEstablished() {
  SetState(kConnected); // 建立连接，设置一开始状态为连接态
  /**
   * TODO:tie
   * channel_->tie(shared_from_this());
   * tie相当于在底层有一个强引用指针记录着，防止析构
   * 为了防止TcpConnection这个资源被误删掉，而这个时候还有许多事件要处理
   * channel->tie 会进行一次判断，是否将弱引用指针变成强引用，变成得话就防止了计数为0而被析构得可能
   */
  channel_->Tie(shared_from_this());
  channel_->EnableReading(); // 向poller注册channel的EPOLLIN读事件

  // 新连接建立 执行回调
  connectionCallback_(shared_from_this());
}

// 连接销毁
void TcpConnection::ConnectDestroyed() {
  if (state_ == kConnected) {
    SetState(kDisconnected);
    channel_->DisableAll(); // 把channel的所有感兴趣的事件从poller中删除掉
    connectionCallback_(shared_from_this());
  }
  channel_->Remove(); // 把channel从poller中删除掉
}

void TcpConnection::HandleRead(Timestamp receiveTime) {
  int savedErrno = 0;
  // TcpConnection会从socket读取数据，然后写入inpuBuffer
  ssize_t n = inputBuffer_.ReadFd(channel_->fd(), &savedErrno);
  if (n > 0) {
    // 已建立连接的用户，有可读事件发生，调用用户传入的回调操作
    // TODO:shared_from_this
    messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
  } else if (n == 0) {
    // 没有数据，说明客户端关闭连接
    HandleClose();
  } else {
    // 出错情况
    errno = savedErrno;
    LOG_ERROR << "TcpConnection::handleRead() failed";
    HandleError();
  }
}

void TcpConnection::HandleWrite() {
  if (channel_->IsWriting()) {
    int saveErrno = 0;
    ssize_t n = outputBuffer_.WriteFd(channel_->fd(), &saveErrno);
    // 正确读取数据
    if (n > 0) {
      outputBuffer_.Retrieve(n);
      // 说明buffer可读数据都被TcpConnection读取完毕并写入给了客户端
      // 此时就可以关闭连接，否则还需继续提醒写事件
      if (outputBuffer_.ReadableBytes() == 0) {
        channel_->DisableWriting();
        // 调用用户自定义的写完数据处理函数
        if (writeCompleteCallback_) {
          // 唤醒loop_对应得thread线程，执行写完成事件回调
          loop_->QueueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
        }
        if (state_ == kDisconnecting) {
          ShutdownInLoop();
        }
      }
    } else {
      LOG_ERROR << "TcpConnection::handleWrite() failed";
    }
  } else {
    // state_不为写状态
    LOG_ERROR << "TcpConnection fd=" << channel_->fd() << " is down, no more writing";
  }
}

void TcpConnection::HandleClose() {
  SetState(kDisconnected);    // 设置状态为关闭连接状态
  channel_->DisableAll();     // 注销Channel所有感兴趣事件
  
  TcpConnectionPtr connPtr(shared_from_this());
  connectionCallback_(connPtr);   
  closeCallback_(connPtr);        // 关闭连接的回调
}

void TcpConnection::HandleError() {
  int optval;
  socklen_t optlen = sizeof(optval);
  int err = 0;
  // TODO:getsockopt ERROR
  if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen)) {
    err = errno;
  } else {
    err = optval;
  }
  LOG_ERROR << "cpConnection::handleError name:" << name_.c_str() << " - SO_ERROR:" << err;
}