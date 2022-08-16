//
// Created by Tim Holzhey on 16.08.22.
//

#include "lang_def.h"

const char *token_str_repr_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_UNKNOWN] = "",
		[TOKEN_TYPE_OPERATOR_ADD] = "+",
		[TOKEN_TYPE_VAR] = "",
		[TOKEN_TYPE_NUM] = "",
};

const char *token_type_name_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_UNKNOWN] = "UNKNOWN",
		[TOKEN_TYPE_OPERATOR_ADD] = "OP_ADD",
		[TOKEN_TYPE_VAR] = "VAR",
		[TOKEN_TYPE_NUM] = "NUM",
};