//
// Created by tholz on 28.08.2022.
//

#ifndef SIGMA_CORE_MATH_EVAL_TRANSFORM_H
#define SIGMA_CORE_MATH_EVAL_TRANSFORM_H

#include "math_lang_def.h"
#include "pattern.h"

retval_t eval_transform_node(ast_node_t *ast, pattern_registry_t *registry);

retval_t eval_transform_function_node(ast_node_t *ast, pattern_registry_t *registry, bool allow_propagation);

#endif //SIGMA_CORE_MATH_EVAL_TRANSFORM_H
