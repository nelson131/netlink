#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <string.h>

char* readline(const char* prompt);
void get_arg(size_t num, char* content, char** arg);
size_t get_args(char* content);

void send_welcome();
void nlog(size_t index, const char* message);

#endif