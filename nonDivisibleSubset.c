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
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'nonDivisibleSubset' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY s
 */

int add_buffer(int* buf, int* buf_ratio, int pos, int num)
{
    int i = -1;

    if (pos >= 100000)
        return 0;

    while (++i < pos)
        if (num == buf[i])
        {   
            buf_ratio[i]++;            
            return pos;
        }
    buf[pos] = num;
    buf_ratio[pos] = 1;
    return (pos + 1);
}

void sort(int* buf, int* buf_ratio, int pos){
    int i = -1;
    int j = -1;
    int tmp;
    int tmp_ratio;

    while (++i < pos)
    {
        j = -1;
        while (++j < pos - 1)
            if (buf_ratio[j] > buf_ratio[j + 1])
            {
                tmp = buf[j];
                tmp_ratio = buf_ratio[j];
                buf[j] = buf[j + 1];
                buf_ratio[j] = buf_ratio[j + 1];
                buf[j + 1] = tmp;
                buf_ratio[j + 1] = tmp_ratio;
            }
    }
}

int check_div(int* buf, int pos, int k)
{
    int i = -1;
    int j = i;
    while (++i < pos)
    {
        j = i;
        while (++j < pos)
            if ((buf[i] + buf[j]) % k == 0)
                return 1;
    }
    return 0;
}

int nonDivisibleSubset(int k, int s_count, int* s) {
    int i = -1;
    int j = 0;
    int pos = 0;
    int* buf = (int*)malloc(sizeof(int) * 100000);
    int* buf_ratio = (int*)malloc(sizeof(int) * 100000);
    int count = 0;

    while (++i < s_count)
    {
        j = i;
        while (++j < s_count)
        {
            if ((s[i] + s[j]) % k == 0)
            {
                pos = add_buffer(buf, buf_ratio, pos, s[i]);
                pos = add_buffer(buf, buf_ratio, pos, s[j]);
            }
        }
    }
    sort(buf, buf_ratio, pos);
    count = s_count - pos;
    while (check_div(buf, pos, k))
    {
        buf[pos - 1] = 0;
        pos--;
    }
    count += pos;
    free(buf);
    free(buf_ratio);
    return (count);
}
/*
int nonDivisibleSubset(int k, int s_count, int* s)
{
    int     i = -1;
    int     j;
    int     sum = 1;
   
    while (++i < s_count)
    {
        j = -1;
        while (++j < s_count)
        {
            if (j != i && (s[i] + s[j]) % k)
        }

    }

    return (sum);
}
*/
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** s_temp = split_string(rtrim(readline()));

    int* s = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int s_item = parse_int(*(s_temp + i));

        *(s + i) = s_item;
    }

    int result = nonDivisibleSubset(k, n, s);

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
 
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
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'nonDivisibleSubset' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY s
 */

int add_buffer(int* buf, int* buf_ratio, int pos, int num)
{
    int i = -1;

    if (pos >= 100000)
        return 0;

    while (++i < pos)
        if (num == buf[i])
        {   
            buf_ratio[i]++;            
            return pos;
        }
    buf[pos] = num;
    buf_ratio[pos] = 1;
    return (pos + 1);
}

void sort(int* buf, int* buf_ratio, int pos){
    int i = -1;
    int j = -1;
    int tmp;
    int tmp_ratio;

    while (++i < pos)
    {
        j = -1;
        while (++j < pos - 1)
            if (buf_ratio[j] > buf_ratio[j + 1])
            {
                tmp = buf[j];
                tmp_ratio = buf_ratio[j];
                buf[j] = buf[j + 1];
                buf_ratio[j] = buf_ratio[j + 1];
                buf[j + 1] = tmp;
                buf_ratio[j + 1] = tmp_ratio;
            }
    }
}

int check_div(int* buf, int pos, int k)
{
    int i = -1;
    int j = i;
    while (++i < pos)
    {
        j = i;
        while (++j < pos)
            if ((buf[i] + buf[j]) % k == 0)
                return 1;
    }
    return 0;
}

int nonDivisibleSubset(int k, int s_count, int* s) {
    int i = -1;
    int j = 0;
    int pos = 0;
    int* buf = (int*)malloc(sizeof(int) * 100000);
    int* buf_ratio = (int*)malloc(sizeof(int) * 100000);
    int count = 0;

    while (++i < s_count)
    {
        j = i;
        while (++j < s_count)
        {
            if ((s[i] + s[j]) % k == 0)
            {
                pos = add_buffer(buf, buf_ratio, pos, s[i]);
                pos = add_buffer(buf, buf_ratio, pos, s[j]);
            }
        }
    }
    sort(buf, buf_ratio, pos);
    count = s_count - pos;
    while (check_div(buf, pos, k))
    {
        buf[pos - 1] = 0;
        pos--;
    }
    count += pos;
    free(buf);
    free(buf_ratio);
    return (count);
}
/*
int nonDivisibleSubset(int k, int s_count, int* s)
{
    int     i = -1;
    int     j;
    int     sum = 1;
   
    while (++i < s_count)
    {
        j = -1;
        while (++j < s_count)
        {
            if (j != i && (s[i] + s[j]) % k)
        }

    }

    return (sum);
}
*/
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** s_temp = split_string(rtrim(readline()));

    int* s = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int s_item = parse_int(*(s_temp + i));

        *(s + i) = s_item;
    }

    int result = nonDivisibleSubset(k, n, s);

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
 

