//
// Created by Tim Holzhey on 23.08.22.
//

#ifndef SIGMA_CORE_PREPROCESS_H
#define SIGMA_CORE_PREPROCESS_H

#include "lang_def.h"

retval_t lang_preprocess(token_t *tokens_in, int num_tokens_in, token_t *tokens_out, int *num_tokens_out, int max_num_tokens_out);

typedef enum {
	PREPROCESSOR_ERROR_OK,
	PREPROCESSOR_ERROR_INSUFFICIENT_SPACE,
} preprocessor_error_t;

preprocessor_error_t preprocessor_errno();

#endif //SIGMA_CORE_PREPROCESS_H
