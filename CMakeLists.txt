cmake_minimum_required(VERSION 3.23)
project(sigma_core)

set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/func
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl/const
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl/derive
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl/simpl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl/string
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/rules
        ${CMAKE_CURRENT_SOURCE_DIR}/inf
        ${CMAKE_CURRENT_SOURCE_DIR}/lang
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/eval
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/parser
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/util
)

add_executable(sigma_core main.c inf/sigma.c inf/sigma.h lang/lexer/lexer.c lang/lexer/lexer.h lang/parser/parser.c lang/parser/parser.h lang/lang_def.h lang/lang_def.c)

include(${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)