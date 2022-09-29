//
// Created by Tim Holzhey on 27.09.22.
//

#ifndef SIGMA_CORE_SIGMA_H
#define SIGMA_CORE_SIGMA_H

#include <stdbool.h>

extern bool g_verbose;

typedef enum {
	RETVAL_OK,
	RETVAL_ERROR,
	RETVAL_COUNT,
} retval_t;

#endif //SIGMA_CORE_SIGMA_H
