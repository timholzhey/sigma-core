//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_LANG_DEF_H
#define SIGMA_CORE_LANG_DEF_H

#define TOKEN_MAX_STR_REPR_LENGTH 32

typedef enum {
	TOKEN_TYPE_UNKNOWN,
	TOKEN_TYPE_OPERATOR_ADD,
	TOKEN_TYPE_VAR,
	TOKEN_TYPE_NUM,
	TOKEN_TYPE_COUNT,
} token_type_t;

typedef struct {
	token_type_t type;
} token_t;

typedef enum {
	RETVAL_OK,
	RETVAL_ERROR,
} retval_t;

typedef struct {
	char str_repr[TOKEN_MAX_STR_REPR_LENGTH];
} token_str_repr_t;

extern const char *token_str_repr_map[TOKEN_TYPE_COUNT];

extern const char *token_type_name_map[TOKEN_TYPE_COUNT];

#endif //SIGMA_CORE_LANG_DEF_H
