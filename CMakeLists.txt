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

# Adds support for working with Gtk4 <signals> and Cambalache
# https://cmake.org/cmake/help/latest/variable/CMAKE_EXECUTABLE_ENABLE_EXPORTS.html
set(CMAKE_EXECUTABLE_ENABLE_EXPORTS TRUE)

project(
  adhd_timer
  VERSION 1.0.0
)

# Adding something we can run - Output name matches target name
add_executable(adhd_timer ${SOURCES})

#===============================================================================
# Setting compilation flags for various compilers and build types:
#===============================================================================

# some test warning levels for GCC
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

# Print system, compiler CMake ID, version and path:
#message(STATUS "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION} ${CMAKE_SYSTEM_PROCESSOR}")
#message(STATUS "Compiler: ${CMAKE_Fortran_COMPILER_ID} ${CMAKE_Fortran_COMPILER_VERSION} ${CMAKE_Fortran_COMPILER}")
#message(STATUS "Build type is: ${CMAKE_BUILD_TYPE}")

#===============================================================================
# Default build type is release
# Uncomment this to debug or use "cmake -D CMAKE_BUILD_TYPE=debug .."
#===============================================================================
# External projects go here i.e. a project that isn't using cmake build
#include(ExternalProject)
#ExternalProject_Add(PostgreSQL
#  GIT_REPOSITORY    https://github.com/postgres/postgres.git
#  GIT_TAG           REL_16_1
#  SOURCE_DIR        ${CMAKE_SOURCE_DIR}/vendors/database/
#  CONFIGURE_COMMAND ./configure 
#  CMAKE_ARGS        ""
#  INSTALL_COMMAND   "" 
#  BUILD_IN_SOURCE   1
#  BUILD_COMMAND $(MAKE) MAKELEVEL=0
#  LOG_CONFIGURE     1
#  LOG_BUILD         1
#  LOG_INSTALL       1
#)

# set(CMAKE_BUILD_TYPE debug)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING
    "Choose build type: None Debug Release"
    FORCE)
endif()

# Find PkgConfig.
find_package(PkgConfig REQUIRED)

# pkg_check_modules(GTK4 REQUIRED gtk4>=4.16.5)
pkg_check_modules(
  Dependencies REQUIRED
  IMPORTED_TARGET 
  gtk4>=4.16.5
)
message("GTK4 include dir: ${GTK4_INCLUDE_DIRS}")
message("GTK4 libraries: ${GTK4_LIBRARY_DIRS}")
message("GTK4 other Cflags: ${GTK4_CFLAGS_OTHER}")


# pkg_check_modules(GMODULE-EXPORT-2.0 REQUIRED gmodule-export-2.0>=2.82.2)
# message("GMODULE-EXPORT-2.0 include dir: ${GMODULE-EXPORT-2.0_INCLUDE_DIRS}")
# message("GMODULE-EXPORT-2.0 libraries: ${GMODULE-EXPORT-2.0_LIBRARY_DIRS}")
# message("GMODULE-EXPORT-2.0 other Cflags: ${GMODULE-EXPORT-2.0_CFLAGS_OTHER}")

message(STATUS "Flags: ${CMAKE_C_FLAGS}")


# # Setup CMake to use GTK+, tell the compiler where to look for headers
# # and to the linker where to look for libraries
# include_directories(${GTK4_INCLUDE_DIRS} ${ADW_INCLUDE_DIRS} ${GMODULE-EXPORT-2.0_INCLUDE_DIRS})
# link_directories(${GTK4_LIBRARY_DIRS} ${ADW_LIBRARY_DIRS} ${GMODULE-EXPORT-2.0_LIBRARY_DIRS})
# add_definitions(${GTK4_CFLAGS_OTHER} ${ADW_CFLAGS_OTHER} ${GMODULE-EXPORT-2.0_CFLAGS_OTHER})


# This is a "default" library, and will match the *** variable setting.
# Other common choices are STATIC, SHARED, and MODULE
# Including header files here helps IDEs but is not required.
# Output libname matches target name, with the usual extensions on your system
#add_library(MyLibExample simple_lib.cpp simple_lib.hpp)

# Link each target with other targets or add options, etc.
# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_include_directories(${PROJECT_NAME} PUBLIC ${GTK4_LIBRARIES})
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${GTK4_LIBRARIES}
    PkgConfig::Dependencies
)

# Target Compile Options
target_compile_options(${PROJECT_NAME} PRIVATE ${WARNING_LEVELS_GCC} $<$<CONFIG:DEBUG>:${WARNING_LEVELS_GCC_DEBUG}>)

#===============================================================================
# Package generation:
#===============================================================================
#set(CPACK_PACKAGE_CHECKSUM SHA256)
#set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
#set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
#set(CPACK_GENERATOR "TGZ")
#set(CPACK_SOURCE_GENERATOR "TGZ")
#include(CPack)

#===============================================================================
# Add subdirectories to build:
#===============================================================================
# add_subdirectory(src)

