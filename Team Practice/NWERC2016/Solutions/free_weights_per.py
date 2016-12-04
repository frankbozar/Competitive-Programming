import sys

R = map(int, sys.stdin.read().split())[1:]
R = R[:len(R)/2] + [2**30]*2 + R[len(R)/2:]

def check(R, thres):
    prev = -1
    for w in R:
        if w <= thres: continue
        if prev in [-1, w]: prev = w-1-prev
        else: return False
    return prev == -1

All = list(sorted([0]+R))
lo = -1
hi = len(R)/2
while hi-lo > 1:
    m = (lo+hi)/2
    if check(R, All[2*m]): hi = m
    else: lo = m
print All[2*hi]
