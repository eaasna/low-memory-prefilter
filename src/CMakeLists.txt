cmake_minimum_required (VERSION 3.8)

# Hashmap build.
add_library ("${PROJECT_NAME}_build_lib" STATIC hashmap_build.cpp)
target_link_libraries ("${PROJECT_NAME}_build_lib" PUBLIC seqan3::seqan3)

# Hashmap search.
add_library ("${PROJECT_NAME}_search_lib" STATIC hashmap_search.cpp)
target_link_libraries ("${PROJECT_NAME}_search_lib" PUBLIC seqan3::seqan3)

# Arguments parsing.
add_library ("${PROJECT_NAME}_arg_lib" STATIC argument_parsing.cpp)
target_link_libraries ("${PROJECT_NAME}_arg_lib" PUBLIC seqan3::seqan3)

# Hashmap executable.
add_executable ("${PROJECT_NAME}" main.cpp)
target_link_libraries ("${PROJECT_NAME}" PRIVATE "${PROJECT_NAME}_lib")

target_include_directories ("${PROJECT_NAME}_lib" PUBLIC ../include)
