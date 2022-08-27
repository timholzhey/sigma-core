//
// Created by Tim Holzhey on 26.08.22.
//

#ifndef SIGMA_CORE_PATTERN_MATCH_H
#define SIGMA_CORE_PATTERN_MATCH_H

#include "lang_def.h"
#include "pattern.h"
#include <stdbool.h>

retval_t pattern_match(ast_node_t *ast, pattern_t *pattern, bool *is_match);

#endif //SIGMA_CORE_PATTERN_MATCH_H
