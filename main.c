#include <stdio.h>
#include "sigma.h"

int main() {
	const char *func = "x+1";
	printf("f(x) = %s\n", func);

	const char *deriv = derive(func, 'x');
	printf("f'(x) = %s\n", deriv);

	return 0;
}
