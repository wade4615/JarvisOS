# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.17.1)

# Set the project name
project (JARVISOS)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_SKIP_PREPROCESSED_SOURCE_RULES TRUE)
set(CMAKE_SKIP_ASSEMBLY_SOURCE_RULES TRUE)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

set(ARCH i386)
string(TOLOWER ${ARCH} ARCH)

enable_language(ASM_NASM)
enable_language(C)
enable_language(RC)

set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS "asm")

include(config/config.cmake)
include(config/compilerflags.cmake)

add_definitions(-D__JARVISOS__)

# Double escape, since CMake unescapes before putting it on the command-line, where it's unescaped again by GCC/CL.
add_definitions(-DJARVISOS_SOURCE_DIR="${JARVISOS_SOURCE_DIR}")
add_definitions(-DJARVISOS_BINARY_DIR="${JARVISOS_BINARY_DIR}")

# There doesn't seem to be a standard for __FILE__ being relative or absolute, so detect it at runtime.
file(RELATIVE_PATH _PATH_PREFIX ${JARVISOS_BINARY_DIR} ${JARVISOS_SOURCE_DIR})
add_compile_flags(-D__RELFILE__="&__FILE__[__FILE__[0] == '.' ? sizeof \\\"${_PATH_PREFIX}\\\" - 1 : sizeof JARVISOS_SOURCE_DIR]")

add_subdirectory(hosttools/tools)
add_subdirectory(source/ntoskrnl)

