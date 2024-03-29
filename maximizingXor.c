#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

// Complete the maximizingXor function below.
int maximizingXor(int l, int r) {
    int a = l - 1;
    int b;
    int c;
    int max = 0;

    while (++a <= r)
    {
        b = l - 1;
        while (++b <= r)
            if ((c = a ^ b) > max)
                max = c;
    }


    return max;

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* l_endptr;
    char* l_str = readline();
    int l = strtol(l_str, &l_endptr, 10);

    if (l_endptr == l_str || *l_endptr != '\0') { exit(EXIT_FAILURE); }

    char* r_endptr;
    char* r_str = readline();
    int r = strtol(r_str, &r_endptr, 10);

    if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

    int result = maximizingXor(l, r);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

