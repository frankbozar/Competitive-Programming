#!/usr/bin/env python3
import sys

def pos(x):
    if x == '': return 0
    if x[0] == '0': return pos(x[1:])
    return 2**len(x)-1-pos(x[1:])

(_, a, b) = sys.stdin.read().split()
print(pos(b)-pos(a)-1)

        
