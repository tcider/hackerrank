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

// Complete the biggerIsGreater function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//

int   str_len(char *str)
{
    int i = -1;
    int size = 0;

    while (str[++i])
        size++;
    return (size);
}

int   sort_str_lend(char *str)//правильно ли считает
{
    int i = 0;
    int size = 1;

    while (str[i + 1])
    {
        if (str[i] != str[i + 1])
            size++;
        i++;
    }
    return (size);

}

char  *str_cpy(char *str, int size)
{
    //int     size;
    char    *res;
    int     i = -1;

    //size = str_len(str);
    res = (char*)malloc(sizeof(char) * (size + 1));
    while (str[++i])
        res[i] = str[i];
    res[i] = '\0';
    return (res);
}

void  sort_str(char *buf, int len)
{
    int     i = -1;
    int     j;
    char    tmp;

    while (++i < len - 1)
    {
        j = 0;
        while (j < len - 1)
        {
            if (buf[j] > buf[j + 1])
            {
                tmp = buf[j];
                buf[j] = buf[j + 1];
                buf[j + 1] = tmp;
            }
            j++;
        }
    }
}

int    *sort_del_dbl(char **str_main, int *base)
{
    int     i = 0;
    int     k = -1;
    char    *res;
    char    *str;
    int     *str_base;
    int     tmp = 1;

    str = *str_main;
    *base = sort_str_lend(str);
    res = (char*)malloc(sizeof(char) * ((*base) + 1));
    str_base = (int*)malloc(sizeof(int) * (*base));
    while (str[i + 1])
    {
        if (str[i] != str[i + 1])
        {
            res[++k] = str[i];
            str_base[k] = tmp;
            tmp = 1;
        }
        else
            tmp++;
        i++;
    }
    res[++k] = str[i];
    str_base[k] = tmp;
    res[++k] = '\0';
    free(str);
    *str_main = res;
    return (str_base);
}

int   alph_index(char c, char *alph)
{
    int     i = -1;

    while (alph[++i])
        if (alph[i] == c)
            return (i);
    //write(1, "-", 1);
    return (-1);
}

void  put_nbr(unsigned long long int num)
{
    char    c;

    if (num < 0)
    {
        write(1, "-", 1);
        put_nbr(-num);
    }
    if (num >= 10)
        put_nbr(num / 10);
    c = '0' + num % 10;
    write(1, &c, 1);
}


unsigned long long   str_to_num(char *str, int len, char **alph, int *base, int **str_base)
{
    int     i = -1;
    unsigned long long     prev = 0;

    //write(1, str, 20);
    *alph = str_cpy(str, len);
    //write(1, str, 73);
    sort_str(*alph, len);
    //write(1, *alph, 73);
    *str_base = sort_del_dbl(alph, base);
    //put_nbr(*base);
    //put_nbr(str_len(*alph));
    //write(1, *alph, 2);
    while (str[++i])
    {
        prev = prev * (*base) + alph_index(str[i], *alph);
        //put_nbr(prev);
        //write(1, "-", 1);
    }
    //put_nbr(prev);
    return (prev);
}

unsigned long long my_pow(int x, int n)
{
    if (n % 2)
        return (x * my_pow(x, n - 1));
    else
        return (n ? my_pow(x, n /2) * my_pow(x, n /2) : 1);
}

char  *num_to_str(unsigned long long num, int len, char *alph, int base, int *str_base)
{
    char    *res;
    int     *str_b;
    int     i = -1;
    //const char  *no = "no answer";

    res = (char*)malloc(sizeof(char) * (len + 1));
    res[len] = '\0';
    str_b = (int*)malloc(sizeof(int) * base);
    while(++i < base)
        str_b[i] = str_base[i];
    while (len)
    {
        if (str_b[num % base])
        {
            res[len - 1] = alph[num % base];
            str_b[num % base]--;
        }
        else
        {
            free(res);
            free(str_b);        
            return (NULL);
        }
        num /= base;
        len--;
    }
    free(str_b);
    //if (num % base)
    //{
    //    free(res);
    //    return (no);
    //}
    //else
        return (res);
}


char* biggerIsGreater(char* w) {
    char    *alph;
    int     base = 0;
    unsigned long long     num;
    unsigned long long     num2;
    int     len;
    int     *str_base;
    char    *res;
    const char  *no = "no answer";
    unsigned long long    pow_num;

    len = str_len(w);
    //put_nbr(len);
    num = str_to_num(w, len, &alph, &base, &str_base);
    put_nbr(num);
    //printf("%d - %d - %s/", num, base, alph);
    //printf("%d-", (int)pow(base, len));
    //pow_num = (unsigned long long)pow(base, len);
    pow_num = my_pow(base, len);
    //printf("%llu", num);
    //put_nbr(str_base[0]);
    write(1, "-", 1);
    //put_nbr(str_base[1]);
    //write(1, "-", 1);
    //put_nbr(str_base[2]);
    //num *= base;
    //while (!(res = num_to_str(num, len, alph, base, str_base)))
    if (base == 1)
        return (no);
    num2 = num + (base - 1);
    while (num2 < pow_num)
    {
        //num += 1;
        if ((res = num_to_str(num2, len, alph, base, str_base)))
        {
            put_nbr(num2);
            write(1, "=", 1);
            put_nbr(num2 - num);
            return (res);
        }
        num2 += (base - 1);
    }
    return (no);
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* T_endptr;
    char* T_str = readline();
    int T = strtol(T_str, &T_endptr, 10);

    if (T_endptr == T_str || *T_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int T_itr = 0; T_itr < T; T_itr++) {
        char* w = readline();

        char* result = biggerIsGreater(w);

        fprintf(fptr, "%s\n", result);
    }

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

