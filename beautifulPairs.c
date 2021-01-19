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

int comp(const void *a, const void *b)
{
    return *((int*)a) - *((int*)b);
}

// Complete the beautifulPairs function below.
int beautifulPairs(int A_count, int* A, int B_count, int* B) {
    int i = 0;
    int j = 0;
    int sum = 0;
    qsort(A, A_count, sizeof(int), comp);
    qsort(B, B_count, sizeof(int), comp);
    while (i < A_count && j < B_count)
    {
        if (A[i] == B[j])
        {
            //if (!i || A[i] != A[i - 1])
                sum++;
            i++;
            j++;
            
        }
        else if (A[i] > B[j])
            j++;
        else
            i++;
    }
    if (sum < A_count)
        sum++;
    return sum;

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** A_temp = split_string(readline());

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* A_item_endptr;
        char* A_item_str = *(A_temp + i);
        int A_item = strtol(A_item_str, &A_item_endptr, 10);

        if (A_item_endptr == A_item_str || *A_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(A + i) = A_item;
    }

    int A_count = n;

    char** B_temp = split_string(readline());

    int* B = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* B_item_endptr;
        char* B_item_str = *(B_temp + i);
        int B_item = strtol(B_item_str, &B_item_endptr, 10);

        if (B_item_endptr == B_item_str || *B_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(B + i) = B_item;
    }

    int B_count = n;

    int result = beautifulPairs(A_count, A, B_count, B);

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

