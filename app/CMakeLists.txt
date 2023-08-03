add_executable(asm assembler.c)
target_compile_features(asm PRIVATE c_std_11)

target_link_libraries(asm PRIVATE AssemblerLib)
