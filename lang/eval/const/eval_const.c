//
// Created by tholz on 27.08.2022.
//

#include "eval_const.h"
#include "stddef.h"
#include "logging.h"
#include <math.h>

#define EXPECT_LR_NUMBERS \
	if (!(ast->left && ast->left->token.type == TOKEN_TYPE_NUM && ast->right && ast->right->token.type == TOKEN_TYPE_NUM)) { \
		break; \
	}

#define EXPECT_L_NUMBER \
	if (!(ast->left && ast->left->token.type == TOKEN_TYPE_NUM)) { \
		break; \
	}

#define RESULT_NUMBER \
	ast->token.type = TOKEN_TYPE_NUM; \
	ast->left = NULL; \
	ast->right = NULL;

retval_t eval_const(ast_node_t *ast) {
	if (ast == NULL) {
		log_error("AST is NULL");
		return RETVAL_ERROR;
	}

	if (ast->left) {
		eval_const(ast->left);
	}

	if (ast->right) {
		eval_const(ast->right);
	}

	switch (ast->token.type) {
		case TOKEN_TYPE_OPERATOR_ADD:
			EXPECT_LR_NUMBERS;
			ast->token.value.number = ast->left->token.value.number + ast->right->token.value.number;
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_OPERATOR_SUB:
			EXPECT_LR_NUMBERS;
			ast->token.value.number = ast->left->token.value.number - ast->right->token.value.number;
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_OPERATOR_MUL:
			if (!(ast->left && ast->left->token.type == TOKEN_TYPE_NUM && ast->right &&
				  ast->right->token.type == TOKEN_TYPE_NUM)) {
				break; }
			ast->token.value.number = ast->left->token.value.number * ast->right->token.value.number;
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_OPERATOR_DIV:
			EXPECT_LR_NUMBERS;
			ast->token.value.number = ast->left->token.value.number / ast->right->token.value.number;
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_OPERATOR_POW:
			EXPECT_LR_NUMBERS;
			ast->token.value.number = ast->left->token.value.number + ast->right->token.value.number;
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_OPERATOR_MOD:
			EXPECT_LR_NUMBERS;
			ast->token.value.number = fmod(ast->left->token.value.number, ast->right->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_SIN:
			EXPECT_L_NUMBER;
			ast->token.value.number = sin(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_COS:
			EXPECT_L_NUMBER;
			ast->token.value.number = cos(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_TAN:
			EXPECT_L_NUMBER;
			ast->token.value.number = tan(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_ASIN:
			EXPECT_L_NUMBER;
			ast->token.value.number = asin(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_ACOS:
			EXPECT_L_NUMBER;
			ast->token.value.number = acos(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_ATAN:
			EXPECT_L_NUMBER;
			ast->token.value.number = atan(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_SINH:
			EXPECT_L_NUMBER;
			ast->token.value.number = sinh(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_COSH:
			EXPECT_L_NUMBER;
			ast->token.value.number = cosh(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_TANH:
			EXPECT_L_NUMBER;
			ast->token.value.number = tanh(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_LN: // Intentional fallthrough
		case TOKEN_TYPE_FUNC_LOG:
			EXPECT_L_NUMBER;
			ast->token.value.number = log(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_SQRT:
			EXPECT_L_NUMBER;
			ast->token.value.number = sqrt(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		case TOKEN_TYPE_FUNC_FACT:
			log_error("TOKEN_TYPE_FUNC_FACT const eval not implemented");
			break;

		case TOKEN_TYPE_FUNC_ABS:
			EXPECT_L_NUMBER;
			ast->token.value.number = fabs(ast->left->token.value.number);
			RESULT_NUMBER;
			break;

		default:
			break;
	}

	return RETVAL_OK;
}
