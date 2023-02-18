#ifndef TIMER_H
#define TIMER_H

#include <functional>

#include "noncopyable.h"
#include "Timestamp.h"

/**
 * Timer用于描述一个定时器
 * 定时器回调函数，下一次超时时刻，重复定时器的时间间隔等
 */
class Timer : noncopyable {
 public:
  using TimerCallback = std::function<void()>;

  Timer(TimerCallback cb, Timestamp when, double interval)
      : callback_(move(cb)),
        expiration_(when),
        interval_(interval),
        repeat_(interval > 0.0) { // 一次性定时器设置为0
  }

  void Run() const { 
    callback_(); 
  }

  Timestamp Expiration() const { return expiration_; }
  bool Repeat() const { return repeat_; }

  // 重启定时器(如果是非重复事件则到期时间置为0)
  void Restart(Timestamp now);

 private:
  const TimerCallback callback_;  // 定时器回调函数
  Timestamp expiration_;          // 下一次的超时时刻
  const double interval_;         // 超时时间间隔，如果是一次性定时器，该值为0
  const bool repeat_;             // 是否重复(false 表示是一次性定时器)
};

#endif // TIMER_H