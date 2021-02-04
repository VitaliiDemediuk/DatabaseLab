#include <stdio.h>
#include <stdlib.h>
#include "dbfunctions.h"
#include "tables.h"
#include "configurations.h"

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
