#ifndef __CVECTOR_H__
#define __CVECTOR_H__

/* macros declare new vector different type */
#define cvector_init_type(type) type *

typedef void (*cvector_constructor_elem_t) (void* adr);
typedef void (*cvector_destructor_elem_t)  (void* adr);
typedef unsigned long size_t;

#ifdef CVECTOR_STRUCT_ENABLE

#define cvector_type(TYPE) struct {                 \
    cvector_constructor_elem_t constructor_pointer; \
    cvector_destructor_elem_t  destructor_pointer;  \
    size_t capacity;                                \
    size_t size;                                    \
    TYPE*  data;                                    \
}

#endif

/*********************
segment with define data
*********************/

/* gets the current capacity of the vector */ 
#define cvector_get_capacity(v)     \
        (v) ? ((size_t *) (v))[-2] : (size_t)0

/* gets the current size of the vector */
#define cvector_get_size(v)         \
        (v) ? ((size_t *) (v))[-1] : (size_t)0

/* macros gets destructor of the vector (need for others functions) */
#define cvector_get_destructor(v)   \
        (v) ? (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) : NULL

/* macros gets constructor of the vector (need for others functions) */
#define cvector_get_constructor(v)  \
        (v) ? (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&((size_t *) (v))[-2])))[-1]))[-1]) : NULL

#define cvector_unpack_vec(v)       \
        &(((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&((size_t *) (v))[-2])))[-1]))[-1])

#define cvector_pack_vec(v)         \
        &(((size_t *) &(((cvector_destructor_elem_t *) &(((cvector_constructor_elem_t *) (v))[1]))[1]))[2])

/* checks if vector is empty
@@@ return 1 - if the vector is empty, other case - 0;
*/
#define cvector_empty(v)                                        \
        (cvector_size(v)) ? 0 : 1

#define cvector_full(v)                                         \
        ((cvector_get_size) == (cvector_get_capacity)) ? 1 : 0

#define cvector_init(size, type) __cvector_initialization_type(size, sizeof(type))

#define cvector_set_constructor(v, construct_fun)               \
        do {                                                    \
            if (!(v))                                           \
                v = cvector_set_grow(0, 0);                     \
            (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1])))[-1]) = construct_fun;   \
        } while(0)

#define cvector_set_destructor(v, destructor_fun)               \
        do {                                                    \
            if (!(v))                                           \
                v = cvector_set_grow(0, 0);                     \
            (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) = destructor_fun;   \
        } while(0)

#define cvector_set_size(v, sz)                                 \
        if ((v))                                                \
            ((size_t *) (v))[-1] = sz

#define cvector_set_capacity(v, sz)                             \
        if ((v))                                                \
            ((size_t *) (v))[-2] = sz
                    
#define cvector_grow_heap(v, size_object)                                   \
        (v) = cvector_realloc(v, cvector_get_capacity(v) * 2, size_object)

#define cvector_push_back(vec, object)                                      \
        if ((cvector_get_size(vec)) >= (cvector_get_capacity(vec))) {       \
            cvector_grow_heap(vec, sizeof(object));                         \
            (vec) = cvector_pack_vec(vec);                                  \
        }                                                                   \
        (vec)[cvector_get_size(vec)] = object;                              \
        cvector_set_size(vec, cvector_get_size(vec) + 1) 

#define cvector_pop_back(vec) (vec)[cvector_get_size(vec) - 1];             \
        cvector_set_size(vec, cvector_get_size(vec) - 1)


/* user interface functions */

void*   __cvector_initialization_type(int size, size_t size_object);
void*   cvector_set_grow(size_t sz, size_t size_object);
void*   cvector_realloc(void* src, size_t size, size_t size_object);
void    cvector_free(void* v);

#endif  // __CVECTOR_H__


