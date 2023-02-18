#ifndef LOG_FILE_H
#define LOG_FILE_H

#include <mutex>
#include <memory>

#include "FileUtil.h"

class LogFile {
 public:
  LogFile(const std::string& basename,
          off_t rollSize,
          int flushInterval = 3,
          int checkEveryN = 1024);
  ~LogFile();

  void Append(const char* data, int len);
  void Flush();
  bool RollFile(); // 滚动日志

 private:
  static std::string GetLogFileName(const std::string& basename, time_t* now);
  void AppendInLock(const char* data, int len);

  const std::string basename_;
  const off_t rollSize_;
  const int flushInterval_;
  const int checkEveryN_;

  int count_;

  std::unique_ptr<std::mutex> mutex_;
  time_t startOfPeriod_;
  time_t lastRoll_;
  time_t lastFlush_;
  std::unique_ptr<FileUtil> file_;

  const static int kRollPerSeconds_ = 60*60*24;
};

#endif // LOG_FILE_H