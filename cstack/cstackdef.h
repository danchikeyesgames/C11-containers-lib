#ifndef __CSTACKDEF_H__
#define __CSTACKDEF_H__

#include <string.h>

#define _sf_cstack_get_size(header) (header->size)

#define _sf_cstack_empty(header) (!header->size)

#define _sf_cstack_get_top(header, object) (memcpy(&object, header->head->mem->data, header->bytes))

#define _sf_cstack_get_data_ptr(header) (header->head->mem->data)

#endif          // __CSTACKDEF_H__