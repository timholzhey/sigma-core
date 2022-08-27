//
// Created by tholz on 27.08.2022.
//

#ifndef SIGMA_CORE_PATTERN_H
#define SIGMA_CORE_PATTERN_H

#include "lang_def.h"

#define MAX_NUM_CAPTURE_GROUPS		9
#define MAX_NUM_MATCH_NODES			100
#define MAX_NUM_REPLACE_NODES		100
#define MAX_NUM_PATTERNS_REGISTRY	100

typedef enum {
	PATTERN_NODE_TYPE_MATCH_TOKEN,
	PATTERN_NODE_TYPE_CAPTURE_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN,
} pattern_node_type_t;

struct pattern_node_t {
	token_type_t token_type;
	int capture_idx;
	struct pattern_node_t *replacement;
	int num_replacement_nodes;
	pattern_node_type_t type;
};
typedef struct pattern_node_t pattern_node_t;

typedef struct {
	pattern_node_t match[MAX_NUM_MATCH_NODES];
	pattern_node_t replace[MAX_NUM_REPLACE_NODES];
	int num_match_nodes;
	int num_replace_nodes;
} pattern_t;

typedef struct {
	pattern_t patterns[MAX_NUM_PATTERNS_REGISTRY];
	int num_patterns;
} pattern_registry_t;

retval_t pattern_apply(ast_node_t *ast, pattern_t *pattern);

retval_t pattern_registry_apply_all(ast_node_t *ast, pattern_registry_t *registry);

retval_t pattern_registry_add_rule(pattern_registry_t *registry, const char *rule);

#endif //SIGMA_CORE_PATTERN_H
