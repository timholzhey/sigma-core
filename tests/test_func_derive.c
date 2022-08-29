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

TEST_DEF(test_func_derive, sin) {
	sigma_init();

	const char *func = "sin(x)";
	const char *expect_result = "cos(x)";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, cos) {
	sigma_init();

	const char *func = "cos(x)";
	const char *expect_result = "-sin(x)";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, sin_add_constants) {
	sigma_init();

	const char *func = "sin(x)+5+2";
	const char *expect_result = "cos(x)";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_plus_constant) {
	sigma_init();

	const char *func = "x+2";
	const char *expect_result = "1";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_mult_constant) {
	sigma_init();

	const char *func = "2*x";
	const char *expect_result = "2";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_plus_var) {
	sigma_init();

	const char *func = "x+x";
	const char *expect_result = "2";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var) {
	sigma_init();

	const char *func = "x";
	const char *expect_result = "1";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, constant) {
	sigma_init();

	const char *func = "5";
	const char *expect_result = "0";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, log) {
	sigma_init();

	const char *func = "log(x)";
	const char *expect_result = "1/x";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, e_raise_x) {
	sigma_init();

	const char *func = "e^x";
	const char *expect_result = "e^x";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, chain_simple) {
	sigma_init();

	const char *func = "sin(2x)";
	const char *expect_result = "2cos(2x)";

	const char *result = sigma_function(func, 'x', SIGMA_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_func_derive) {
	TEST_REG(test_func_derive, exponent_simple);
	TEST_REG(test_func_derive, exponent_simple2);
	TEST_REG(test_func_derive, sin);
	TEST_REG(test_func_derive, cos);
	TEST_REG(test_func_derive, sin_add_constants);
	TEST_REG(test_func_derive, var_plus_constant);
	TEST_REG(test_func_derive, var_mult_constant);
	TEST_REG(test_func_derive, var_plus_var);
	TEST_REG(test_func_derive, var);
	TEST_REG(test_func_derive, constant);
	TEST_REG(test_func_derive, log);
	TEST_REG(test_func_derive, e_raise_x);
	TEST_REG(test_func_derive, chain_simple);
}
