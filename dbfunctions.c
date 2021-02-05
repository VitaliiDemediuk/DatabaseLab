#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbfunctions.h"
#include "tables.h"
#include "configurations.h"
#include "indextables.h"
#include "trashstack.h"

void get_m(){
    int pk_id;
    scanf("%d", &pk_id);
    IndexTableRow* per_row = categories_index_table_get(pk_id);
    if(per_row != NULL && !per_row->is_deleted) {
        Category *per_category_row = read_category(per_row->position);
        print_category(per_category_row);
    }else{
        printf("Invalid pk_id!!!\n");
    }
}

void get_s(){
    int pk_id;
    scanf("%d", &pk_id);
    IndexTableRow* per_row = goods_index_table_get(pk_id);
    if(per_row != NULL && !per_row->is_deleted) {
        Goods *per_category_row = read_goods(per_row->position);
        print_goods(per_category_row);
    }else{
        printf("Invalid pk_id!!!\n");
    }
}

void get_all_m(){
    Category record;
    FILE* file = fopen(CATEGORIES_FILE, "rb");
    while(!feof(file)){
        if(fread(&record, 1, sizeof(record), file) > 0 &&
            !categories_index_table_get(record.pk_id)->is_deleted){
            print_category(&record);
        }
    }
    fclose(file);
}

void get_all_s(){
    Goods record;
    FILE* file = fopen(GOODS_FILE, "rb");
    while(!feof(file)){
        if(fread(&record, 1, sizeof(record), file) > 0 &&
            !goods_index_table_get(record.pk_id)->is_deleted){
            print_goods(&record);
        }
    }
    fclose(file);

}

void del_m(){
    int pk_id;
    scanf("%d", &pk_id);
    IndexTableRow* categories_row = categories_index_table_get(pk_id);
    if(categories_row != NULL && !categories_row->is_deleted) {
        Category *del_category = read_category(categories_row->position);
        categories_row->is_deleted = true;
        trash_push(get_category_trash_stack(), pk_id);

        int slave_id = del_category->first_slave_id;
        while (slave_id != -1) {
            IndexTableRow *goods_row = goods_index_table_get(slave_id);
            Goods *del_goods = read_goods(goods_row->position);
            goods_row->is_deleted = true;
            trash_push(get_goods_trash_stack(), del_goods->pk_id);
            slave_id = del_goods->next_id;
            free(del_goods);
        }
        free(del_category);
    }else{
        printf("Invalid pk_id\n");
        return;
    }
}

void del_s(){
    int pk_id;
    scanf("%d", &pk_id);
    IndexTableRow* goods_row = goods_index_table_get(pk_id);
    if(goods_row != NULL && !goods_row->is_deleted) {
        Goods *del_goods = read_goods(goods_row->position);
        goods_row->is_deleted = true;
        trash_push(get_category_trash_stack(), pk_id);

        Category *per_category = read_category(categories_index_table_get(del_goods->fk_category_id)->position);
        if(per_category->first_slave_id == del_goods->pk_id){
            per_category->first_slave_id = del_goods->next_id;
            write_category(per_category, categories_index_table_get(per_category->pk_id)->position);
        }else{
            int pk_id_slave = per_category->first_slave_id;
            Goods *slave;
            int slave_next_id;
            do {
                slave = read_goods(goods_index_table_get(pk_id_slave)->position);
                slave_next_id = slave->next_id;
                if(slave_next_id != del_goods->pk_id){
                    free(slave);
                }
            }while(slave_next_id != del_goods->pk_id);
            slave->next_id = del_goods->next_id;
            write_goods(slave, goods_index_table_get(slave->pk_id)->position);
        }
        free(per_category);
        free(del_goods);
    }else{
        printf("Invalid pk_id\n");
        return;
    }
}

void update_m(){
    int pw_id;
    char field[50];
    scanf("%d %s", &pw_id, field);
    IndexTableRow* index_table_row = categories_index_table_get(pw_id);
    if(index_table_row != NULL && !index_table_row->is_deleted) {
        Category *category_to_update = read_category(index_table_row->position);
        if (strcmp(field, "pw_id") == 0) {
            scanf("%d", &category_to_update->pk_id);
        } else if (strcmp(field, "name") == 0) {
            getchar();
            scanf("%[^\n]", category_to_update->name);
        } else if (strcmp(field, "about") == 0) {
            getchar();
            scanf("%[^\n]", category_to_update->about);
        } else {
            printf("Invalid field\n");
            return;
        }
        write_category(category_to_update, index_table_row->position);
        free(category_to_update);
    }else{
        printf("Invalid pk_id\n");
        return;
    }
}

void update_s(){
    int pw_id;
    char field[50];
    scanf("%d %s", &pw_id, field);
    IndexTableRow* index_table_row = goods_index_table_get(pw_id);
    if(index_table_row != NULL && !index_table_row->is_deleted) {
        Goods *goods_to_update = read_goods(index_table_row->position);
        if (strcmp(field, "pw_id") == 0) {
            scanf("%d", &goods_to_update->pk_id);
        } else if (strcmp(field, "name") == 0) {
            getchar();
            scanf("%[^\n]", goods_to_update->name);
        } else if (strcmp(field, "price") == 0) {
            scanf("%d", &goods_to_update->price);
        } else if (strcmp(field, "sale_price") == 0) {
            scanf("%d", &goods_to_update->sale_price);
        } else if (strcmp(field, "sale_price") == 0) {
            scanf("%d", &goods_to_update->sale_price);
        } else if (strcmp(field, "description") == 0) {
            getchar();
            scanf("%[^\n]", goods_to_update->description);
        } else if (strcmp(field, "description") == 0) {
            getchar();
            scanf("%[^\n]", goods_to_update->description);
        } else if (strcmp(field, "count") == 0) {
            scanf("%d", &goods_to_update->count);
        } else if (strcmp(field, "fk_category_id") == 0) {
            scanf("%d", &goods_to_update->fk_category_id);
        } else if (strcmp(field, "fk_section_id") == 0) {
            scanf("%d", &goods_to_update->fk_section_id);
        } else {
            printf("Invalid field\n");
            return;
        }
        write_goods(goods_to_update, index_table_row->position);
        free(goods_to_update);
    }else{
        printf("Invalid pk_id\n");
        return;
    }
}

void insert_m(){
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

void insert_s(){
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

void calc_m(){
    printf("%d\n", get_categories_row_number() - trash_size(get_category_trash_stack()));
}

void calc_s(){
    printf("%d\n", get_goods_row_number() - trash_size(get_goods_trash_stack()));
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
