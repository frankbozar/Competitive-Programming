#!/usr/bin/env python3

n = input()
v = sorted(enumerate(map(int, input().split())), key=lambda x:-x[1])

if v[0][1] <= sum(map(lambda x: x[1], v[1:])):
    print(' '.join(map(lambda x: str(x[0]+1), v)))
else:
    print('impossible')
