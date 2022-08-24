#include "cvector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void cvector_destroy_for_each(void* v, size_t size_object);

void* __cvector_initialization_type(int size, size_t size_object) {
    void* vector = malloc(sizeof(cvector_constructor_elem_t) + sizeof(cvector_destructor_elem_t) + 2*sizeof(size_t) + size*size_object);
    vector = cvector_pack_vec(vector);
    cvector_set_capacity(vector, (size_t) size);
    cvector_set_size(vector, 0);
    cvector_set_destructor(vector, NULL);
    cvector_set_constructor(vector, NULL);

    return vector;
}

void* cvector_set_grow(size_t sz, size_t size_object) {
    void* vec = NULL;
    vec = __cvector_initialization_type(sz, size_object);
    
    return vec;
}

void* cvector_copy_func(void* vec_dest, void* vec_src, size_t size_object) {
    size_t size = 0;
    void* src_ptr = NULL;
    void* dest_ptr = NULL;

    if (vec_src) {
        src_ptr = cvector_unpack_vec(vec_src);
        size = sizeof(cvector_constructor_elem_t) + sizeof(cvector_destructor_elem_t) + 2*sizeof(size_t) + cvector_get_capacity(vec_src) * size_object;
        if (vec_dest)
            cvector_free(vec_dest);
    
        dest_ptr = (void *) malloc(size);
        memcpy(dest_ptr, src_ptr, size);
        dest_ptr = cvector_pack_vec(dest_ptr);
    } else {
        if (vec_dest)
            cvector_free(vec_dest);

        return NULL;
    }

    return dest_ptr;
}

void* cvector_realloc(void* src, size_t size, size_t size_object) {
    size_t new_size = sizeof(cvector_constructor_elem_t) + sizeof(cvector_destructor_elem_t) + 2*sizeof(size_t) + size*size_object;
    void* v = NULL;
    
    if (src == NULL)
        v = malloc(new_size);
    else
        v = realloc(cvector_unpack_vec(src), new_size);

    v = cvector_pack_vec(v);
    cvector_set_capacity(v, size);

    return v;
}

void cvector_free(void* v) {
    free(&(((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1])))[-1]));
}

void __cvector_destroy(void* v, size_t size_object) {
    if ((cvector_get_destructor(v)) != NULL)
        cvector_destroy_for_each(v, size_object);
    cvector_free(v);
}

// -----------------------------------
//          static function
// -----------------------------------

static void cvector_destroy_for_each(void* v, size_t size_object) {
    size_t size = cvector_get_size(v);
    cvector_destructor_elem_t destruct = cvector_get_destructor(v);
    for (int i = 0; i < size; ++i) {
        destruct((void*) (v + i * size_object));
    }
}