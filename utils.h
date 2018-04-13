/* Tema1 SO,Bucur Ionut-Cristian,333CA
 */

#ifndef UTILS_H_
#define UTILS_H_	1

#define MAX_COMMAND_SIZE 20000

#define DEFAULT_OUTPUT stdout
#define DEFAULT_OUTPUT_MODE "a"

#define ERROR_FILE_OPEN "Can't open file"
#define ERROR_SIZE "Size must be a number"
#define ERROR_FILE_WRITE "Can't write file"
#define DEFAULT_NUMBER_BASE 10
#define READ_FILE_MODE "r"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "[ERROR](%s, %d):",		\
						__FILE__, __LINE__);	\
				perror(call_description);		\
				exit(EXIT_FAILURE);		\
		}							\
	} while (0)


typedef int bool;
enum{false, true};


bool is_number(char *input);

int nr_of_occurences_of_char(char *string, char c);

#endif
