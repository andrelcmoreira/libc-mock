#ifndef LIBC_MOCK_H_
#define LIBC_MOCK_H_

#define MOCK_FUNCTION_WITH_ACTION(ret, name, params, action) \
  ret mock_##name params { action } \
  set_##name (mock_##name);

#define MOCK_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return (typeof(ret))0; })

#define MOCK_VOID_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return; })

#define CHECK_CALL(func, times) \
  if (get_called_times_##func() != times) { \
    printf("function %s expected to be called %d and was called %d!\n", \
      #func, times, get_called_times_##func()); \
  } \
  set_called_times_##func(0); \

#define __DECLARE_SETTER(name, ret_ptr, ptr_params) \
  void set_##name(ret_ptr (*_##name_ptr) ptr_params);

#define __DECLARE_COUNTER_HANDLERS(name) \
  void set_called_times_##name(uint8_t count); \
  uint8_t get_called_times_##name();

#define __DECLARE_MOCK(name, ret_ptr, ptr_params) \
  __DECLARE_SETTER(name, ret_ptr, ptr_params); \
  __DECLARE_COUNTER_HANDLERS(name);

__DECLARE_MOCK(write, ssize_t, (int, const void *, size_t));
__DECLARE_MOCK(read, ssize_t, (int, void *, size_t));

#endif  // LIBC_MOCK_H_
