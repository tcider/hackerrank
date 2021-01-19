#include <stdio.h>
#include <stdlib.h>

int module(int i)
{
    if (i < 0)
        i = -1 * i;
    return (i);
}
 
int**   rotate(int** s)
{
    int**   tmp;
    tmp = (int**)malloc(sizeof(int*) * 3);
    int     i = 0;
    int     j = -1;
    while (i < 3)
    {
        tmp[i] = (int*)malloc(sizeof(int) * 3);
        j = -1;
        while (++j < 3)
            tmp[i][j] = s[2 - j][i];
        i++;
    }
    return (tmp);
}
 
int     minus(int** s1, int** s2)
{
    int s = 0;
    int i = -1;
    int j = -1;
 
    while (++i < 3)
    {
        j = -1;
        while (++j < 3)
            s += module(s1[i][j] - s2[i][j]);
    }
    return (s);
}
// Complete the formingMagicSquare function below.
int formingMagicSquare(int s_rows, int s_columns, int** s) {
    int i = -1;
    int min = 15;
	int	tmp = 0;
	int** orig = (int**)malloc(sizeof(int*) * 3);
	while (++i < 3)
		orig[i] = (int*)malloc(sizeof(int) * 3);
	orig[0][0] = 4;
	orig[1][0] = 3;
	orig[2][0] = 8;
    orig[0][1] = 9;
	orig[1][1] = 5;
	orig[2][1] = 1;
	orig[0][2] = 2;
	orig[1][2] = 7;
	orig[2][2] = 6;
 
    s_rows = s_columns;
	i = -1;
	while (++i <= 4)
    {
        tmp = minus(orig, s);
        if (tmp < min)
            min = tmp;
        //orig = rotate(orig);
    }
    return (tmp);
}

int	main()
{
	int i = -1;

	int** orig = (int**)malloc(sizeof(int*) * 3);
	while (++i < 3)
		orig[i] = (int*)malloc(sizeof(int) * 3);
	orig[0][0] = 4;
	orig[1][0] = 3;
	orig[2][0] = 7;
    orig[0][1] = 9;
	orig[1][1] = 5;
	orig[2][1] = 2;
	orig[0][2] = 2;
	orig[1][2] = 7;
	orig[2][2] = 6;

	printf("%d\n", formingMagicSquare(3, 3, orig));
}

