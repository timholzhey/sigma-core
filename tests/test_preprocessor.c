//
// Created by Tim Holzhey on 23.08.22.
//

#include "testlib.h"
#include "lexer.h"
#include "preprocess.h"

TEST_DEF(test_preprocessor, precedence_simple) {
	int num_tokens_in = 7;
	token_t tokens_in[num_tokens_in];
	tokens_in[0].type = TOKEN_TYPE_NUM;
	tokens_in[1].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens_in[2].type = TOKEN_TYPE_NUM;
	tokens_in[3].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens_in[4].type = TOKEN_TYPE_VAR;
	tokens_in[5].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[6].type = TOKEN_TYPE_NUM;
	int num_tokens_out = 0;
	token_t tokens_out[1000];

	retval_t ret = lang_preprocess(tokens_in, num_tokens_in, tokens_out, &num_tokens_out, 1000);
	preprocessor_error_t err = preprocessor_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_ADD, TOKEN_TYPE_PAREN_OPEN, TOKEN_TYPE_NUM,
										 TOKEN_TYPE_OPERATOR_MUL, TOKEN_TYPE_VAR, TOKEN_TYPE_PAREN_CLOSE,
										 TOKEN_TYPE_OPERATOR_SUB, TOKEN_TYPE_NUM};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PREPROCESSOR_ERROR_OK);
	TEST_ASSERT_EQ(num_tokens_out, 9);

	for (int i = 0; i < num_tokens_out; i++) {
		TEST_ASSERT_EQ(tokens_out[i].type, expect_token_types[i]);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_preprocessor, expand_unary_simple) {
	int num_tokens_in = 2;
	token_t tokens_in[num_tokens_in];
	tokens_in[0].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[1].type = TOKEN_TYPE_VAR;
	int num_tokens_out = 0;
	token_t tokens_out[1000];

	retval_t ret = lang_preprocess(tokens_in, num_tokens_in, tokens_out, &num_tokens_out, 1000);
	preprocessor_error_t err = preprocessor_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_SUB, TOKEN_TYPE_VAR};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PREPROCESSOR_ERROR_OK);
	TEST_ASSERT_EQ(num_tokens_out, 3);

	for (int i = 0; i < num_tokens_out; i++) {
		TEST_ASSERT_EQ(tokens_out[i].type, expect_token_types[i]);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_preprocessor, fail_insufficient_space) {
	int num_tokens_in = 2;
	token_t tokens_in[num_tokens_in];
	tokens_in[0].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[1].type = TOKEN_TYPE_VAR;
	int num_tokens_out = 0;
	token_t tokens_out[1000];

	retval_t ret = lang_preprocess(tokens_in, num_tokens_in, tokens_out, &num_tokens_out, 2);
	preprocessor_error_t err = preprocessor_errno();

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, PREPROCESSOR_ERROR_INSUFFICIENT_SPACE);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_preprocessor, truncate_consecutive_negative_signs) {
	int num_tokens_in = 10;
	token_t tokens_in[num_tokens_in];
	tokens_in[0].type = TOKEN_TYPE_NUM;
	tokens_in[1].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[2].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[3].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[4].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[5].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[6].type = TOKEN_TYPE_VAR;
	tokens_in[7].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[8].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens_in[9].type = TOKEN_TYPE_NUM;
	int num_tokens_out = 0;
	token_t tokens_out[1000];

	retval_t ret = lang_preprocess(tokens_in, num_tokens_in, tokens_out, &num_tokens_out, 1000);
	preprocessor_error_t err = preprocessor_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_SUB, TOKEN_TYPE_VAR,
										 TOKEN_TYPE_OPERATOR_ADD, TOKEN_TYPE_NUM};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PREPROCESSOR_ERROR_OK);
	TEST_ASSERT_EQ(num_tokens_out, 5);

	for (int i = 0; i < num_tokens_out; i++) {
		TEST_ASSERT_EQ(tokens_out[i].type, expect_token_types[i]);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_preprocessor, implicit_multiplication) {
	int num_tokens_in = 2;
	token_t tokens_in[num_tokens_in];
	tokens_in[0].type = TOKEN_TYPE_NUM;
	tokens_in[1].type = TOKEN_TYPE_VAR;
	int num_tokens_out = 0;
	token_t tokens_out[1000];

	retval_t ret = lang_preprocess(tokens_in, num_tokens_in, tokens_out, &num_tokens_out, 1000);
	preprocessor_error_t err = preprocessor_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_MUL, TOKEN_TYPE_VAR};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PREPROCESSOR_ERROR_OK);
	TEST_ASSERT_EQ(num_tokens_out, 3);

	for (int i = 0; i < num_tokens_out; i++) {
		TEST_ASSERT_EQ(tokens_out[i].type, expect_token_types[i]);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_preprocessor) {
	TEST_REG(test_preprocessor, precedence_simple);
	TEST_REG(test_preprocessor, expand_unary_simple);
	TEST_REG(test_preprocessor, fail_insufficient_space);
	TEST_REG(test_preprocessor, truncate_consecutive_negative_signs);
	TEST_REG(test_preprocessor, implicit_multiplication);
}
