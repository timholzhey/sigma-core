//
// Created by tholz on 27.08.2022.
//


#include "testlib.h"
#include "lang_def.h"
#include <string.h>
#include "sigma.h"

TEST_DEF(test_func_const, mult_simple) {
	sigma_init();

	const char *func = "2*2*x";
	const char *expect_result = "4x";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, mult_long) {
	sigma_init();

	const char *func = "1*2*3*4*x";
	const char *expect_result = "120x";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_func_const) {
	TEST_REG(test_func_const, mult_simple);
	TEST_REG(test_func_const, mult_long);
}
