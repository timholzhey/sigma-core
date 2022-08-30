//
// Created by Tim Holzhey on 25.08.22.
//

#include <string.h>
#include "testlib.h"
#include "stringify.h"
#include "parser.h"
#include "lexer.h"

TEST_DEF(test_stringify, simple_prefix) {
	int num_tokens = 2;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_SIN;
	tokens[1].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "sin(x)";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_infix) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_VAR;
	tokens[1].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[2].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "x+x";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_postfix) {
	int num_tokens = 2;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_VAR;
	tokens[1].type = TOKEN_TYPE_FUNC_FACT;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "x!";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_surround) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_ABS;
	tokens[1].type = TOKEN_TYPE_VAR;
	tokens[2].type = TOKEN_TYPE_FUNC_ABS;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "|x|";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_number) {
	int num_tokens = 1;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 3.141f;
	ast_node_t ast = {0};

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "3.141";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_parentheses) {
	int num_tokens = 7;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_VAR;
	tokens[1].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[2].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[3].type = TOKEN_TYPE_VAR;
	tokens[4].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[5].type = TOKEN_TYPE_VAR;
	tokens[6].type = TOKEN_TYPE_PAREN_CLOSE;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "x+xx";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_implicit_multiplication) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 2;
	tokens[1].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[2].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "2x";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_subtract_from_zero) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 0;
	tokens[1].type = TOKEN_TYPE_OPERATOR_SUB;
	tokens[2].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "-x";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_stringify, simple_precedence_parentheses) {
	int num_tokens = 7;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 1;
	tokens[1].type = TOKEN_TYPE_OPERATOR_DIV;
	tokens[2].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[3].type = TOKEN_TYPE_NUM;
	tokens[3].value.number = 2;
	tokens[4].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[5].type = TOKEN_TYPE_VAR;
	tokens[6].type = TOKEN_TYPE_PAREN_CLOSE;
	ast_node_t ast = {0};

	lexer_set_var('x');

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	char *string = NULL;
	char *expect_string = "1/(2x)";
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast, &string, &str_len);
	TEST_ASSERT_EQ(string_ret, RETVAL_OK);
	TEST_ASSERT_EQ_STRING(string, expect_string, strlen(expect_string));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_stringify) {
	TEST_REG(test_stringify, simple_prefix);
	TEST_REG(test_stringify, simple_infix);
	TEST_REG(test_stringify, simple_postfix);
	TEST_REG(test_stringify, simple_surround);
	TEST_REG(test_stringify, simple_number);
	TEST_REG(test_stringify, simple_parentheses);
	TEST_REG(test_stringify, simple_implicit_multiplication);
	TEST_REG(test_stringify, simple_subtract_from_zero);
	TEST_REG(test_stringify, simple_precedence_parentheses);
}
