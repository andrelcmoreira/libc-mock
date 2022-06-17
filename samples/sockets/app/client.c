#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include "common.h"

int connect_server() {
  int fd;
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(struct sockaddr_in));

  if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    return 0;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(SERVER_PORT);
  inet_aton(SERVER_ADDR, &addr.sin_addr);

  if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
    close(fd);
    return 0;
  }

  return fd;
}

int get_date(char *buffer, const size_t buffer_size) {
  int fd = connect_server();

  if (fd > 0) {
    if (recv(fd, buffer, buffer_size, MSG_WAITALL) < 0) {
      return 0;
    }
  }

  return -1;
}

#ifdef MAIN
int main() {
  char buffer[11] = { 0 };  // XX/XX/XXXX

  if (!get_date(buffer, sizeof(buffer))) {
    printf("date = %s\n", buffer);
  }

  return 0;
}
#endif
