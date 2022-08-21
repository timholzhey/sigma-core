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

TEST_DEF(test_parser, fail_unexpected_token) {
	int num_tokens = 4;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[1].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[2].type = TOKEN_TYPE_NUM;
	tokens[3].type = TOKEN_TYPE_NUM;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, PARSER_ERROR_UNEXPECTED_TOKEN);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, fail_surrounding_mismatch) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_ABS;
	tokens[1].type = TOKEN_TYPE_NUM;
	tokens[2].type = TOKEN_TYPE_NUM;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, PARSER_ERROR_SURROUNDING_MISMATCH);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_infix) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[1].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[2].type = TOKEN_TYPE_NUM;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_ADD);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_NUM);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_prefix) {
	int num_tokens = 2;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_SIN;
	tokens[1].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_FUNC_SIN);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_VAR);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_postfix) {
	int num_tokens = 2;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_VAR;
	tokens[1].type = TOKEN_TYPE_FUNC_FACT;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_FUNC_FACT);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_VAR);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_surround) {
	int num_tokens = 3;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_ABS;
	tokens[1].type = TOKEN_TYPE_VAR;
	tokens[2].type = TOKEN_TYPE_FUNC_ABS;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_FUNC_ABS);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_VAR);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_parentheses) {
	int num_tokens = 7;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[1].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[2].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[3].type = TOKEN_TYPE_VAR;
	tokens[4].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[5].type = TOKEN_TYPE_NUM;
	tokens[6].type = TOKEN_TYPE_PAREN_CLOSE;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_ADD);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_EQ(ast.right->left->token.type, TOKEN_TYPE_VAR);
	TEST_ASSERT_EQ(ast.right->right->token.type, TOKEN_TYPE_NUM);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_parentheses_2) {
	int num_tokens = 7;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[1].type = TOKEN_TYPE_VAR;
	tokens[2].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[3].type = TOKEN_TYPE_NUM;
	tokens[4].type = TOKEN_TYPE_PAREN_CLOSE;
	tokens[5].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[6].type = TOKEN_TYPE_NUM;
	ast_node_t ast = {0};

	retval_t ret = parser_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_ADD);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_EQ(ast.left->left->token.type, TOKEN_TYPE_VAR);
	TEST_ASSERT_EQ(ast.left->right->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_NUM);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_parser) {
	TEST_REG(test_parser, fail_tokens_null);
	TEST_REG(test_parser, fail_no_tokens);
	TEST_REG(test_parser, fail_unexpected_token);
	TEST_REG(test_parser, fail_surrounding_mismatch);
	TEST_REG(test_parser, simple_infix);
	TEST_REG(test_parser, simple_prefix);
	TEST_REG(test_parser, simple_postfix);
	TEST_REG(test_parser, simple_surround);
	TEST_REG(test_parser, simple_parentheses);
	TEST_REG(test_parser, simple_parentheses_2);
}