# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0.0)
project (RandomNumberGods LANGUAGES C)

include(FindPkgConfig)
pkg_check_modules(TALLOC REQUIRED talloc)
pkg_check_modules(CHECK check)

add_compile_options(-Wall -Wextra -Werror)

include_directories(SYSTEM ${TALLOC_INCLUDEDIR} ${CHECK_INCLUDEDIR})

add_library(rngods constant.c dethread.c lcg.c randu.c rngod.c sequence.c xorshift.c)
add_executable(check constant_check.c dethread_check.c randu_check.c rngod_check.c sequence_check.c xorshift_check.c)
target_link_libraries(check rngods ${TALLOC_LDFLAGS} ${CHECK_LDFLAGS})
