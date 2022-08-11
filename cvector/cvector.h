#ifndef __CVECTOR_H__
#define __CVECTOR_H__

/* macros declare new vector different type */
#define cvector_init_type(type) type *

typedef void (*cvector_constructor_elem_t) (void* adr);
typedef void (*cvector_destructor_elem_t)  (void* adr);
typedef unsigned long size_t;

typedef struct vec_cvector_struct {
    cvector_constructor_elem_t constructor_pointer;
    cvector_destructor_elem_t  destructor_pointer;
    size_t capacity;
    size_t size;
    void*  data;
} cvector_t;

#define cvector_get_capacity(v)  \
        (v) ? ((size_t *) (v))[-2] : (size_t)0;

#define cvector_get_size(v)  \
        (v) ? ((size_t *) (v))[-1] : (size_t)0;

#define cvector_get_destructor(v)  \
        (v) ? (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) : NULL;

#define cvector_get_constructor(v) \
        (v) ? (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *)) (v))[-2])))[-1]))[-1]) : NULL;  

#define cvector_empty(v)                                    \
        (cvector_size) ? 0 : 1

#define cvector_full(v)                                     \
        ((cvector_get_size) == (cvector_get_capacity)) ? 1 : 0

#define cvector_init(size, type) __cvector_initialization_type(size, sizeof(type))

#define cvector_set_constructor(v, construct_fun)           \
        do {                                                \
            if (!(v))                                       \
                cvector_set_grow(v, 0);                     \
            (cvector_get_constructor) = construct_fun;      \
        } while(0)

#define cvector_set_festructor(v, destructor_fun)           \
        do {                                                \
            if (!(v))                                       \
                cvector_set_grow(v, 0);                     \
            (cvector_get_destructor) = destructor_fun;      \
        } while(0)

#define cvector_set_size(v, sz)                             \
        if ((v))                                            \
            (cvector_get_size) = sz

#define cvector_set_capacity(v, sz)                         \
        if (v)                                              \
            (cvector_get_capacity = sz
                    
/* user interface functions */

void cvector_push_back();

#endif  // __CVECTOR_H__


