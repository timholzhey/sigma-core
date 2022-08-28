//
// Created by tholz on 28.08.2022.
//

#include "testlib.h"
#include "lang_def.h"
#include <string.h>
#include "sigma.h"

TEST_DEF(test_func_derive, exponent_simple) {
	sigma_init();

	const char *func = "x^2";
	const char *expect_result = "2x";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, exponent_simple2) {
	sigma_init();

	const char *func = "2*x^3";
	const char *expect_result = "6*x^2"; // TODO: apply reverse precedence rules to simplify

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, sin_simple) {
	sigma_init();

	const char *func = "sin(x)";
	const char *expect_result = "cos(x)";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, constant) {
	sigma_init();

	const char *func = "x+2";
	const char *expect_result = "1";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_func_derive) {
	TEST_REG(test_func_derive, exponent_simple);
	TEST_REG(test_func_derive, exponent_simple2);
	TEST_REG(test_func_derive, sin_simple);
	TEST_REG(test_func_derive, constant);
}
