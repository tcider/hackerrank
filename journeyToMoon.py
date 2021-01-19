#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the journeyToMoon function below.
def journeyToMoon(n, astronaut):
    v = dict()
    for i in astronaut:
        i.append(-1)
    k = 0
    while k < n:
        if k not in v:
            v[k] = set()
            v[k].add(k)
        flag = 0
        for i in astronaut:
            if i[2] == -1 and (i[0] == k or i[1] == k):
                i[2] = k
                v[k].add(i[0])
                v[k].add(i[1])
                if i[0] != k and i[0] in v:
                    v[i[0]].clear()
                elif i[0] != k:
                    v[i[0]] = set()
                if i[0] != k and i[1] in v:
                    v[i[1]].clear()           
                elif i[1] != k:
                    v[i[1]] = set()    
        k += 1
    k = 0
    s = 0
    while k < n:
        l = len(v[k])
        if l:
            m = 0
            while m < n:
                ll = len(v[m])
                if m != k and ll:
                    s += l * ll
                m += 1
        k += 1
    print(astronaut)
    print(v)
    return int (s / 2)

                

    

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    np = input().split()

    n = int(np[0])

    p = int(np[1])

    astronaut = []

    for _ in range(p):
        astronaut.append(list(map(int, input().rstrip().split())))

    result = journeyToMoon(n, astronaut)

    fptr.write(str(result) + '\n')

    fptr.close()

