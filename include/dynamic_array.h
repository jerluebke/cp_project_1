#pragma once
#include "xmalloc.h"

#define FACTOR 1.5L


#define DARRAY_EXTERN(TYPE, NAME)                                           \
extern inline TYPE DArray_##NAME##_get(DArray_##NAME *da, size_t i);        \
extern inline NAME##Iterator *DArray_##NAME##_start(DArray_##NAME *da);     \
extern inline NAME##Iterator *DArray_##NAME##_end(DArray_##NAME *da);       \
extern inline void DArray_##NAME##_init(DArray_##NAME *da, size_t initial); \
extern inline void DArray_##NAME##_append(DArray_##NAME *da, TYPE elem);    \
extern inline void DArray_##NAME##_extend(DArray_##NAME *da,                \
                                          DArray_##NAME *in);               \
extern inline void DArray_##NAME##_free(DArray_##NAME *da);


#define DARRAY_TYPEDEF(TYPE, NAME)  \
typedef TYPE NAME##Iterator;        \
DARRAY_STRUCT(TYPE, NAME)           \
DARRAY_GET(TYPE, NAME)              \
DARRAY_START(TYPE, NAME)            \
DARRAY_END(TYPE, NAME)              \
DARRAY_INIT(TYPE, NAME)             \
DARRAY_APPEND(TYPE, NAME)           \
DARRAY_EXTEND(TYPE, NAME)           \
DARRAY_FREE(NAME)


/* struct DArray
 * wrapper for regular array with dynamic insertion
 * for reference see: https://stackoverflow.com/a/3536261/9133910
 *
 * Members
 * =======
 * p, TYPE *   :   array of data
 * _used, size_t   :   space in use
 * _size, size_t   :   space available
 *
 */
#define DARRAY_STRUCT(TYPE, NAME)                                           \
typedef struct {                                                            \
    TYPE *p;                                                                \
    size_t _used, _size;                                                    \
} DArray_##NAME;                                                            \


/* DArray_start, DArray_end
 * get pointer to first or end (i.e. one behind last) element of data for
 * c++-style iterating:
 *
 *     Iterator *it, *end;
 *     it = DArray_start(da);
 *     end = DArray_end(da);
 *     while ( it != end )
 *         // do something
 *
 * Params
 * ======
 * da, DArray *    :   DArray over which to iterate
 *
 * Returns
 * =======
 * Iterator * (aka TYPE *, e.g. const Item **) pointing to the Arrays first
 *     or one beyond last element
 *
 *  */
#define DARRAY_START(TYPE, NAME)                                            \
inline NAME##Iterator *DArray_##NAME##_start(DArray_##NAME *da)             \
{                                                                           \
    return da->p;                                                           \
}

/* see DArray_start */
#define DARRAY_END(TYPE, NAME)                                              \
inline NAME##Iterator *DArray_##NAME##_end(DArray_##NAME *da)               \
{                                                                           \
    return da->p + da->_used;                                               \
}


/* DArray_get
 * subscript wrapper to access some DArray's data
 * NO BOUNDCHECKING!
 *
 * Params
 * ======
 * da, DArray *    :   DArray whichs p to access
 * i, size_t       :   index to access
 *
 */
#define DARRAY_GET(TYPE, NAME)                                              \
inline TYPE DArray_##NAME##_get(DArray_##NAME *da, size_t i)                \
{                                                                           \
    return da->p[i];                                                        \
}                                                                           \


/* DArray_init
 * allocate p to given size
 *
 * Params
 * ======
 * da, DArray *    :   DArray to initialize
 * initial, size_t :   its initial size
 *
 */
#define DARRAY_INIT(TYPE, NAME)                                             \
inline void DArray_##NAME##_init(DArray_##NAME *da, size_t initial)         \
{                                                                           \
    da->p = xmalloc(sizeof(TYPE) * initial);                                \
    da->_used = 0;                                                          \
    da->_size = initial;                                                    \
}


/* DArray_insert
 * insert value of TYPE at the end of given DArray
 * realloc its data if necessary by factor FACTOR
 *
 * Params
 * ======
 * da, DArray *    :   DArray in which to insert
 * elem, TYPE      :   value to insert
 *
 */
#define DARRAY_APPEND(TYPE, NAME)                                           \
inline void DArray_##NAME##_append(DArray_##NAME *da, TYPE elem)            \
{                                                                           \
    if ( da->_used == da->_size )  {                                        \
        da->_size = (da->_size + 1) * FACTOR;   /* in case da->_size == 0 */\
        da->p = xrealloc(da->p, sizeof(TYPE) * da->_size);                  \
    }                                                                       \
    da->p[da->_used++] = elem;  /* set elem and increment da->_used */      \
}


/* DArray_extend
 * append values from other DArray at end of given DArray
 * realloc if necessary
 *
 * Params
 * ======
 * da, DArray *    :   DArray onto which to extend
 * in, DArray *    :   DArray to extend onto da
 *
 */
#define DARRAY_EXTEND(TYPE, NAME)                                           \
inline void DArray_##NAME##_extend(DArray_##NAME *da, DArray_##NAME *in)    \
{                                                                           \
    size_t new_size = da->_used + in->_used, i = 0;                         \
    if ( new_size >= da->_size ) {                                          \
        da->_size = new_size;                                               \
        da->p = xrealloc(da->p, sizeof(TYPE) * da->_size);                  \
    }                                                                       \
    while ( da->_used < new_size )                                          \
        da->p[da->_used++] = in->p[i++];                                    \
}


/* DArray_free
 * free and set NULL pointer of given DArray
 * set _used and _size to 0
 *
 * Params
 * ======
 * da, DArray *    :   DArray to free
 *
 */
#define DARRAY_FREE(NAME)                                                   \
inline void DArray_##NAME##_free(DArray_##NAME *da)                         \
{                                                                           \
    free(da->p);                                                            \
    da->p = NULL;                                                           \
    da->_used = da->_size = 0;                                              \
}

/* vim: set ff=unix tw=79 sw=4 ts=4 et ic ai : */
