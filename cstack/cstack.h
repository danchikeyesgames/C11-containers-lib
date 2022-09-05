#ifndef __CSTACK_H__
#define __CSTACK_H__

#include <stddef.h>

#define CSTACK_STRUCT_ENABLE
#ifdef CSTACK_STRUCT_ENABLE

typedef struct Item_cstack {
    size_t size_object;
    void* data;
} Item;

typedef struct __cstack {
    Item* data;
    struct __cstack* next;
} cstack;
#endif      // CSTACK_STRUCT_ENABLE

typedef struct __header {
    size_t size;
    cstack* head;
} *cstack_header;

#define cstack_isEmpty(head) (!head->size)

#define cstack_push_back(header, data) cstack_push(header, data, data ? sizeof(*data) : NULL)

#define cstack_unpack(header) header->head->data

#define cstack_pop_back_type(header, TYPE) header->head ? *((TYPE *) cstack_unpack(header)) : 0;    \
        do {                                                    \
            cstack* new = header->head->next;                   \
            free(header->head->data);                           \
            free(header->head);                                 \
            header->head = new;                                 \
        } while(0)

#define cstack_create_stack(header) cstack_createStack(&header)

#define cstack_destroy(header) cstack_destroy_each_node(&header)

#define cstack_check_destroy(header) header ? cstack_destroy_each_node(&header) : header

void    cstack_createStack(cstack_header* header);
void    cstack_push(cstack_header header, void* data, size_t size_object);
void*   cstack_pop_back(cstack_header header);

void    cstack_destroy_each_node(cstack_header* header);

#undef CSTACK_STRUCT_ENABLE
#endif      // __CSTACK_H__