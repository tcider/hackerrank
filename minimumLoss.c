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

// Complete the minimumLoss function below.
int minimumLoss(int price_count, long* price) {
    int i = -1;
    int j;
    int min = 0;

    while (++i < price_count - 1)
    {
        j = i;
        while (++j < price_count)
        {
            if (price[i] - price[j] > 0)
            {
                if (!min)
                    min = price[i] - price[j];
                else if (price[i] - price[j] < min)
                    min = price[i] - price[j]; 
            }
        }
    }
    return min;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** price_temp = split_string(readline());

    long* price = malloc(n * sizeof(long));

    for (int i = 0; i < n; i++) {
        char* price_item_endptr;
        char* price_item_str = *(price_temp + i);
        long price_item = strtol(price_item_str, &price_item_endptr, 10);

        if (price_item_endptr == price_item_str || *price_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(price + i) = price_item;
    }

    int price_count = n;

    int result = minimumLoss(price_count, price);

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

