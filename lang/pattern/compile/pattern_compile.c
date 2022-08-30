//
// Created by tholz on 25.08.2022.
//

#include "pattern_compile.h"
#include "logging.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

static bool allow_permutation = false;

retval_t pattern_compile(const char *rule, size_t rule_len, pattern_t *pattern) {
	if (rule == NULL || rule_len == 0 || pattern == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	memset(pattern, 0, sizeof(pattern_t));
	char tok_buf[50];
	int tok_buf_pos = 0;
	bool do_capture = false, do_eval = false, do_access_capture = false, do_match_number = false, was_access_capture = false, do_error = false, do_invert = false;
	pattern_node_t *pattern_nodes = pattern->match;
	pattern_node_t replacement_nodes[100];
	int *pattern_node_pos = &pattern->num_match_nodes;
	int replacement_node_pos = 0;
	int capture_index = 0;
	pattern_node_t *store_node;
	int *store_node_pos;
	allow_permutation = true;

	for (int i = 0; i < rule_len; i++) {
		if (rule[i] == '~') {
			allow_permutation = false;
			tok_buf_pos = 0;
			continue;
		}

		if (rule[i] == '@') {
			pattern->do_propagate = 1;
		}

		if (rule[i] == '(' && !do_capture && !do_eval) {
			do_capture = true;
			tok_buf_pos = 0;
			continue;
		}

		if (rule[i] == '[' && !do_eval) {
			do_eval = true;
			tok_buf_pos = 0;
			continue;
		}

		if (rule[i] == '$') {
			do_access_capture = true;
			tok_buf_pos = 0;
			continue;
		}

		if (rule[i] == '!') {
			do_invert = true;
			tok_buf_pos = 0;
			continue;
		}

		store_node = &pattern_nodes[*pattern_node_pos];
		store_node_pos = pattern_node_pos;

		if (do_eval) {
			store_node = &replacement_nodes[replacement_node_pos];
			store_node_pos = &replacement_node_pos;

			replacement_nodes[replacement_node_pos].type = PATTERN_NODE_TYPE_MATCH_TOKEN;
			if (do_access_capture) {
				if (rule[i] < '1' || rule[i] > '9') {
					log_error("Illegal capture index %c", rule[i]);
					return RETVAL_ERROR;
				}
				replacement_nodes[replacement_node_pos].capture_idx = rule[i] - '1';
				replacement_nodes[replacement_node_pos].type = PATTERN_NODE_TYPE_REPLACE_TOKEN;
				replacement_node_pos++;
				do_access_capture = false;
				was_access_capture = true;
				tok_buf_pos = 0;
				continue;
			}
			if (rule[i] == ']') {
				if (do_match_number) {
					do_match_number = false;
					store_node->type = PATTERN_NODE_TYPE_MATCH_TOKEN;
					store_node->has_number = 1;
					store_node->is_inverted = do_invert;
					tok_buf[tok_buf_pos] = '\0';
					store_node->number = strtod(tok_buf, NULL);

					if (do_capture) {
						store_node->capture_idx = capture_index++;
						store_node->type = PATTERN_NODE_TYPE_CAPTURE_TOKEN;
						do_capture = false;
					}

					tok_buf_pos = 0;
					(*store_node_pos)++;
				}

				pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN;
				pattern_nodes[*pattern_node_pos].replacement = malloc(replacement_node_pos * sizeof(pattern_node_t));
				if (pattern_nodes[*pattern_node_pos].replacement == NULL) {
					log_error("Could not allocate memory for replacement nodes");
					return RETVAL_ERROR;
				}
				memcpy(pattern_nodes[*pattern_node_pos].replacement, replacement_nodes, replacement_node_pos * sizeof(pattern_node_t));
				pattern_nodes[*pattern_node_pos].num_replacement_nodes = replacement_node_pos;
				do_eval = false;
				do_invert = false;
				tok_buf_pos = 0;
				replacement_node_pos = 0;
				(*pattern_node_pos)++;
				i++;
				continue;
			}

			if (was_access_capture) {
				was_access_capture = false;
				tok_buf_pos = 0;
				continue;
			}
		}

		if (do_access_capture) {
			if (rule[i] < '1' || rule[i] > '9') {
				log_error("Illegal capture index %c", rule[i]);
				return RETVAL_ERROR;
			}
			store_node->type = PATTERN_NODE_TYPE_REPLACE_TOKEN;
			store_node->capture_idx = rule[i] - '1';
			(*store_node_pos)++;
			do_access_capture = false;
			do_invert = false;
			tok_buf_pos = 0;
			i++;
			continue;
		}

		if ((rule[i] == ',' || (rule[i] == ' ' && !do_error) || rule[i] == '>' || rule[i] == ':' || (rule[i] == ')' && do_capture) ||
			 (rule[i] == '=' && (do_capture || do_eval)) || i == rule_len - 1) && tok_buf_pos > 0) {
			pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_MATCH_TOKEN;
			store_node->is_inverted = do_invert;

			if (do_match_number) {
				do_match_number = false;
				store_node->type = PATTERN_NODE_TYPE_MATCH_TOKEN;
				store_node->has_number = 1;
				tok_buf[tok_buf_pos] = '\0';
				store_node->number = strtod(tok_buf, NULL);

				if (do_capture) {
					store_node->capture_idx = capture_index++;
					store_node->type = PATTERN_NODE_TYPE_CAPTURE_TOKEN;
					do_capture = false;
				}

				tok_buf_pos = 0;
				(*store_node_pos)++;
				i++;
				continue;
			}

			if (memcmp(tok_buf, "NUM", tok_buf_pos) == 0) {
				if (do_capture || do_eval) {
					if (rule[i] == '=') {
						do_match_number = true;
					}
				}
			}

			if (do_error) {
				do_error = false;
				tok_buf[tok_buf_pos++] = rule[i];
				store_node->type = PATTERN_NODE_TYPE_REPLACE_ERROR;
				store_node->token_type = TOKEN_TYPE_ERR;
				store_node->error_desc = malloc(tok_buf_pos + 1);
				if (store_node->error_desc == NULL) {
					log_error("Could not allocate memory for error description");
					return RETVAL_ERROR;
				}
				const char *err = "Error: ";
				uint32_t err_len = strlen(err);
				memcpy(store_node->error_desc, err, err_len);
				memcpy(store_node->error_desc + err_len, tok_buf, tok_buf_pos);
				store_node->error_desc[tok_buf_pos + err_len + 1] = '\0';
				store_node->error_desc_len = tok_buf_pos + err_len;
				(*store_node_pos)++;

				tok_buf_pos = 0;
				continue;
			}

			if (memcmp(tok_buf, "ERR", tok_buf_pos) == 0) {
				do_error = true;
				tok_buf_pos = 0;
				continue;
			}

			bool match_token = false;
			for (int j = 0; j < TOKEN_TYPE_COUNT; j++) {
				if (memcmp(tok_buf, token_type_name_map[j], tok_buf_pos) == 0) {
					store_node->token_type = j;
					match_token = true;
					break;
				}
			}

			if (!match_token) {
				log_error("Unrecognized token \"%.*s\" at %u in \"%s\"", tok_buf_pos, tok_buf, i, rule);
				return RETVAL_ERROR;
			}

			if (do_match_number) {
				tok_buf_pos = 0;
				continue;
			}

			if (do_capture) {
				pattern_nodes[*pattern_node_pos].capture_idx = capture_index++;
				pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_CAPTURE_TOKEN;
				do_capture = false;
				i++;
			}

			do_invert = false;
			tok_buf_pos = 0;
			(*store_node_pos)++;
			continue;
		}

		if ((rule[i] == ' ' && (!do_error || tok_buf_pos == 0)) || rule[i] == '\t') {
			tok_buf_pos = 0;
			continue;
		}

		if (rule[i] == '>') {
			pattern_nodes = pattern->replace;
			pattern_node_pos = &pattern->num_replace_nodes;
			tok_buf_pos = 0;
			continue;
		}

		tok_buf[tok_buf_pos++] = rule[i];
	}

	return RETVAL_OK;
}

bool pattern_compile_is_permutation_allowed() {
	return allow_permutation;
}
