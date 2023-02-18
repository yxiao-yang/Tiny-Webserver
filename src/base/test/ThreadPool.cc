#include "ThreadPool.h"

#include <stdio.h>
#include <unistd.h>
#include <functional>

#include "Logging.h"
#include "CurrentThread.h"


int count = 0;

void showInfo() {
  LOG_INFO << CurrentThread::Tid();
}

void test1() {
  ThreadPool pool;
  pool.setThreadSize(4);
  for (int i = 0; i < 5000; i++) {
    pool.add(showInfo);
  }
  pool.add([]{sleep(5);});
  pool.start();    
}

void initFunc() {
  printf("Create thread %d\n", ++count);
}

int main() {
  test1();
  return 0;
}