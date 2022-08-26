//
// Created by tholz on 25.08.2022.
//

#ifndef SIGMA_CORE_PATTERN_COMPILE_H
#define SIGMA_CORE_PATTERN_COMPILE_H

#include "lang_def.h"
#include <stddef.h>

typedef enum {
	PATTERN_NODE_TYPE_MATCH_TOKEN,
	PATTERN_NODE_TYPE_CAPTURE_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_TOKEN,
	PATTERN_NODE_TYPE_REPLACE_EVAL_TOKEN,
} pattern_node_type_t;

typedef struct {
	token_type_t token_type;
	int replace_idx;
} pattern_replacement_node_t;

typedef struct {
	token_type_t token_type;
	int capture_idx;
	pattern_replacement_node_t *capture_replacement;
	int num_capture_replacements;
	pattern_node_type_t type;
} pattern_node_t;

typedef struct {
	pattern_node_t match[100];
	pattern_node_t replace[100];
	int num_match_nodes;
	int num_replace_nodes;
} pattern_t;

retval_t pattern_compile_rule(const char *rule, size_t rule_len, pattern_t *pattern);

#endif //SIGMA_CORE_PATTERN_COMPILE_H
