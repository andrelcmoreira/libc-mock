#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "app.h"
#include "libc_mock.h"

void write_failure_testcase() {
  printf("running %s\n", __FUNCTION__);

  MOCK_FUNCTION(ssize_t, write, (int fd, const void *buf, size_t count));

  assert(write_msg("hello") == -1);

  // CHECK_CALL(write, 1);
}

void write_success_testcase() {
  printf("running %s\n", __FUNCTION__);

  MOCK_FUNCTION_WITH_ACTION(ssize_t, write,
                            (int fd, const void *buf, size_t count),
                            {
                              printf("hello from mock :)\n");
                              return count;
                            });

  assert(!write_msg("hello"));

  // CHECK_CALL(write, 1);
}

int main() {
  write_success_testcase();
  write_failure_testcase();

  return 0;
}
