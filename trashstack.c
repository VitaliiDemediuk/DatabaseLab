#include "trashstack.h"
#include <stdio.h>
#include <stdlib.h>

static Stack category_trash_stack;
static Stack goods_trash_stack;

Stack* get_category_trash_stack(){
    return &category_trash_stack;
}

Stack* get_goods_trash_stack(){
    return &goods_trash_stack;
}

void trash_push(Stack* trash_stack, int pk_id){
    Node* new_node = (Node *)malloc(sizeof(Node));
    new_node->next = trash_stack->head;
    new_node->element = pk_id;
    trash_stack->head = new_node;
    ++trash_stack->size;
}

int trash_pop(Stack* trash_stack){
    Node* old_head = trash_stack->head;
    int res = old_head->element;
    trash_stack->head = old_head->next;
    free(old_head);
    --trash_stack->size;
    return res;
}

int trash_peek(Stack* trash_stack){
    return trash_stack->head->element;
}

int trash_size(Stack* trash_stack){
    return trash_stack->size;
}

bool trash_is_empty(Stack* trash_stack){
    return trash_stack->head == NULL;
}