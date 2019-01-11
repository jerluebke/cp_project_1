#include "types.h"
#include "xmalloc.h"
#include "dynamic_array.h"

extern inline void *realloc_or_exit(void *ptr, size_t nbytes, const char *file, int line);
extern inline void *malloc_or_exit(size_t nbytes, const char *file, int line);

DARRAY_EXTERN(const Item *, Item)
DARRAY_EXTERN(const Value *, Value)

/* vim: set ff=unix tw=79 sw=4 ts=4 et ic ai : */
