#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <functional>

#include "Timestamp.h"
#include "LogStream.h"


// SourceFile的作用是提取文件名
class SourceFile {
 public:
  explicit SourceFile(const char* filename)
      : data_(filename) {
    /**
     * 找出data中出现/最后一次的位置，从而获取具体的文件名
     * 2022/10/26/test.log
     */
    const char* slash = strrchr(filename, '/');
    if (slash) {
        data_ = slash + 1;
    }
    size_ = static_cast<int>(strlen(data_));
  }

  const char* data_;
  int size_;
};

class Logger {
 public:
  enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    LEVEL_COUNT,
  };

  // member function
  Logger(const char* file, int line);
  Logger(const char* file, int line, LogLevel level);
  Logger(const char* file, int line, LogLevel level, const char* func);
  ~Logger();

  // 流是会改变的
  LogStream& Stream() { return impl_.stream_; }

  // TODO:static关键字作用的函数必须在源文件实现?
  static LogLevel logLevel();
  static void SetLogLevel(LogLevel level);

  // 输出函数和刷新缓冲区函数
  using OutputFunc = std::function<void(const char* msg, int len)>;
  using FlushFunc = std::function<void()>;
  static void SetOutput(OutputFunc);
  static void SetFlush(FlushFunc);

 private:
  // 内部类
  class Impl {
   public:
    using LogLevel = Logger::LogLevel;
    Impl(LogLevel level, int savedErrno, const char* file, int line);
    void FormatTime();
    void Finish();

    Timestamp time_;
    LogStream stream_;
    LogLevel level_;
    int line_;
    SourceFile basename_;
  };

  // Logger's member variable 
  Impl impl_;
};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel LogLevel() {
  return g_logLevel;
}

// 获取errno信息
const char* GetErrnoMsg(int savedErrno);

/**
 * 当日志等级小于对应等级才会输出
 * 比如设置等级为FATAL，则logLevel等级大于DEBUG和INFO，DEBUG和INFO等级的日志就不会输出
 */
#define LOG_DEBUG if (LogLevel() <= Logger::DEBUG) \
  Logger(__FILE__, __LINE__, Logger::DEBUG, __func__).Stream()
#define LOG_INFO if (LogLevel() <= Logger::INFO) \
  Logger(__FILE__, __LINE__).Stream()
#define LOG_WARN Logger(__FILE__, __LINE__, Logger::WARN).Stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::ERROR).Stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::FATAL).Stream()

#endif // LOGGING_H