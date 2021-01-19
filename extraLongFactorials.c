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

// Complete the extraLongFactorials function below.
int    arr_mult(unsigned short int *arr1, int size1, unsigned short int *arr2, int size2, unsigned short int *arr)
{
    int dig1 = 0;
    int dig2 = 0;
    int i = 0;
    int j = 0;
    int ost = 0;
    int ost2 = 0;
    int k = 0, n = 0;
    
    while (k < size1)
    {
        i = j;
        dig1 = arr1[k];
        n = 0;
        while (n < size2)
        {
            dig2 = arr2[n];
            if (dig1 * dig2 + ost > 9)
            {
                arr[i] += (ost2 + (dig1 * dig2 + ost) % 10);
                if (arr[i] > 9)
                {
                    ost2 = arr[i] / 10;
                    arr[i] = arr[i] % 10;
                }
                else
                {
                    ost2 = 0;
                }
                ost = (dig1 * dig2 + ost) / 10;
            }
            else
            {
                arr[i] += (ost2 + dig1 * dig2 + ost);
                if (arr[i] > 9)
                {
                    ost2 = arr[i] / 10;
                    arr[i] = arr[i] % 10;
                }
                else
                {
                    ost2 = 0;
                }
                ost = 0;
            }
            i++;
            n++;
        }
        if (ost || ost2)
        {
            arr[i] += (ost + ost2);
            if (arr[i] > 9)
            {
                arr[i] = arr[i] % 10;
                i++;
                arr[i] = arr[i] / 10;
            }
            i++;
            ost = 0;
            ost2 = 0;
        }
        j++;
        k++;
    }
    return (i);
}
 
void extraLongFactorials(int n) {
    unsigned short int arr[1000] = {0};
    unsigned short int arr1[1000] = {0};
    unsigned short int arr2[1000] = {0};

    int i = 0;
    int j = 0;
    int    l = 0;

    int k = 2;
    int tmp = k;
    
    if (n == 1 || !n)
    {
        printf("%d", 1);
        return ;
    }

    if (n < 0)
    {
        printf ("0");
        return ;
    }
    arr[0] = 1;
    j = 1;
    while (k <= n)
    {
        l = 0;
        while (l < j)
        {
            arr2[l] = arr[l];
            arr[l] = 0;
            l++;
        }
        i = 0;
        tmp = k;
        while (tmp)
        {
            arr1[i] = tmp % 10;
            tmp /= 10;
            i++;
        }
        j = arr_mult(arr1, i, arr2, l, arr);
        k++;
    }
    while (--j >= 0)
        printf("%d", arr[j]); 
}

int main()
{
    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    extraLongFactorials(n);

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

