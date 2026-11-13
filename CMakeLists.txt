cmake_minimum_required(VERSION 3.1...3.28)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)
set(CMAKE_PROJECT_DESCRIPTION "ADHD Timer application")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/saphieron/adhd_timer")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXECUTABLE_ENABLE_EXPORTS TRUE)

project(
  adhd_timer
  VERSION 1.0.0
)

################################
# Add GLib resource generation
################################
find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(GRESOURCE_XML ${PROJECT_SOURCE_DIR}/adhd_timer.gresource.xml)
set(GRESOURCE_C   adhd_timer.gresource.c)
set(GRESOURCE_PATH ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})

add_custom_command(
    OUTPUT ${GRESOURCE_C}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        ${GRESOURCE_XML}
        --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
        --generate-source
    VERBATIM
    MAIN_DEPENDENCY ${GRESOURCE_XML}
)

add_custom_target(gre_resource_generation
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

add_executable(adhd_timer
    ${SOURCES}
    ${GRESOURCE_PATH}
)

set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
    PROPERTIES GENERATED TRUE
)
add_dependencies(${PROJECT_NAME} gre_resource_generation)

set(WARNING_LEVELS_GCC
    -Werror
)
set(WARNING_LEVELS_GCC_DEBUG
    #-Wfloat-equal
    #-Wextra
    -Wall
    -Wdeprecated-declarations
    #-Wundef
    #-Wshadow
    #-Wpointer-arith
    #-Wcast-align
    #-Wstrict-overflow=5
    #-Wwrite-strings
    #-Waggregate-return
    #-Wcast-qual
    #-Wswitch-default
    #-Wswitch-enum
    #-Wconversion
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose build type: None Debug Release"
    FORCE)
endif()

find_package(PkgConfig REQUIRED)

pkg_check_modules(
  Dependencies REQUIRED
  IMPORTED_TARGET
  gtk4>=4.14.0
)
message("GTK4 include dir: ${GTK4_INCLUDE_DIRS}")
message("GTK4 libraries: ${GTK4_LIBRARY_DIRS}")
message("GTK4 other Cflags: ${GTK4_CFLAGS_OTHER}")


message(STATUS "Flags: ${CMAKE_C_FLAGS}")

target_include_directories(${PROJECT_NAME} PUBLIC ${GTK4_LIBRARIES})
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${GTK4_LIBRARIES}
    PkgConfig::Dependencies
)

target_compile_options(${PROJECT_NAME} PRIVATE ${WARNING_LEVELS_GCC} $<$<CONFIG:DEBUG>:${WARNING_LEVELS_GCC_DEBUG}>)
