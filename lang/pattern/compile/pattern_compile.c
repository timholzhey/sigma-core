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
	bool do_capture = false, do_eval = false, do_access_capture = false, do_match_number = false, was_access_capture = false;
	pattern_node_t *pattern_nodes = pattern->match;
	pattern_node_t replacement_nodes[100];
	int *pattern_node_pos = &pattern->num_match_nodes;
	int replacement_node_pos = 0;
	int capture_index = 0;
	pattern_node_t *store_node;
	int *store_node_pos;

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
			tok_buf_pos = 0;
			i++;
			continue;
		}

		if ((rule[i] == ',' || rule[i] == ' ' || rule[i] == '>' || (rule[i] == ')' && do_capture) ||
			 (rule[i] == '=' && (do_capture || do_eval))) && tok_buf_pos > 0) {
			pattern_nodes[*pattern_node_pos].type = PATTERN_NODE_TYPE_MATCH_TOKEN;

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
				continue;
			}

			if (memcmp(tok_buf, "NUM", tok_buf_pos) == 0) {
				if (do_capture || do_eval) {
					if (rule[i] == '=') {
						do_match_number = true;
					}
				}
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

			tok_buf_pos = 0;
			(*store_node_pos)++;
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
