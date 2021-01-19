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

typedef struct      s_list
{
    int             data;
    int             index;
    struct s_list   *next;
}                   t_list;

int     cmp(const void *a, const void *b)
{
    return *((int*)a)- *((int*)b);
}

t_list  *createElem(int data, int i)
{
    t_list  *list;

    list = (t_list*)malloc(sizeof(list));
    list->data = data;
    list->index = i;
    list->next = NULL;
    return list;
}

t_list  *makeList(int *arr, int size)
{
    int i = -1;
    t_list  *tmp;
    t_list  *prev = NULL;
    t_list  *head;
    t_list  *final_head;

    //qsort(arr, size, sizeof(int), cmp);
    while (++i < size)
    {
        tmp = createElem(arr[i], i);
        if (prev)
            prev->next = tmp;
        else
            head = tmp;
        prev = tmp;
    }
    prev->next = NULL;
    final_head = head;
    i = -1;
    while (++i < size)
    {
        prev = NULL;
        while (head && head->next)
        {
            if (head->data > head->next->data)
            {
                if (head == final_head)
                    final_head = head->next;
                tmp = head->next;
                head->next = head->next->next;
                tmp->next = head;
                if (prev)
                    prev->next = tmp;
                prev = tmp;
            }
            else
            {
                prev = head;
                head = head->next;
            }
        }
        head = final_head;
    }
    return final_head;
}

int     getMedian(t_list *list, int size)
{
    int i = 0;

    if (size == 1)
        return 2 * list->data;
    while (++i < size / 2)
        list = list->next;
    if (size % 2)
        return 2 * list->next->data;
    else
        return list->data + list->next->data;
}

t_list  *changeList(t_list *list, int *arr, int rem, int add)
{
    t_list  *prev;
    t_list  *final_head;
    t_list  *tmp;
    int     flag = 1;

    prev = NULL;
    final_head = list;
    while (flag && list)
    {
        if (list->index == rem)
        {
            if (prev)
                prev->next = list->next;
            else
                final_head = list->next;
            flag = 0;
        }
        else
            prev = list;
        list = list->next;
    }
    list = final_head;
    prev = NULL;
    while (list && arr[add] >= list->data)
    {
        prev = list;
        list = list->next;
    }
    tmp = createElem(arr[add], add);
    if (!prev)
    {
        tmp->next = final_head;
        final_head = tmp;
    }
    else
    {
        prev->next = tmp;
        tmp->next = list;
    }
    return final_head;  
}

// Complete the activityNotifications function below.
int activityNotifications(int expenditure_count, int* expenditure, int d) {
    t_list  *list;
    int     i = d;
    int sum;

    list = makeList(expenditure, d);
    if (expenditure[d] >= getMedian(list, d))
        sum = 1;
    else
        sum = 0;
    while (++i < expenditure_count)
    {
        list = changeList(list, expenditure, i - d - 1, i - 1); 
        if (expenditure[i] >= getMedian(list, d))
            sum++;
    }
    return sum;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nd = split_string(readline());

    char* n_endptr;
    char* n_str = nd[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* d_endptr;
    char* d_str = nd[1];
    int d = strtol(d_str, &d_endptr, 10);

    if (d_endptr == d_str || *d_endptr != '\0') { exit(EXIT_FAILURE); }

    char** expenditure_temp = split_string(readline());

    int* expenditure = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* expenditure_item_endptr;
        char* expenditure_item_str = *(expenditure_temp + i);
        int expenditure_item = strtol(expenditure_item_str, &expenditure_item_endptr, 10);

        if (expenditure_item_endptr == expenditure_item_str || *expenditure_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(expenditure + i) = expenditure_item;
    }

    int expenditure_count = n;

    int result = activityNotifications(expenditure_count, expenditure, d);

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

