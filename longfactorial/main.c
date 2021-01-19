#include <stdio.h>

int long_mult(int num1, int num2, unsigned short int* arr)
{
    int dig1 = 0;
    int dig2 = 0;
    int i = 0;
    int j = 0;
    int ost = 0;
    int ost2 = 0;
    int tmp = num2;
    
    while (num1 != 0)
    {
        i = j;
        dig1 = num1 % 10;
        num1 = num1 / 10;
        num2 = tmp;
        while (num2 != 0)
        {
            dig2 = num2 % 10;
            num2 = num2 / 10;
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
    }
    return (i);
}

int	arr_mult(unsigned short int *arr1, int size1, unsigned short int *arr2, int size2, unsigned short int *arr)
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
    unsigned short int arr[100] = {0};
    unsigned short int arr1[100] = {0};
    unsigned short int arr2[100] = {0};

	int i = 0;
	int j = 0;
	int	l = 0;

	int k = 2;
	int tmp = k;
	
	if (n == 1 || !n)
	{
		printf("%d", 1);
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

int		main(void)
{
	extraLongFactorials(30);
}
