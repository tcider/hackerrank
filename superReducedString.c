#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

// Complete the superReducedString function below.

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */

int str_len(char *str)
{
    return *str ? 1 + str_len(str + 1) : 0;
}

int str_char(char *s, int len)
{
    int i = -1;
    int sum = 0;

    while (++i < len)
        if (s[i])
            sum++;
    return sum;
}

char* superReducedString(char* s) {
    int flag = 1;
    int i = -1;
    int st;
    int end;
    char *buf;
    int len = str_len(s);
    static char no[] = "Empty String";

    //printf("%d", len);
    while (++i < len - 1)
        if (s[i] && s[i] == s[i + 1])
        {
            flag = 1;
            s[i] = 0;
            s[i + 1] = 0;
            st = i;
            end = i + 1;
            while (flag)
            {
                while (st > 0 && !s[st])
                    st--;
                while (end < len - 1 && !s[end])
                    end++;
                if (s[st] && s[st] == s[end])
                {
                    s[st] = 0;
                    s[end] = 0;
                }
                else
                    flag = 0;
            }
        }
    if ((st = str_char(s, len)))
    {
        buf = (char*)malloc(sizeof(char) * (st + 1));
        i = -1;
        end = -1;
        while (++i < len)
          if (s[i])
             buf[++end] = s[i];
        buf[++end] = 0;
        return buf;
    }
    else 
        return no;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = superReducedString(s);

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

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

