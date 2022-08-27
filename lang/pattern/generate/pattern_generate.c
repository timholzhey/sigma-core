//
// Created by tholz on 27.08.2022.
//

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pattern_generate.h"
#include "logging.h"

static retval_t pattern_generate_permutations(pattern_t *pattern_in, pattern_t *patterns_out, int *num_patterns, int max_num_patterns, int node_idx) {
	int num_nodes = pattern_in->num_match_nodes;

	if (num_nodes > 2 * node_idx + 1) {
		pattern_generate_permutations(pattern_in, patterns_out, num_patterns, max_num_patterns, 2 * node_idx + 1);
	}

	if (num_nodes > 2 * node_idx + 2) {
		pattern_generate_permutations(pattern_in, patterns_out, num_patterns, max_num_patterns, 2 * node_idx + 2);
	}

	if (num_nodes > 2 * node_idx + 2) {
		if (*num_patterns + 1 > max_num_patterns || *num_patterns + 1 > MAX_NUM_PATTERN_PERMUTATIONS) {
			log_error("Insufficient space in pattern output");
			return RETVAL_ERROR;
		}

		pattern_t *new_pattern = &patterns_out[*num_patterns];
		if (new_pattern == NULL) {
			log_error("Could not allocate memory for pattern");
			return RETVAL_ERROR;
		}

		memcpy(new_pattern, pattern_in, sizeof(pattern_t));

		pattern_node_t temp[MAX_NUM_MATCH_NODES] = {0};
		int subtree_len = 1;
		for (int i = 2 * node_idx + 1; i < num_nodes; i += subtree_len) {
			int left_idx = i;
			int right_idx = i + subtree_len;
			if (right_idx >= num_nodes) {
				break;
			}
			memcpy(temp, &new_pattern->match[left_idx], subtree_len * sizeof(pattern_node_t));
			memcpy(&new_pattern->match[left_idx], &new_pattern->match[right_idx], subtree_len * sizeof(pattern_node_t));
			memcpy(&new_pattern->match[right_idx], temp, subtree_len * sizeof(pattern_node_t));
			subtree_len *= 2;
		}

		(*num_patterns)++;

		if (num_nodes > 2 * node_idx + 2) {
			pattern_generate_permutations(new_pattern, patterns_out, num_patterns, max_num_patterns, 2 * node_idx + 1);
			pattern_generate_permutations(new_pattern, patterns_out, num_patterns, max_num_patterns, 2 * node_idx + 2);
		}
	}

	return RETVAL_OK;
}

static void pattern_cleanup_permutations(pattern_t *patterns, int *num_patterns) {
	pattern_t temp[MAX_NUM_PATTERN_PERMUTATIONS];
	int temp_idx = 0;

	for (int i = 0; i < *num_patterns; i++) {
		bool is_unique = true;
		for (int j = i + 1; j < *num_patterns; j++) {
			bool is_match = true;
			for (int k = 0; k < patterns[i].num_match_nodes; k++) {
				if (patterns[i].match[k].token_type != patterns[j].match[k].token_type) {
					is_match = false;
					break;
				}
			}
			if (is_match) {
				is_unique = false;
				break;
			}
		}
		if (is_unique) {
			temp[temp_idx++] = patterns[i];
		}
	}

	*num_patterns = temp_idx;
	memcpy(patterns, temp, temp_idx * sizeof(pattern_t));
}

retval_t pattern_generate(pattern_t *pattern_in, pattern_t *patterns_out, int *num_patterns, int max_num_patterns) {
	if (pattern_generate_permutations(pattern_in, patterns_out, num_patterns, max_num_patterns, 0) != RETVAL_OK) {
		log_error("Pattern permutation failed");
		return RETVAL_ERROR;
	}

	pattern_cleanup_permutations(patterns_out, num_patterns);

	return RETVAL_OK;
}
