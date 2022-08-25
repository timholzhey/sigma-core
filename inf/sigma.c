//
// Created by Tim Holzhey on 16.08.22.
//

#include "sigma.h"
#include "lang_def.h"
#include "lexer.h"
#include "parser.h"
#include "logging.h"
#include "preprocess.h"
#include "evaluator.h"
#include "stringify/stringify.h"

#define MAX_NUM_TOKENS 1000

const char *retval_string[RETVAL_COUNT] = {
		[RETVAL_OK] = "OK",
		[RETVAL_ERROR] = "Error",
};

static const char *sigma_function(const char *func_str, char var, sigma_function_t sigma_func) {
	token_t tokens[MAX_NUM_TOKENS];
	int num_tokens = 0;

	lexer_set_var(var);

	retval_t lex_ret = lang_lex(func_str, tokens, &num_tokens, MAX_NUM_TOKENS);
	if (lex_ret != RETVAL_OK) {
		log_error("Error: Lexer returned %s (%d)\n", retval_string[lex_ret], lex_ret);
	}

	token_t processed_tokens[MAX_NUM_TOKENS];
	int num_processed_tokens = 0;

	retval_t preprocess_ret = lang_preprocess(tokens, num_tokens, processed_tokens, &num_processed_tokens,
											  MAX_NUM_TOKENS);
	if (preprocess_ret != RETVAL_OK) {
		log_error("Error: Preprocessor returned %s (%d)\n", retval_string[preprocess_ret], preprocess_ret);
	}

	ast_node_t ast_in = {0};

	retval_t parse_ret = lang_parse(tokens, num_tokens, &ast_in);
	if (parse_ret != RETVAL_OK) {
		log_error("Error: Parser returned %s (%d)\n", retval_string[parse_ret], parse_ret);
	}

	ast_node_t ast_out = {0};

	retval_t eval_ret = lang_eval(&ast_in, &ast_out, sigma_func);
	if (eval_ret != RETVAL_OK) {
		log_error("Error: Evaluator returned %s (%d)\n", retval_string[eval_ret], eval_ret);
	}

	char *string = NULL;
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast_out, &string, &str_len);
	if (string_ret != RETVAL_OK) {
		log_error("Error: Stringifier returned %s (%d)\n", retval_string[string_ret], string_ret);
	}

	return string;
}

const char *derive(const char *func, char var) {
	return sigma_function(func, var, SIGMA_FUNCTION_DERIVE);
}
