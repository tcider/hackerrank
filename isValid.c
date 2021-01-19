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

// Complete the isValid function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* isValid(char* s) {
    int arr[26] = {0};
    int i = -1;
    int flag1 = 0;
    int flag2 = 0;
    int tmp = 0;
    static char no[] = "NO";
    static char yes[] = "YES";
    int count = 0;

    while (s[++i])
        arr[(int)(s[i] - 'a')]++;
    i = -1;
    while (++i < 26)
    {
        if (arr[i])
        {
            count++;
            if (flag1 == 0)
            {
                tmp = arr[i];
                flag1 = 1;
            }
            else
            {
                if (tmp == arr[i])
                    flag1 = flag1;
                else if (tmp - arr[i] == 1)
                    flag1++;
                else if (arr[i] - tmp == 1)
                    flag2++;
                else
                {
                    return no;
                }
            }
        }
    }
    if (count == 1 || (flag1 && flag1 == count) || (flag1 == 1 && flag2 == 1) || (flag1 == 1 && flag2 == 0))
        return yes;
    else
        return no;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

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

