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
    char command[50];
    while(true) {
        scanf("%s", command);
        if (strcmp(command, "get-m") == 0) {
            get_m();
        } else if (strcmp(command, "get-s") == 0) {
            get_s();
        } else if (strcmp(command, "get-s") == 0) {
            get_s();
        } else if (strcmp(command, "del-m") == 0) {
            del_m();
        } else if (strcmp(command, "del-s") == 0) {
            del_s();
        } else if (strcmp(command, "update-m") == 0) {
            update_m();
        } else if (strcmp(command, "update-s") == 0) {
            update_s();
        } else if (strcmp(command, "insert-m") == 0) {
            insert_m();
        } else if (strcmp(command, "insert-s") == 0) {
            insert_s();
        } else if (strcmp(command, "calc-m") == 0) {
            calc_m();
        } else if (strcmp(command, "calc-s") == 0) {
            calc_s();
        } else if (strcmp(command, "ut-m") == 0) {
            ut_m();
        } else if (strcmp(command, "ut-s") == 0) {
            ut_s();
        } else if (strcmp(command, "end") == 0) {
            end_program();
            break;
        } else {
            printf("Invalid command: %s\n", command);
        }
    }
    return 0;
}
