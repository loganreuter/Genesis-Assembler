file(GLOB source *.c)
file(GLOB headers *.h)

add_library(ErrorsLib SHARED ${source} ${headers})

target_compile_features(ErrorsLib PUBLIC c_std_99)