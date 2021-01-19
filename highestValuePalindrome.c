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

// Complete the highestValuePalindrome function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//

char  *MakeIt(char *s, int n , int ext)
{
    int i = -1;

    while (++i < n / 2)
    {
        if (ext >= 2 && s[i] == s[n - 1 - i] && s[i] != '9')
        {
            s[i] = '9';
            s[n - i - 1] = '9';
            ext -= 2;
        }
        else if (ext > 0 && s[i] != s[n - 1 - i])
        {
            if (s[i] != '9' && s[n - 1 - i] != '9')
                ext--;
            s[i] = '9';
            s[n - i - 1] = '9';
        }
        else if (!ext)
        {
            if (s[i] > s[n - i - 1])
                s[n - i - 1] = s[i];
            else
                s[i] = s[n - i -1];
        }
    }
    if (ext && n % 2)
        s[n / 2] = '9';
    return s;
}

char* highestValuePalindrome(char* s, int n, int k) {
    static char *no = "-1";
    int i = -1;
    int sum = 0;

    while (++i < n / 2)
        if (s[i] != s[n - i -1])
            sum++;
    if (sum > k)
        return no;
    else
        return MakeIt(s, n, k - sum);
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

    char* s = readline();

    char* result = highestValuePalindrome(s, n, k);

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

