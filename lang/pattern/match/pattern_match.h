//
// Created by Tim Holzhey on 26.08.22.
//

#ifndef SIGMA_CORE_PATTERN_MATCH_H
#define SIGMA_CORE_PATTERN_MATCH_H

#include "lang_def.h"
#include "pattern/compile/pattern_compile.h"
#include <stdbool.h>

bool pattern_match(ast_node_t *ast, pattern_t *pattern);

#endif //SIGMA_CORE_PATTERN_MATCH_H
