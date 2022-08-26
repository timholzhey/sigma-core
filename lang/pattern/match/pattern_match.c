//
// Created by Tim Holzhey on 26.08.22.
//

#include "pattern_match.h"
#include "logging.h"

static bool pattern_match_node(ast_node_t *ast, pattern_node_t *pattern_node, int node_idx, int num_nodes) {
	if (ast == NULL && pattern_node[node_idx].token_type != TOKEN_TYPE_NONE) {
		return false;
	}
	if (num_nodes > node_idx && ast->token.type != pattern_node[node_idx].token_type && pattern_node[node_idx].token_type != TOKEN_TYPE_ANY) {
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

bool pattern_match(ast_node_t *ast, pattern_t *pattern) {
	return pattern_match_node(ast, pattern->match, 0, pattern->num_match_nodes);
}
