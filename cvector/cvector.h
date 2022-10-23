#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <stddef.h>

/* macro declare new vector different type */
#define cvector_t(type) type *

typedef void (*cvector_constructor_elem_t) (void* src_vec, void* dest_vec, void* cvector_args);
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

/**
 * @brief gets the current capacity of the vector 
 * 
 * @param v created vector
 */ 
#define cvector_get_capacity(v)             \
        ((v) ? ((size_t *) (v))[-2] : (size_t)0)

/**
 * @brief gets the current size of the vector 
 * 
 * @param v created vector
 */
#define cvector_get_size(v)                 \
        ((v) ? ((size_t *) (v))[-1] : (size_t)0)

/** 
 * @brief gets destructor of the vector (need for advanced functions) 
 * 
 * @param v created vector
 */
#define cvector_get_destructor(v)           \
        ((v) ? (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) : NULL)

/**
 * @brief gets constructor of the vector (need for others functions)
 * 
 * @param v created vector
 */
#define cvector_get_constructor(v)          \
        ((v) ? (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&((size_t *) (v))[-2])))[-1]))[-1]) : NULL)

/**
 * @brief macro move pointer to the beginning of the allocation memory 
 * 
 * @param v vector
 */
#define cvector_unpack_vec(v)               \
        (&(((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&((size_t *) (v))[-2])))[-1]))[-1]))

/**
 * @brief macro move pointer to the beginning array segment of the allocated memory
 * 
 * @param v vector
 */
#define cvector_pack_vec(v)                 \
        (&(((size_t *) &(((cvector_destructor_elem_t *) &(((cvector_constructor_elem_t *) (v))[1]))[1]))[2]))

/**
 * @brief checks vector for an empty
 * 
 * @param v vector
 * 
 * @return if the vector is empty: 1, other case: 0
 */
#define cvector_empty(v)                                        \
        ((cvector_size(v)) ? 0 : 1)

/**
 * @brief checks vector for a full
 * 
 * @param v vector
 * 
 * @return if the vector is full: 1, other case: 0;
 */
#define cvector_full(v)                                         \
        (((cvector_get_size(v)) == (cvector_get_capacity(v))) ? 1 : 0)

/**
 * @brief init vector of defined TYPE
 * 
 * @param TYPE data type
 * @param size size of vector
 * 
 * @return void* pointer on the allocated memory (has packed yet)
 * @overload cvetor_init(TYPE, size), default size = 1
 */
#define cvector_init(TYPE, ...) __cvector_initialization_type(#__VA_ARGS__[0] != '\0' ? __VA_ARGS__ : 1, sizeof(TYPE))

/**
 * @brief install constructor in the vector 
 * 
 * @param v vector 
 * @param f_construct the function constructor for vector
 */
#define cvector_set_constructor(v, f_construct)                 \
        do {                                                    \
            if (!(v))                                           \
                v = __cvector_initialization_type(0, 0);        \
            (((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1])))[-1]) = f_construct;\
        } while(0)

/** 
 * @brief install destructor in the vector 
 * 
 * @param v vector
 * @param f_destructor the function destructor for vector
 */
#define cvector_set_destructor(v, f_destructor)                 \
        do {                                                    \
            if (!(v))                                           \
                v = __cvector_initialization_type(0, 0);        \
            (((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1]) = f_destructor;   \
        } while(0)

/**
 * @brief install size in the vector equal sz 
 * 
 * @param v vector
 * @param sz new size
 */
#define cvector_set_size(v, sz)                                 \
        if ((v))                                                \
            ((size_t *) (v))[-1] = sz

/**
 * @brief install capacity in the vector equal sz
 * 
 * @param v vector
 * @param sz new capacity
 */
#define cvector_set_capacity(v, sz)                             \
        if ((v))                                                \
            ((size_t *) (v))[-2] = sz

/**
 * @brief allocate in 2 times more memory in a heap than size of a capacity vector
 * 
 * @param v vector
 * @param size_object size of object
 */
#define cvector_grow_heap(v, size_object)                       \
        (v) = (v) ? cvector_realloc(v, (cvector_get_capacity(v)) * 2, size_object) : cvector_realloc(v, (size_t) 2, size_object)

/**
 * @brief inserts object in vector by index (objects move rigth)
 * 
 * @param vec created vector
 * @param object object
 * @param index index in vector where object will be insert
 */
#define cvector_insert(vec, object, index)                                                              \
        do {                                                                                            \
            size_t size = cvector_get_size(vec);                                                        \
            if (vec) {                                                                                  \
                if (index < cvector_get_capacity(vec) && cvector_get_capacity(vec) > size) {            \
                    for (int i = size - 1; i >= index; --i) {                                           \
                        (vec)[i + 1] = (vec)[i];                                                        \
                    }                                                                                   \
                    (vec)[index] = object;                                                              \
                    cvector_set_size(vec, size + 1);                                                    \
                }                                                                                       \
            }                                                                                           \
        } while(0)

/**
 * @brief remove object in vector by index
 * 
 * @param vec created vector
 * @param index index in vector
 */
#define cvector_erase(vec, index)                                                                       \
        do {                                                                                            \
            size_t size = cvector_get_size(vec);                                                        \
            if (index < cvector_get_capacity(vec) && size > index) {                                    \
                for (int i = index; i < size - 1; ++i) {                                                \
                    vec[i] = vec[i + 1];                                                                \
                }                                                                                       \
            }                                                                                           \
            cvector_set_size(vec, size - 1);                                                            \
        } while(0)

/**
 * @brief if there is free memory then add at the end of a vector new object, else raise capacity/memory for a vector 
 * 
 * @param vec vector
 * @param object inserted object
 */
#define cvector_push_back(vec, object)                                      \
        if ((cvector_full(vec)))                                            \
            cvector_grow_heap(vec, sizeof(object));                         \
                                                                            \
        (vec)[cvector_get_size(vec)] = object;                              \
        cvector_set_size(vec, (cvector_get_size(vec)) + 1)

/**
 * @brief erase last element, work like as stack
 * 
 * @param vec created vector
 */
#define cvector_pop_back(vec)                                                           \
        do {                                                                            \
            if (!cvector_empty(vec)) {                                                  \
                cvector_destructor_elem_t destructor = cvector_get_destructor(vec);     \
                if ((cvector_get_destructor(vec)) != NULL)                              \
                        destructor(&(vec)[(cvector_get_size(vec)) - 1]);                \
                cvector_set_size(vec, (cvector_get_size(vec)) - 1);                     \
            }                                                                           \
        } while(0)

/**
 * @brief add object in back of the vector to use constructor
 * 
 * @param vec your vector
 * @param object inserted object
 * @param args arguments for constructor function 
 */
#define cvector_cpush_back(vec, object, args)                                                           \
        do {                                                                                            \
            cvector_constructor_elem_t constructor = cvector_get_constructor(vec);                      \
            if ((cvector_full(vec)))                                                                    \
                cvector_grow_heap(vec, sizeof(object));                                                 \
                                                                                                        \
            if (constructor != NULL)                                                                    \
                constructor((void *) &object, (void *) &((vec)[cvector_get_size(vec)]), (void *) args); \
            else (vec)[cvector_get_size(vec)] = object;                                                 \
                                                                                                        \
            cvector_set_size(vec, (cvector_get_size(vec)) + 1);                                         \
        } while(0)

/**
 * @brief change capacity size of vector (if data size < new_size then last elements are erased)
 * 
 * @param vec your vector
 * @param new_size capacity size of new vector
 * @param object_type data type in your vector
 */
#define cvector_resize(vec, new_size, object_type)                                  \
        if (new_size < cvector_get_size(vec)) cvector_set_size(vec, new_size);      \
        vec = cvector_realloc(vec, new_size, sizeof(object_type))

/**
 * @brief erase all elements of vector, but cans to use vector continue
 * 
 * @param vec your vector
 */
#define cvector_clear(vec)                                                          \
        do {                                                                        \
            cvector_pop_back(vec);                                                  \
        } while(!cvector_empty(vec))

/**
 * @brief free the vector also call a destructor for each element
 * 
 * @param v vector
 */
#define cvector_destroy(v) __cvector_destroy(v, sizeof(*v))

/**
 * @brief if ptr not equal NULL calling cvector_destroy()
 *
 * @throw warning: protect from destroy NULL memory
 * 
 * @param ptr vector
 */
#define cvector_check_destroy(ptr) (ptr ? (__cvector_destroy(ptr, sizeof(*ptr)), ptr = NULL) : ptr)

/**
 * @brief if ptr not equal NULL calling cvector_free()
 * @throw protect from free NULL memory
 *
 * @param ptr vector
 */
#define cvector_check_free(ptr) (ptr ? (cvector_free(ptr), ptr = NULL) : ptr)

//  --------------------------------------------------------------------------------
/********           user interface functions segment                       ********/

void*   cvector_realloc(void* src, size_t size, size_t size_object);
void    cvector_free(void* v);

/*********             macro functions  segment                           **********/

void*   __cvector_initialization_type(int size, size_t size_object);
void    __cvector_destroy(void* v, size_t size_object);

//  ----------------------------------------------------------------------------------

#endif      // __CVECTOR_H__