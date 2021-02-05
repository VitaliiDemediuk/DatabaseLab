#include <stdio.h>
#include <stdlib.h>
#include "dbfunctions.h"
#include "tables.h"
#include "configurations.h"
#include "indextables.h"
#include "trashstack.h"

int get_m(int pk_id){
    IndexTableRow* per_row = categories_index_table_get(pk_id);
    if(per_row != NULL && !per_row->is_deleted) {
        Category *per_category_row = read_category(per_row->position);
        print_category(per_category_row);
    }else{
        printf("Invalid pk_id!!!\n");
    }
}

int get_s(int pk_id){
    IndexTableRow* per_row = goods_index_table_get(pk_id);
    if(per_row != NULL && !per_row->is_deleted) {
        Goods *per_category_row = read_goods(per_row->position);
        print_goods(per_category_row);
    }else{
        printf("Invalid pk_id!!!\n");
    }
}

int insert_m(){
    Category* record = scan_category();
    Stack* trash_stack = get_category_trash_stack();
    int pos;
    if(trash_is_empty(trash_stack)){
        pos = get_categories_row_number();
        write_category(record, -1);
    }else{
        int pk_id = trash_pop(trash_stack);
        pos = categories_index_table_get(pk_id)->position;
        write_category(record, pos);
        categories_index_table_remove(pk_id);
    }
    IndexTableRow *row = (IndexTableRow*)malloc(sizeof(IndexTableRow));
    row->position = pos;
    row->is_deleted = false;
    categories_index_table_insert(record->pk_id, row);
    free(record);
}

int insert_s(){
    Goods* record = scan_goods();
    Stack* trash_stack = get_goods_trash_stack();

    IndexTableRow* per_row = categories_index_table_get(record->fk_category_id);
    Category* per_category_row = read_category(per_row->position);
    record->next_id = per_category_row->first_slave_id;
    per_category_row->first_slave_id = record->pk_id;
    write_category(per_category_row, per_row->position);

    int pos;
    if(trash_is_empty(trash_stack)){
        pos = get_goods_row_number();
        write_goods(record, -1);
    }else{
        int pk_id = trash_pop(trash_stack);
        pos = goods_index_table_get(pk_id)->position;
        write_goods(record, pos);
        goods_index_table_remove(pk_id);
    }
    IndexTableRow *row = (IndexTableRow*)malloc(sizeof(IndexTableRow));
    row->position = pos;
    row->is_deleted = false;
    goods_index_table_insert(record->pk_id, row);
    free(per_category_row);
    free(record);
}

void ut_m(){
    Category record;
    FILE* file = fopen(CATEGORIES_FILE, "rb");
    while(!feof(file)){
        if(fread(&record, 1, sizeof(record), file) > 0){
            print_whole_category(&record);
        }
    }
    fclose(file);
}

void ut_s(){
    Goods record;
    FILE* file = fopen(GOODS_FILE, "rb");
    while(!feof(file)){
        if(fread(&record, 1, sizeof(record), file) > 0){
            print_whole_goods(&record);
        }
    }
    fclose(file);
}
