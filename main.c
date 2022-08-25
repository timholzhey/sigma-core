#include <stdio.h>
#include <string.h>
#include "pattern_compile.h"
#include "sigma.h"

int main() {
	const char *func = "x+1.5/sin(x)";
	printf("f(x) =  %s\n", func);

	const char *deriv = derive(func, 'x');
	printf("f'(x) = %s\n", deriv);

	const char *rule = "MUL,(NUM),MUL,-,-,(NUM),(ANY) > MUL,[MUL,$1,$2],$3";
	pattern_t pattern;
	pattern_compile_rule(rule, strlen(rule), &pattern);

	return 0;
}
