#ifndef __CSTACK_H__
#define __CSTACK_H__

#include <stddef.h>

#include "cstackdef.h"

/**
 * @brief primary file with declare types and functions
 *          
 * @author btw i use arch
 * 
 * @def CSTACK_STRUCT_ENABLE to use lib  
 */

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
} cstack_header, *cstack_t;

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
#define cstack_unpack(header) (_sf_cstack_pointer_head(header))

/**
 * @brief gets data in node
 * 
 * @param node node in stack
 * 
 * @return pointer on data segment
 */
#define cstack_unpack_node(node) (_sf_ccstack_unpack_node(node))

/**
 * @brief create and init stack
 * 
 * @param cstack_header your declaration variable type of cstack_t
 * @param f_const pointer to constructor function (for allocated elemets, other case can put NULL)
 * @param f_dest  pointer to destructor function  (for allocated elemets, other case can put NULL)
 * @param TYPE    type of objects in stack
 */
#define cstack_create(cstack_header, f_const, f_dest, TYPE) _sf_cstack_create(&cstack_header, f_const, f_dest, sizeof(TYPE))

/**
 * @brief data top element of stack replace to object
 * 
 * @param header your stack
 * @param object object which accept data from stack
 * 
 * @return 1: stack has not element; 0: others case
 */
#define cstack_get_top(header, object) _sf_cstack_cget_top(header, object)

/**
 * @brief get pointer to element in stack
 * 
 * @param header stack
 * 
 * @return pointer to object from top node (type of void*, can require casting to your type pointer) 
 */
#define cstack_get_data_ptr(header) (_sf_cstack_get_data_ptr(header))

/**
 * @brief erase top element in the stack
 * 
 * @param cstack your stack
 */
#define cstack_pop(cstack) _sf_cstack_pop(cstack)

/***************************************************
 * * * * * * * * functions segment * * * * * * * * *
 ***************************************************/

void    _sf_cstack_create(cstack_t* header, cstack_constructor_t c, cstack_destructor_t d, size_t type_size);
void    _sf_cstack_pop(cstack_t cs);

#endif      // __CSTACK_H__