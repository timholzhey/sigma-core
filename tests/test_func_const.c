//
// Created by tholz on 27.08.2022.
//

#include "testlib.h"
#include "math_lang_def.h"
#include <string.h>
#include "math_core.h"

TEST_DEF(test_func_const, mult_commut_simple) {
	math_core_init();

	const char *func = "2*2*x";
	const char *expect_result = "4x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, mult_commut_implicit_mult) {
	math_core_init();

	const char *func = "2x";
	const char *expect_result = "2x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, mult_commut_long) {
	math_core_init();

	const char *func = "1*2*3*4*5*x";
	const char *expect_result = "120x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, add_commut_simple) {
	math_core_init();

	const char *func = "2+2+x";
	const char *expect_result = "x+4";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, add_commut_long) {
	math_core_init();

	const char *func = "1+2+3+4+5+x";
	const char *expect_result = "x+15";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, add_commut_long_unordered) {
	math_core_init();

	const char *func = "1+2+x+3+4+5";
	const char *expect_result = "x+15";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, raise_to_power_one) {
	math_core_init();

	const char *func = "x^1";
	const char *expect_result = "x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, raise_to_power_zero) {
	math_core_init();

	const char *func = "x^0";
	const char *expect_result = "1";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, raise_one_to_power) {
	math_core_init();

	const char *func = "1^6";
	const char *expect_result = "1";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, add_zero) {
	math_core_init();

	const char *func = "x+0";
	const char *expect_result = "x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, multiply_zero) {
	math_core_init();

	const char *func = "x*0";
	const char *expect_result = "0";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, multiply_one) {
	math_core_init();

	const char *func = "x*1";
	const char *expect_result = "x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, multiply_var_var) {
	math_core_init();

	const char *func = "x*x";
	const char *expect_result = "x^2";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, add_var_multiples) {
	math_core_init();

	const char *func = "2x+3x";
	const char *expect_result = "5x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, multiply_var_powers) {
	math_core_init();

	const char *func = "x^2*x^3";
	const char *expect_result = "x^5";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, divide_by_one) {
	math_core_init();

	const char *func = "x/1";
	const char *expect_result = "x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, divide_by_zero) {
	math_core_init();

	const char *func = "x/0";
	const char *expect_result = "Error: Division by zero";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, binom1) {
	math_core_init();

	const char *func = "(x+3)^2";
	const char *expect_result = "x^2+6x+9";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_const, binom2) {
	math_core_init();

	const char *func = "(x-3)^2";
	const char *expect_result = "x^2+9-6x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_CONST);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_func_const) {
	TEST_REG(test_func_const, mult_commut_simple);
	TEST_REG(test_func_const, mult_commut_implicit_mult);
	TEST_REG(test_func_const, mult_commut_long);
	TEST_REG(test_func_const, add_commut_simple);
	TEST_REG(test_func_const, add_commut_long);
	TEST_REG(test_func_const, add_commut_long_unordered);
	TEST_REG(test_func_const, raise_to_power_one);
	TEST_REG(test_func_const, raise_to_power_zero);
	TEST_REG(test_func_const, raise_one_to_power);
	TEST_REG(test_func_const, add_zero);
	TEST_REG(test_func_const, multiply_zero);
	TEST_REG(test_func_const, multiply_one);
	TEST_REG(test_func_const, multiply_var_var);
	TEST_REG(test_func_const, add_var_multiples);
	TEST_REG(test_func_const, multiply_var_powers);
	TEST_REG(test_func_const, divide_by_one);
	TEST_REG(test_func_const, divide_by_zero);
	TEST_REG(test_func_const, binom1);
	TEST_REG(test_func_const, binom2);
}
