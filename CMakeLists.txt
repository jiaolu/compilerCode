cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
project(compiler LANGUAGES CXX)

add_executable(compiler
    compiler.cpp
    lex.cpp
    parser.cpp
    ast.cpp
    codegen.cpp
    assemNode.cpp
)

target_compile_features(compiler PRIVATE cxx_std_23)
