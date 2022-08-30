add_executable(
        run_tests
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

        ${CMAKE_CURRENT_SOURCE_DIR}/lib/testlib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_lexer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_parser.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_preprocessor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_stringify.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_pattern.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_func_const.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_func_derive.c
)

target_link_libraries(run_tests m)
