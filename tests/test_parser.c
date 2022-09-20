//
// Created by Tim Holzhey on 21.08.22.
//

#include "testlib.h"
#include "math_parser.h"
#include "math_lexer.h"

TEST_DEF(test_parser, fail_tokens_null) {
	retval_t ret = lang_parse(NULL, 10, NULL);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_ERROR);
	TEST_ASSERT_EQ(err, PARSER_ERROR_TOKENS_NULL);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, fail_no_tokens) {
	token_t tokens[] = {};

	retval_t ret = lang_parse(tokens, 0, NULL);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
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

TEST_DEF(test_parser, simple_parentheses_3) {
	int num_tokens = 7;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 2;
	tokens[1].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[2].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[3].type = TOKEN_TYPE_VAR;
	tokens[4].type = TOKEN_TYPE_OPERATOR_POW;
	tokens[5].type = TOKEN_TYPE_NUM;
	tokens[5].value.number = 3;
	tokens[6].type = TOKEN_TYPE_PAREN_CLOSE;
	ast_node_t ast = {0};

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_OPERATOR_POW);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_parentheses_sin) {
	int num_tokens = 4;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_SIN;
	tokens[1].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[2].type = TOKEN_TYPE_VAR;
	tokens[3].type = TOKEN_TYPE_PAREN_CLOSE;
	ast_node_t ast = {0};

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_FUNC_SIN);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_VAR);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_parentheses_sin2) {
	int num_tokens = 6;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_FUNC_SIN;
	tokens[1].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[2].type = TOKEN_TYPE_NUM;
	tokens[3].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[4].type = TOKEN_TYPE_VAR;
	tokens[5].type = TOKEN_TYPE_PAREN_CLOSE;
	ast_node_t ast = {0};

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_FUNC_SIN);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_OPERATOR_MUL);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, simple_parentheses_power) {
	int num_tokens = 7;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_PAREN_OPEN;
	tokens[1].type = TOKEN_TYPE_VAR;
	tokens[2].type = TOKEN_TYPE_OPERATOR_ADD;
	tokens[3].type = TOKEN_TYPE_NUM;
	tokens[4].type = TOKEN_TYPE_PAREN_CLOSE;
	tokens[5].type = TOKEN_TYPE_OPERATOR_POW;
	tokens[6].type = TOKEN_TYPE_NUM;
	ast_node_t ast = {0};

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_POW);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_OPERATOR_ADD);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(ast.left->left->token.type, TOKEN_TYPE_VAR);
	TEST_ASSERT_EQ(ast.left->right->token.type, TOKEN_TYPE_NUM);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_parser, complex) {
	const char *str = "x+1.5/sin(x)";
	token_t tokens[1000];
	lexer_set_var('x');
	int num_tokens = 0;

	token_type_t expect_token_types[] = {TOKEN_TYPE_VAR, TOKEN_TYPE_OPERATOR_ADD, TOKEN_TYPE_NUM,
										 TOKEN_TYPE_OPERATOR_DIV, TOKEN_TYPE_FUNC_SIN, TOKEN_TYPE_PAREN_OPEN,
										 TOKEN_TYPE_VAR, TOKEN_TYPE_PAREN_CLOSE};

	retval_t lex_ret = lang_lex(str, tokens, &num_tokens, 1000);
	lexer_error_t lex_err = lexer_errno();

	TEST_ASSERT_EQ(lex_ret, RETVAL_OK);
	TEST_ASSERT_EQ(lex_err, LEXER_ERROR_OK);

	for (int i = 0; i < sizeof(expect_token_types) / sizeof(token_type_t); i++) {
		TEST_ASSERT_EQ(tokens[i].type, expect_token_types[i]);
	}

	ast_node_t ast = {0};

	retval_t ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);
	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_DIV);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_OPERATOR_ADD);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_FUNC_SIN);

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
	TEST_REG(test_parser, simple_parentheses_3);
	TEST_REG(test_parser, simple_parentheses_sin);
	TEST_REG(test_parser, simple_parentheses_sin2);
	TEST_REG(test_parser, simple_parentheses_power);
	TEST_REG(test_parser, complex);
}