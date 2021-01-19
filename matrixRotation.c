#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

typedef struct s_cor
{
    int         i;
    int         j;
}              t_cor;

t_cor   new_cord(t_cor cor, int rows, int cols)
{
    
    if (cor.j < cols / 2 && (cor.i >= cor.j && cor.i < rows - (cor.j + 1)))
        cor.i++;
    else if (cor.j >= cols - cols / 2 && (cor.i >= cols - cor.j && cor.i < rows - (cols - cor.j - 1)))
        cor.i--;
    else if (cor.i < rows / 2 && (cor.j > cor.i && cor.j < cols - cor.i))
        cor.j--;
    else if (cor.i >= rows - rows / 2 && (cor.j >= (rows - cor.i - 1) && cor.j < cols - (rows - cor.i)))
        cor.j++;
    
    return (cor);
}

int     **generate_matrix(int rows, int cols)
{
    int     **new_matrix;
    int     i = -1;

    new_matrix = (int**)malloc(sizeof(int*) * rows);
    while (++i < rows)
        new_matrix[i] = (int*)malloc(sizeof(int) * cols);
    return (new_matrix);
}

int     get_ring(t_cor cor, int rows, int cols)
{
    /*
    int     ring;
    if (cor.i * cor.j == 0 || cor.i == rows - 1 || cor.j == cols - 1)
        return (0);
    if (rows < cols)
        ring = (cor.i < rows / 2) ? cor.i : (rows - cor.i - 1);
    else
        ring = (cor.j < cols / 2) ? cor.j : (cols - cor.j - 1);
    return (ring);
    */
    int ring1;
    int ring2;

    ring1 = (cor.i < rows / 2) ? cor.i : (rows - cor.i - 1);
    ring2 = (cor.j < cols / 2) ? cor.j : (cols - cor.j - 1);
    if (ring1 < ring2)
        return (ring1);
    else
        return (ring2);
}
// Complete the matrixRotation function below.
void matrixRotation(int matrix_rows, int matrix_columns, int** matrix, int r) {
    int     **new_matrix;
    t_cor   new_cor;
    int i = -1;
    int j;
    int k;
    int ring;
    int tmp = r;

    //r = r % ((matrix_columns + matrix_rows - 2) * 2);
    new_matrix = generate_matrix(matrix_rows, matrix_columns);
    while (++i < matrix_rows)
    {
        j = -1;
        while (++j < matrix_columns)
        {
            k = -1;
            new_cor.i = i;
            new_cor.j = j;
            ring = get_ring(new_cor, matrix_rows, matrix_columns);
            //printf("%d-", ring);
            //r = tmp;
            tmp = r % ((matrix_columns + matrix_rows - 2 - 4 * ring) * 2);
            //printf("%d-", tmp);
            while (++k < tmp)
            {
                new_cor = new_cord(new_cor, matrix_rows, matrix_columns);
            }
            //printf("%d:%d-", new_cor.i, new_cor.j);
            new_matrix[new_cor.i][new_cor.j] = matrix[i][j];
        }
        //printf("\n");
    }
    i = -1;
    while (++i < matrix_rows)
    {
        j = -1;
        while (++j < matrix_columns)
        {
            printf("%d", new_matrix[i][j]);
            if (j == matrix_columns - 1)
                printf("\n");
            else
                printf(" ");
        }
    }
}

int main()
{
    char** mnr = split_string(rtrim(readline()));

    char* m_endptr;
    char* m_str = mnr[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mnr[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* r_endptr;
    char* r_str = mnr[2];
    int r = strtol(r_str, &r_endptr, 10);

    if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

    int** matrix = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(matrix + i) = malloc(n * (sizeof(int)));

        char** matrix_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < n; j++) {
            char* matrix_item_endptr;
            char* matrix_item_str = *(matrix_item_temp + j);
            int matrix_item = strtol(matrix_item_str, &matrix_item_endptr, 10);

            if (matrix_item_endptr == matrix_item_str || *matrix_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(matrix + i) + j) = matrix_item;
        }
    }

    int matrix_rows = m;
    int matrix_columns = n;

    matrixRotation(matrix_rows, matrix_columns, matrix, r);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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

