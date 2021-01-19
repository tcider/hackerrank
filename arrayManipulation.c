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

// Complete the arrayManipulation function below.
long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries) {
    /*
    int     i = -1;
    long     mid;
    long     sum = 0;
    long     norm;

    while (++i < queries_rows)
    {
        sum += queries[i][2] * (queries[i][0] + queries[i][1]) / 2;
        norm += queries[i][2];
    }
    mid = sum / norm;
    printf("%ld", mid);
    i = -1;
    sum = 0;
    while (++i < queries_rows)
        if (queries[i][0] <= mid && queries[i][1] >= mid)
            sum += queries[i][2];
    return sum;


    */
    assert(queries_columns == 3);
    assert(queries_rows);

    int i = 0;
    int j;
    long resMax = 0;
    
    int min = queries[0][0];
    int max = queries[0][1];
    
    while (++i < queries_rows)
    {
        if (queries[i][0] < min)
            min = queries[i][0];
        if (queries[i][1] > max)
            max = queries[i][1];
    }
    
    //int min = 1;
    //int max = n;
    long *arr = (long*)calloc((max - min + 1), sizeof(long));
    i = -1;
    while (++i < queries_rows)
    {
        j = queries[i][0] - min - 1;
        while (++j <= queries[i][1] - min)
        {
            arr[j] += queries[i][2];
            if (arr[j] > resMax)
                resMax = arr[j];
        }
    }
    /*
    i = 0;
    j = max - min + 1;
    resMax = arr[0];
    while (++i < j)
        if (arr[i] > resMax)
            resMax = arr[i];
    */
    return resMax;
    
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nm = split_string(readline());

    char* n_endptr;
    char* n_str = nm[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* m_endptr;
    char* m_str = nm[1];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    int** queries = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));

        char** queries_item_temp = split_string(readline());

        for (int j = 0; j < 3; j++) {
            char* queries_item_endptr;
            char* queries_item_str = *(queries_item_temp + j);
            int queries_item = strtol(queries_item_str, &queries_item_endptr, 10);

            if (queries_item_endptr == queries_item_str || *queries_item_endptr != '\0') { exit(EXIT_FAILURE); }

            *(*(queries + i) + j) = queries_item;
        }
    }

    int queries_rows = m;
    int queries_columns = 3;

    long result = arrayManipulation(n, queries_rows, queries_columns, queries);

    fprintf(fptr, "%ld\n", result);

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

