//
// Created by Tim Holzhey on 20.09.22.
//

#include <string.h>
#include <printf.h>
#include <stdbool.h>
#include "sigma_compile.h"
#include "math_core.h"
#include "sigma_lang_def.h"
#include "logging.h"

typedef enum {
	SIGMA_CONTEXT_ANY,
	SIGMA_CONTEXT_SIGMA,
	SIGMA_CONTEXT_MATH,
} sigma_context_t;

retval_t sigma_compile(const char *input, char *output, int output_length) {
	int buf_pos = 0;
	char buf[256];
	int input_pos = 0;
	sigma_context_t context = SIGMA_CONTEXT_SIGMA;
	math_function_t math_function_stack[256];
	int math_function_stack_size = 0;
	int paren_stack_size = 0;
	char paren_stack[256];
	bool do_begin_scope = false;
	bool do_end_scope = false;
	int output_pos = 0;

	while (input[input_pos] != '\0') {
		buf[buf_pos++] = input[input_pos++];

		if (buf[buf_pos - 1] == '(') {
			paren_stack[paren_stack_size++] = '(';
		} else if (buf[buf_pos - 1] == ')') {
			if (output_pos == 0) {
				if (buf_pos > output_length) {
					log_error("Output buffer too small");
					return RETVAL_ERROR;
				}
				memcpy(output, buf, buf_pos - 1);
				output[buf_pos - 1] = '\0';
				output_pos = buf_pos;
			}
			paren_stack_size--;
			do_end_scope = true;
		}

		if (do_begin_scope) {
			do_begin_scope = false;
			if (buf[0] != '(') {
				log_error("Expected '(' when switching to new context");
				return RETVAL_ERROR;
			}
			buf_pos = 0;
			continue;
		}

		for (int i = 0; i < MATH_FUNCTION_COUNT; i++) {
			if (strncmp(buf, math_function_str_repr_map[i], buf_pos) == 0) {
				if (math_function_str_repr_map[i][buf_pos] == '\0') {
					buf_pos = 0;
					do_begin_scope = true;
					context = SIGMA_CONTEXT_ANY;
					math_function_stack[math_function_stack_size++] = i;
					break;
				}
			}
		}

		if (do_end_scope) {
			do_end_scope = false;
			buf_pos = 0;
			context = SIGMA_CONTEXT_SIGMA;
			math_function_stack_size--;
			const char *result = math_function(output, 'x', math_function_stack[math_function_stack_size]);
			int result_len = strlen(result);
			if (result_len > output_length) {
				log_error("Output buffer too small");
				return RETVAL_ERROR;
			}
			memcpy(output, result, result_len);
			output[result_len] = '\0';
			continue;
		}
	}

	return RETVAL_OK;
}
