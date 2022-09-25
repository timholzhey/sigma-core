//
// Created by Tim Holzhey on 16.08.22.
//

#include <stdbool.h>
#include "func_derive.h"
#include "math_core.h"
#include "math_lang_def.h"
#include "math_lexer.h"
#include "math_parser.h"
#include "logging.h"
#include "math_preprocess.h"
#include "math_evaluator.h"
#include "math_stringify.h"
#include "func_const.h"

#define MAX_NUM_TOKENS 1000

static bool module_initialized = false;

void math_core_init() {
	if (module_initialized) {
		return;
	}
	func_derive_init();
	func_const_init();
	module_initialized = true;
}

const char *retval_string[RETVAL_COUNT] = {
		[RETVAL_OK] = "OK",
		[RETVAL_ERROR] = "Error",
};

const char *math_function(const char *func_str, char var, math_function_t sigma_func) {
	if (!module_initialized) {
		log_error("Sigma: Module is not initialized");
		return "ERR";
	}

	if (sigma_func >= MATH_FUNCTION_COUNT) {
		log_error("Unknown sigma function %u", sigma_func);
		return "ERR";
	}

	token_t tokens[MAX_NUM_TOKENS];
	int num_tokens = 0;

	lexer_set_var(var);

	retval_t lex_ret = lang_lex(func_str, tokens, &num_tokens, MAX_NUM_TOKENS);
	if (lex_ret != RETVAL_OK) {
		log_error("Error: Lexer returned %s (%d)\n", retval_string[lex_ret], lex_ret);
		return "ERR";
	}

	token_t processed_tokens[MAX_NUM_TOKENS];
	int num_processed_tokens = 0;

	retval_t preprocess_ret = lang_preprocess(tokens, num_tokens, processed_tokens, &num_processed_tokens,
											  MAX_NUM_TOKENS);
	if (preprocess_ret != RETVAL_OK) {
		log_error("Error: Preprocessor returned %s (%d)\n", retval_string[preprocess_ret], preprocess_ret);
		return "ERR";
	}

	ast_node_t ast_in = {0};

	retval_t parse_ret = lang_parse(processed_tokens, num_processed_tokens, &ast_in);
	if (parse_ret != RETVAL_OK) {
		log_error("Error: Parser returned %s (%d)\n", retval_string[parse_ret], parse_ret);
		return "ERR";
	}

	ast_node_t ast_out = {0};

	retval_t eval_ret = lang_eval(&ast_in, &ast_out, sigma_func);
	if (eval_ret != RETVAL_OK) {
		log_error("Error: Evaluator returned %s (%d)\n", retval_string[eval_ret], eval_ret);
		return "ERR";
	}

	char *string = NULL;
	int str_len = 0;

	retval_t string_ret = lang_stringify(&ast_out, &string, &str_len);
	if (string_ret != RETVAL_OK) {
		log_error("Error: Stringifier returned %s (%d)\n", retval_string[string_ret], string_ret);
		return "ERR";
	}

	return string;
}

const char *derive(const char *func, char var) {
	return math_function(func, var, MATH_FUNCTION_DERIVE);
}
