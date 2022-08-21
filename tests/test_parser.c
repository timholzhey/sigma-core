//
// Created by Tim Holzhey on 21.08.22.
//

#include "testlib.h"
#include "parser.h"

TEST_DEF(test_parser, fail_tokens_null) {
	retval_t ret = parser_parse(NULL, 10, NULL);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, PARSER_ERROR_TOKENS_NULL);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, fail_no_tokens) {
	token_t tokens[] = {};

	retval_t ret = parser_parse(tokens, 0, NULL);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, PARSER_ERROR_NO_TOKENS);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_parser) {
	TEST_REG(test_parser, fail_tokens_null);
	TEST_REG(test_parser, fail_no_tokens);
}