#include "CurrentThread.h"

namespace CurrentThread {
  __thread int t_cachedTid = 0;

  void CacheTid() {
    if (t_cachedTid == 0) {
      t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
    }
  }
}