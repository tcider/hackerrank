#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'dynamicArray' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER n
#  2. 2D_INTEGER_ARRAY queries
#

def dynamicArray(n, queries):
    # Write your code here
    last = 0
    k = 0
    res = []
    res2 = []
    while k < n:
        res.append([])
        k += 1
    for i in queries:
        if i[0] == 1:
            res[(i[1] ^ last) % n].append(i[2])
        else:
            j = (i[1] ^ last) % n
            last = res[j][i[2] % len(res[j])]
            res2.append(last)
            print (last)
    return res2

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    q = int(first_multiple_input[1])

    queries = []

    for _ in range(q):
        queries.append(list(map(int, input().rstrip().split())))

    result = dynamicArray(n, queries)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()

