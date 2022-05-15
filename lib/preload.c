#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>

#include <dlfcn.h>

#define GENERATE_HOOK(ret, name, params_sig, param_types, param_values) \
  ret name params_sig { \
    if (mocked_##name) { \
      return mocked_##name param_values; \
    } \
    printf("executing default action\n"); \
    void *_##name_ptr = dlsym(RTLD_NEXT, #name); \
    if (_##name_ptr) { \
      ret (*real_##name) param_types = \
        (ret (*) param_types)_##name_ptr; \
      return real_##name param_values; \
    } \
    return 0; \
  }

ssize_t (*mocked_write)(int, const void *, size_t);

void set_write(ssize_t (*write_ptr)(int, const void *, size_t)) {
  mocked_write = write_ptr;
}

GENERATE_HOOK(ssize_t, write,
              (int fd, const void *buffer, size_t length),
              (int, const void *, size_t),
              (fd, buffer, length));
