#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <iostream>
#include <string>
#include <sys/time.h>

class Timestamp {
 public:
  Timestamp()
      : microSecondsSinceEpoch_(0) {
  }

  explicit Timestamp(int64_t microSecondsSinceEpoch)
      : microSecondsSinceEpoch_(microSecondsSinceEpoch) {
  }

  // 获取当前时间戳
  static Timestamp Now();

  //用std::string形式返回,格式[millisec].[microsec]
  std::string ToString() const;
  //格式, "%4d年%02d月%02d日 星期%d %02d:%02d:%02d.%06d",时分秒.微秒
  std::string ToFormattedString(bool showMicroseconds = false) const;

  //返回当前时间戳的微秒
  int64_t MicroSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
  //返回当前时间戳的秒数
  time_t SecondsSinceEpoch() const { 
    return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond); 
  }

  // 失效的时间戳，返回一个值为0的Timestamp
  static Timestamp Invalid() {
    return Timestamp();
  }

  // 1秒=1000*1000微妙
  static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    // 表示时间戳的微秒数(自epoch开始经历的微妙数)
    int64_t microSecondsSinceEpoch_;
};

/**
 * 定时器需要比较时间戳，因此需要重载运算符
 */
inline bool operator<(Timestamp lhs, Timestamp rhs) {
  return lhs.MicroSecondsSinceEpoch() < rhs.MicroSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs) {
    return lhs.MicroSecondsSinceEpoch() == rhs.MicroSecondsSinceEpoch();
}

// 如果是重复定时任务就会对此时间戳进行增加。
inline Timestamp addTime(Timestamp timestamp, double seconds) {
  // 将延时的秒数转换为微妙
  int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
  // 返回新增时后的时间戳
  return Timestamp(timestamp.MicroSecondsSinceEpoch() + delta);
}

#endif // TIME_STAMP_H