#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>

#include "client.h"
#include "libc_mock.h"

void get_date_success_testcase() {
  char mocked_date[] = "17/06/2022";
  char read_date[11] = { 0 };

  printf("running %s\n", __FUNCTION__);

  {
    MOCK_FUNCTION(int, connect,
                  (int sockfd, const struct sockaddr *addr, socklen_t addrlen));
    MOCK_FUNCTION_WITH_ACTION(ssize_t, recv,
                              (int sockfd, void *buf, size_t len, int flags),
                              {
                                memcpy(buf, mocked_date, strlen(mocked_date));
                                return len;
                              });
  }

  assert(get_date(read_date, sizeof(read_date)) != 0);
  assert(!strcmp(read_date, mocked_date));

  CHECK_CALL(connect, 1);
  CHECK_CALL(recv, 1);
}

void get_date_recv_failure_testcase() {
  char mocked_date[] = "17/06/2022";
  char read_date[11] = { 0 };

  printf("running %s\n", __FUNCTION__);

  {
    MOCK_FUNCTION(int, connect,
                  (int sockfd, const struct sockaddr *addr, socklen_t addrlen));
    MOCK_FUNCTION(ssize_t, recv,
                  (int sockfd, void *buf, size_t len, int flags));
  }

  assert(get_date(read_date, sizeof(read_date)) == -1);
  assert(!strcmp(read_date, ""));

  CHECK_CALL(connect, 1);
  CHECK_CALL(recv, 1);
}

void get_date_connect_failure_testcase() {
  char read_date[11] = { 0 };

  printf("running %s\n", __FUNCTION__);

  {
    MOCK_FUNCTION_WITH_ACTION(int, connect,
                              (int sockfd, const struct sockaddr *addr, socklen_t addrlen),
                              {
                                return -1;
                              });
    MOCK_FUNCTION(ssize_t, recv,
                  (int sockfd, void *buf, size_t len, int flags));
  }

  assert(get_date(read_date, sizeof(read_date)) == -1);
  assert(!strcmp(read_date, ""));

  CHECK_CALL(connect, 1);
  CHECK_CALL(recv, 0);
}

int main() {
  get_date_success_testcase();
  get_date_recv_failure_testcase();
  get_date_connect_failure_testcase();

  return 0;
}
