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
// Complete the hackerlandRadioTransmitters function below.
int hackerlandRadioTransmitters(int x_count, int* x, int k) {
    int     i = -1;
    int     tmp = 0;
    int     tmp2;
    int     sum = 0;
    int     flag = 0;

    qsort(x, x_count, sizeof(int), comp);
    while (++i < x_count)
        if (x[i] > tmp && !flag)
        {
            flag = 1;
            sum++;
            tmp2 = x[i];
            tmp = x[i];
        }
        else if (flag)
        {
            if (x[i] <= tmp + k)
                tmp2 = x[i];
            else {
                tmp = tmp2 + k;
                flag = 0;            
                i--;
            }
        }

    return sum;

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nk = split_string(readline());

    char* n_endptr;
    char* n_str = nk[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* k_endptr;
    char* k_str = nk[1];
    int k = strtol(k_str, &k_endptr, 10);

    if (k_endptr == k_str || *k_endptr != '\0') { exit(EXIT_FAILURE); }

    char** x_temp = split_string(readline());

    int* x = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* x_item_endptr;
        char* x_item_str = *(x_temp + i);
        int x_item = strtol(x_item_str, &x_item_endptr, 10);

        if (x_item_endptr == x_item_str || *x_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(x + i) = x_item;
    }

    int x_count = n;

    int result = hackerlandRadioTransmitters(x_count, x, k);

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

