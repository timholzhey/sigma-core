//
// Created by tholz on 27.08.2022.
//

#ifndef SIGMA_CORE_MATH_EVAL_CONST_H
#define SIGMA_CORE_MATH_EVAL_CONST_H

#include "math_lang_def.h"

retval_t eval_const(ast_node_t *ast);

double eval_const_x(ast_node_t *ast, double x);

#endif //SIGMA_CORE_MATH_EVAL_CONST_H
