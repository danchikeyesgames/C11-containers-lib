#ifndef __CVECADV_H__
#define __CVECADV_H__

#include "cvector.h"

/* copy the vec_src to vec_dest
    [out] vec_dest
    [in]  vec_src
    @@@ return vector
*/
#define cvector_copy(vec_dest, vec_src) cvector_copy_func((void **) &vec_dest, vec_src, vec_src ? sizeof(*vec_src) : 0)

#define cvector_ccopy(vec_dest, vec_src, foo)                                               \
        do {                                                                                \
            cvector_destroy(vec_dest);                                                      \
            vec_dest = vec_src ? __cvector_initialization_type(cvector_get_size(vec_src), sizeof(*vec_src)) : NULL; \
            cvector_set_size(vec_dest, cvector_get_size(vec_src));                          \
            cvector_set_constructor(vec_dest, cvector_get_constructor(vec_src));            \
            cvector_set_destructor(vec_dest, cvector_get_destructor(vec_src));              \
            for (int i = 0; i < cvector_get_size(vec_src); ++i) {                           \
                foo(&(vec_dest)[i], &(vec_src)[i]);                                         \
            }                                                                               \
        } while(0)


/* concatenation two of vectors
    [out] vec_dest
    [out] vec_src = NULL
    @@@ return resulting vector
*/
#define cvector_con(vec_dest, vec_src) cvector_concatenation((void **) &vec_dest, (void **) &vec_src, vec_src ? sizeof(*vec_src) : 0)


void*   cvector_copy_func(void** vec_dest, void* vec_src, size_t size_object);
void*   cvector_concatenation(void** vec_dest, void** vec_src, size_t size_object);

#endif          // __CVECADV_H__