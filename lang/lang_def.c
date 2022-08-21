//
// Created by Tim Holzhey on 16.08.22.
//

#include "lang_def.h"

const char *token_str_repr_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_UNKNOWN] = "",
		[TOKEN_TYPE_OPERATOR_ADD] = "+",
		[TOKEN_TYPE_OPERATOR_SUB] = "-",
		[TOKEN_TYPE_OPERATOR_MUL] = "*",
		[TOKEN_TYPE_OPERATOR_DIV] = "/",
		[TOKEN_TYPE_OPERATOR_POW] = "^",
		[TOKEN_TYPE_OPERATOR_MOD] = "%",
		[TOKEN_TYPE_FUNC_SIN] = "sin",
		[TOKEN_TYPE_FUNC_COS] = "cos",
		[TOKEN_TYPE_FUNC_TAN] = "tan",
		[TOKEN_TYPE_FUNC_ASIN] = "asin",
		[TOKEN_TYPE_FUNC_ACOS] = "acos",
		[TOKEN_TYPE_FUNC_ATAN] = "atan",
		[TOKEN_TYPE_FUNC_SINH] = "sinh",
		[TOKEN_TYPE_FUNC_COSH] = "cosh",
		[TOKEN_TYPE_FUNC_TANH] = "tanh",
		[TOKEN_TYPE_FUNC_LN] = "ln",
		[TOKEN_TYPE_FUNC_LOG] = "log",
		[TOKEN_TYPE_FUNC_SQRT] = "sqrt",
		[TOKEN_TYPE_FUNC_FACT] = "!",
		[TOKEN_TYPE_FUNC_ABS] = "|",
		[TOKEN_TYPE_PAREN_OPEN] = "(",
		[TOKEN_TYPE_PAREN_CLOSE] = ")",
		[TOKEN_TYPE_VAR] = "",
		[TOKEN_TYPE_NUM] = "",
};

const uint32_t token_flags_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_UNKNOWN] = TOKEN_FLAG_NONE,
		[TOKEN_TYPE_OPERATOR_ADD] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_SUB] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_MUL] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_DIV] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_POW] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_MOD] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_FUNC_SIN] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_COS] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_TAN] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_ASIN] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_ACOS] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_ATAN] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_SINH] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_COSH] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_TANH] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_LN] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_LOG] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_SQRT] = TOKEN_FLAG_PREFIX,
		[TOKEN_TYPE_FUNC_FACT] = TOKEN_FLAG_SUFFIX,
		[TOKEN_TYPE_FUNC_ABS] = TOKEN_FLAG_SURROUND,
		[TOKEN_TYPE_PAREN_OPEN] = TOKEN_FLAG_BEGIN_SCOPE,
		[TOKEN_TYPE_PAREN_CLOSE] = TOKEN_FLAG_END_SCOPE,
		[TOKEN_TYPE_VAR] = TOKEN_FLAG_NONE,
		[TOKEN_TYPE_NUM] = TOKEN_FLAG_NONE,
};

const char *token_type_name_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_UNKNOWN] = "UNKNOWN",
		[TOKEN_TYPE_OPERATOR_ADD] = "OP_ADD",
		[TOKEN_TYPE_OPERATOR_SUB] = "OP_SUB",
		[TOKEN_TYPE_OPERATOR_MUL] = "OP_MUL",
		[TOKEN_TYPE_OPERATOR_DIV] = "OP_DIV",
		[TOKEN_TYPE_OPERATOR_POW] = "OP_POW",
		[TOKEN_TYPE_OPERATOR_MOD] = "OP_MOD",
		[TOKEN_TYPE_FUNC_SIN] = "FUNC_SIN",
		[TOKEN_TYPE_FUNC_COS] = "FUNC_COS",
		[TOKEN_TYPE_FUNC_TAN] = "FUNC_TAN",
		[TOKEN_TYPE_FUNC_ASIN] = "FUNC_ASIN",
		[TOKEN_TYPE_FUNC_ACOS] = "FUNC_ACOS",
		[TOKEN_TYPE_FUNC_ATAN] = "FUNC_ATAN",
		[TOKEN_TYPE_FUNC_SINH] = "FUNC_SINH",
		[TOKEN_TYPE_FUNC_COSH] = "FUNC_COSH",
		[TOKEN_TYPE_FUNC_TANH] = "FUNC_TANH",
		[TOKEN_TYPE_FUNC_LN] = "FUNC_LN",
		[TOKEN_TYPE_FUNC_LOG] = "FUNC_LOG",
		[TOKEN_TYPE_FUNC_SQRT] = "FUNC_SQRT",
		[TOKEN_TYPE_FUNC_FACT] = "FUNC_FACT",
		[TOKEN_TYPE_FUNC_ABS] = "FUNC_ABS",
		[TOKEN_TYPE_PAREN_OPEN] = "PAREN_OPEN",
		[TOKEN_TYPE_PAREN_CLOSE] = "PAREN_CLOSE",
		[TOKEN_TYPE_VAR] = "VAR",
		[TOKEN_TYPE_NUM] = "NUM",
};