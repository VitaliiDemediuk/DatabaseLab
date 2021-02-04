#ifndef DATABASELAB_INDEXTABLES_H
#define DATABASELAB_INDEXTABLES_H
#include <stdbool.h>

typedef struct _IndexTableRow {
    int position;
    bool is_deleted;
} IndexTableRow;

void categories_index_table_init();
void goods_index_table_init();

void categories_index_table_insert(int pk_id, IndexTableRow* row);
void goods_index_table_insert(int pk_id, IndexTableRow* row);

IndexTableRow* categories_index_table_get(int pk_id);

IndexTableRow* goods_index_table_get(int pk_id);

void categories_index_table_save();
void goods_index_table_save();

void categories_index_table_free();
void goods_index_table_free();

#endif //DATABASELAB_INDEXTABLES_H
