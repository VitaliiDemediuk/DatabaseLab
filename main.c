#include <stdio.h>
#include "dbfunctions.h"
#include "configurations.h"
#include <stdbool.h>
#include "indextables.h"
#include "trashstack.h"
#include "dbfunctions.h"
#include <glib.h>
#include "init.h"

int main() {
    start_program();
    get_m(1);
    get_m(3);
    get_s(1);
    get_s(3);
    get_s(5);
//    insert_m();
//    insert_s();
//    ut_m();
//    ut_s();
    end_program();
    return 0;
}
