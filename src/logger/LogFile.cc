#include "LogFile.h"

LogFile::LogFile(const std::string& basename,
        off_t rollSize,
        int flushInterval,
        int checkEveryN)
    : basename_(basename),
      rollSize_(rollSize),
      flushInterval_(flushInterval),
      checkEveryN_(checkEveryN),
      count_(0),
      mutex_(new std::mutex),
      startOfPeriod_(0),
      lastRoll_(0),
      lastFlush_(0) {
  RollFile();
}

LogFile::~LogFile() = default;

void LogFile::Append(const char* data, int len) {
  std::lock_guard<std::mutex> lock(*mutex_);
  AppendInLock(data, len);
}

void LogFile::AppendInLock(const char* data, int len) {
  file_->Append(data, len);

  if (file_->WrittenBytes() > rollSize_) {
    RollFile();
  } else {
    ++count_;
    if (count_ >= checkEveryN_) {
      count_ = 0;
      time_t now = ::time(NULL);
      time_t thisPeriod = now / kRollPerSeconds_ * kRollPerSeconds_;
      if (thisPeriod != startOfPeriod_) {
        RollFile();
      } else if (now - lastFlush_ > flushInterval_) {
        lastFlush_ = now;
        file_->Flush();
      }
    }
  }
}


void LogFile::Flush() {
  // std::lock_guard<std::mutex> lock(*mutex_);
  file_->Flush();
}

// 滚动日志
// basename + time + hostname + pid + ".log"
bool LogFile::RollFile() {
  time_t now = 0;
  std::string filename = GetLogFileName(basename_, &now);
  // 计算现在是第几天 now/kRollPerSeconds求出现在是第几天，再乘以秒数相当于是当前天数0点对应的秒数
  time_t start = now / kRollPerSeconds_ * kRollPerSeconds_;

  if (now > lastRoll_) {
    lastRoll_ = now;
    lastFlush_ = now;
    startOfPeriod_ = start;
    // 让file_指向一个名为filename的文件，相当于新建了一个文件
    file_.reset(new FileUtil(filename));
    return true;
  }
  return false;
}

std::string LogFile::GetLogFileName(const std::string& basename, time_t* now) {
  std::string filename;
  filename.reserve(basename.size() + 64);
  filename = basename;

  char timebuf[32];
  struct tm tm;
  *now = time(NULL);
  localtime_r(now, &tm);
  // 写入时间
  strftime(timebuf, sizeof timebuf, ".%Y%m%d-%H%M%S", &tm);
  filename += timebuf;

  filename += ".log";

  return filename;
}