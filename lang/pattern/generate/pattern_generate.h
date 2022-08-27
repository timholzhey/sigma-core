//
// Created by tholz on 27.08.2022.
//

#ifndef SIGMA_CORE_PATTERN_GENERATE_H
#define SIGMA_CORE_PATTERN_GENERATE_H

#include "lang_def.h"
#include "pattern.h"

#define MAX_NUM_PATTERN_PERMUTATIONS	100

retval_t pattern_generate(pattern_t *pattern_in, pattern_t *patterns_out, int *num_patterns, int max_num_patterns);

#endif //SIGMA_CORE_PATTERN_GENERATE_H
