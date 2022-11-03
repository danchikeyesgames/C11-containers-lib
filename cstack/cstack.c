#include <stdlib.h>
#include <string.h>

#include "cstack.h"

static void* cstack_malloc();
static void cstack_free_node(cstack_node* nd);
static void cstack_free_Item(cstack_Item* nd);
static void cstack_free(cstack_t st);

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
            destructor(tmp->mem->data);
        }
        cstack_free_Item(tmp->mem);
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

void sf_cstack_destroy(cstack_t st) {
    cstack_node* current_node = cstack_unpack(st);
    cstack_node* next_node = NULL;
    cstack_destructor_t destructor = st->destructor;

    while (current_node != NULL) {
        next_node = current_node->next;

        if (destructor) {
            destructor(current_node->mem->data);
        }
        cstack_free_Item(current_node->mem);
        cstack_free_node(current_node);

        current_node = next_node;
    }
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

static void cstack_free_Item(cstack_Item* nd) {
    free(nd);
}

static void cstack_free(cstack_t st) {
    free(st);
}