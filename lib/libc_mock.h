#ifndef LIBC_MOCK_H_
#define LIBC_MOCK_H_

#include "preload.h"

#define MOCK_FUNCTION_WITH_ACTION(ret, name, params, action) \
  ret mock_##name params { action } \
  set_##name (mock_##name);

#define MOCK_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return (typeof(ret))0; })

#define MOCK_VOID_FUNCTION(ret, name, params) \
  MOCK_FUNCTION_WITH_ACTION(ret, name, params, { return; })

#define CHECK_CALL(name, times)

#endif  // LIBC_MOCK_H_
