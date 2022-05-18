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

int read_msg(size_t max_size, char *out_buff) {
  int fd;

  fd = open(FILENAME, O_RDONLY);

  if (fd > 0) {
    int ret = read(fd, out_buff, max_size);

    close(fd);

    if (ret > 0) {
      return 0;
    }
  }

  return -1;
}

#ifdef MAIN
int main() {
  char buffer[255];

  if (write_msg("test")) {
    printf("failure to write the data\n");
    return -1;
  }

  printf("data written successfully!\n");

  if (read_msg(sizeof(buffer), buffer)) {
    printf("failure to read the data\n");
    return -1;
  }

  printf("read msg = %s\n", buffer);

  return 0;
}
#endif
