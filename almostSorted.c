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

int cmp(const void *a, const void *b)
{
    return (*((int*)a) - *((int*)b));
}
// Complete the almostSorted function below.
void almostSorted(int arr_count, int* arr) {
    int *res;
    int i = -1;
    int j = arr_count;
    int par[2];
    int count = 0;

    res = (int*)malloc(sizeof(int) * arr_count);
    memcpy(res, arr, sizeof(int) * arr_count);
    qsort(res, arr_count, sizeof(int), cmp);

    while (++i < arr_count)
        res[i] = arr[i] - res[i];
    i = -1;
    while (i < arr_count - 2 && !res[++i]);
    while (j > 0 && !res[--j]);
    if (j == 0)
    {
        printf("yes");
        return;
    }
    par[0] = i + 1;
    par[1] = j + 1;
    while (i < j)
        if (res[i] != 0 && res[i] + res[j] == 0)
        {
            count++;
            i++;
            j--;
        }
        else if (!(!res[i] && !res[j]) || count != 1)
        {
            printf("no");
            return;
        }
    printf("yes\n");
    if (count == 1)
        printf("swap ");
    else
        printf("reverse ");
    printf("%d %d", par[0], par[1]);
    return;
}

int main()
{
    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** arr_temp = split_string(readline());

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* arr_item_endptr;
        char* arr_item_str = *(arr_temp + i);
        int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

        if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(arr + i) = arr_item;
    }

    int arr_count = n;

    almostSorted(arr_count, arr);

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

