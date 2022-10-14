#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <stddef.h>

/* macros declare new vector different type */
#define cvector_t(type) type *

typedef void (*cvector_constructor_elem_t) (void* adr, void* cvector_args);
typedef void (*cvector_destructor_elem_t)  (void* adr);

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
        ((v) ? ((size_t *) (v))[-2] : (size_t)0)

/* gets the current size of the vector */
#define cvector_get_size(v)         \
        ((v) ? ((size_t *) (v))[-1] : (size_t)0)

/* macros gets destructor of the vector (need for others functions) */
#define cvector_get_destructor(v)   \
        ((v) ? (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) : NULL)

/* macros gets constructor of the vector (need for others functions) */
#define cvector_get_constructor(v)  \
        ((v) ? (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&((size_t *) (v))[-2])))[-1]))[-1]) : NULL)

/* macros move pointer to the beginning of the allocation memory */
#define cvector_unpack_vec(v)       \
        (&(((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&((size_t *) (v))[-2])))[-1]))[-1]))

/* macros move pointer to the beginning of the array segment of allocation memory */
#define cvector_pack_vec(v)         \
        (&(((size_t *) &(((cvector_destructor_elem_t *) &(((cvector_constructor_elem_t *) (v))[1]))[1]))[2]))

/* checks if vector is empty
@@@ return 1 - if the vector is empty, other case - 0;
*/
#define cvector_empty(v)                                        \
        ((cvector_size(v)) ? 0 : 1)

/* checks if vector is full
@@@ return 1 - if the vector is full, other case - 0;
*/
#define cvector_full(v)                                         \
        (((cvector_get_size(v)) == (cvector_get_capacity(v))) ? 1 : 0)

/*  init cvector of defined TYPE 
    return void* pointer on the allocated memory (packed yet)
@@@@@@ overload
cvetor_init(TYPE, size) ---- default size = 1;
*/
#define cvector_init(TYPE, ...) __cvector_initialization_type(#__VA_ARGS__[0] != '\0' ? __VA_ARGS__ : 1, sizeof(TYPE))

/* install constructor in the vector */
#define cvector_set_constructor(v, construct_fun)               \
        do {                                                    \
            if (!(v))                                           \
                v = __cvector_initialization_type(0, 0);        \
            (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1])))[-1]) = construct_fun;   \
        } while(0)

/* install destructor in the vector */
#define cvector_set_destructor(v, destructor_fun)               \
        do {                                                    \
            if (!(v))                                           \
                v = __cvector_initialization_type(0, 0);        \
            (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) = destructor_fun;   \
        } while(0)

/* install size in the vector equal sz */
#define cvector_set_size(v, sz)                                 \
        if ((v))                                                \
            ((size_t *) (v))[-1] = sz

/* install capacity in the vector equal sz */
#define cvector_set_capacity(v, sz)                             \
        if ((v))                                                \
            ((size_t *) (v))[-2] = sz

/*  raise or eraise of the vector to size `sz` 
    if vector is NULL then use cvector_init(...), dont work with a not initialization vector
    @@@ return pointer on new vector (pointer has packed yet)
*/

/* allocate in 2 times more memory in a heap
   if size of the vector equal it capacity
*/
#define cvector_grow_heap(v, size_object)                                   \
        (v) = (v) ? cvector_realloc(v, (cvector_get_capacity(v)) * 2, size_object) : cvector_realloc(v, (size_t) 2, size_object)

#define cvector_insert(vec, object, index)                                  \
        do {                                                                \
            size_t size = cvector_get_size(vec);                            \
            if (vec) {                                                      \
                if (index < cvector_get_capacity(vec) && cvector_get_capacity(vec) > size + 1) {     \
                    for (int i = size; i >= index; --i) {                   \
                        vec[i + 1] = vec[i];                                \
                    }                                                       \
                    vec[index] = object;                                    \
                }                                                           \
            }                                                               \
        } while(0)

/*  if there is free memory then
    add at the end of a vector new object, else raise capacity/memory for a vector 
*/
#define cvector_push_back(vec, object)                                      \
        if ((cvector_full(vec)))                                            \
            cvector_grow_heap(vec, sizeof(object));                         \
                                                                            \
        (vec)[cvector_get_size(vec)] = object;                              \
        cvector_set_size(vec, (cvector_get_size(vec)) + 1)

/* pop object at the end of a vector & return this object
    @@@ return object at the end
*/
#define cvector_pop_back(vec)                                                       \
        do {                                                                        \
            cvector_destructor_elem_t destructor = cvector_get_destructor(vec);     \
            if ((cvector_get_destructor(vec)) != NULL)                              \
                    destructor(&(vec)[(cvector_get_size(vec)) - 1]);                \
            cvector_set_size(vec, (cvector_get_size(vec)) - 1);                     \
        } while(0)

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

/*
    free the vector also call a destructor for each element
*/
#define cvector_destroy(v) __cvector_destroy(v, sizeof(*v))

/*
    if ptr not equal NULL calling cvector_destroy()
    protect from destroy NULL memory
*/
#define cvector_check_destroy(ptr) ptr ? (__cvector_destroy(ptr, sizeof(*ptr)), ptr = NULL) : ptr

/*
    if ptr not equal NULL calling cvector_free()
    protect from free NULL memory
*/
#define cvector_check_free(ptr) ptr ? (cvector_free(ptr), ptr = NULL) : ptr

//  --------------------------------------------------------------------------------
/********           user interface functions segment                       ********/

void*   cvector_copy_func(void** vec_dest, void* vec_src, size_t size_object);
void*   cvector_concatenation(void** vec_dest, void** vec_src, size_t size_object);
void*   cvector_realloc(void* src, size_t size, size_t size_object);
void    cvector_free(void* v);

/*********             macro functions  segment                           **********/

void*   __cvector_initialization_type(int size, size_t size_object);
void    __cvector_destroy(void* v, size_t size_object);

//  ----------------------------------------------------------------------------------

#endif  // __CVECTOR_H__


