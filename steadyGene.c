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

typedef struct  s_data
{
    int     a;
    int     c;
    int     t;
    int     g;
}               t_data;

t_data  *make_letter(char c)
{
    t_data  *data;

    data = (t_data*)malloc(sizeof(t_data));
    data->a = (c == 'A') ? 1 : 0;
    data->c = (c == 'C') ? 1 : 0;
    data->t = (c == 'T') ? 1 : 0;
    data->g = (c == 'G') ? 1 : 0;
    return data;
}

t_data  *add_letter(t_data *prev, char c)
{
    t_data  *tmp;

    tmp = make_letter(c);
    tmp->a += prev->a;
    tmp->c += prev->c;
    tmp->t += prev->t;
    tmp->g += prev->g;
    return tmp;
}

t_data  *make_diff(t_data *last, int size)
{
    t_data  *tmp;

    tmp = make_letter('0');
    tmp->a = size / 4 - last->a;
    tmp->c = size / 4 - last->c;
    tmp->t = size / 4 - last->t;
    tmp->g = size / 4 - last->g;
    return tmp;
}

int     get_start(t_data *diff)
{
    int sum = 0;

    if (diff->a > 0)
        sum += diff->a;
    if (diff->c > 0)
        sum += diff->c;
    if (diff->t > 0)
        sum += diff->t;
    if (diff->g > 0)
        sum += diff->g;
    return sum;
}

t_data  *dup_data(t_data *a)
{
    t_data  *tmp;

    tmp = make_letter('0');
    tmp->a = a->a;
    tmp->c = a->c;
    tmp->t = a->t;
    tmp->g = a->g;
    return tmp;
}

t_data  *sub_data(t_data *a, t_data *b)
{
    t_data  *tmp;

    tmp = make_letter('0');
    tmp->a = a->a - b->a;
    tmp->c = a->c - b->c;
    tmp->t = a->t - b->t;
    tmp->g = a->g - b->g;
    return tmp;
}

t_data  *add_data(t_data *a, t_data *b)
{
    t_data  *tmp;

    tmp = make_letter('0');
    tmp->a = a->a + b->a;
    tmp->c = a->c + b->c;
    tmp->t = a->t + b->t;
    tmp->g = a->g + b->g;
    return tmp;
}

int     check_res(t_data *res, int size)
{
    int sum = 0;

    if (res->a >= 0)
        sum += res->a;
    else
        return 0;
    if (res->c >= 0)
        sum += res->c;
    else
        return 0;
    if (res->t >= 0)
        sum += res->t;
    else
        return 0;
    if (res->g >= 0)
        sum += res->g;
    else
        return 0;
    if (sum == size)
        return 1;
    return 0; 
}

// Complete the steadyGene function below.
int steadyGene(char* gene) {
    int size = -1;
    int i = 0;
    int start;
    t_data  **data;
    t_data  *diff;
    t_data  *tmp1;
    t_data  *tmp2;

    while (gene[++size]);
    data = (t_data**)malloc(sizeof(t_data*) * size);
    data[0] = make_letter(gene[0]);
    while (++i < size)
    {
        data[i] = add_letter(data[i - 1], gene[i]);
        if (!data[i])
            return size;
    }
    diff = make_diff(data[i - 1], size);
    start = get_start(diff);
    while (start < size)
    {
        i = start - 1;
        while (i < size)
        {
            tmp1 = (i < start) ? dup_data(data[i]) : sub_data(data[i], data[i - start]);
            if (!tmp1)
                return start;
            tmp2 = add_data(tmp1, diff);
            if (!tmp2)
                return start;
            if (check_res(tmp2, start))
                return start;
            free(tmp1);
            free(tmp2);
            i++;
        }
        start++;
    }
    return size;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* gene = readline();

    int result = steadyGene(gene);

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

