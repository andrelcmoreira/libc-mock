#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>

#include <dlfcn.h>

#define GENERATE_LIBC_HOOK(ret, name, params_sig, param_types, param_values) \
  ret (*mocked_##name) param_types; \
  void set_##name(ret (*_##name_ptr) param_types) { \
    mocked_##name = _##name_ptr; \
  } \
  ret name params_sig { \
    if (mocked_##name) { \
      return mocked_##name param_values; \
    } \
    void *_##name_ptr = dlsym(RTLD_NEXT, #name); \
    if (!dlerror()) { \
      ret (*real_##name) param_types = \
        (ret (*) param_types)_##name_ptr; \
      return real_##name param_values; \
    } \
    return (typeof(ret))0; \
  }

GENERATE_LIBC_HOOK(ssize_t, write,
                   (int fd, const void *buffer, size_t length),
                   (int, const void *, size_t),
                   (fd, buffer, length));
