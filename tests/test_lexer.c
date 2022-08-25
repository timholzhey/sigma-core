//
// Created by Tim Holzhey on 21.08.22.
//

#include "testlib.h"
#include "lexer.h"

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

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, LEXER_ERROR_UNKNOWN_TOKEN);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_lexer) {
	TEST_REG(test_lexer, simple);
	TEST_REG(test_lexer, unknown_token);
}
