//
// Created by tholz on 25.08.2022.
//

#ifndef SIGMA_CORE_PATTERN_COMPILE_H
#define SIGMA_CORE_PATTERN_COMPILE_H

#include "lang_def.h"
#include <stddef.h>
#include "pattern.h"

retval_t pattern_compile(const char *rule, size_t rule_len, pattern_t *pattern);

#endif //SIGMA_CORE_PATTERN_COMPILE_H
