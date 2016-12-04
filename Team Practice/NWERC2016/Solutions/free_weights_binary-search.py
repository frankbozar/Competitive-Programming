#!/usr/bin/env python

def solve(v):
    lef = -1
    rgt = max(v)
    while lef + 1 < rgt:
        mid = (lef + rgt) / 2
        z = filter(lambda i: i > mid, v)
        if z[0::2] <> z[1::2]:
            lef = mid
        else:
            rgt = mid
    return rgt

n = int(raw_input())
v = map(lambda x: map(int, raw_input().split()), range(2))
print max(map(solve, v))


