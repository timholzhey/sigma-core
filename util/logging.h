//
// Created by Tim Holzhey on 21.08.22.
//

#ifndef SIGMA_CORE_LOGGING_H
#define SIGMA_CORE_LOGGING_H

#include <stdio.h>

#define LOG_COLOR_RESET		"\033[0m"
#define LOG_COLOR_RED		"\033[31m"
#define LOG_COLOR_ORANGE	"\033[33m"

#define log_internal(color, ...) { \
	printf(color);       \
	printf(__VA_ARGS__);    \
	printf("%s\n", LOG_COLOR_RESET); \
}

#define log_internal_noterm(color, ...) { \
	printf(color);       \
	printf(__VA_ARGS__);    \
	printf("%s", LOG_COLOR_RESET); \
}

#if defined(DEBUG_GLOBAL) && DEBUG_GLOBAL == 1
#define log_debug(...)				if (g_verbose) log_internal(LOG_COLOR_RESET, __VA_ARGS__);
#else
#define log_debug(...)
#endif

#define log_info(...)				log_internal(LOG_COLOR_RESET, __VA_ARGS__);
#define log_error(...)				log_internal(LOG_COLOR_RED, __VA_ARGS__);
#define log_output(...)				log_internal(LOG_COLOR_ORANGE, __VA_ARGS__);

#define log_info_noterm(...)		log_internal_noterm(LOG_COLOR_RESET, __VA_ARGS__);
#define log_error_noterm(...)		log_internal_noterm(LOG_COLOR_RED, __VA_ARGS__);
#define log_output_noterm(...)		log_internal_noterm(LOG_COLOR_ORANGE, __VA_ARGS__);

#endif //SIGMA_CORE_LOGGING_H
