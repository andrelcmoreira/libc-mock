#ifndef PRELOAD_H_
#define PRELOAD_H_

void set_write(ssize_t (*write_ptr)(int, const void *, size_t));

#endif
