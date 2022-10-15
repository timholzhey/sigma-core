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
#include "math_core.h"
#include "math_eval_const.h"
#include "pattern_compile.h"
#include "pattern_generate.h"

static pattern_t *applied_pattern;

retval_t pattern_apply(ast_node_t *ast, pattern_t *pattern, bool *applied) {
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

	log_debug_noterm("Applying Transform %s: ", pattern->name);
	debug_print_ast(ast);
	log_debug_noterm(" -> ");

	ast_node_t ast_out;
	if (pattern_replace(ast, pattern, &ast_out) != RETVAL_OK) {
		log_error("Pattern replacing failed")
		return RETVAL_ERROR;
	}

	memcpy(ast, &ast_out, sizeof(ast_node_t));

	debug_print_ast(ast);
	log_debug_noterm("\n");

	if (eval_const(ast) != RETVAL_OK) {
		log_error("Constant evaluation failed");
		return RETVAL_ERROR;
	}

	*applied = true;

	return RETVAL_OK;
}

retval_t pattern_registry_apply_all(ast_node_t *ast, pattern_registry_t *registry, bool *applied, bool *propagate) {
	for (int i = 0; i < registry->num_patterns; i++) {
		if (registry->patterns[i].do_propagate && *propagate) {
			continue;
		}
		if (pattern_apply(ast, &registry->patterns[i], applied) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
		if (*applied) {
			applied_pattern = &registry->patterns[i];
			*propagate |= registry->patterns[i].do_propagate;
			return RETVAL_OK;
		}
	}

	return RETVAL_OK;
}

pattern_t *pattern_get_applied() {
	return applied_pattern;
}

retval_t pattern_registry_add_rule(pattern_registry_t *registry, const char *name, const char *rule) {
	if (registry == NULL || name == NULL || rule == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	uint32_t name_len = strlen(name);
	uint32_t registry_name_len = strlen(registry->name);

	if (registry_name_len + 1 + name_len> MAX_PATTERN_NAME_LEN) {
		log_error("Pattern name too large");
		return RETVAL_ERROR;
	}

	if (registry->num_patterns + 1 > MAX_NUM_PATTERNS_REGISTRY) {
		log_error("Cannot add pattern to registry: Maximum patterns in registry exceeded!");
		return RETVAL_ERROR;
	}

	if (pattern_compile(rule, strlen(rule), &registry->patterns[registry->num_patterns]) != RETVAL_OK) {
		log_error("Cannot add pattern to registry: Compilation failed!")
		return RETVAL_ERROR;
	}

	memcpy(registry->patterns[registry->num_patterns].name, registry->name, registry_name_len);
	memcpy(registry->patterns[registry->num_patterns].name + registry_name_len, "_", 1);
	memcpy(registry->patterns[registry->num_patterns].name + registry_name_len + 1, name, strlen(name));

	if (!pattern_compile_is_permutation_allowed()) {
		registry->num_patterns++;
		return RETVAL_OK;
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
