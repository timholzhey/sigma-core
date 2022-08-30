//
// Created by Tim Holzhey on 26.08.22.
//

#include "pattern_match.h"
#include "logging.h"

static bool is_node_function(ast_node_t *node) {
	if (node->token.type == TOKEN_TYPE_VAR) {
		return true;
	}
	if (node->left && is_node_function(node->left)) {
		return true;
	}
	if (node->right && is_node_function(node->right)) {
		return true;
	}
	return false;
}

static bool pattern_match_node(ast_node_t *ast, pattern_node_t *pattern_node, int node_idx, int num_nodes) {
	if (ast == NULL) {
		if (pattern_node[node_idx].token_type == TOKEN_TYPE_NONE) {
			return true;
		}
		return false;
	}

	if (num_nodes > node_idx && (ast->token.type != pattern_node[node_idx].token_type &&
								 pattern_node[node_idx].token_type != TOKEN_TYPE_ANY &&
								 pattern_node[node_idx].token_type != TOKEN_TYPE_FUNC &&
								 pattern_node[node_idx].is_inverted == 0) ||
		(pattern_node[node_idx].has_number == 1 && ast->token.value.number != pattern_node[node_idx].number) ||
		(pattern_node[node_idx].token_type == TOKEN_TYPE_FUNC && !is_node_function(ast)) ||
		(pattern_node[node_idx].is_inverted == 1 && ast->token.type == pattern_node[node_idx].token_type)) {
		return false;
	}

	if (num_nodes > 2 * node_idx + 1 && !pattern_match_node(ast->left, pattern_node, 2 * node_idx + 1, num_nodes)) {
		return false;
	}

	if (num_nodes > 2 * node_idx + 2 && !pattern_match_node(ast->right, pattern_node, 2 * node_idx + 2, num_nodes)) {
		return false;
	}

	return true;
}

retval_t pattern_match(ast_node_t *ast, pattern_t *pattern, bool *is_match) {
	if (ast == NULL || pattern == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	*is_match = pattern_match_node(ast, pattern->match, 0, pattern->num_match_nodes);
	return RETVAL_OK;
}
