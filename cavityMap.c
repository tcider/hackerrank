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

// Complete the cavityMap function below.

// Please store the size of the string array to be returned in result_count pointer. For example,
// char a[2][6] = {"hello", "world"};
//
// *result_count = 2;
//
// return a;
//
char** cavityMap(int grid_count, char** grid, int* result_count) {
    int     i = -1;
    int     j = -1;
    char    tmp;
    char    **res;
    int     len = 0;

    while(grid[0][++j])
        len++;
    res = (char**)malloc(sizeof(char*) * grid_count);
    while (++i < grid_count)
    {
        j = -1;
        res[i] = (char*)malloc(sizeof(char) * (len + 1));
        while (++j < len)
        {
            tmp = grid[i][j];
            if (i > 0 && i < grid_count - 1 && j > 0 && j < len - 1 &&
                grid[i][j + 1] < tmp && grid[i][j - 1] < tmp &&
                grid[i + 1][j] < tmp && grid[i - 1][j] < tmp)
                res[i][j] = 'X';
            else
                res[i][j] = tmp;
        }
        res[i][j] = '\0';
    }
    *result_count = grid_count;
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** grid = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* grid_item = readline();

        *(grid + i) = grid_item;
    }

    int grid_count = n;

    int result_count;
    char** result = cavityMap(grid_count, grid, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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

