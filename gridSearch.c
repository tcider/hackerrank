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

// Complete the gridSearch function below.

// Please either make the string static or allocate on the heap. For example,
// static char str[] = "hello world";
// return str;
//
// OR
//
// char* str = "hello world";
// return str;
//
char* gridSearch(int G_count, char** G, int P_count, char** P) {
    int i = -1;
    int j;
    int k;
    int l;
    int flag = 0;
    static char *yes = "YES";
    static char *no = "NO";

    while (++i <= G_count - P_count)
    {
        j = -1;
        while (G[i][++j])
        {
            if (G[i][j] == P[0][0])
            {
                flag = 1;
                k = -1;
                while (++k < P_count && flag)
                {
                    l = -1;
                    while (P[k][++l] && G[i + k][j + l] && flag)
                    {
                        if (G[i + k][j + l] != P[k][l])
                            flag = 0;
                    }
                    if ((P[k][l] && !G[i + k][j + l]))
                        flag = 0;
                }
            if (flag)
                return (yes);
            }
        }
    }
    return (no);


}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* t_endptr;
    char* t_str = readline();
    int t = strtol(t_str, &t_endptr, 10);

    if (t_endptr == t_str || *t_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** RC = split_string(readline());

        char* R_endptr;
        char* R_str = RC[0];
        int R = strtol(R_str, &R_endptr, 10);

        if (R_endptr == R_str || *R_endptr != '\0') { exit(EXIT_FAILURE); }

        char* C_endptr;
        char* C_str = RC[1];
        int C = strtol(C_str, &C_endptr, 10);

        if (C_endptr == C_str || *C_endptr != '\0') { exit(EXIT_FAILURE); }

        char** G = malloc(R * sizeof(char*));

        for (int i = 0; i < R; i++) {
            char* G_item = readline();

            *(G + i) = G_item;
        }

        int G_count = R;

        char** rc = split_string(readline());

        char* r_endptr;
        char* r_str = rc[0];
        int r = strtol(r_str, &r_endptr, 10);

        if (r_endptr == r_str || *r_endptr != '\0') { exit(EXIT_FAILURE); }

        char* c_endptr;
        char* c_str = rc[1];
        int c = strtol(c_str, &c_endptr, 10);

        if (c_endptr == c_str || *c_endptr != '\0') { exit(EXIT_FAILURE); }

        char** P = malloc(r * sizeof(char*));

        for (int i = 0; i < r; i++) {
            char* P_item = readline();

            *(P + i) = P_item;
        }

        int P_count = r;

        char* result = gridSearch(G_count, G, P_count, P);

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

