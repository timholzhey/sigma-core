//
// Created by Tim Holzhey on 16.08.22.
//

#include "lang_def.h"

const char *token_str_repr_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_NONE] = "",
		[TOKEN_TYPE_ANY] = "",
		[TOKEN_TYPE_ERR] = "",
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
		[TOKEN_TYPE_CONST_E] = "e",
};

const char *token_type_name_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_NONE] = "-",
		[TOKEN_TYPE_ANY] = "ANY",
		[TOKEN_TYPE_ERR] = "ERR",
		[TOKEN_TYPE_OPERATOR_ADD] = "ADD",
		[TOKEN_TYPE_OPERATOR_SUB] = "SUB",
		[TOKEN_TYPE_OPERATOR_MUL] = "MUL",
		[TOKEN_TYPE_OPERATOR_DIV] = "DIV",
		[TOKEN_TYPE_OPERATOR_POW] = "POW",
		[TOKEN_TYPE_OPERATOR_MOD] = "MOD",
		[TOKEN_TYPE_FUNC_SIN] = "SIN",
		[TOKEN_TYPE_FUNC_COS] = "COS",
		[TOKEN_TYPE_FUNC_TAN] = "TAN",
		[TOKEN_TYPE_FUNC_ASIN] = "ASIN",
		[TOKEN_TYPE_FUNC_ACOS] = "ACOS",
		[TOKEN_TYPE_FUNC_ATAN] = "ATAN",
		[TOKEN_TYPE_FUNC_SINH] = "SINH",
		[TOKEN_TYPE_FUNC_COSH] = "COSH",
		[TOKEN_TYPE_FUNC_TANH] = "TANH",
		[TOKEN_TYPE_FUNC_LN] = "LN",
		[TOKEN_TYPE_FUNC_LOG] = "LOG",
		[TOKEN_TYPE_FUNC_SQRT] = "SQRT",
		[TOKEN_TYPE_FUNC_FACT] = "FACT",
		[TOKEN_TYPE_FUNC_ABS] = "ABS",
		[TOKEN_TYPE_PAREN_OPEN] = "PAREN_OPEN",
		[TOKEN_TYPE_PAREN_CLOSE] = "PAREN_CLOSE",
		[TOKEN_TYPE_VAR] = "VAR",
		[TOKEN_TYPE_NUM] = "NUM",
		[TOKEN_TYPE_CONST_E] = "E",
};

const uint32_t token_flags_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_NONE] = TOKEN_FLAG_NONE,
		[TOKEN_TYPE_ANY] = TOKEN_FLAG_NONE,
		[TOKEN_TYPE_ERR] = TOKEN_FLAG_NONE,
		[TOKEN_TYPE_OPERATOR_ADD] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_SUB] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_MUL] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_DIV] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_POW] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_OPERATOR_MOD] = TOKEN_FLAG_INFIX,
		[TOKEN_TYPE_FUNC_SIN] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_COS] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_TAN] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_ASIN] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_ACOS] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_ATAN] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_SINH] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_COSH] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_TANH] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_LN] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_LOG] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_SQRT] = TOKEN_FLAG_PREFIX | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_FUNC_FACT] = TOKEN_FLAG_POSTFIX,
		[TOKEN_TYPE_FUNC_ABS] = TOKEN_FLAG_SURROUND | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_PAREN_OPEN] = TOKEN_FLAG_BEGIN_SCOPE | TOKEN_FLAG_IMPL_MUL_BEFORE,
		[TOKEN_TYPE_PAREN_CLOSE] = TOKEN_FLAG_END_SCOPE | TOKEN_FLAG_IMPL_MUL_AFTER,
		[TOKEN_TYPE_VAR] = TOKEN_FLAG_IMPL_MUL_BEFORE | TOKEN_FLAG_IMPL_MUL_AFTER,
		[TOKEN_TYPE_NUM] = TOKEN_FLAG_IMPL_MUL_AFTER,
		[TOKEN_TYPE_CONST_E] = TOKEN_FLAG_NONE,
};

const uint8_t token_precedence_map[TOKEN_TYPE_COUNT] = {
		[TOKEN_TYPE_NONE] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_ANY] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_ERR] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_OPERATOR_ADD] = 2,
		[TOKEN_TYPE_OPERATOR_SUB] = 2,
		[TOKEN_TYPE_OPERATOR_MUL] = 1,
		[TOKEN_TYPE_OPERATOR_DIV] = 1,
		[TOKEN_TYPE_OPERATOR_POW] = 0,
		[TOKEN_TYPE_OPERATOR_MOD] = 1,
		[TOKEN_TYPE_FUNC_SIN] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_COS] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_TAN] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_ASIN] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_ACOS] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_ATAN] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_SINH] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_COSH] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_TANH] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_LN] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_LOG] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_SQRT] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_FACT] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_FUNC_ABS] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_PAREN_OPEN] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_PAREN_CLOSE] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_VAR] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_NUM] = TOKEN_PRECEDENCE_NONE,
		[TOKEN_TYPE_CONST_E] = TOKEN_PRECEDENCE_NONE,
};
