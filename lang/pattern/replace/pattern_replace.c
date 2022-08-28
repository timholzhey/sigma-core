//
// Created by Tim Holzhey on 26.08.22.
//

#include "pattern_replace.h"
#include "pattern_capture.h"
#include "logging.h"
#include <stdlib.h>
#include <string.h>

static retval_t pattern_replace_node(pattern_node_t *pattern_nodes, int node_idx, int num_nodes,
									 ast_node_t **capture_nodes, int num_capture_groups, ast_node_t *ast) {
	if (ast == NULL) {
		log_error("AST is NULL");
		return RETVAL_ERROR;
	}

	pattern_node_t *node = &pattern_nodes[node_idx];
	switch (node->type) {
		case PATTERN_NODE_TYPE_MATCH_TOKEN:
			ast->token.type = node->token_type;
			ast->left = NULL;
			ast->right = NULL;

			if (node->has_number == 1) {
				ast->token.value_type = TOKEN_VALUE_TYPE_NUMBER;
				ast->token.value.number = node->number;
			}
			break;

		case PATTERN_NODE_TYPE_REPLACE_TOKEN: {
			int capture_idx = node->capture_idx;
			if (capture_idx < 0 || capture_idx >= num_capture_groups) {
				log_error("Invalid capture group replacement index");
				return RETVAL_ERROR;
			}

			memcpy(ast, capture_nodes[capture_idx], sizeof(ast_node_t));
		}
		break;

		case PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN:
			if (node->num_replacement_nodes == 0) {
				log_error("Cannot replace with no nodes provided");
				return RETVAL_ERROR;
			}
			if (pattern_replace_node(node->replacement, 0,
									 node->num_replacement_nodes, capture_nodes, num_capture_groups,
									 ast) != RETVAL_OK) {
				log_error("Failed to build replacement node");
				return RETVAL_ERROR;
			}
			break;

		default:
			log_error("Unhandled pattern node type %u", node->type);
			return RETVAL_ERROR;
	}

	if (num_nodes > 2 * node_idx + 1) {
		ast->left = malloc(sizeof(ast_node_t));
		if (ast->left == NULL) {
			log_error("Could not allocate memory for AST node");
			return RETVAL_ERROR;
		}
		if (pattern_replace_node(pattern_nodes, 2 * node_idx + 1, num_nodes, capture_nodes, num_capture_groups,
								 ast->left) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (num_nodes > 2 * node_idx + 2) {
		ast->right = malloc(sizeof(ast_node_t));
		if (ast->right == NULL) {
			log_error("Could not allocate memory for AST node");
			return RETVAL_ERROR;
		}
		if (pattern_replace_node(pattern_nodes, 2 * node_idx + 2, num_nodes, capture_nodes, num_capture_groups,
								 ast->right) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	return RETVAL_OK;
}

retval_t pattern_replace(ast_node_t *ast_in, pattern_t *pattern, ast_node_t *ast_out) {
	if (ast_in == NULL || pattern == NULL || ast_out == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	ast_node_t *capture_groups[10];
	int num_capture_groups = 0;

	if (pattern_capture(ast_in, pattern, capture_groups, &num_capture_groups) != RETVAL_OK) {
		log_error("Failed to build capture groups");
		return RETVAL_ERROR;
	}

	if (pattern_replace_node(pattern->replace, 0, pattern->num_replace_nodes, capture_groups, num_capture_groups,
							 ast_out) != RETVAL_OK) {
		log_error("Failed to build replacement AST");
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}
