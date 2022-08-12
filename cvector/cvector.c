#include "cvector.h"

#include <stdio.h>
#include <stdlib.h>

void* __cvector_initialization_type(int size, size_t size_object) {
    void* vector = malloc(sizeof(cvector_constructor_elem_t) + sizeof(cvector_destructor_elem_t) + 2*sizeof(size_t) + size*size_object);
    vector = &((size_t *) &(((cvector_destructor_elem_t *) &(((cvector_constructor_elem_t *) vector)[1]))[1]))[2];
    cvector_set_capacity(vector, size);
    cvector_set_size(vector, 0);
    cvector_set_destructor(vector, NULL);
    cvector_set_constructor(vector, NULL);

    return vector;
}