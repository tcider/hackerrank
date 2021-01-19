#include <stdio.h>
#include <stdlib.h>

int        find_place(int num, int start, int end, int* scores)
{
    if (end - start <= 1)
    {
        if (num < scores[end])
            return (end + 1);
        else if (num < scores[start])
            return (start + 1);
        else
            return (start);
    }
    if (num < scores[(end + start) / 2])
        return (find_place(num, ((end + start) / 2), end, scores));
    else if (num > scores[(end + start) / 2])
        return (find_place(num, start, ((end + start) / 2), scores));
    else if (num == scores[(end + start) / 2])
        return ((end + start) / 2);
    return (0);
}

int* climbingLeaderboard(int scores_count, int* scores, int alice_count, int* alice, int* result_count) {
    int i = 0;
    int j = 1;
    int size = 1;
    int* res;
 
    res = (int*)malloc(sizeof(int) * alice_count);
    while (++i < scores_count)
        if (scores[i] != scores[i - 1])
            size++;
    int arr[size];
    arr[0] = scores[0];
    i = 0;
    while (++i < scores_count)
        if (scores[i] != scores[i - 1])
        {
            arr[j] = scores[i];
            j++;
        }
    i = -1;
    while (++i < alice_count)
        res[i] = find_place(alice[i], 0, size - 1, arr) + 1;
    result_count = res;
    return (res);
}

int		main(void)
{
	int		aa[7] = {100, 100, 50, 40, 40, 20, 10};
	int		bb[4] = {5, 25, 50, 120};
	int		*p;
	int		i = -1;

	p = (int*)malloc(sizeof(int) * 6);
	p = climbingLeaderboard(7, aa, 4, bb, p);
	while (++i < 6)
		printf("%d\n", p[i]);
	//i = find_place(120, 0, 6, aa);
	//printf("\n%d\n", i);
}
	
