//
// Created by tholz on 27.08.2022.
//

#include "pattern_capture.h"
#include "stddef.h"
#include "logging.h"

static retval_t pattern_capture_node(ast_node_t *ast, pattern_node_t *pattern_node, int num_pattern_nodes, int node_idx,
								 ast_node_t **capture_nodes, int *num_capture_groups) {
	if (ast == NULL) {
		return RETVAL_ERROR;
	}

	if (pattern_node[node_idx].type == PATTERN_NODE_TYPE_CAPTURE_TOKEN) {
		int capture_idx = pattern_node[node_idx].capture_idx;
		if (capture_idx < 0 || capture_idx >= MAX_NUM_CAPTURE_GROUPS) {
			log_error("Capture index %u is out of range", capture_idx);
			return RETVAL_ERROR;
		}
		capture_nodes[capture_idx] = ast;
		(*num_capture_groups)++;
	}

	if (num_pattern_nodes > 2 * node_idx + 1 && ast->left) {
		if (pattern_capture_node(ast->left, pattern_node, num_pattern_nodes, 2 * node_idx + 1, capture_nodes, num_capture_groups) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (num_pattern_nodes > 2 * node_idx + 2 && ast->right) {
		if (pattern_capture_node(ast->right, pattern_node, num_pattern_nodes, 2 * node_idx + 2, capture_nodes, num_capture_groups) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	return RETVAL_OK;
}

retval_t pattern_capture(ast_node_t *ast, pattern_t *pattern, ast_node_t **capture_nodes, int *num_capture_groups) {
	if (ast == NULL || pattern == NULL || capture_nodes == NULL || num_capture_groups == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	return pattern_capture_node(ast, pattern->match, pattern->num_match_nodes, 0, capture_nodes, num_capture_groups);
}
