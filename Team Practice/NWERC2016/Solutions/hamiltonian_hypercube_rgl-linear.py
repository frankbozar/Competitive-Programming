#!/usr/bin/env python

def get(x):
    res = ''
    acc = False
    for i in x:
        acc = (acc != (i == '1'))
        res += ('1' if acc else '0')
    return int(res,2)

n,a,b = raw_input().split()
print abs(get(a)-get(b))-1
