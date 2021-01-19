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
char** split_string(char*);

// Complete the absolutePermutation function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//
int* absolutePermutation(int n, int k, int* result_count) {
    int i = -1;
    int     *base;
    int     *res;
    
    *result_count = n;
    base = (int*)calloc(n, sizeof(int));
    res = (int*)calloc(n, sizeof(int));
    while (++i < n)
    {
        if (i < k)
        {
            res[i] = i + 1 + k;
            if (res[i] <= n)
                base[i + k] = 1;
            else
            {
                res[i] = i + 1 - k;
                base[i - k] = 1;
            }
            if (res[i] <= 0)
            {
                *result_count = 1;
                res[0] = -1;
                return (res);
            }
        }
        else {
            if (!base[i - k])
            {
                res[i] = i + 1 - k;
                base[i - k] = 1;
            }
            else if (!base[i + k] && i + 1 + k <= n)
            {
                res[i] = i + 1 + k;
                base[i + k] = 1;
            }
            else {
                *result_count = 1;
                res[0] = -1;
                return (res);
            }
        } 
    }
    return (res);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** nk = split_string(readline());

        char* n_endptr;
        char* n_str = nk[0];
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* k_endptr;
        char* k_str = nk[1];
        int k = strtol(k_str, &k_endptr, 10);

        if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

        int result_count;
        int* result = absolutePermutation(n, k, &result_count);

        for (int i = 0; i < result_count; i++) {
            fprintf(fptr, "%d", *(result + i));

            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }

        fprintf(fptr, "\n");
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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

