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

// Complete the fairRations function below.
int fairRations(int B_count, int* B) {
    int i = -1;
    int tmp = -1;
    int sum = 0;

    while (++i < B_count)
        if (B[i] % 2)
        {
            if (tmp != -1)
            {
                sum += (i - tmp);
                tmp = -1;
            }
            else 
                tmp = i;
        }
        //else if (tmp != -1 && B[i] == 10) //
         //   return 0;
    if (tmp != - 1)
        return -1;
    return 2 * sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* N_endptr;
    char* N_str = readline();
    int N = strtol(N_str, &N_endptr, 10);

    if (N_endptr == N_str || *N_endptr != '\0') { exit(EXIT_FAILURE); }

    char** B_temp = split_string(readline());

    int* B = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        char* B_item_endptr;
        char* B_item_str = *(B_temp + i);
        int B_item = strtol(B_item_str, &B_item_endptr, 10);

        if (B_item_endptr == B_item_str || *B_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(B + i) = B_item;
    }

    int B_count = N;

    int result = fairRations(B_count, B);

    if (result > 0)
        fprintf(fptr, "%d\n", result);
    else
        fprintf(fptr, "NO");

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

