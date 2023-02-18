#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../net/Buffer.h"

int main() {
  Buffer* output = new Buffer;

  // 响应行
  char buf[32];
  memset(buf, '\0', sizeof(buf));
  snprintf(buf, sizeof(buf), "HTTP/1.1 %d ", 200);
  output->Append(buf);
  output->Append("OK");
  output->Append("\r\n");

  std::cout << output->GetBufferAllAsString() << std::endl;

  return 0;
}

// g++ test.cc -g -o test