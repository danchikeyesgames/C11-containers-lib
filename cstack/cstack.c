#include <stdlib.h>
#include <string.h>

#include "cstack.h"

static void* cstack_malloc();

void _sf_cstack_create(cstack_t* header, cstack_constructor_t c, cstack_destructor_t d, size_t type_size) {
    (*header) = (cstack_t) cstack_malloc();
    (*header)->constructor = c;
    (*header)->constructor = d;
    (*header)->bytes = type_size;
    (*header)->head = NULL;
    (*header)->size = 0;
}




/*
    ****************************** STATIC FUNCTION *******************************
*/

static void* cstack_malloc() {
    return malloc(sizeof(cstack_header));
}