cmake_minimum_required(VERSION 3.16)
project(sigma_core)

set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/func
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/transform
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/transform

        ${CMAKE_CURRENT_SOURCE_DIR}/inf

        ${CMAKE_CURRENT_SOURCE_DIR}/lang
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/const
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/transform
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/parser
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/preprocess
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/postprocess
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/stringify

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/compile
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/match
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/capture
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/replace
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/generate

        ${CMAKE_CURRENT_SOURCE_DIR}/lib

        ${CMAKE_CURRENT_SOURCE_DIR}/util
)

add_executable(
        sigma_core
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c

        ${CMAKE_CURRENT_SOURCE_DIR}/inf/sigma.c

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/lexer/lexer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/parser/parser.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/lang_def.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/evaluator.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/const/eval_const.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/transform/eval_transform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/preprocess/preprocess.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/postprocess/postprocess.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/stringify/stringify.c

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/pattern.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/compile/pattern_compile.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/match/pattern_match.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/replace/pattern_replace.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/capture/pattern_capture.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/generate/pattern_generate.c

        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/impl/func_derive.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/deriv/transform/derive_transform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/impl/func_const.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/transform/const_transform.c

        ${CMAKE_CURRENT_SOURCE_DIR}/util/io.c
)

include(${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)

target_link_libraries(sigma_core m)
