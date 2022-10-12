#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "logging.h"
#include "math_core.h"
#include "io.h"
#include "sigma_compile.h"

#define INPUT_BUFFER_SIZE		1024
#define OUTPUT_BUFFER_SIZE		(5 * 1024)

#define VERSION_MAJOR			0
#define VERSION_MINOR			1
#define VERSION_PATCH			0

bool g_verbose;

int main(int argc, char **argv) {
	math_core_init();

	char in_buf[INPUT_BUFFER_SIZE];
	char out_buf[OUTPUT_BUFFER_SIZE];

	if (argc > 1) {
		while (*++argv) {
			if (strcmp(*argv, "-v") == 0) {
				g_verbose = true;
			} else if (strcmp(*argv, "--version") == 0) {
				log_info("Sigma algebra engine v%d.%d.%d.", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
				return 0;
			} else if (strcmp(*argv, "-c") == 0) {
					++argv;
					if (!*argv) {
						log_error("Expected input after -c");
						return 1;
					}
					if (sigma_compile(*argv, out_buf, OUTPUT_BUFFER_SIZE) != RETVAL_OK) {
						log_error("Error compiling input");
						return 1;
					}
					printf("%s\n", out_buf);
					return 0;
			} else {
				log_error("Unknown argument: %s", *argv);
				return 1;
			}
		}
	}

	printf("Sigma algebra engine v%d.%d.%d.\n"
		   "Type \"help\" for more information and \"q\" to quit.\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

	while (1) {
		int ret = cli_get_line("> ", in_buf, INPUT_BUFFER_SIZE);
		if (ret != 0) {
			return 1;
		}

		if (strcmp(in_buf, "q") == 0) {
			break;
		}

		if (strcmp(in_buf, "repo") == 0) {
			log_info("https://github.com/timholzhey/sigma-core");
			continue;
		}

		if (strcmp(in_buf, "version") == 0) {
			log_info("Sigma algebra engine v%d.%d.%d.", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
			continue;
		}

		if (strcmp(in_buf, "verbose") == 0) {
			g_verbose = !g_verbose;
			log_info("Verbose mode %s.", g_verbose ? "enabled" : "disabled");
			continue;
		}

		if (strcmp(in_buf, "help") == 0) {
			log_info("%-35sShow this message", "help");
			log_info("%-35sQuit the program", "q");
			log_info("%-35sShow git repository", "repo");
			log_info("%-35sShow version", "version");
			log_info("%-35sToggle verbose mode", "verbose");
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
