//
// Created by tholz on 30.08.2022.
//

#include "io.h"
#include <stdio.h>
#include <string.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

int cli_get_line(char *prompt, char *buff, size_t sz) {
	int ch, extra;

	if (prompt != NULL) {
		printf("%s", prompt);
		fflush(stdout);
	}
	if (fgets(buff, sz, stdin) == NULL)
		return NO_INPUT;

	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}

	buff[strlen(buff) - 1] = '\0';
	return OK;
}
