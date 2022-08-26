//
// Created by Tim Holzhey on 26.08.22.
//

#include "pattern_replace.h"
#include "logging.h"

static retval_t pattern_replace_node(ast_node_t *ast, pattern_node_t *pattern_nodes, int node_idx, int num_nodes) {
	if (ast == NULL) {
		return RETVAL_ERROR;
	}

	switch (pattern_nodes[node_idx].type) {
		case PATTERN_NODE_TYPE_REPLACE_TOKEN:
			ast->token.type = pattern_nodes[node_idx].token_type;
			break;

		case PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN:
			pattern_eval_node(ast, pattern_nodes[node_idx].capture_replacement, pattern_nodes[node_idx].num_capture_replacements);
			break;

		default:
			log_error("Unknown pattern node type %u", pattern_nodes[node_idx].type);
			return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

void pattern_get_capture_groups(ast_node_t *ast, pattern_node_t *pattern_nodes) {

}

retval_t pattern_replace(ast_node_t *ast, pattern_t *pattern) {
	ast_node_t capture_groups[10];
	pattern_get_capture_groups(ast, pattern->match, capture_groups);
	return pattern_replace_node(ast, pattern->replace, 0, pattern->num_replace_nodes);
}
