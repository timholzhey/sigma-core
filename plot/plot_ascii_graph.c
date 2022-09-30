//
// Created by Tim Holzhey on 27.09.22.
//

#include <string.h>
#include "plot_ascii_graph.h"
#include "math_core.h"
#include "math_lang_def.h"
#include "math_eval_const.h"
#include "testlib.h"

#define GRID_WIDTH		100
#define GRID_HEIGHT		50

#define GRID_X_MIN		(-10.0f)
#define GRID_X_MAX		10.0f
#define GRID_Y_MIN		(-10.0f)
#define GRID_Y_MAX		10.0f

static char grid[GRID_HEIGHT * GRID_WIDTH + 1];

retval_t plot_ascii_graph(const char *input, char **output) {
	ast_node_t ast = {0};

	// clear grid
	memset(grid, ' ', sizeof(grid));

	// insert x axis
	memset(grid + GRID_HEIGHT / 2 * (GRID_WIDTH + 1), '-', GRID_WIDTH);

	// insert y axis
	for (int i = 0; i < GRID_HEIGHT; i++) {
		grid[i * (GRID_WIDTH + 1) + GRID_WIDTH / 2] = '|';
	}

	// insert new lines
	for (int i = 0; i < GRID_HEIGHT; i++) {
		grid[i * (GRID_WIDTH + 1) + GRID_WIDTH] = '\n';
	}

	retval_t ret = math_parse(input, 'x', &ast);

	// Sample function values
	double fx_values[GRID_WIDTH];
	for (int i = 0; i < GRID_WIDTH; i++) {
		float x = GRID_X_MIN + (float)i / (float)GRID_WIDTH * (GRID_X_MAX - GRID_X_MIN);
		fx_values[i] = eval_const_x(&ast, x);
	}

	// fill in dots for function values
	for (int i = 0; i < GRID_WIDTH; i++) {
		float x = GRID_X_MIN + (float)i / (float)GRID_WIDTH * (GRID_X_MAX - GRID_X_MIN);
		float y = fx_values[i];
		int grid_x = i;
		int grid_y = (int)((y - GRID_Y_MIN) / (GRID_Y_MAX - GRID_Y_MIN) * GRID_HEIGHT);
		if (grid_y >= 0 && grid_y < GRID_HEIGHT) {
			grid[(GRID_HEIGHT - grid_y) * (GRID_WIDTH + 1) + grid_x] = '*';
		}
	}

	// null terminate grid
	grid[GRID_HEIGHT * GRID_WIDTH] = '\0';

	// set output to grid
	*output = grid;

	return RETVAL_OK;
}
