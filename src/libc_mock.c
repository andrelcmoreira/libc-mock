#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>

#include <dlfcn.h>

#define DECLARE_MOCK_IMPL(ret, name, params_sig, param_types, param_values) \
  DECLARE_SETTER_IMPL(ret, name, param_types) \
  DECLARE_COUNTER_HANDLERS_IMPL(name) \
  GENERATE_LIBC_HOOK(ret, name, params_sig, param_types, param_values)

#define DECLARE_SETTER_IMPL(ret, name, param_types) \
  ret (*mocked_##name) param_types; \
  void set_##name(ret (*_##name_ptr) param_types) { \
    mocked_##name = _##name_ptr; \
  }

#define DECLARE_COUNTER_HANDLERS_IMPL(name) \
  static uint8_t called_times_##name; \
  void set_called_times_##name(const uint8_t count) { \
    called_times_##name = count; \
  } \
  uint8_t get_called_times_##name() { \
    return called_times_##name; \
  }

#define GENERATE_LIBC_HOOK(ret, name, params_sig, param_types, param_values) \
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

DECLARE_MOCK_IMPL(ssize_t, write,
                  (int fd, const void *buffer, size_t length),
                  (int, const void *, size_t),
                  (fd, buffer, length));

DECLARE_MOCK_IMPL(ssize_t, read,
                  (int fd, void *buffer, size_t length),
                  (int, void *, size_t),
                  (fd, buffer, length));

DECLARE_MOCK_IMPL(ssize_t, send,
                  (int sockfd, const void *buf, size_t len, int flags),
                  (int, const void *, size_t, int),
                  (sockfd, buf, len, flags));

DECLARE_MOCK_IMPL(ssize_t, recv,
                  (int sockfd, void *buf, size_t len, int flags),
                  (int, void *, size_t, int),
                  (sockfd, buf, len, flags));

DECLARE_MOCK_IMPL(int, connect,
                  (int sockfd, const struct sockaddr *addr, socklen_t addrlen),
                  (int, const struct sockaddr *, socklen_t),
                  (sockfd, addr, addrlen));
