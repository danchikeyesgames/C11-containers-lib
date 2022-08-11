#ifndef __CVECTOR_H__
#define __CVECTOR_H__

/* macros declare new vector different type */
#define con_cvector_init_type(type) type *

typedef void (*cvector_constructor_elem_t) (void* adr);
typedef void (*cvector_destructor_elem_t)  (void* adr);
typedef unsigned long size_t;

typedef struct vec_cvector_struct {
    cvector_constructor_elem_t constructor_pointer;
    cvector_destructor_elem_t  destructor_pointer;
    size_t capacity;
    size_t size;
    void*  data;
} con_cvector_t;

#define con_cvector_get_capacity(v)  \
        (v) ? ((size_t *) (v))[-2] : (size_t)0;

#define con_cvector_get_size(v)  \
        (v) ? ((size_t *) (v))[-1] : (size_t)0;

#define con_cvector_get_destructor(v)  \
        (v) ? (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) : NULL;

#define con_cvector_get_constructor(v) \
        (v) ? (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *)) (v))[-2])))[-1]))[-1]) : NULL;  

#define con_cvector_empty(v)   \
        (con_cvector_size) ? 0 : 1;

#define con_cvector_full(v)    \
        ((con_cvector_size) == (con_cvector_capacity)) ? 1 : 0;






#endif  // __CVECTOR_H__


