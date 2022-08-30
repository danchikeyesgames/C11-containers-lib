#include <cstack.h>
#include <stdlib.h>

void cstack_createStack(cstack_header* header) {
    *header = cstack_malloc();
    (*header)->size = 0;
    (*header)->head = NULL;
}



/*---------------------------------
          static functions
---------------------------------*/

static Item* cstack_malloc_Item() {

}

static cstack* cstack_malloc_node() {

}

static cstack_header cstack_malloc(void) {
    return (cstack_header) malloc(sizeof(struct __header));
}