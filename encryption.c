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

// Complete the encryption function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//

int     str_len(char *str)
{
    int     i = -1;
    int     size = 0;

    while (str[++i])
        size++;
    return (size);
}

int     sq_floor(int num)
{
    int     res;

    res = 1;

    while (res * res <= num)
        res++;
    return (res - 1);
}

char* encryption(char* s) {
    int     size;
    int     size2;
    int     row;
    int     col;
    char    *res;
    int     i = -1;
    int     j = -1;
    int     k = -1;

    size = str_len(s);
    row = sq_floor(size);
    col = size / row;
    if (size % row)
        col++;
    if (col - row > 1)
    {
        col--;
        row++;
    }
    size2 = size + col - 1;
    res = (char*)malloc(sizeof(char) * (size2 + 1));
    while (++i < col)
    {
        j = -1;
        while (++j < row && j * col + i < size)
            res[++k] = s[j * col +i];
        res[++k] = ' ';
    }
    res[k] = '\0';
    return (res);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = encryption(s);

    fprintf(fptr, "%s\n", result);

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

