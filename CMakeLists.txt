cmake_minimum_required(VERSION 3.16)
project(sigma_core)

set(CMAKE_C_STANDARD 99)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/

        ${CMAKE_CURRENT_SOURCE_DIR}/func
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/transform
        ${CMAKE_CURRENT_SOURCE_DIR}/func/derive
        ${CMAKE_CURRENT_SOURCE_DIR}/func/derive/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/derive/transform
        ${CMAKE_CURRENT_SOURCE_DIR}/func/integrate
        ${CMAKE_CURRENT_SOURCE_DIR}/func/integrate/impl
        ${CMAKE_CURRENT_SOURCE_DIR}/func/integrate/transform
        ${CMAKE_CURRENT_SOURCE_DIR}/plot/integrate
        ${CMAKE_CURRENT_SOURCE_DIR}/plot/integrate/impl

        ${CMAKE_CURRENT_SOURCE_DIR}/core

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

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/sigma
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/sigma/compile

        ${CMAKE_CURRENT_SOURCE_DIR}/lib

        ${CMAKE_CURRENT_SOURCE_DIR}/util
)

add_executable(
        sigma_core
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c

        ${CMAKE_CURRENT_SOURCE_DIR}/core/math_core.c

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/lexer/math_lexer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/parser/math_parser.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/math_lang_def.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/math_evaluator.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/const/math_eval_const.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/eval/transform/math_eval_transform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/preprocess/math_preprocess.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/postprocess/math_postprocess.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/math/stringify/math_stringify.c

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/pattern.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/compile/pattern_compile.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/match/pattern_match.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/replace/pattern_replace.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/capture/pattern_capture.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/pattern/generate/pattern_generate.c

        ${CMAKE_CURRENT_SOURCE_DIR}/lang/sigma/sigma_lang_def.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lang/sigma/compile/sigma_compile.c

        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/impl/func_const.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/const/transform/const_transform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/derive/impl/func_derive.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/derive/transform/derive_transform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/integrate/impl/func_integrate.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/integrate/transform/integrate_transform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/func/plot/impl/func_plot.c

        ${CMAKE_CURRENT_SOURCE_DIR}/util/io.c
)

include(${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)

target_compile_definitions(sigma_core PRIVATE DEBUG_GLOBAL=1)

set(CMAKE_VERBOSE_MAKEFILE on)

target_link_libraries(sigma_core m)

# Rename executable to sigma
set_target_properties(sigma_core PROPERTIES OUTPUT_NAME sigma)

# Copy executable to root/build directory
add_custom_command(TARGET sigma_core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:sigma_core>
        ${CMAKE_CURRENT_SOURCE_DIR}/build/sigma)

# After build, move the executable to /usr/local/bin
add_custom_command(TARGET sigma_core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sigma_core> ~/bin/sigma
        COMMENT "Moving executable to /usr/local/bin/sigma")
