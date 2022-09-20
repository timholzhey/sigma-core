#include <stdio.h>
#include <string.h>
#include "math_core.h"
#include "io.h"
#include "sigma_compile.h"

int main(int argc, char **argv) {
	math_core_init();

	char buff[255];

	if (argc > 1) {
		char output[256];
		sigma_compile(argv[1], output, 256);
		printf("%s\n", output);
		return 0;
	}

	while (1) {
		int ret = cli_get_line("Input function to derive in respect to x\nf(x) = ", buff, sizeof(buff));
		if (ret != 0) {
			return 1;
		}

		if (strcmp(buff, "exit") == 0 || strcmp(buff, "q") == 0) {
			break;
		}

		printf("f'(x) = %s\n\n", derive(buff, 'x'));
	}

	return 0;
}
