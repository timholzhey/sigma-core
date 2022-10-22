//
// Created by Tim Holzhey on 21.08.22.
//

#include "testlib.h"
#include "math_lexer.h"

TEST_DEF(test_lexer, simple) {
	const char *input = "1.5*x^2-3!";
	token_t tokens[1000];
	lexer_set_var('x');
	int num_tokens = 0;

	retval_t ret = lang_lex(input, tokens, &num_tokens, 1000);
	lexer_error_t err = lexer_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_MUL, TOKEN_TYPE_VAR,
										 TOKEN_TYPE_OPERATOR_POW, TOKEN_TYPE_NUM};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, LEXER_ERROR_OK);

	for (int i = 0; i < sizeof(expect_token_types) / sizeof(token_type_t); i++) {
		TEST_ASSERT_EQ(tokens[i].type, expect_token_types[i]);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_lexer, unknown_token) {
	const char *input = "1+u";
	token_t tokens[1000];
	int num_tokens = 0;

	retval_t ret = lang_lex(input, tokens, &num_tokens, 1000);
	lexer_error_t err = lexer_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_ADD, TOKEN_TYPE_USER_VAR};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, LEXER_ERROR_OK);

	for (int i = 0; i < sizeof(expect_token_types) / sizeof(token_type_t); i++) {
		TEST_ASSERT_EQ(tokens[i].type, expect_token_types[i]);
	}

	TEST_ASSERT_EQ_DOUBLE(tokens[0].value.number, 1.0f);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_lexer, simple2) {
	const char *input = "2*2*x";
	token_t tokens[1000];
	lexer_set_var('x');
	int num_tokens = 0;

	retval_t ret = lang_lex(input, tokens, &num_tokens, 1000);
	lexer_error_t err = lexer_errno();

	token_type_t expect_token_types[] = {TOKEN_TYPE_NUM, TOKEN_TYPE_OPERATOR_MUL, TOKEN_TYPE_NUM,
										 TOKEN_TYPE_OPERATOR_MUL, TOKEN_TYPE_VAR};

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, LEXER_ERROR_OK);

	for (int i = 0; i < sizeof(expect_token_types) / sizeof(token_type_t); i++) {
		TEST_ASSERT_EQ(tokens[i].type, expect_token_types[i]);
	}

	TEST_ASSERT_EQ_DOUBLE(tokens[0].value.number, 2.0f);
	TEST_ASSERT_EQ_DOUBLE(tokens[2].value.number, 2.0f);

	TEST_CLEAN_UP_AND_RETURN(0);

}

TEST_RUNNER(test_lexer) {
	TEST_REG(test_lexer, simple);
	TEST_REG(test_lexer, unknown_token);
	TEST_REG(test_lexer, simple2);
}
