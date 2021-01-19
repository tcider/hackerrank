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

int maxThree(int a, int b, int c)
{
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

int makeNum(int a, int b, int c)
{
    if (a && b)
        return (a + b - c);
    else if (a)
        return (a);
    else
        return (b);
}

// Complete the connectedCell function below.
int connectedCell(int matrix_rows, int matrix_columns, int** matrix) {
    int i = -1;
    int j;
    int max = 0;

    while (++i < matrix_rows)
    {
        j = -1;
        while (++j < matrix_columns)
            if (matrix[i][j])
            {
                if (!i && j)
                    matrix[i][j] = matrix[i][j - 1] + 1;
                else if (i && !j)
                    matrix[i][j] = matrix[i - 1][j] + 1;
                else if (i && j)
                    matrix[i][j] = makeNum(matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]) + 1;
                if (matrix[i][j] > max)
                    max = matrix[i][j];
            }
    }

    i = -1;
    while (++i < matrix_rows)
    {
        j = -1;
        while (++j < matrix_columns)
            printf("%d-", matrix[i][j]);
        printf("\n");
    }

    return max;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* m_endptr;
    char* m_str = readline();
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    int** matrix = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(matrix + i) = malloc(m * (sizeof(int)));

        char** matrix_item_temp = split_string(readline());

        for (int j = 0; j < m; j++) {
            char* matrix_item_endptr;
            char* matrix_item_str = *(matrix_item_temp + j);
            int matrix_item = strtol(matrix_item_str, &matrix_item_endptr, 10);

            if (matrix_item_endptr == matrix_item_str || *matrix_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int matrix_rows = n;
    int matrix_columns = m;

    int result = connectedCell(matrix_rows, matrix_columns, matrix);

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

