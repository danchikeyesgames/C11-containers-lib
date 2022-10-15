#include "cvecadv.h"


void* cvector_copy_func(void** vec_dest_src, void* vec_src, size_t size_object) {
    size_t size = 0;
    void* vec_dest = *vec_dest_src;
    void* src_ptr = NULL;
    void* dest_ptr = NULL;

    if (vec_src) {
        src_ptr = cvector_unpack_vec(vec_src);
        size = cvector_sizeof(cvector_get_capacity(vec_src), size_object);
        if (vec_dest)
            cvector_destroy(vec_dest);
    
        dest_ptr = (void *) malloc(size);
        memcpy(dest_ptr, src_ptr, size);
        dest_ptr = cvector_pack_vec(dest_ptr);
    } else {
        if (vec_dest)
            cvector_destroy(vec_dest);

        return NULL;
    }

    *vec_dest_src = dest_ptr;
    return dest_ptr;
}


void* cvector_concatenation(void** vec_dest_src, void** vec_src_ptr, size_t size_object) {
    void*   vec_dest  = *vec_dest_src;
    void*   vec_src   = *vec_src_ptr;
    size_t  size_src  = cvector_get_size(vec_src);
    size_t  size_dest = cvector_get_size(vec_dest);
    void*   dest_vector_start = cvector_unpack_vec(vec_dest);
    void*   new_vec   = NULL;
    void*   vectorptr = NULL;

    if (size_src + size_dest > cvector_get_capacity(vec_dest)) {
        new_vec = malloc(cvector_sizeof(size_src + size_dest, size_object));
        memcpy(new_vec, dest_vector_start, cvector_sizeof(size_dest, size_object));
        cvector_free(vec_dest);
        new_vec = cvector_pack_vec(new_vec);
        cvector_set_capacity(new_vec, size_dest + size_src);
    } else new_vec = vec_dest;

    vectorptr = new_vec + size_dest * size_object;
    memcpy(vectorptr, vec_src, size_object * size_src);
    cvector_set_size(new_vec, size_dest + size_src);

    cvector_free(vec_src);
    *vec_src_ptr = NULL;
    *vec_dest_src = new_vec;
    return new_vec;
}