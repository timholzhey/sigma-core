#include <stdio.h>
#include <string.h>
#include "sigma.h"
#include "io.h"

int main(int argc, char *argv[]) {
	sigma_init();

	if (argc > 1) {
		printf("%s", derive(argv[1], 'x'));
		return 0;
	}

	char buff[255];

	while (1) {
		int ret = cli_get_line("Input function to derive in respect to x\nf(x) = ", buff, sizeof(buff));
		if (ret != 0) {
			return 1;
		}

		if (strcmp(buff, "exit") == 0) {
			break;
		}

		printf("f'(x) = %s\n\n", derive(buff, 'x'));
	}

	return 0;
}
