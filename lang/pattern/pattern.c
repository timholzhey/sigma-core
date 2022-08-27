//
// Created by tholz on 27.08.2022.
//

#include "pattern.h"
#include <stdbool.h>
#include "pattern_match.h"
#include "pattern_replace.h"
#include "logging.h"
#include <stddef.h>
#include <string.h>
#include <eval_const.h>
#include <pattern_compile.h>
#include <pattern_generate.h>

retval_t pattern_apply(ast_node_t *ast, pattern_t *pattern) {
	if (ast == NULL || pattern == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	bool match = false;
	if (pattern_match(ast, pattern, &match) != RETVAL_OK) {
		log_error("Pattern matching failed");
		return RETVAL_ERROR;
	}

	if (!match) {
		return RETVAL_OK;
	}

	ast_node_t ast_out;
	if (pattern_replace(ast, pattern, &ast_out) != RETVAL_OK) {
		log_error("Pattern replacing failed")
		return RETVAL_ERROR;
	}

	memcpy(ast, &ast_out, sizeof(ast_node_t));

	if (eval_const(ast) != RETVAL_OK) {
		log_error("Constant evaluation failed");
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

retval_t pattern_registry_apply_all(ast_node_t *ast, pattern_registry_t *registry) {
	for (int i = 0; i < registry->num_patterns; i++) {
		if (pattern_apply(ast, &registry->patterns[i]) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	return RETVAL_OK;
}

retval_t pattern_registry_add_rule(pattern_registry_t *registry, const char *rule) {
	if (registry->num_patterns + 1 > MAX_NUM_PATTERNS_REGISTRY) {
		log_error("Cannot add pattern to registry: Maximum patterns in registry exceeded!");
		return RETVAL_ERROR;
	}

	if (pattern_compile(rule, strlen(rule), &registry->patterns[registry->num_patterns]) != RETVAL_OK) {
		log_error("Cannot add pattern to registry: Compilation failed!")
		return RETVAL_ERROR;
	}

	pattern_t patterns[100];
	int num_patterns = 0;
	if (pattern_generate(&registry->patterns[registry->num_patterns], patterns, &num_patterns, 100) != RETVAL_OK) {
		log_error("Cannot add pattern to registry: Generation failed!");
		return RETVAL_ERROR;
	}

	registry->num_patterns++;

	memcpy(&registry->patterns[registry->num_patterns], patterns, num_patterns * sizeof(pattern_t));
	registry->num_patterns += num_patterns;

	return RETVAL_OK;
}
