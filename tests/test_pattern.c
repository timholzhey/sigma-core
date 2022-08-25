//
// Created by tholz on 26.08.2022.
//

#include "testlib.h"
#include "lang_def.h"
#include "pattern_compile.h"
#include <string.h>

TEST_DEF(test_pattern, compile_simple) {
	const char *rule = "MUL,(NUM),MUL,-,-,(NUM),(ANY) > MUL,[MUL,$1,$2],$3";
	pattern_t pattern;

	retval_t ret = pattern_compile_rule(rule, strlen(rule), &pattern);

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

	TEST_ASSERT_TRUE(pattern.replace[0].capture_replacement == NULL);
	TEST_ASSERT_TRUE(pattern.replace[1].capture_replacement != NULL);
	TEST_ASSERT_TRUE(pattern.replace[2].capture_replacement == NULL);

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_pattern) {
	TEST_REG(test_pattern, compile_simple);
}
