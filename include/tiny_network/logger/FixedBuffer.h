#ifndef FIXED_BUFFER_H
#define FIXED_BUFFER_H

#include <assert.h>
#include <string.h> // memcpy
#include <strings.h>
#include <string>

#include "noncopyable.h"

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000*1000; 

template <int SIZE>
class FixedBuffer : noncopyable {
 public:
  FixedBuffer()
      : cur_(data_) {
  }

  void Append(const char* buf, size_t len) {
    if (static_cast<size_t>(Avail()) > len) {
      memcpy(cur_, buf, len);
      cur_ += len;
    }
  }

  const char* Data() const { return data_; }
  int Length() const { return static_cast<int>(End() - data_); }

  char* Current() { return cur_; }
  int Avail() const { return static_cast<int>(End() - cur_); }
  void Add(size_t len) { cur_ += len; }

  void Reset() { cur_ = data_; }
  void Bzero() { ::bzero(data_, sizeof(data_)); }

  std::string ToString() const { return std::string(data_, Length()); }

 private:
  const char* End() const { return data_ + sizeof(data_); }

  char data_[SIZE];
  char* cur_; 
};

#endif // FIXED_BUFFER_H