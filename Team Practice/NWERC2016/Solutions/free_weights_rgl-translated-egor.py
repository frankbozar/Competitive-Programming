#!/usr/bin/env python3

r,n = 0,int(input())
for o in range(2):
  a,v = None,map(int, input().split())
  for i in v:
    if a is None: a = i
    elif a == i: a = None
    else:
      r = max(r,min(a,i))
      a = max(a,i)
  r = max(r,0 if a is None else a)
print(r)
