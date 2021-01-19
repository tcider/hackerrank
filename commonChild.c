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

int ijChild(char *s1, char *s2, int i, int j)
{
    int sum = 0;
    int flag;
    int k;

    while (s1[i])
    {
        flag = 1;
        k = j;
        while (flag && s2[k])
        {
            if (s1[i] == s2[k])
            {
                sum++;
                j = k + 1;
                flag = 0;
            }
            k++;
        }
        i++;
    }

    return sum; 
}

int iChild(char *s1, char *s2, int i)
{
    int j = -1;
    int tmp;
    int max = 0;

    while (s1[i])
    {
        while (s2[++j])
        {
            tmp = ijChild(s1, s2, i, j);
            if (tmp > max)
               max = tmp;
        }
        i++;
    }
    return max;
}

// Complete the commonChild function below.
int commonChild(char* s1, char* s2) {
    int i = -1;
    int tmp;
    int max = 0;

    while (s1[++i])
    {
        tmp = iChild(s1, s2, i);
        if (tmp > max)
            max = tmp;
    }
    return max;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s1 = readline();

    char* s2 = readline();

    int result = commonChild(s1, s2);

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

