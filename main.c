#include <stdio.h>
#include <string.h>
#include "pattern/compile/pattern_compile.h"
#include "sigma.h"

int main() {
	sigma_init();

	const char *func = "x+1.5/sin(x)";
	printf("f(x) =  %s\n", func);

	const char *deriv = derive(func, 'x');
	printf("f'(x) = %s\n", deriv);

	return 0;
}
