#!/usr/bin/env python

def get(x):
    x = int(x,2)
    for i in range(5,-1,-1):
        x ^= x >> (2**i)
    return x

n,a,b = raw_input().split()
print abs(get(a)-get(b))-1
