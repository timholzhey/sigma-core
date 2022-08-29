#include <stdio.h>
#include "sigma.h"
#include "io.h"

int main() {
	sigma_init();

	char buff[255];

	while (1) {
		int ret = cli_get_line("Input function to derive in respect to x\nf(x) = ", buff, sizeof(buff));
		if (ret != 0) {
			return 1;
		}

		printf("f'(x) = %s\n\n", derive(buff, 'x'));
	}

	return 0;
}
