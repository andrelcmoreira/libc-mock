#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME  "app_data"

int write_msg(const char *buff) {
  int fd;

  fd = open(FILENAME, O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);

  if (fd > 0) {
    size_t size = strlen(buff);
    int ret = write(fd, buff, size);

    close(fd);

    if (ret == size) {
      return 0;
    }
  }

  return -1;
}

#ifdef MAIN
int main() {
  if (!write_msg("test")) {
    printf("data written successfully!\n");
  } else {
    printf("failure to write the data\n");
  }

  return 0;
}
#endif
