#ifndef __CSTACK_H__
#define __CSTACK_H__

#include <stddef.h>

#include "cstackdef.h"

#define CSTACK_STRUCT_ENABLE

typedef void (*cstack_destructor_t) (void* adr);
typedef void (*cstack_constructor_t) (void* src_stack, void* dest_stack, void* cstack_args);

typedef struct __Item_cstack {
    size_t size_object;
    void* data;
} Item;

typedef struct __cstack_node {
    Item* mem;
    struct  __cstack_node* next;
} cstack_node;

/**
 * @brief header structure for cstack
 * 
 * @struct cstack_t
 */
typedef struct __header {
    size_t          bytes;
    size_t          size;
    cstack_node*    head;
    cstack_destructor_t  destructor;
    cstack_constructor_t constructor;
} *cstack_t;

/**
 * @brief gets current size of the stack 
 * 
 * @param cstack your stack
 */
#define cstack_get_size(cstack) _sf_cstack_get_size(cstack)

/**
 * @brief checks empty of stack 
 * 
 * @param cstack your stack
 * 
 * @return 1: if stack empty, 0: if size > 0
 */
#define cstack_empty(cstack) _sf_cstack_empty(cstack)

/**
 * @brief gets top stack node
 * 
 * @param header your stack
 * 
 * @return pointer on top element of the stack
 */
#define cstack_unpack(header) (header->head)

#define cstack_create(cstack_header, f_const, f_dest, TYPE) _sf_cstack_create(&cstack_header, f_const, f_dest, sizeof(TYPE))

#define cstack_get_top(header, object) (_sf_cstack_get_top(header, object))

#define cstack_get_data_ptr(header) (_sf_cstack_get_data_ptr(header))

/***************************************************
 * * * * * * * * functions segment * * * * * * * * *
 ***************************************************/

void    _sf_cstack_create(cstack_t* header, cstack_constructor_t c, cstack_destructor_t d, size_t type_size);

#endif      // __CSTACK_H__