#ifndef DATABASELAB_DBFUNCTIONS_H
#define DATABASELAB_DBFUNCTIONS_H

#include "tables.h"

int get_m(int pk_id);
int get_s(int pk_id);

int del_m(int pk_id);
int del_s(int pk_id);

int update_m();
int update_s();

int insert_m();
int insert_s();

int calc_m(int id);
int cals_s(int id);

void ut_m();
void ut_s();

#endif //DATABASELAB_DBFUNCTIONS_H
