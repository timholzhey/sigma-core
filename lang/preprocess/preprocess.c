//
// Created by Tim Holzhey on 23.08.22.
//

#include <printf.h>
#include <string.h>
#include <stdbool.h>
#include "preprocess.h"
#include "logging.h"

static token_t tokens_temp[1000];
static preprocessor_error_t error;

#define PREPROCESSOR_FAIL_WITH_MSG(...) { \
	log_error_noterm("Preprocessor failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

retval_t preprocessor_process(token_t *tokens_in, int num_tokens_in, token_t *tokens_out, int *num_tokens_out, int max_num_tokens_out) {
	error = PREPROCESSOR_ERROR_OK;

	if (num_tokens_in > max_num_tokens_out) {
		error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
		PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
	}

	// Copy tokens from in to out
	memcpy(tokens_out, tokens_in, num_tokens_in * sizeof(token_t));
	*num_tokens_out = num_tokens_in;

	// Expand unary operators: leading plus or minus
	bool begin_scope = true;
	for (int i = 0; i < *num_tokens_out; i++) {
		if (tokens_out[i].type == TOKEN_TYPE_PAREN_OPEN) {
			begin_scope = true;
			continue;
		}
		if (begin_scope && (tokens_out[i].type == TOKEN_TYPE_OPERATOR_ADD || tokens_out[i].type == TOKEN_TYPE_OPERATOR_SUB)) {
			// Insert zero before leading operator
			int k = 0;
			for (int j = 0; j < *num_tokens_out; j++, k++) {
				if (j == i) {
					tokens_temp[k].type = TOKEN_TYPE_NUM;
					tokens_temp[k].value_type = TOKEN_VALUE_TYPE_NUMBER;
					tokens_temp[k].value.number = 0;
					k++;
				}
				tokens_temp[k] = tokens_out[j];
			}
			*num_tokens_out = k;
			if (*num_tokens_out > max_num_tokens_out) {
				error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
				PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
			}
			i++;

			// Copy back from temp
			memcpy(tokens_out, tokens_temp, *num_tokens_out * sizeof(token_t));
		}
		begin_scope = false;
	}

	// Truncate consecutive negative signs
	uint8_t consec_neg_count = 0;
	for (int i = 0; i < *num_tokens_out; i++) {
		if (tokens_out[i].type == TOKEN_TYPE_OPERATOR_SUB) {
			consec_neg_count++;
			continue;
		}
		if (consec_neg_count > 1) {
			if (consec_neg_count % 2 == 0) {
				tokens_out[i - consec_neg_count].type = TOKEN_TYPE_OPERATOR_ADD;
			} else {
				tokens_out[i - consec_neg_count].type = TOKEN_TYPE_OPERATOR_SUB;
			}
			for (int j = i; j < *num_tokens_out; j++) {
				tokens_out[j - consec_neg_count + 1] = tokens_out[j];
			}
			*num_tokens_out -= consec_neg_count - 1;
			i -= consec_neg_count - 1;
		}
		consec_neg_count = 0;
	}

	// Insert parenthesis based on operator precedence
	for (int prec = 0; prec < MAX_TOKEN_PRECEDENCE; prec++) {
		// Find operator of that precedence level
		for (int i = 0; i < *num_tokens_out; i++) {
			if (token_precedence_map[tokens_out[i].type] == prec) {
				// Find boundaries left and right
				int left_bound = 0;
				for (int j = i; j > 0; j--) {
					if (token_precedence_map[tokens_out[j].type] > prec && token_precedence_map[tokens_out[j].type] != TOKEN_PRECEDENCE_NONE) {
						left_bound = j + 1;
						break;
					}
				}

				int right_bound = *num_tokens_out - 1;
				for (int j = i; j < *num_tokens_out; j++) {
					if (token_precedence_map[tokens_out[j].type] > prec && token_precedence_map[tokens_out[j].type] != TOKEN_PRECEDENCE_NONE) {
						right_bound = j - 1;
						break;
					}
				}

				// Insert parenthesis before left bound and after right bound into temp
				int k = 0;
				for (int j = 0; j < *num_tokens_out; j++, k++) {
					if (j == left_bound) {
						tokens_temp[k++].type = TOKEN_TYPE_PAREN_OPEN;
					}
					tokens_temp[k] = tokens_out[j];
					if (j == right_bound) {
						tokens_temp[++k].type = TOKEN_TYPE_PAREN_CLOSE;
					}
				}
				*num_tokens_out = k;
				if (*num_tokens_out > max_num_tokens_out) {
					error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
					PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
				}
				i += 2;

				// Copy back from temp
				memcpy(tokens_out, tokens_temp, *num_tokens_out * sizeof(token_t));
			}
		}
	}

	return RETVAL_OK;
}

preprocessor_error_t preprocessor_errno() {
	return error;
}
