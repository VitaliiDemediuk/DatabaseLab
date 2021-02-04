#include <stdio.h>
//#include "dbfunctions.h"
//#include "configurations.h"
#include <stdbool.h>
#include "indextables.h"
#include <glib.h>

int main() {
    categories_index_table_init();
    goods_index_table_init();
    IndexTableRow* row1 = categories_index_table_get(1);
    printf("%d %d\n", row1->position, row1->is_deleted);
    categories_index_table_save();
    goods_index_table_save();
    return 0;
}
