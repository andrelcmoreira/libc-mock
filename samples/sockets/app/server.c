#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

void send_date(int client_fd) {
  char date[11] = { 0 };
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  sprintf(date, "%d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  send(client_fd, date, strlen(date), MSG_DONTWAIT);
}

int setup_server() {
  int fd;
  struct sockaddr_in server_addr;

  memset(&server_addr, 0, sizeof(struct sockaddr_in));

  if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    return 0;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
    close(fd);
    return 0;
  }

  if (listen(fd, 1) == -1) {
    close(fd);
    return 0;
  }

  return fd;
}

#ifdef MAIN
int main() {
  int client_fd;
  int server_fd;

  server_fd = setup_server();
  if (!server_fd) {
    return 1;
  }

  if ((client_fd = accept(server_fd, NULL, NULL)) > 0) {
    send_date(client_fd);
  }

  close(client_fd);
  close(server_fd);

  return 0;
}
#endif
