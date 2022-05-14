#include <stdio.h>

ssize_t (*mocked_write)(int, const void *, size_t);

void set_write(ssize_t (*write_ptr)(int, const void *, size_t)) {
  mocked_write = write_ptr;
}

ssize_t write(int fd, const void *buffer, size_t length) {
  if (mocked_write) {
    return mocked_write(fd, buffer, length);
  }

  printf("executing default action\n");

  return 0;
}
