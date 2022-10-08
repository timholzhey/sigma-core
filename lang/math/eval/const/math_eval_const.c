//
// Created by tholz on 27.08.2022.
//

#include "math_eval_const.h"
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

double eval_const_x(ast_node_t *ast, double x) {
	if (ast == NULL) {
		log_error("AST is NULL");
		return 0.0;
	}

	switch (ast->token.type) {
		case TOKEN_TYPE_OPERATOR_ADD:
			return eval_const_x(ast->left, x) + eval_const_x(ast->right, x);

		case TOKEN_TYPE_OPERATOR_SUB:
			return eval_const_x(ast->left, x) - eval_const_x(ast->right, x);

		case TOKEN_TYPE_OPERATOR_MUL:
			return eval_const_x(ast->left, x) * eval_const_x(ast->right, x);

		case TOKEN_TYPE_OPERATOR_DIV:
			return eval_const_x(ast->left, x) / eval_const_x(ast->right, x);

		case TOKEN_TYPE_OPERATOR_POW:
			return pow(eval_const_x(ast->left, x), eval_const_x(ast->right, x));

		case TOKEN_TYPE_OPERATOR_MOD:
			return fmod(eval_const_x(ast->left, x), eval_const_x(ast->right, x));

		case TOKEN_TYPE_FUNC_SIN:
			return sin(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_COS:
			return cos(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_TAN:
			return tan(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_ASIN:
			return asin(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_ACOS:
			return acos(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_ATAN:
			return atan(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_SINH:
			return sinh(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_COSH:
			return cosh(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_TANH:
			return tanh(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_LN: // Intentional fallthrough
		case TOKEN_TYPE_FUNC_LOG:
			return log(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_SQRT:
			return sqrt(eval_const_x(ast->left, x));

		case TOKEN_TYPE_FUNC_FACT:
			log_error("TOKEN_TYPE_FUNC_FACT const eval not implemented");
			break;

		case TOKEN_TYPE_FUNC_ABS:
			return fabs(eval_const_x(ast->left, x));

		case TOKEN_TYPE_CONST_E:
			return M_E;

		case TOKEN_TYPE_CONST_PI:
			return M_PI;

		case TOKEN_TYPE_VAR:
			return x;

		case TOKEN_TYPE_NUM:
			return ast->token.value.number;

		default:
			break;
	}

	return 0.0;
}

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
			EXPECT_LR_NUMBERS;
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
			ast->token.value.number = pow(ast->left->token.value.number, ast->right->token.value.number);
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

//		case TOKEN_TYPE_CONST_E:
//			ast->token.value.number = M_E;
//			RESULT_NUMBER;
//			break;
//
//		case TOKEN_TYPE_CONST_PI:
//			ast->token.value.number = M_PI;
//			RESULT_NUMBER;
//			break;

		default:
			break;
	}

	return RETVAL_OK;
}
