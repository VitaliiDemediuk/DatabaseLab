#ifndef DATABASELAB_TRASHSTACK_H
#define DATABASELAB_TRASHSTACK_H

#include <stdbool.h>

typedef struct _Node{
    int element;
    struct _Node* next;
} Node;

typedef struct _Stack{
    Node* head;
    int size;
} Stack;

Stack* get_category_trash_stack();

Stack* get_goods_trash_stack();

void trash_push(Stack* trash_stack, int pos);

int trash_pop(Stack* trash_stack);

int trash_peek(Stack* trash_stack);

int trash_size(Stack* trash_stack);

bool trash_is_empty(Stack* trash_stack);

#endif //DATABASELAB_TRASHSTACK_H
