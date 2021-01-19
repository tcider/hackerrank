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

// Complete the happyLadybugs function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* happyLadybugs(char* b) {
    static char *yes = "YES";
    static char *no = "NO";
    int i = -1;
    int flag = 0;
    //int flag2 = 0;

    char    *buf = (char*)calloc(26, sizeof(char));
    while (b[++i])
    {
        if (b[i] == '_')
            flag = 1;
        else {
            buf[b[i] - 'A'] += 1;
            //flag2 = 1;
        }
    }
    i = -1;
    while (++i < 26)
        if (buf[i] == 1)
            return (no);
    if (flag)
        return (yes);
    else {
        return (no);
    }



}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* g_endptr;
    char* g_str = readline();
    int g = strtol(g_str, &g_endptr, 10);

    if (g_endptr == g_str || *g_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int g_itr = 0; g_itr < g; g_itr++) {
        char* n_endptr;
        char* n_str = readline();
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* b = readline();

        char* result = happyLadybugs(b);

        fprintf(fptr, "%s\n", result);
    }

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

// Complete the happyLadybugs function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* happyLadybugs(char* b) {
    static char *yes = "YES";
    static char *no = "NO";
    int i = -1;
    int flag = 0;
    //int flag2 = 0;

    char    *buf = (char*)calloc(26, sizeof(char));
    while (b[++i])
    {
        if (b[i] == '_')
            flag = 1;
        else {
            buf[b[i] - 'A'] += 1;
            //flag2 = 1;
        }
    }
    i = -1;
    while (++i < 26)
        if (buf[i] == 1)
            return (no);
    if (flag)
        return (yes);
    else {
        return (no);
    }



}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* g_endptr;
    char* g_str = readline();
    int g = strtol(g_str, &g_endptr, 10);

    if (g_endptr == g_str || *g_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int g_itr = 0; g_itr < g; g_itr++) {
        char* n_endptr;
        char* n_str = readline();
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* b = readline();

        char* result = happyLadybugs(b);

        fprintf(fptr, "%s\n", result);
    }

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

