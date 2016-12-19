import sys
a, b, c=map(int, sys.stdin.read().split())
print(min(a, b>>1, c>>2)*7)
