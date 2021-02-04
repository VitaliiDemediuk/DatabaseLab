#include <stdio.h>
#include "dbfunctions.h"
#include "configurations.h"
#include <stdbool.h>
#include "indextables.h"
#include "trashstack.h"
#include <glib.h>

int main() {
    trash_push(11212);
    printf("%d\n", trash_peek());

    return 0;
}
