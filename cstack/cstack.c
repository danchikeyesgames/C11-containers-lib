#include <cstack.h>
#include <stdlib.h>
#include <string.h>

static Item* cstack_malloc_Item(size_t sz, void* data);
static cstack* cstack_malloc_node(void);
static cstack_header cstack_malloc(void);
static void cstack_free_node(cstack* node);

void cstack_createStack(cstack_header* header) {
    *header = cstack_malloc();
    (*header)->size = 0;
    (*header)->head = NULL;
}

void cstack_push(cstack_header header, void* data, size_t size_object) {
    cstack *new_node = cstack_malloc_node();
    Item* new_Item = cstack_malloc_Item(size_object, data);
    cstack* prevNode = header->head;

    new_node->data  = new_Item;
    new_node->next  = prevNode;
    header->head    = new_node;
}

void* cstack_pop_back(cstack_header header) {
    cstack* node = header->head;
    void* p = NULL;

    if (node) {
        p = node->data;
        header->head = node->next;
        free(node);
    }

    return p;
}

void cstack_destroy_each_node(cstack_header* header) {
    cstack* node = (*header)->head;
    
    while (node) {
        node = node->next;
        cstack_free_node(node);
    }

    *header = NULL;
}

/*---------------------------------
          static functions
---------------------------------*/

static Item* cstack_malloc_Item(size_t sz, void* data) {
    Item* node = (Item *) malloc(sizeof(Item));
    void* new_data = malloc(sz);

    memcpy(new_data, data, sz);
    node->size_object = sz;
    node->data = new_data;

    return node;
}

static cstack* cstack_malloc_node(void) {
    return (cstack *) malloc(sizeof(struct __cstack));
}

static cstack_header cstack_malloc(void) {
    return (cstack_header) malloc(sizeof(struct __header));
}

static void cstack_free_node(cstack* node) {
    free(node->data);
    free(node);
}