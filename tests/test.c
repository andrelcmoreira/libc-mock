#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "app.h"
#include "libc_mock.h"

void write_failure_testcase() {
  printf("running %s\n", __FUNCTION__);

  MOCK_FUNCTION(ssize_t, write, (int fd, const void *buf, size_t count));

  assert(write_msg("hello") == -1);
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
}

void read_success_testcase() {
  char mocked_buffer[] = "fake message";
  char read_buffer[20] = { 0 };
  size_t size = strlen(mocked_buffer);

  printf("running %s\n", __FUNCTION__);

  MOCK_FUNCTION_WITH_ACTION(ssize_t, read,
                            (int fd, void *buf, size_t count),
                            {
                              memcpy(buf, mocked_buffer, size);
                              return size;
                            });

  assert(!read_msg(sizeof(read_buffer), read_buffer));
  assert(!strcmp(mocked_buffer, read_buffer));
}

void read_failure_testcase() {
  char read_buffer[20] = { 0 };

  printf("running %s\n", __FUNCTION__);

  MOCK_FUNCTION_WITH_ACTION(ssize_t, read,
                            (int fd, void *buf, size_t count),
                            {
                              return 0;
                            });

  assert(read_msg(sizeof(read_buffer), read_buffer) == -1);
  assert(!strcmp(read_buffer, ""));

}

int main() {
  write_success_testcase();
  write_failure_testcase();

  read_success_testcase();
  read_failure_testcase();

  return 0;
}
