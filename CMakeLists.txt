cmake_minimum_required(VERSION 3.17)
project(DatabaseLab C)

set(CMAKE_C_STANDARD 11)

FIND_PACKAGE(PkgConfig REQUIRED)

PKG_CHECK_MODULES(GLIB REQUIRED glib-2.0)

INCLUDE_DIRECTORIES(
        src/include/
        ${GLIB_INCLUDE_DIRS}
)

LINK_DIRECTORIES(${GLIB_LIBRARY_DIRS})

add_executable(DatabaseLab main.c dbfunctions.c dbfunctions.h configurations.h tables.h tables.c indextables.c indextables.h trashstack.c trashstack.h init.c init.h)

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${GLIB_LIBRARIES})