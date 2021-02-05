#include "indextables.h"
#include <glib.h>
#include <stdio.h>
#include "configurations.h"
#include "trashstack.h"

static GHashTable* categories_index_table;
static GHashTable* goods_index_table;

//Auxiliary functions ---------------------------
void index_table_insert(GHashTable *table, int pk_id, IndexTableRow* row){
    g_hash_table_insert(table, GINT_TO_POINTER(pk_id), (gpointer)(row));
}

void read_index_table(char* file_name, GHashTable* hash_table, Stack* trash_stack){
    FILE* file = fopen(file_name, "rb");
    int pk_id;
    while(!feof(file)){
        IndexTableRow *row = (IndexTableRow*)malloc(sizeof(IndexTableRow));
        if(fread(&pk_id, 1, sizeof(pk_id), file) > 0 &&
           fread(row, 1, sizeof(*row), file) > 0){
            if(row->is_deleted) {
                trash_push(trash_stack, row->position);
            }
            index_table_insert(hash_table, pk_id, row);
        }
    }
    fclose(file);
}

void write_row(gpointer key, gpointer value, gpointer user_data){
    FILE* file = (FILE*)user_data;
    int key_cast = GPOINTER_TO_INT(key);
    IndexTableRow *value_cast = (IndexTableRow*)value;
    fwrite(&key_cast, 1, sizeof(key_cast), file);
    fwrite(value_cast, 1, sizeof(*value_cast), file);
}

void write_index_table(char* file_name, GHashTable* hash_table){
    FILE* file = fopen(file_name, "wb");
    g_hash_table_foreach(hash_table, write_row, (gpointer)file);
    fclose(file);
}
//-----------------------------------------------

void categories_index_table_init() {
    categories_index_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    read_index_table(CATEGORIES_INDEX_TABLE_FILE, categories_index_table, get_category_trash_stack());
}

void goods_index_table_init() {
    goods_index_table = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    read_index_table(GOODS_INDEX_TABLE_FILE, goods_index_table, get_goods_trash_stack());
}

int get_categories_row_number(){
    return g_hash_table_size(categories_index_table);
}

int get_goods_row_number(){
    return g_hash_table_size(goods_index_table);
}

void categories_index_table_insert(int pk_id, IndexTableRow* row){
    index_table_insert(categories_index_table, pk_id, row);
}

void goods_index_table_insert(int pk_id, IndexTableRow* row){
    index_table_insert(goods_index_table, pk_id, row);
}

void categories_index_table_remove(int pk_id){
    g_hash_table_remove(categories_index_table, GINT_TO_POINTER(pk_id));
}

void goods_index_table_remove(int pk_id){
    g_hash_table_remove(goods_index_table, GINT_TO_POINTER(pk_id));
}

IndexTableRow* categories_index_table_get(int pk_id){
    return g_hash_table_lookup(categories_index_table, GINT_TO_POINTER(pk_id));
}

IndexTableRow* goods_index_table_get(int pk_id){
    return g_hash_table_lookup(goods_index_table, GINT_TO_POINTER(pk_id));
}

void categories_index_table_save() {
    write_index_table(CATEGORIES_INDEX_TABLE_FILE, categories_index_table);
}

void goods_index_table_save() {
    write_index_table(GOODS_INDEX_TABLE_FILE, goods_index_table);
}

void categories_index_table_free() {
    g_hash_table_destroy(categories_index_table);
}

void goods_index_table_free() {
    g_hash_table_destroy(goods_index_table);
}