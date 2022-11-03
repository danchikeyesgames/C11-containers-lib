#include <stdlib.h>
#include <string.h>

#include "cstack.h"

static void* cstack_malloc();
static void cstack_free_node(cstack_node* nd);

void _sf_cstack_create(cstack_t* header, cstack_constructor_t c, cstack_destructor_t d, size_t type_size) {
    (*header) = (cstack_t) cstack_malloc();
    (*header)->constructor = c;
    (*header)->constructor = d;
    (*header)->bytes = type_size;
    (*header)->head = NULL;
    (*header)->size = 0;
}

void _sf_cstack_pop(cstack_t cs) {
    cstack_destructor_t destructor = cs->destructor;
    cstack_node* tmp = cstack_unpack(cs);

    if (tmp) {
        cs->head = cs->head->next;
        --cs->size;
        
        if (destructor) {
            destrutor(tmp->mem->data);
        }
        cstack_free_node(tmp);
    }
}

cstack_node* sf_cstack_peek(cstack_t stack, size_t count) {
    cstack_node* tmp = stack->head;
    size_t i = 1;

    while (i++ < count) {
        tmp = tmp->next;
    }

    return tmp;
}

/*
    ****************************** STATIC FUNCTION *******************************
*/

static void* cstack_malloc() {
    return malloc(sizeof(cstack_header));
}

static void cstack_free_node(cstack_node* nd) {
    free(nd);
}