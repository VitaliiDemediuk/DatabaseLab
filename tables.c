#include "tables.h"
#include <stdio.h>

void print_goods(Goods *record){
    printf("PK_ID: %d NAME: %s PRICE: %d SALE_PRICE: %d DESC: %s "
           "PHOTO: %s FK_CATEGORY_ID: %d FK_SECTION_ID: %d COUNT %d\n",
           record->pk_id,
           record->name,
           record->price,
           record->sale_price,
           record->description,
           record->photo,
           record->fk_category_id,
           record->fk_section_id,
           record->count);
}

void print_whole_goods(Goods *record){
    printf("PK_ID: %d NAME: %s PRICE: %d SALE_PRICE: %d DESC: %s "
           "PHOTO: %s FK_CATEGORY_ID: %d FK_SECTION_ID: %d COUNT %d NEXT_ID: %d\n",
           record->pk_id,
           record->name,
           record->price,
           record->sale_price,
           record->description,
           record->photo,
           record->fk_category_id,
           record->fk_section_id,
           record->count,
           record->next_id);
}

void print_category(Category *record){
    printf("PK_ID: %d NAME: %s ABOUT: %s\n",
           record->pk_id,
           record->name,
           record->about);
}

void print_whole_category(Category *record){
    printf("PK_ID: %d NAME: %s ABOUT: %s FIRST_SLAVE_ID: %d\n",
           record->pk_id,
           record->name,
           record->about,
           record->first_slave_id);
}