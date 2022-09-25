//
// Created by Tim Holzhey on 26.08.22.
//

#ifndef SIGMA_CORE_PATTERN_REPLACE_H
#define SIGMA_CORE_PATTERN_REPLACE_H

#include "math_lang_def.h"
#include "pattern.h"

retval_t pattern_replace(ast_node_t *ast_in, pattern_t *pattern, ast_node_t *ast_out);

#endif //SIGMA_CORE_PATTERN_REPLACE_H
