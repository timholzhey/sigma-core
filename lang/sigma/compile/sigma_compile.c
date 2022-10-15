//
// Created by Tim Holzhey on 20.09.22.
//

#include <string.h>
#include <stdbool.h>
#include "sigma_compile.h"
#include "math_core.h"
#include "sigma_lang_def.h"
#include "logging.h"

#define SIGMA_ERROR_AT(x) \
	log_info("%s", input);        \
	log_info_noterm("%*s", x - 1, ""); \
	log_info_noterm("^\n");     \

retval_t sigma_compile(const char *input, char *output, int output_length) {
	int buf_pos = 0;
	char buf[256];
	int input_pos = 0;
	uint32_t input_len = strlen(input);
	math_function_t math_function_stack[256];
	int math_function_stack_size = 0;
	int paren_stack_size = 0;
	char paren_stack[256];
	bool do_begin_scope = false;
	bool do_end_scope = false;
	bool is_shorthand = false;
	bool has_second_arg = false;
	char second_arg = 'x';
	int output_pos = 0;

	while (input[input_pos] != '\0') {
		buf[buf_pos++] = input[input_pos++];

		if (buf[buf_pos - 1] == ',') {
			if (has_second_arg) {
				SIGMA_ERROR_AT(input_pos);
				log_error("Unexpected ',' in expression");
				return RETVAL_ERROR;
			}
			has_second_arg = true;
			if (output_pos == 0) {
				if (buf_pos > output_length) {
					log_error("InternalError: Output buffer too small");
					return RETVAL_ERROR;
				}
				memcpy(output, buf, buf_pos - 1);
				output[buf_pos - 1] = '\0';
				output_pos = buf_pos;
				buf_pos = 0;
			}
		}

		if (buf[buf_pos - 1] == '[') {
			paren_stack[paren_stack_size++] = '[';
		} else if (buf[buf_pos - 1] == ']') {
			if (has_second_arg) {
				second_arg = buf[0];
			} else {
				second_arg = 'x';
			}
			if (output_pos == 0) {
				if (buf_pos > output_length) {
					log_error("InternalError: Output buffer too small");
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
			if (!is_shorthand) {
				if (buf[0] != '[') {
					SIGMA_ERROR_AT(input_pos);
					log_error("SigmaError: Expected '[' when beginning a scope");
					return RETVAL_ERROR;
				}
				buf_pos = 0;
				continue;
			}
		}

		if (is_shorthand && input_pos == input_len) {
			do_end_scope = true;
			memcpy(output, buf, buf_pos);
			output[buf_pos] = '\0';
			output_pos = buf_pos;
		}

		for (int i = 0; i < MATH_FUNCTION_COUNT; i++) {
			if (strncmp(buf, math_function_str_repr_map[i], buf_pos) == 0) {
				if (math_function_str_repr_map[i][buf_pos] == '\0') {
					buf_pos = 0;
					do_begin_scope = true;
					math_function_stack[math_function_stack_size++] = i;
					break;
				}
			}
		}

		for (int i = 0; i < MATH_FUNCTION_COUNT; i++) {
			if (strncmp(buf, math_function_shorthand_str_repr_map[i], buf_pos) == 0) {
				if (math_function_shorthand_str_repr_map[i][buf_pos] == '\0') {
					buf_pos = 0;
					do_begin_scope = true;
					is_shorthand = true;
					math_function_stack[math_function_stack_size++] = i;
					break;
				}
			}
		}

		if (do_end_scope) {
			do_end_scope = false;
			buf_pos = 0;
			while (math_function_stack_size > 0) {
				math_function_stack_size--;
				const char *result = math_function(output, second_arg, math_function_stack[math_function_stack_size]);
				if (strncmp(result, "ERR", 3) == 0) {
					return RETVAL_ERROR;
				}
				uint32_t result_len = strlen(result);
				if (result_len > output_length) {
					log_error("InternalError: Output buffer too small");
					return RETVAL_ERROR;
				}
				memcpy(output, result, result_len);
				output[result_len] = '\0';

				if (!is_shorthand) {
					break;
				}
			}
			continue;
		}
	}

	if (buf_pos != 0) {
		const char *result = math_function(input, second_arg, MATH_FUNCTION_CONST);
		if (strncmp(result, "ERR", 3) == 0) {
			return RETVAL_ERROR;
		}
		uint32_t result_len = strlen(result);
		if (result_len > output_length) {
			log_error("InternalError: Output buffer too small");
			return RETVAL_ERROR;
		}
		memcpy(output, result, result_len);
		output[result_len] = '\0';
	}

	return RETVAL_OK;
}
