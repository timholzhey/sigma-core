#include <stdio.h>
#include <string.h>
#include "logging.h"
#include "math_core.h"
#include "io.h"
#include "sigma_compile.h"

#define INPUT_BUFFER_SIZE		1024
#define OUTPUT_BUFFER_SIZE		1024

int main(int argc, char **argv) {
	math_core_init();

	char in_buf[INPUT_BUFFER_SIZE];
	char out_buf[OUTPUT_BUFFER_SIZE];

	if (argc > 1) {
		sigma_compile(argv[1], out_buf, OUTPUT_BUFFER_SIZE);
		printf("%s\n", out_buf);
		return 0;
	}

	printf("Sigma algebra engine v0.0.1.\n"
		   "Type \"help\" for more information and \"q\" to quit.\n");

	while (1) {
		int ret = cli_get_line("> ", in_buf, INPUT_BUFFER_SIZE);
		if (ret != 0) {
			return 1;
		}

		if (strcmp(in_buf, "q") == 0) {
			break;
		}

		if (strcmp(in_buf, "help") == 0) {
			log_info("%-35sShow this message", "help");
			log_info("%-35sQuit the program", "q");
			log_info("%-35sDerive a function (short: '<function>)", "derive[<function>(,<variable>)]");
			log_info("%-35sEvaluate a constant expression (short: <function>)\n", "const[<function>]");
			continue;
		}

		if (sigma_compile(in_buf, out_buf, OUTPUT_BUFFER_SIZE) == RETVAL_OK) {
			log_output("%s", out_buf);
		}
	}

	return 0;
}
