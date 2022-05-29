#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>

#include <dlfcn.h>

#define GENERATE_LIBC_HOOK(ret, name, params_sig, param_types, param_values) \
  ret (*mocked_##name) param_types; \
  void set_##name(ret (*_##name_ptr) param_types) { \
    mocked_##name = _##name_ptr; \
  } \
  uint8_t called_times_##name = 0; \
  void set_called_times_##name(const uint8_t count) { \
    called_times_##name = count; \
  } \
  uint8_t get_called_times_##name() { \
    return called_times_##name; \
  } \
  ret name params_sig { \
    if (mocked_##name) { \
      set_called_times_##name(get_called_times_##name() + 1); \
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

GENERATE_LIBC_HOOK(ssize_t, read,
                   (int fd, void *buffer, size_t length),
                   (int, void *, size_t),
                   (fd, buffer, length));
