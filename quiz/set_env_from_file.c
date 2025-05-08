#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set_env_from_file.h"

#define MAX_LINE_LENGTH 256

bool set_env_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        return false;
    }
    char line[MAX_LINE_LENGTH];
    char *saveptr;
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok_r(line, "=", &saveptr);
        char *value = strtok_r(NULL, "\n", &saveptr);
        if (key && value) {
            setenv(key, value, 1);
        }
    }
    fclose(file);
    return true;
}
