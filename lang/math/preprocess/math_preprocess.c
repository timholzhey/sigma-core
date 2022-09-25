//
// Created by Tim Holzhey on 23.08.22.
//

#include <string.h>
#include <stdbool.h>
#include "math_preprocess.h"
#include "logging.h"

static token_t tokens_temp[1000];
static preprocessor_error_t error;

#define PREPROCESSOR_FAIL_WITH_MSG(...) { \
	log_error_noterm("Preprocessor failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

retval_t lang_preprocess(token_t *tokens_in, int num_tokens_in, token_t *tokens_out, int *num_tokens_out, int max_num_tokens_out) {
	error = PREPROCESSOR_ERROR_OK;

	if (num_tokens_in > max_num_tokens_out) {
		error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
		PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
	}

	// Copy tokens from in to out
	memcpy(tokens_out, tokens_in, num_tokens_in * sizeof(token_t));
	*num_tokens_out = num_tokens_in;

	// Check for unmatched parentheses
	token_type_t paren_stack[100];
	int paren_stack_size = 0;
	for (int i = 0; i < num_tokens_in; i++) {
		if (tokens_out[i].type == TOKEN_TYPE_PAREN_OPEN) {
			paren_stack[paren_stack_size++] = TOKEN_TYPE_PAREN_OPEN;
		} else if (tokens_out[i].type == TOKEN_TYPE_PAREN_CLOSE) {
			if (paren_stack_size == 0) {
				error = PREPROCESSOR_ERROR_UNMATCHED_PARENTHESES;
				PREPROCESSOR_FAIL_WITH_MSG("Unmatched parentheses");
			}
			paren_stack_size--;
		}
	}
	if (paren_stack_size > 0) {
		error = PREPROCESSOR_ERROR_UNMATCHED_PARENTHESES;
		PREPROCESSOR_FAIL_WITH_MSG("Unmatched parentheses");
	}

	// Expand unary operators: leading plus or minus
	bool begin_scope = true;
	for (int i = 0; i < *num_tokens_out; i++) {
		if (tokens_out[i].type == TOKEN_TYPE_PAREN_OPEN) {
			begin_scope = true;
			continue;
		}
		if (begin_scope && (tokens_out[i].type == TOKEN_TYPE_OPERATOR_ADD || tokens_out[i].type == TOKEN_TYPE_OPERATOR_SUB)) {
			// Insert zero before leading operator
			if (*num_tokens_out + 1 > max_num_tokens_out) {
				error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
				PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
			}
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
			i++;

			// Copy back from temp
			memcpy(tokens_out, tokens_temp, *num_tokens_out * sizeof(token_t));
		}
		begin_scope = false;
	}

	// Truncate consecutive negative signs
	uint8_t consec_neg_count = 0;
	for (int i = 0; i < *num_tokens_out; i++) {
		// Accumulate negative signs
		if (tokens_out[i].type == TOKEN_TYPE_OPERATOR_SUB) {
			consec_neg_count++;
			continue;
		}
		// Truncate
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

	// Insert implicit multiplication operator
	for (int i = 1; i < *num_tokens_out; i++) {
		// Find matching pair
		if (token_flags_map[tokens_out[i].type] & TOKEN_FLAG_IMPL_MUL_BEFORE &&
			token_flags_map[tokens_out[i - 1].type] & TOKEN_FLAG_IMPL_MUL_AFTER &&
			!(token_flags_map[tokens_out[i].type] & TOKEN_FLAG_SURROUND &&
			  (token_flags_map[tokens_out[i - 1].type] & TOKEN_FLAG_SURROUND) == 0)) {
			if (*num_tokens_out + 1 > max_num_tokens_out) {
				error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
				PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
			}

			for (int j = *num_tokens_out - 1; j >= i; j--) {
				tokens_out[j + 1] = tokens_out[j];
			}

			// Insert mult operator
			tokens_out[i].type = TOKEN_TYPE_OPERATOR_MUL;

			(*num_tokens_out)++;
			i++;
		}
	}

	// Insert parenthesis based on operator precedence
	for (int prec = 0; prec < MAX_TOKEN_PRECEDENCE; prec++) {
		// Find operator of that precedence level
		for (int i = 0; i < *num_tokens_out; i++) {
			if (token_precedence_map[tokens_out[i].type] == prec) {
				// Find boundaries left and right
				int left_bound = 0;
				for (int j = i; j > 0; j--) {
					if (tokens_out[j].type == TOKEN_TYPE_PAREN_CLOSE) {
						break;
					}
					if (token_precedence_map[tokens_out[j].type] > prec && token_precedence_map[tokens_out[j].type] != TOKEN_PRECEDENCE_NONE) {
						left_bound = j + 1;
						break;
					}
				}

				int right_bound = *num_tokens_out - 1;
				for (int j = i; j < *num_tokens_out; j++) {
					if (tokens_out[j].type == TOKEN_TYPE_PAREN_OPEN) {
						break;
					}
					if (token_precedence_map[tokens_out[j].type] > prec && token_precedence_map[tokens_out[j].type] != TOKEN_PRECEDENCE_NONE) {
						right_bound = j - 1;
						break;
					}
				}

				// Check if wrapping is necessary
				if (left_bound == 0 && right_bound == *num_tokens_out - 1) {
					continue;
				}

				// Insert parenthesis before left bound and after right bound into temp
				if (*num_tokens_out + 2 > max_num_tokens_out) {
					error = PREPROCESSOR_ERROR_INSUFFICIENT_SPACE;
					PREPROCESSOR_FAIL_WITH_MSG("Not enough space in token output");
				}
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
