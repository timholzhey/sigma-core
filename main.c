#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include "logging.h"
#include "math_core.h"
#include "io.h"
#include "sigma_compile.h"

#define INPUT_BUFFER_SIZE		1024
#define OUTPUT_BUFFER_SIZE		(5 * 1024)

#define VERSION_MAJOR			0
#define VERSION_MINOR			1
#define VERSION_PATCH			0

#define PATH_TO_REPO			"PATH_TO_REPO"

static void print_usage() {
	log_info("Sigma algebra engine v%d.%d.%d.\n",
			 VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
	log_info("Usage: sigma [options]");
	log_info("Options:");
	log_info("%-20sVerbose output", "   -v");
	log_info("%-20sPrint version", "   --version");
	log_info("%-20sCompile input", "   -c <input>");
	log_info("%-20sPrint this help", "   -h");
	log_info("%-20sBuild from source", "   --build");
}

int main(int argc, char **argv) {
	struct timeval tv;
	gettimeofday(&tv,NULL);
	uint32_t time_at_start = 1000000 * tv.tv_sec + tv.tv_usec;

	math_core_init();

	gettimeofday(&tv,NULL);
	uint32_t time_after_boot = 1000000 * tv.tv_sec + tv.tv_usec;
	float boot_up_time_ms = (float) (time_after_boot - time_at_start) / 1000.0f;

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
				log_info("%s", out_buf);
				return 0;
			} else if (strcmp(*argv, "-h") == 0) {
				print_usage();
				return 0;
			} if (strcmp(*argv, "--build") == 0) {
				char cmd[1024];
				sprintf(cmd, "cmake --build %s/cmake-build-debug --target sigma_core -j 6", PATH_TO_REPO);
				log_info("%s", cmd);
				system(cmd);
				return 0;
			} else {
				log_error("Unknown argument: %s", *argv);
				print_usage();
				return 1;
			}
		}
	}

	log_info("Sigma algebra engine v%d.%d.%d. (%.2f ms)\n"
		   "Type \"help\" for more information and \"q\" to quit.",
		   VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, boot_up_time_ms);

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
			log_info("%-40sShow this message", "help");
			log_info("%-40sQuit the program", "q");
			log_info("%-40sShow git repository", "repo");
			log_info("%-40sShow version", "version");
			log_info("%-40sToggle verbose mode", "verbose");
			log_info("%-40s------------", "------------");
			log_info("%-40sDerive a function (short: der <function>)", "func_derive[<function>(,<variable>)]");
			log_info("%-40sIntegrate a function (short: int <function>)", "func_integrate[<function>(,<variable>)]");
			log_info("%-40sEvaluate a constant expression (short: <function>)\n", "func_const[<function>]");
			continue;
		}

		if (sigma_compile(in_buf, out_buf, OUTPUT_BUFFER_SIZE) == RETVAL_OK) {
			log_output("%s", out_buf);
		}
	}

	return 0;
}
