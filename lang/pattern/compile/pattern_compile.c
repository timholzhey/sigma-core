//
// Created by tholz on 25.08.2022.
//

#include "pattern_compile.h"
#include "logging.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

retval_t pattern_compile(const char *rule, size_t rule_len, pattern_t *pattern) {
	if (rule == NULL || rule_len == 0 || pattern == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	memset(pattern, 0, sizeof(pattern_t));
	char tok_buf[16];
	int tok_buf_pos = 0;
	bool do_capture = false;
	bool do_eval = false;
	bool do_access_capture = false;
	pattern_node_t *pattern_nodes = pattern->match;
	pattern_node_t replacement_nodes[100];
	int *pattern_node_pos = &pattern->num_match_nodes;
	int replacement_node_pos = 0;
	int capture_index = 0;
	token_type_t *store_type;

	for (int i = 0; i < rule_len; i++) {
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

		store_type = &pattern_nodes[*pattern_node_pos].token_type;
		if (do_eval) {
			store_type = &replacement_nodes[replacement_node_pos].token_type;
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
				tok_buf_pos = 0;
				continue;
			}
			if (rule[i] == ']') {
				pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN;
				pattern_nodes[*pattern_node_pos].replacement = malloc(replacement_node_pos * sizeof(pattern_node_t));
				if (pattern_nodes[*pattern_node_pos].replacement == NULL) {
					log_error("Could not allocate memory for replacement nodes");
					return RETVAL_ERROR;
				}
				memcpy(pattern_nodes[*pattern_node_pos].replacement, replacement_nodes, replacement_node_pos * sizeof(pattern_node_t));
				pattern_nodes[*pattern_node_pos].num_replacement_nodes = replacement_node_pos;
				do_eval = false;
				tok_buf_pos = 0;
				replacement_node_pos = 0;
				(*pattern_node_pos)++;
				i++;
				continue;
			}
		}

		if (do_access_capture) {
			if (rule[i] < '1' || rule[i] > '9') {
				log_error("Illegal capture index %c", rule[i]);
				return RETVAL_ERROR;
			}
			pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_REPLACE_TOKEN;
			pattern_nodes[*pattern_node_pos].capture_idx = rule[i] - '1';
			(*pattern_node_pos)++;
			do_access_capture = false;
			tok_buf_pos = 0;
			continue;
		}

		if ((rule[i] == ',' || rule[i] == ' ' || rule[i] == '>' || (rule[i] == ')' && do_capture)) && tok_buf_pos > 0) {
			pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_MATCH_TOKEN;
			if (memcmp(tok_buf, "MUL", tok_buf_pos) == 0) {
				*store_type = TOKEN_TYPE_OPERATOR_MUL;
			} else if (memcmp(tok_buf, "ADD", tok_buf_pos) == 0) {
				*store_type = TOKEN_TYPE_OPERATOR_ADD;
			} else if (memcmp(tok_buf, "NUM", tok_buf_pos) == 0) {
				*store_type = TOKEN_TYPE_NUM;
			} else if (memcmp(tok_buf, "-", tok_buf_pos) == 0) {
				*store_type = TOKEN_TYPE_NONE;
			} else if (memcmp(tok_buf, "ANY", tok_buf_pos) == 0) {
				*store_type = TOKEN_TYPE_ANY;
			} else {
				log_error("Unrecognized token %.*s", tok_buf_pos, tok_buf);
				return RETVAL_ERROR;
			}
			if (do_capture) {
				pattern_nodes[*pattern_node_pos].capture_idx = capture_index++;
				pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_CAPTURE_TOKEN;
				do_capture = false;
				i++;
			}
			tok_buf_pos = 0;
			if (do_eval) {
				replacement_node_pos++;
				continue;
			}
			(*pattern_node_pos)++;
			continue;
		}

		if (rule[i] == ' ' || rule[i] == '\t') {
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
