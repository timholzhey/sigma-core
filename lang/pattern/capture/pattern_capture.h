//
// Created by tholz on 27.08.2022.
//

#ifndef SIGMA_CORE_PATTERN_CAPTURE_H
#define SIGMA_CORE_PATTERN_CAPTURE_H

#include "math_lang_def.h"
#include "pattern.h"

retval_t pattern_capture(ast_node_t *ast, pattern_t *pattern, ast_node_t **capture_nodes, int *num_capture_groups);

#endif //SIGMA_CORE_PATTERN_CAPTURE_H
