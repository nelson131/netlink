#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

char* readline(const char* prompt);
void get_arg(size_t num, char* content, char** arg);
void nlog(size_t index, const char* message);

#endif