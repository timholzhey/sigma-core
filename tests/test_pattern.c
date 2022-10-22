//
// Created by tholz on 26.08.2022.
//

#include "testlib.h"
#include "math_lang_def.h"
#include "pattern_compile.h"
#include "math_parser.h"
#include "pattern_match.h"
#include "pattern_replace.h"
#include <string.h>
#include <pattern_capture.h>
#include <pattern_generate.h>

TEST_DEF(test_pattern, compile_simple) {
	const char *rule = "MUL,(NUM),MUL,-,-,(NUM),(ANY) > MUL,[MUL,$1,$2],$3";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 7;
	expect_pattern.num_replace_nodes = 3;

	expect_pattern.match[0].token_type = TOKEN_TYPE_OPERATOR_MUL;
	expect_pattern.match[1].token_type = TOKEN_TYPE_NUM;
	expect_pattern.match[2].token_type = TOKEN_TYPE_OPERATOR_MUL;
	expect_pattern.match[3].token_type = TOKEN_TYPE_NONE;
	expect_pattern.match[4].token_type = TOKEN_TYPE_NONE;
	expect_pattern.match[5].token_type = TOKEN_TYPE_NUM;
	expect_pattern.match[6].token_type = TOKEN_TYPE_ANY;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_OPERATOR_MUL;
	expect_pattern.replace[1].token_type = TOKEN_TYPE_NONE;
	expect_pattern.replace[2].token_type = TOKEN_TYPE_NONE;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_TRUE(pattern.replace[0].replacement == NULL);
	TEST_ASSERT_TRUE(pattern.replace[1].replacement != NULL);
	TEST_ASSERT_EQ(pattern.replace[1].num_replacement_nodes, 3);
	TEST_ASSERT_EQ(pattern.replace[1].replacement[0].token_type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_EQ(pattern.replace[1].replacement[0].type, PATTERN_NODE_TYPE_MATCH_TOKEN);
	TEST_ASSERT_EQ(pattern.replace[1].replacement[1].type, PATTERN_NODE_TYPE_REPLACE_TOKEN);
	TEST_ASSERT_EQ(pattern.replace[1].replacement[1].capture_idx, 0);
	TEST_ASSERT_EQ(pattern.replace[1].replacement[2].type, PATTERN_NODE_TYPE_REPLACE_TOKEN);
	TEST_ASSERT_EQ(pattern.replace[1].replacement[2].capture_idx, 1);
	TEST_ASSERT_TRUE(pattern.replace[2].replacement == NULL);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_simple2) {
	const char *rule = "LOG,VAR > DIV,[NUM=1],VAR,";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 2;
	expect_pattern.num_replace_nodes = 3;

	expect_pattern.match[0].token_type = TOKEN_TYPE_FUNC_LOG;
	expect_pattern.match[1].token_type = TOKEN_TYPE_VAR;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_OPERATOR_DIV;
	expect_pattern.replace[1].token_type = TOKEN_TYPE_NUM;
	expect_pattern.replace[2].token_type = TOKEN_TYPE_VAR;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_simple3) {
	const char *rule = "~POW,(NUM=1),ANY > [NUM=1]";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 3;
	expect_pattern.num_replace_nodes = 1;

	expect_pattern.match[0].token_type = TOKEN_TYPE_OPERATOR_POW;
	expect_pattern.match[1].token_type = TOKEN_TYPE_NUM;
	expect_pattern.match[2].token_type = TOKEN_TYPE_ANY;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_NUM;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_match_number) {
	const char *rule = "POW,(ANY),(NUM=1) > $1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 3;
	expect_pattern.num_replace_nodes = 1;

	expect_pattern.match[0].token_type = TOKEN_TYPE_OPERATOR_POW;
	expect_pattern.match[1].token_type = TOKEN_TYPE_ANY;
	expect_pattern.match[2].token_type = TOKEN_TYPE_NUM;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_NONE;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_EQ(pattern.match[2].capture_idx, 1);
	TEST_ASSERT_EQ(pattern.match[2].type, PATTERN_NODE_TYPE_CAPTURE_TOKEN);
	TEST_ASSERT_EQ(pattern.match[2].has_number, 1);
	TEST_ASSERT_EQ_DOUBLE(pattern.match[2].number, 1.0f);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_replace_number) {
	const char *rule = "POW,VAR,(NUM) > MUL,$1,POW,-,-,VAR,[SUB,$1,NUM=1]";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 3;
	expect_pattern.num_replace_nodes = 7;

	expect_pattern.match[0].token_type = TOKEN_TYPE_OPERATOR_POW;
	expect_pattern.match[1].token_type = TOKEN_TYPE_VAR;
	expect_pattern.match[2].token_type = TOKEN_TYPE_NUM;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_OPERATOR_MUL;
	expect_pattern.replace[1].token_type = TOKEN_TYPE_NONE;
	expect_pattern.replace[2].token_type = TOKEN_TYPE_OPERATOR_POW;
	expect_pattern.replace[3].token_type = TOKEN_TYPE_NONE;
	expect_pattern.replace[4].token_type = TOKEN_TYPE_NONE;
	expect_pattern.replace[5].token_type = TOKEN_TYPE_VAR;
	expect_pattern.replace[6].token_type = TOKEN_TYPE_NONE;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_NOT_NULL(pattern.replace[6].replacement);
	TEST_ASSERT_EQ(pattern.replace[6].num_replacement_nodes, 3);
	TEST_ASSERT_EQ(pattern.replace[6].replacement[0].token_type, TOKEN_TYPE_OPERATOR_SUB);
	TEST_ASSERT_EQ(pattern.replace[6].replacement[1].token_type, TOKEN_TYPE_NONE);
	TEST_ASSERT_EQ(pattern.replace[6].replacement[2].token_type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(pattern.replace[6].replacement[2].has_number, 1);
	TEST_ASSERT_EQ_DOUBLE(pattern.replace[6].replacement[2].number, 1.0f);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_replace_only_number) {
	const char *rule = "POW,(ANY),(NUM=0) > [NUM=1]";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 3;
	expect_pattern.num_replace_nodes = 1;

	expect_pattern.match[0].token_type = TOKEN_TYPE_OPERATOR_POW;
	expect_pattern.match[1].token_type = TOKEN_TYPE_ANY;
	expect_pattern.match[2].token_type = TOKEN_TYPE_NUM;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_NONE;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_NOT_NULL(pattern.replace[0].replacement);
	TEST_ASSERT_EQ(pattern.replace[0].num_replacement_nodes, 1);
	TEST_ASSERT_EQ(pattern.replace[0].replacement[0].token_type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ(pattern.replace[0].replacement[0].has_number, 1);
	TEST_ASSERT_EQ_DOUBLE(pattern.replace[0].replacement[0].number, 1.0f);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_replace_error) {
	const char *rule = "VAR > ERR: Example error description";
	const char *err_desc = "Error: Example error description";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 1;
	expect_pattern.num_replace_nodes = 1;

	expect_pattern.match[0].token_type = TOKEN_TYPE_VAR;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_ERR;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_EQ(pattern.replace[0].type, PATTERN_NODE_TYPE_REPLACE_ERROR);
	TEST_ASSERT_EQ_U32(pattern.replace[0].error_desc_len, strlen(err_desc));
	TEST_ASSERT_NOT_NULL(pattern.replace[0].error_desc);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_propagate) {
	const char *rule = "@(FUNC),(FUNC) > MUL,$1,$2";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 2;
	expect_pattern.num_replace_nodes = 3;

	expect_pattern.match[0].token_type = TOKEN_TYPE_FUNC;
	expect_pattern.match[1].token_type = TOKEN_TYPE_FUNC;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_OPERATOR_MUL;
	expect_pattern.replace[1].token_type = TOKEN_TYPE_NONE;
	expect_pattern.replace[2].token_type = TOKEN_TYPE_NONE;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_EQ(pattern.do_propagate, 1);
	TEST_ASSERT_EQ(pattern.replace[1].type, PATTERN_NODE_TYPE_REPLACE_TOKEN);
	TEST_ASSERT_EQ(pattern.replace[1].capture_idx, 0);
	TEST_ASSERT_EQ(pattern.replace[2].type, PATTERN_NODE_TYPE_REPLACE_TOKEN);
	TEST_ASSERT_EQ(pattern.replace[2].capture_idx, 1);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, compile_inverted) {
	const char *rule = "ADD,(!NUM),(NUM) > ADD,$2,$1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 3;
	expect_pattern.num_replace_nodes = 3;

	expect_pattern.match[0].token_type = TOKEN_TYPE_OPERATOR_ADD;
	expect_pattern.match[1].token_type = TOKEN_TYPE_NUM;
	expect_pattern.match[2].token_type = TOKEN_TYPE_NUM;

	expect_pattern.replace[0].token_type = TOKEN_TYPE_OPERATOR_ADD;
	expect_pattern.replace[1].token_type = TOKEN_TYPE_NONE;
	expect_pattern.replace[2].token_type = TOKEN_TYPE_NONE;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	for (int i = 0; i < expect_pattern.num_match_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.match[i].token_type, pattern.match[i].token_type);
	}

	for (int i = 0; i < expect_pattern.num_replace_nodes; i++) {
		TEST_ASSERT_EQ(expect_pattern.replace[i].token_type, pattern.replace[i].token_type);
	}

	TEST_ASSERT_EQ(pattern.match[1].is_inverted, 1);
	TEST_ASSERT_EQ(pattern.match[2].is_inverted, 0);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, match_simple) {
	const char *rule = "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 7;
	expect_pattern.num_replace_nodes = 3;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	int num_tokens = 5;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 2;
	tokens[1].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[2].type = TOKEN_TYPE_NUM;
	tokens[2].value.number = 3;
	tokens[3].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[4].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	bool match = false;
	retval_t match_ret = pattern_match(&ast, &pattern, &match);

	TEST_ASSERT_EQ(match_ret, RETVAL_OK);
	TEST_ASSERT_EQ(match, true);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, capture_simple) {
	const char *rule = "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 7;
	expect_pattern.num_replace_nodes = 3;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	int num_tokens = 5;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 2;
	tokens[1].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[2].type = TOKEN_TYPE_NUM;
	tokens[2].value.number = 3;
	tokens[3].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[4].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	bool match = false;
	retval_t match_ret = pattern_match(&ast, &pattern, &match);

	TEST_ASSERT_EQ(match_ret, RETVAL_OK);
	TEST_ASSERT_EQ(match, true);

	ast_node_t *capture_nodes[10] = {0};
	int num_capture_nodes = 0;
	retval_t capture_ret = pattern_capture(&ast, &pattern, capture_nodes, &num_capture_nodes);

	TEST_ASSERT_EQ(capture_ret, RETVAL_OK);
	TEST_ASSERT_EQ(num_capture_nodes, 3);
	TEST_ASSERT_NOT_NULL(capture_nodes[0]);
	TEST_ASSERT_NOT_NULL(capture_nodes[1]);
	TEST_ASSERT_NOT_NULL(capture_nodes[2]);
	TEST_ASSERT_EQ(capture_nodes[0]->token.type, TOKEN_TYPE_VAR);
	TEST_ASSERT_EQ(capture_nodes[1]->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ_DOUBLE(capture_nodes[1]->token.value.number, 2.0f);
	TEST_ASSERT_EQ(capture_nodes[2]->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ_DOUBLE(capture_nodes[2]->token.value.number, 3.0f);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, replace_simple) {
	const char *rule = "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 7;
	expect_pattern.num_replace_nodes = 3;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	int num_tokens = 5;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 2;
	tokens[1].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[2].type = TOKEN_TYPE_NUM;
	tokens[2].value.number = 3;
	tokens[3].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[4].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	bool match = false;
	retval_t match_ret = pattern_match(&ast, &pattern, &match);

	TEST_ASSERT_EQ(match_ret, RETVAL_OK);
	TEST_ASSERT_EQ(match, true);

	ast_node_t ast_out;
	retval_t replace_ret = pattern_replace(&ast, &pattern, &ast_out);

	TEST_ASSERT_EQ(replace_ret, RETVAL_OK);
	TEST_ASSERT_EQ(ast_out.token.type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_NOT_NULL(ast_out.left);
	TEST_ASSERT_EQ(ast_out.left->token.type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_NOT_NULL(ast_out.left->left);
	TEST_ASSERT_EQ(ast_out.left->left->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ_DOUBLE(ast_out.left->left->token.value.number, 2.0f);
	TEST_ASSERT_NOT_NULL(ast_out.left->right);
	TEST_ASSERT_EQ(ast_out.left->right->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ_DOUBLE(ast_out.left->right->token.value.number, 3.0f);
	TEST_ASSERT_NOT_NULL(ast_out.right);
	TEST_ASSERT_EQ(ast_out.right->token.type, TOKEN_TYPE_VAR);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, apply_simple) {
	const char *rule = "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 7;
	expect_pattern.num_replace_nodes = 3;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	int num_tokens = 5;
	token_t tokens[num_tokens];
	tokens[0].type = TOKEN_TYPE_NUM;
	tokens[0].value.number = 2;
	tokens[1].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[2].type = TOKEN_TYPE_NUM;
	tokens[2].value.number = 3;
	tokens[3].type = TOKEN_TYPE_OPERATOR_MUL;
	tokens[4].type = TOKEN_TYPE_VAR;
	ast_node_t ast = {0};

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast);
	parser_error_t err = parser_errno();

	TEST_ASSERT_EQ(parse_ret, RETVAL_OK);
	TEST_ASSERT_EQ(err, PARSER_ERROR_OK);

	bool applied = false;

	retval_t apply_ret = pattern_apply(&ast, &pattern, &applied);

	TEST_ASSERT_EQ(apply_ret, RETVAL_OK);
	TEST_ASSERT_EQ(applied, true);

	TEST_ASSERT_EQ(ast.token.type, TOKEN_TYPE_OPERATOR_MUL);
	TEST_ASSERT_NOT_NULL(ast.left);
	TEST_ASSERT_EQ(ast.left->token.type, TOKEN_TYPE_NUM);
	TEST_ASSERT_EQ_DOUBLE(ast.left->token.value.number, 6.0f);
	TEST_ASSERT_NOT_NULL(ast.right);
	TEST_ASSERT_EQ(ast.right->token.type, TOKEN_TYPE_VAR);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_pattern, generate_simple) {
	const char *rule = "MUL,MUL,(ANY),(NUM),(NUM),-,- > MUL,[MUL,$2,$3],$1";
	pattern_t pattern;

	retval_t ret = pattern_compile(rule, strlen(rule), &pattern);

	pattern_t expect_pattern;
	expect_pattern.num_match_nodes = 7;
	expect_pattern.num_replace_nodes = 3;

	TEST_ASSERT_EQ(ret, RETVAL_OK);
	TEST_ASSERT_EQ(pattern.num_match_nodes, expect_pattern.num_match_nodes);
	TEST_ASSERT_EQ(pattern.num_replace_nodes, expect_pattern.num_replace_nodes);

	const int max_num_patterns = 100;
	pattern_t patterns[100];
	int num_patterns = 0;
	retval_t generate_ret = pattern_generate(&pattern, patterns, &num_patterns, max_num_patterns);

	TEST_ASSERT_EQ(generate_ret, RETVAL_OK);
	TEST_ASSERT_EQ(num_patterns, 2);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_pattern) {
	TEST_REG(test_pattern, compile_simple);
	TEST_REG(test_pattern, compile_simple2);
	TEST_REG(test_pattern, compile_simple3);
	TEST_REG(test_pattern, compile_match_number);
	TEST_REG(test_pattern, compile_replace_number);
	TEST_REG(test_pattern, compile_replace_only_number);
	TEST_REG(test_pattern, compile_replace_error);
	TEST_REG(test_pattern, compile_propagate);
	TEST_REG(test_pattern, compile_inverted);
	TEST_REG(test_pattern, match_simple);
	TEST_REG(test_pattern, capture_simple);
	TEST_REG(test_pattern, replace_simple);
	TEST_REG(test_pattern, apply_simple);
	TEST_REG(test_pattern, generate_simple);
}
