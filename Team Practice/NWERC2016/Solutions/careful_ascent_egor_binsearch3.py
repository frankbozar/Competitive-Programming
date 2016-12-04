#!/usr/bin/env python3

#translation of egor_binsearch to python3

#performs binary search over the horizontal velocity
#         by simulating the flight for a given horizontal velocity

x,y=map(int, input().split())
n=int(input())

shields=[]
for _ in range(n):
    l,u,f=input().split()
    shields.append((int(l), int(u), float(f)))

shields.sort()
shields.append((y,y,1.0))#sentinel

min_v, max_v=-100.0, 100.0 #actually -10.0, 10.0 would be enough...

while max_v-min_v>1e-9:
    middle=(min_v+max_v)/2.0
    current_x=0.0
    last=0
    for shield in shields:
        current_x+=(shield[0]-last)*middle
        current_x+=(shield[1]-shield[0])*shield[2]*middle
        last=shield[1]
    if current_x>x:
        max_v=middle
    else:
        min_v=middle
       
print((min_v+max_v)/2.0)

