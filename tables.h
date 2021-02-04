#ifndef DATABASELAB_TABLES_H
#define DATABASELAB_TABLES_H

#include <stdio.h>

typedef struct _Goods {
    int pk_id;
    char name[50];
    int price;
    int sale_price;
    char description[200];
    char photo[100];
    int count;
    int fk_category_id;
    int fk_section_id;
    int next_id;
} Goods;

typedef struct _Category {
    int pk_id;
    char name[50];
    char about[200];
    int first_slave_id;
} Category;

void print_goods(Goods *record);
void print_whole_goods(Goods *record);

void print_category(Category *record);
void print_whole_category(Category *record);


Goods* read_goods(int pos);
Category* read_category(int pos);

Goods* scan_goods();
Category* scan_category();

#endif //DATABASELAB_TABLES_H
