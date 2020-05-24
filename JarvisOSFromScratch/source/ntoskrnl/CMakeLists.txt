project (ntoskrnl)

set(CMAKE_C_FLAGS " -m32 -std=gnu99 -ffreestanding -O2")
set(CMAKE_EXE_LINKER_FLAGS " -ffreestanding -O2 -nostdlib -lgcc -T ${CMAKE_CURRENT_SOURCE_DIR}/src/linker.ld")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

list(APPEND ASM_SOURCE_FILES src/boot.asm)
list(APPEND SOURCE_FILES src/kernel.c)

include_directories(include)

# Add an executable
add_executable(ntoskrnl  ${ASM_SOURCE_FILES} ${SOURCE_FILES})
