find_package(argparse REQUIRED)

add_executable(cptpp cptpp.cpp)
target_link_libraries(cptpp PRIVATE argparse::argparse)
target_compile_features(cptpp PRIVATE cxx_std_20)
