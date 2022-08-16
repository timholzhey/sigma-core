//
// Created by Tim Holzhey on 16.08.22.
//

#include <string.h>
#include <printf.h>
#include <stdlib.h>
#include "lexer.h"

static struct {
	char var;
} m_lexer;

void lexer_set_var(char var) {
	m_lexer.var = var;
}

int str_match_partial(const char *in, const char *match, size_t in_len, size_t match_len) {
	if (in_len > match_len) {
		return 1;
	}
	return strncmp(in, match, match_len);
}

retval_t lexer_lex(const char *input, token_t *tokens) {
	int input_pos = 0;
	int token_count = 0;
	char buf[512];
	int buf_pos = 0;
	size_t input_len = strlen(input);
	token_type_t latest_token_type = TOKEN_TYPE_UNKNOWN;

	for (; input_pos < input_len; input_pos++) {
		// look ahead
		buf[buf_pos++] = input[input_pos];

		// check str repr
		int num_matches = 0;
		for (int i = 0; i < TOKEN_TYPE_COUNT; i++) {
			if (str_match_partial(buf, token_str_repr_map[i], buf_pos, strlen(token_str_repr_map[i])) == 0) {
				num_matches++;
				latest_token_type = i;
			}
		}
		// check var
		if (str_match_partial(buf, &m_lexer.var, buf_pos, 1) == 0) {
			num_matches++;
			latest_token_type = TOKEN_TYPE_VAR;
		}
		// check num (float)
		float num = strtof(buf, NULL);
		if (num != 0.0) {
			printf("got number %s\n", buf);
			num_matches++;
			latest_token_type = TOKEN_TYPE_NUM;
		}

		if (num_matches == 0 || input_pos == input_len - 1) {
			if (latest_token_type != TOKEN_TYPE_UNKNOWN) {
				// add token
				tokens[token_count].type = latest_token_type;
				token_count++;

				// reset buffer
				buf_pos = 0;
				latest_token_type = TOKEN_TYPE_UNKNOWN;

				// push back
				if (num_matches != 0 && input_pos == input_len - 1) {
					continue;
				}
				input_pos--;
				continue;
			} else {
				// error
				printf("error: unknown token '%c'\n", input[input_pos]);
				return RETVAL_ERROR;
			}
		}
	}

	// DEBUG
	printf("Tokens: ");
	for (int i = 0; i < token_count; i++) {
		printf("[%s] ", token_type_name_map[tokens[i].type]);
	}
	printf("\n");

	return RETVAL_OK;
}