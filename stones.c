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

// Complete the stones function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//

int  cmp(const void *a, const void *b)
{
    return *((int*)a) - *((int*)b);
}

int  in_arr(int tmp, int *arr, int size)
{
    int i = -1;

    while (++i < size)
        if (arr[i] == tmp)
            return 1;
    return 0;
}

int* stones(int n, int a, int b, int* result_count) {
    int *res;
    int i = -1;
    int k = 0;
    int tmp = a + b;

    if (a == b)
    {
        res = (int*)malloc(sizeof(int) * 1);
        res[0] = (n - 1) * a;
        *result_count = 1;
        return res;
    }
    a = (a > b) ? a : b;
    b = tmp - a;
    res = (int*)malloc(sizeof(int) * n);
    while (++i < n)
    {
        tmp = i * a + (n - 1 - i) * b;
        if (!in_arr(tmp, res, k))
        {
            res[k] = tmp;
            k++;
        }
    }
    *result_count = k;
    qsort(res, k, sizeof(int), cmp);
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* T_endptr;
    char* T_str = readline();
    int T = strtol(T_str, &T_endptr, 10);

    if (T_endptr == T_str || *T_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int T_itr = 0; T_itr < T; T_itr++) {
        char* n_endptr;
        char* n_str = readline();
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

        char* a_endptr;
        char* a_str = readline();
        int a = strtol(a_str, &a_endptr, 10);

        if (a_endptr == a_str || *a_endptr != '\0') { exit(EXIT_FAILURE); }

        char* b_endptr;
        char* b_str = readline();
        int b = strtol(b_str, &b_endptr, 10);

        if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

        int result_count;
        int* result = stones(n, a, b, &result_count);

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

