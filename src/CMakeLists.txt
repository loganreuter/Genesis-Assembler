file(GLOB source *.c)
file(GLOB header *.h)

add_subdirectory(lexer)

add_library(AssemblerLib ${source} ${header})

target_include_directories(AssemblerLib PUBLIC ../include)
target_link_libraries(AssemblerLib PUBLIC LexerLib)

target_compile_features(AssemblerLib PUBLIC c_std_99)
