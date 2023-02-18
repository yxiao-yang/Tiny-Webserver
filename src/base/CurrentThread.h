#ifndef CURRENT_THREAD_H
#define CURRENT_THREAD_H

#include <unistd.h>
#include <sys/syscall.h>

namespace CurrentThread {
  extern __thread int t_cachedTid; // 保存tid缓冲，避免多次系统调用
  
  void CacheTid();

  // 内联函数
  inline int Tid() {
    if (__builtin_expect(t_cachedTid == 0, 0)) {
      CacheTid();
    }
    return t_cachedTid;
  }
} // namespace CurrentThread

#endif // CURRENT_THREAD_H