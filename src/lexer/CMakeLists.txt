file(GLOB SOURCE *.c)
file(GLOB HEADERS *.h)

add_library(LexerLib ${SOURCE} ${HEADERS})

target_include_directories(LexerLib PUBLIC ../../include)
target_include_directories(LexerLib PUBLIC ../errors)

target_compile_features(LexerLib PUBLIC c_std_99)