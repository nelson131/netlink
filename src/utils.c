#include "utils.h"
#include <stdio.h>

char* readline(const char* prompt){
    printf("%s", prompt);

    size_t len = 0;
    size_t container = 16;
    char* res = malloc(container);
    if(!res){
        nlog(1, "Failed to malloc memory for readline");
        return NULL;
    }

    int c;
    while((c = getchar()) != EOF && c != '\n'){
        if(len + 1 >= container){
            container *= 2;
            char* temp = realloc(res, container);
            res = temp;
        }
        res[len++] = (char) c;
    }

    if(c == EOF && len == 0){
        free(res);
        return NULL;
    }

    res[len++] = '\0';
    char* temp = realloc(res, len);
    if(!temp){
        nlog(1, "Failed to relloc memory for readline");
        return NULL;
    }
    res = temp;
    return res;
}

void get_arg(size_t num, char* content, char** arg) {
    if(*arg){
        free(*arg);
        *arg = NULL;
    }

    size_t i = 0;
    size_t counter = 0;

    while (content[i] != '\0' && counter < num) {
        while (content[i] != '\0' && content[i] != ' ') i++;
        counter++;
    }

    if (content[i] == '\0') return;

    size_t start = i;
    while (content[i] != '\0' && content[i] != ' ') i++;
    size_t end = i;

    size_t len = 0;
    char* res = malloc(end - start + 1);
    for(size_t j = start; j < end; j++){
        res[len++] = content[j];
    }
    res[len++] = '\0';

    *arg = res;
}

void nlog(size_t index, const char* prompt){
    char* prefix = NULL;
    switch (index){
        case 0:
            prefix = "[SUCCESS]";
            break;
        case 1:
            prefix = "[ERROR]";
            break;
        case 2:
            prefix = "[INFO]";
            break;
        case 3:
            prefix = "[WARNING]";
            break;
        default:
            break;
    }

    printf("%s %s\n", prefix, prompt);
}