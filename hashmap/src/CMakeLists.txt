cmake_minimum_required (VERSION 3.8)

# Shared interface
add_library ("${PROJECT_NAME}_interface" INTERFACE)
target_link_libraries ("${PROJECT_NAME}_interface" INTERFACE seqan3::seqan3)
target_include_directories ("${PROJECT_NAME}_interface" INTERFACE ../include)

# Hashmap build.
add_library ("${PROJECT_NAME}_build_lib" STATIC hashmap_build.cpp)
target_link_libraries ("${PROJECT_NAME}_build_lib" PUBLIC "${PROJECT_NAME}_interface")

# Hashmap search.
add_library ("${PROJECT_NAME}_search_lib" STATIC hashmap_search.cpp)
target_link_libraries ("${PROJECT_NAME}_search_lib" PUBLIC "${PROJECT_NAME}_interface")

# Arguments parsing.
add_library ("${PROJECT_NAME}_arg_lib" STATIC argument_parsing.cpp)
target_link_libraries ("${PROJECT_NAME}_arg_lib" PUBLIC "${PROJECT_NAME}_interface")

# Whole library
add_library ("${PROJECT_NAME}_lib" INTERFACE)
target_link_libraries ("${PROJECT_NAME}_lib" INTERFACE "${PROJECT_NAME}_arg_lib")
target_link_libraries ("${PROJECT_NAME}_lib" INTERFACE "${PROJECT_NAME}_build_lib")
target_link_libraries ("${PROJECT_NAME}_lib" INTERFACE "${PROJECT_NAME}_search_lib")

# Hashmap executable.
add_executable ("${PROJECT_NAME}" main.cpp)
target_link_libraries ("${PROJECT_NAME}" PRIVATE "${PROJECT_NAME}_lib")
