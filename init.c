#include "init.h"
#include "indextables.h"

void start_program(){
    categories_index_table_init();
    goods_index_table_init();
}

void end_program(){
    categories_index_table_save();
    goods_index_table_save();
    categories_index_table_free();
    goods_index_table_free();
}