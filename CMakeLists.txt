cmake_minimum_required(VERSION 3.16)
project(space_explorer C)

set(CMAKE_C_STANDARD 11)

# main game
add_executable(space_explorer
        Space_eXplorer_game.c
        function_definition.c
        "test/unit test/iso_unit_test_1.c"
        "test/unit test/iso_unit_test_2.c"
)
