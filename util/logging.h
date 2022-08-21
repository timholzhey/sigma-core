//
// Created by Tim Holzhey on 21.08.22.
//

#ifndef SIGMA_CORE_LOGGING_H
#define SIGMA_CORE_LOGGING_H

#include <stdio.h>

#define LOG_COLOR_RESET		"\033[0m"
#define LOG_COLOR_RED		"\033[31m"

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

#define log_error(...)				log_internal(LOG_COLOR_RED, __VA_ARGS__);
#define log_error_noterm(...)		log_internal_noterm(LOG_COLOR_RED, __VA_ARGS__);

#endif //SIGMA_CORE_LOGGING_H
