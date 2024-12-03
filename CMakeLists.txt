cmake_minimum_required (VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(HW03_Allocator VERSION ${PROJECT_VERSION})

#configure_file(version.h.in version.h)

add_executable (HW03_Allocator "main.cpp" "main.h" "hw03_allocator.h" "hw03_vector.h")

set_target_properties(HW03_Allocator PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(HW03_Allocator PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    target_compile_options(HW03_Allocator PRIVATE
        /W4
    )
else ()
    target_compile_options(HW03_Allocator PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

install(TARGETS HW03_Allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)