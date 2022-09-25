//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_MATH_LANG_DEF_H
#define SIGMA_CORE_MATH_LANG_DEF_H

#include <stdint.h>

#define TOKEN_MAX_STR_REPR_LENGTH	32
#define TOKEN_MAX_STR_IDENT_LENGTH	32

typedef enum {
	TOKEN_TYPE_NONE,
	TOKEN_TYPE_ANY,
	TOKEN_TYPE_ERR,
	TOKEN_TYPE_FUNC,
	TOKEN_TYPE_OPERATOR_ADD,
	TOKEN_TYPE_OPERATOR_SUB,
	TOKEN_TYPE_OPERATOR_MUL,
	TOKEN_TYPE_OPERATOR_DIV,
	TOKEN_TYPE_OPERATOR_POW,
	TOKEN_TYPE_OPERATOR_MOD,
	TOKEN_TYPE_FUNC_SIN,
	TOKEN_TYPE_FUNC_COS,
	TOKEN_TYPE_FUNC_TAN,
	TOKEN_TYPE_FUNC_ASIN,
	TOKEN_TYPE_FUNC_ACOS,
	TOKEN_TYPE_FUNC_ATAN,
	TOKEN_TYPE_FUNC_SINH,
	TOKEN_TYPE_FUNC_COSH,
	TOKEN_TYPE_FUNC_TANH,
	TOKEN_TYPE_FUNC_LN,
	TOKEN_TYPE_FUNC_LOG,
	TOKEN_TYPE_FUNC_SQRT,
	TOKEN_TYPE_FUNC_FACT,
	TOKEN_TYPE_FUNC_ABS,
	TOKEN_TYPE_PAREN_OPEN,
	TOKEN_TYPE_PAREN_CLOSE,
	TOKEN_TYPE_VAR,
	TOKEN_TYPE_NUM,
	TOKEN_TYPE_CONST_E,
	TOKEN_TYPE_COUNT,
} token_type_t;

typedef struct {
	double number;
	char identifier[TOKEN_MAX_STR_IDENT_LENGTH];
	uint8_t identifier_len;
} token_value_t;

typedef enum {
	TOKEN_VALUE_TYPE_NONE,
	TOKEN_VALUE_TYPE_NUMBER,
	TOKEN_VALUE_TYPE_IDENTIFIER,
} token_value_type_t;

typedef struct {
	token_type_t type;
	token_value_t value;
	token_value_type_t value_type;
} token_t;

typedef enum {
	RETVAL_OK,
	RETVAL_ERROR,
	RETVAL_COUNT,
} retval_t;

#define TOKEN_FLAG_NONE					0x00
#define TOKEN_FLAG_PREFIX				0x01
#define TOKEN_FLAG_INFIX				0x02
#define TOKEN_FLAG_POSTFIX				0x04
#define TOKEN_FLAG_SURROUND				0x08
#define TOKEN_FLAG_BEGIN_SCOPE			0x10
#define TOKEN_FLAG_END_SCOPE			0x20
#define TOKEN_FLAG_IMPL_MUL_BEFORE		0x40
#define TOKEN_FLAG_IMPL_MUL_AFTER		0x80

#define TOKEN_PRECEDENCE_NONE	0xFF
#define MAX_TOKEN_PRECEDENCE	2

extern const char *token_str_repr_map[TOKEN_TYPE_COUNT];
extern const char *token_type_name_map[TOKEN_TYPE_COUNT];
extern const uint32_t token_flags_map[TOKEN_TYPE_COUNT];
extern const uint8_t token_precedence_map[TOKEN_TYPE_COUNT];

struct ast_node_t {
	struct ast_node_t *left;
	struct ast_node_t *right;
	token_t token;
};
typedef struct ast_node_t ast_node_t;

ast_node_t *ast_get_node_by_index(ast_node_t *root, uint32_t index);

#endif //SIGMA_CORE_MATH_LANG_DEF_H
