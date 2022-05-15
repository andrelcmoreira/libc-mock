#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>

#include <dlfcn.h>

ssize_t (*mocked_write)(int, const void *, size_t);

void set_write(ssize_t (*write_ptr)(int, const void *, size_t)) {
  mocked_write = write_ptr;
}

ssize_t write(int fd, const void *buffer, size_t length) {
  if (mocked_write) {
    return mocked_write(fd, buffer, length);
  }

  printf("executing default action\n");

  void *write_ptr = dlsym(RTLD_NEXT, "write");

  if (write_ptr) {
    ssize_t (*real_write)(int, const void *, size_t) =
      (ssize_t (*)(int, const void *, size_t))write_ptr;
    return real_write(fd, buffer, length);
  }

  return 0;
}
