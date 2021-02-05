#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include "indextables.h"
#include "configurations.h"

void print_goods(Goods *record){
    printf("PK_ID: %d NAME: %s PRICE: %d SALE_PRICE: %d DESC: %s "
           "PHOTO: %s FK_CATEGORY_ID: %d FK_SECTION_ID: %d COUNT: %d\n",
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
           "PHOTO: %s FK_CATEGORY_ID: %d FK_SECTION_ID: %d COUNT: %d NEXT_ID: %d\n",
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

//if pos == -1, write record to the end of file!
void write_goods(Goods* record, int pos){
    if(pos == -1){
        FILE* file = fopen(GOODS_FILE, "ab");
        fwrite(record, 1, sizeof(Goods), file);
        fclose(file);
    }else{
        FILE* file = fopen(GOODS_FILE, "rb+");
        fseek(file, sizeof(Goods)*pos, SEEK_SET);
        fwrite(record, 1, sizeof(Goods), file);
        fclose(file);
    }
}


//if pos == -1, write record to the end of file!
void write_category(Category* record, int pos){
    if(pos == -1){
        FILE* file = fopen(CATEGORIES_FILE, "ab");
        fwrite(record, 1, sizeof(Category), file);
        fclose(file);
    }else{
        FILE* file = fopen(CATEGORIES_FILE, "rb+");
        fseek(file, sizeof(Category)*pos, SEEK_SET);
        fwrite(record, 1, sizeof(Category), file);
        fclose(file);
    }
}

Goods* read_goods(int pos){
    FILE* file = fopen(GOODS_FILE, "rb");
    fseek(file, sizeof(Goods)*pos, SEEK_SET);
    Goods* record = (Goods*)malloc(sizeof(Goods));
    fread(record, 1, sizeof(Goods), file);
    fclose(file);
    return record;
}

Category* read_category(int pos){
    FILE* file = fopen(CATEGORIES_FILE, "rb");
    fseek(file, sizeof(Category)*pos, SEEK_SET);
    Category* record = (Category*)malloc(sizeof(Category));
    fread(record, 1, sizeof(Category), file);
    fclose(file);
    return record;
}

Goods* scan_goods(){
    Goods* record = (Goods*)malloc(sizeof(Goods));

    printf("PK_ID: ");
    scanf("%d", &record->pk_id);

    printf("NAME: ");
    getchar();
    scanf("%[^\n]", record->name);

    printf("PRICE: ");
    scanf("%d", &record->price);

    printf("SALE_PRICE: ");
    scanf("%d", &record->sale_price);

    printf("DESC: ");
    getchar();
    scanf("%[^\n]", record->description);

    printf("PHOTO: ");
    getchar();
    scanf("%[^\n]", record->photo);

    printf("FK_CATEGORY_ID: ");
    scanf("%d", &record->fk_category_id);

    printf("FK_SECTION_ID: ");
    scanf("%d", &record->fk_section_id);

    printf("COUNT: ");
    scanf("%d", &record->count);

    return record;
}

Category* scan_category(){
    Category* record = (Category*)malloc(sizeof(Category));

    printf("PK_ID: ");
    scanf("%d", &record->pk_id);

    printf("NAME: ");
    getchar();
    scanf("%[^\n]", record->name);

    printf("ABOUT: ");
    getchar();
    scanf("%[^\n]", record->about);

    record->first_slave_id = -1;

    return record;
}