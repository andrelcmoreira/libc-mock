#ifndef LIBC_MOCK_H_
#define LIBC_MOCK_H_

#define MOCK_FUNCTION_WITH_ACTION(ret, name, params, action) \
  ret mock_##name params { action } \
  set_##name (mock_##name);

#define MOCK_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return (typeof(ret))0; })

#define MOCK_VOID_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return; })

#define CHECK_CALL(name, times)

#define DECLARE_SETTER(ret, name, ret_ptr, ptr_params) \
  ret set_##name(ret_ptr (*_##name_ptr) ptr_params);

DECLARE_SETTER(void, write, ssize_t, (int, const void *, size_t));

#endif  // LIBC_MOCK_H_
