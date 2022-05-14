#ifndef LIBC_MOCK_H_
#define LIBC_MOCK_H_

#define MOCK_FUNCTION_WITH_ACTION(ret, name, params, action) \
  ret mock_##name params { action } \
  set_##name (mock_##name);

#define MOCK_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return 0; })

#define CHECK_CALL(name, times)

#endif  // LIBC_MOCK_H_
