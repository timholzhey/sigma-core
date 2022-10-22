//
// Created by tholz on 22.10.2022.
//

#ifndef SIGMA_CORE_FUNC_INTEGRATE_H
#define SIGMA_CORE_FUNC_INTEGRATE_H

#include "math_lang_def.h"

void func_integrate_init();

retval_t func_integrate(ast_node_t *ast_in, ast_node_t *ast_out);

#endif //SIGMA_CORE_FUNC_INTEGRATE_H
