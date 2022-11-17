#ifndef __CSTACKDEF_H__
#define __CSTACKDEF_H__

#include <string.h>

#define _sf_cstack_get_size(header) (header->size)

#define _sf_cstack_empty(header) (!header->size)

#define _sf_cstack_get_top(header, object) 0;                       \
        (memcpy(&object, header->head->mem->data, header->bytes))

#define _sd_cstack_get_top(header) (header->head->mem)

#define _sf_cstack_unpack_node(node) (node->mem->data)

#define _sf_cstack_cget_top(header, object)                         \
        cstack_unpack(header) == NULL ? 1 : (_sf_cstack_get_top(header, object))

#define _sf_cstack_get_data_ptr(header) (header->head->mem->data)

#define _sf_cstack_pointer_head(header) (header->head)

#endif          // __CSTACKDEF_H__