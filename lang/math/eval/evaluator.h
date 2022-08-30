//
// Created by Tim Holzhey on 23.08.22.
//

#ifndef SIGMA_CORE_EVALUATOR_H
#define SIGMA_CORE_EVALUATOR_H

#include "lang_def.h"
#include "sigma.h"
#include "pattern.h"

retval_t lang_eval(ast_node_t *ast_in, ast_node_t *ast_out, sigma_function_t func);

#endif //SIGMA_CORE_EVALUATOR_H
