#include "cvector.h"

#include <stdio.h>
#include <stdlib.h>

void* __cvector_initialization_type(int size, size_t size_object) {
    void* vector = malloc(sizeof(cvector_constructor_elem_t) + sizeof(cvector_destructor_elem_t) + 2*sizeof(size_t) + size*size_object);
    vector = &(((size_t *) &(((cvector_destructor_elem_t *) &(((cvector_constructor_elem_t *) vector)[1]))[1]))[2]);
    cvector_set_capacity(vector, size);
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

void* cvector_realloc(void* src, size_t size, size_t size_object) {
    cvector_set_capacity(src, size);
    size_t new_size = sizeof(cvector_constructor_elem_t) + sizeof(cvector_destructor_elem_t) + 2*sizeof(size_t) + size*size_object;
    return realloc(cvector_unpack_vec(src), new_size);
}

void cvector_free(void* v) {
    free(&(((cvector_constructor_elem_t *) (&(((cvector_destructor_elem_t *) (&(((size_t *) (v))[-2])))[-1])))[-1]));
}
