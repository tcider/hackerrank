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

int new_num(int **arr, int i, int j)
{
    int sum;
    
    sum = arr[i-1][j-1] + arr[i - 2][j - 1] + arr[i - 2][j - 2] + arr[i - 2][j] +\
    arr[i][j - 2] + arr[i][j - 1] + arr[i][j];
    return (sum);    
}

int add_num(int **arr, int i, int j)
{
    int sum;
    
    sum = arr[i - 1][j - 1] + arr[i - 2][j] + arr[i][j] - arr[i - 1][j - 2] -\
    arr[i - 2][j - 3] - arr[i][j - 3];
    return (sum);
}


// Complete the hourglassSum function below.
int hourglassSum(int arr_rows, int arr_columns, int** arr) {
    static int   tmp[4][4];
    int          i = -1;
    int          j;
    int          max = -63;
    
    while (++i < arr_rows - 2)
    {
        j = -1;
        while (++j < arr_columns - 2)
        {
            if (!j)
                tmp[i][j] = new_num(arr, i + 2, j + 2);
            else 
                tmp[i][j] = tmp[i][j - 1] + add_num(arr, i + 2, j + 2);
            if (tmp[i][j] > max)
                max = tmp[i][j];
        }
    }
    return (max);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int** arr = malloc(6 * sizeof(int*));

    for (int i = 0; i < 6; i++) {
        *(arr + i) = malloc(6 * (sizeof(int)));

        char** arr_item_temp = split_string(readline());

        for (int j = 0; j < 6; j++) {
            char* arr_item_endptr;
            char* arr_item_str = *(arr_item_temp + j);
            int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

            if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(arr + i) + j) = arr_item;
        }
    }

    int arr_rows = 6;
    int arr_columns = 6;

    int result = hourglassSum(arr_rows, arr_columns, arr);

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

