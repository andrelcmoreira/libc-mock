#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME  "app_data"

void write_msg(const char *buff) {
  int fd;

  fd = open(FILENAME, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);

  if (fd > 0) {
    int ret = write(fd, buff, strlen(buff));

    if (ret > 0) {
      printf("data written successfully!\n");
    } else {
      printf("failure to write the data\n");
    }
  }

  close(fd);
}

#ifdef MAIN
int main() {
  write_msg("test");
  return 0;
}
#endif
