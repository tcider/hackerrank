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

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(char* s) {
    int i = -1;
    int size = 0;
    unsigned long **arr;
    int j, k;
    int sum = 0;

    while (s[++i])
        size++;
    arr = (unsigned long**)malloc(sizeof(unsigned long*) * (size - 1));
    i = -1;
    while (++i < size - 1)
    {
        arr[i] = (unsigned long*)malloc(sizeof(unsigned long) * (size - i));
        j = -1;
        while (++j < size - i)
            if (!i)
                arr[i][j] = ((int)s[j] * (int)s[j] * (int)s[j] * (int)s[j]);
            else
                arr[i][j] = arr[i - 1][j] + ((int)s[j + i] * (int)s[j + i] * (int)s[j + i] * (int)s[j + i]);
    }
    i = -1;
    while (++i < size - 1)
    {
        j = -1;
        while (++j < size - i)
        {
            k = j;
            while (++k < size - i)
                if (arr[i][j] == arr[i][k])
                    sum++;
        }
    }
    /*
    i = -1;
    while (++i < size - 1)
    {
        j = -1;
        while (++j < size - i)
            printf("%d-", arr[i][j]);
        printf("\n");
    }
    */
    return sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* q_endptr;
    char* q_str = readline();
    int q = strtol(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* s = readline();

        int result = sherlockAndAnagrams(s);

        fprintf(fptr, "%d\n", result);
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

