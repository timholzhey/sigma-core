//
// Created by Tim Holzhey on 16.08.22.
//

#include <string.h>
#include <printf.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "logging.h"

static struct {
	char var;
	lexer_error_t error;
} m_lexer;

void lexer_set_var(char var) {
	m_lexer.var = var;
}

char lexer_get_var() {
	return m_lexer.var;
}

typedef enum {
	STR_MATCH_NO_MATCH,
	STR_MATCH_PARTIAL_MATCH,
	STR_MATCH_FULL_MATCH,
} str_match_partial_ret_t;

static str_match_partial_ret_t str_match_partial(const char *in, const char *match, size_t in_len, size_t match_len) {
	if (in_len > match_len) {
		return STR_MATCH_NO_MATCH;
	}
	if (strncmp(in, match, match_len) == 0) {
		return STR_MATCH_FULL_MATCH;
	}
	return strncmp(in, match, in_len) == 0 ? STR_MATCH_PARTIAL_MATCH : STR_MATCH_NO_MATCH;
}

typedef enum {
	PARSE_NUMBER_STATE_SIGN_OPT,
	PARSE_NUMBER_STATE_DIGIT_REQ,
	PARSE_NUMBER_STATE_DIGITS,
	PARSE_NUMBER_STATE_DECIMAL_REQ,
	PARSE_NUMBER_STATE_DECIMAL,
} parse_number_state_t;

#define LEXER_FAIL_WITH_MSG(...) { \
	log_error_noterm("Lexer failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

static str_match_partial_ret_t is_string_number(const char *buf, size_t buf_len, bool sign) {
	parse_number_state_t state = sign ? PARSE_NUMBER_STATE_SIGN_OPT : PARSE_NUMBER_STATE_DIGIT_REQ;

	int pos = 0;
	while (pos < buf_len) {
		switch (state) {
			case PARSE_NUMBER_STATE_SIGN_OPT:
				if (buf[pos] == '-') {
					state = PARSE_NUMBER_STATE_DIGIT_REQ;
				} else if (buf[pos] == '+') {
					state = PARSE_NUMBER_STATE_DIGIT_REQ;
				} else if (buf[pos] >= '0' && buf[pos] <= '9') {
					state = PARSE_NUMBER_STATE_DIGITS;
				} else {
					return STR_MATCH_NO_MATCH;
				}
				break;
			case PARSE_NUMBER_STATE_DIGIT_REQ:
				if (buf[pos] >= '0' && buf[pos] <= '9') {
					state = PARSE_NUMBER_STATE_DIGITS;
				} else {
					return STR_MATCH_NO_MATCH;
				}
				break;
			case PARSE_NUMBER_STATE_DIGITS:
				if (buf[pos] >= '0' && buf[pos] <= '9') {
					state = PARSE_NUMBER_STATE_DIGITS;
				} else if (buf[pos] == '.') {
					state = PARSE_NUMBER_STATE_DECIMAL_REQ;
				} else {
					return STR_MATCH_NO_MATCH;
				}
				break;
			case PARSE_NUMBER_STATE_DECIMAL_REQ:
			case PARSE_NUMBER_STATE_DECIMAL:
				if (buf[pos] >= '0' && buf[pos] <= '9') {
					state = PARSE_NUMBER_STATE_DECIMAL;
				} else {
					return STR_MATCH_NO_MATCH;
				}
				break;
			default:
				return STR_MATCH_NO_MATCH;
		}
		pos++;
	}

	if (state == PARSE_NUMBER_STATE_DIGIT_REQ || state == PARSE_NUMBER_STATE_DECIMAL_REQ) {
		return STR_MATCH_PARTIAL_MATCH;
	}

	return STR_MATCH_FULL_MATCH;
}

retval_t lang_lex(const char *input, token_t *tokens, int *num_tokens, int max_num_tokens) {
	m_lexer.error = LEXER_ERROR_OK;

	int input_pos = 0;
	char buf[512];
	int buf_pos = 0;
	size_t input_len = strlen(input);
	token_t latest_token;
	str_match_partial_ret_t best_match = STR_MATCH_NO_MATCH;
	bool start_of_expression = true;

	for (; input_pos < input_len; input_pos++) {
		str_match_partial_ret_t match;

		// look ahead
		buf[buf_pos++] = input[input_pos];

		// check str repr
		int num_matches = 0;
		for (int i = 0; i < TOKEN_TYPE_COUNT; i++) {
			match = str_match_partial(buf, token_str_repr_map[i], buf_pos, strlen(token_str_repr_map[i]));
			if (match > STR_MATCH_NO_MATCH) {
				num_matches++;
			}
			if (match > best_match) {
				latest_token.type = i;
				best_match = match;
			}
		}
		// check var
		match = str_match_partial(buf, &m_lexer.var, buf_pos, 1);
		if (match > STR_MATCH_NO_MATCH) {
			num_matches++;
		}
		if (match > best_match) {
			latest_token.type = TOKEN_TYPE_VAR;
			best_match = match;
		}
		// check number
		match = is_string_number(buf, buf_pos, start_of_expression);
		if (match > STR_MATCH_NO_MATCH) {
			num_matches++;
		}
		if (match > best_match) {
			float num = strtof(buf, NULL);
			num_matches++;
			latest_token.type = TOKEN_TYPE_NUM;
			latest_token.value_type = TOKEN_VALUE_TYPE_NUMBER;
			latest_token.value.number = num;
		}

		if (num_matches == 0 || input_pos == input_len - 1) {
			if (latest_token.type != TOKEN_TYPE_UNKNOWN) {
				if (*num_tokens > max_num_tokens) {
					m_lexer.error = LEXER_ERROR_INSUFFICIENT_SPACE;
					LEXER_FAIL_WITH_MSG("Insufficient space in output tokens");
				}

				// add token
				memcpy(&tokens[*num_tokens], &latest_token, sizeof(token_t));
				(*num_tokens)++;

				// reset
				buf_pos = 0;
				latest_token.type = TOKEN_TYPE_UNKNOWN;
				latest_token.value_type = TOKEN_VALUE_TYPE_NONE;
				best_match = STR_MATCH_NO_MATCH;

				start_of_expression = false;
				// check for start of expression tokens like opening parenthesis

				// push back
				if (num_matches != 0 && input_pos == input_len - 1) {
					continue;
				}
				input_pos--;
				continue;
			} else {
				m_lexer.error = LEXER_ERROR_UNKNOWN_TOKEN;
				LEXER_FAIL_WITH_MSG("Unknown token '%c'", input[input_pos]);
			}
		}
	}

	return RETVAL_OK;
}

lexer_error_t lexer_errno() {
	return m_lexer.error;
}
