//
// Created by tholz on 27.08.2022.
//

#ifndef SIGMA_CORE_PATTERN_H
#define SIGMA_CORE_PATTERN_H

#include <stdbool.h>
#include "math_lang_def.h"

#define MAX_NUM_CAPTURE_GROUPS		9
#define MAX_NUM_MATCH_NODES			100
#define MAX_NUM_REPLACE_NODES		100
#define MAX_NUM_PATTERNS_REGISTRY	100
#define MAX_PATTERN_NAME_LEN		50
#define MAX_NUM_PROPAGATION_INDICES	10

typedef enum {
	PATTERN_NODE_TYPE_MATCH_TOKEN,
	PATTERN_NODE_TYPE_CAPTURE_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_ERROR,
} pattern_node_type_t;

struct pattern_node_t {
	token_type_t token_type;
	uint8_t capture_idx;
	struct pattern_node_t *replacement;
	uint8_t num_replacement_nodes;
	pattern_node_type_t type;
	uint8_t has_number:1;
	uint8_t is_inverted:1;
	uint8_t is_same:1;
	uint8_t is_negative:1;
	int equal_idx;
	char *error_desc;
	uint8_t error_desc_len;
	double number;
};
typedef struct pattern_node_t pattern_node_t;

typedef struct {
	pattern_node_t match[MAX_NUM_MATCH_NODES];
	pattern_node_t replace[MAX_NUM_REPLACE_NODES];
	uint8_t num_match_nodes;
	uint8_t num_replace_nodes;
	uint8_t num_propagation_indices;
	uint8_t propagation_indices[MAX_NUM_PROPAGATION_INDICES];
	char name[MAX_PATTERN_NAME_LEN];
	uint8_t do_propagate:1;
} pattern_t;

typedef struct {
	pattern_t patterns[MAX_NUM_PATTERNS_REGISTRY];
	int num_patterns;
	const char *name;
} pattern_registry_t;

retval_t pattern_apply(ast_node_t *ast, pattern_t *pattern, bool *applied);

retval_t pattern_registry_apply_all(ast_node_t *ast, pattern_registry_t *registry, bool *applied, bool *propagate);

pattern_t *pattern_get_applied();

retval_t pattern_registry_add_rule(pattern_registry_t *registry, const char *name, const char *rule);

#endif //SIGMA_CORE_PATTERN_H
