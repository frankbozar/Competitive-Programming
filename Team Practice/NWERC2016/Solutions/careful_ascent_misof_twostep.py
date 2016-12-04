# binary search is an overkill! :)
# just compute what you hit with v=1
# increasing speed just scales everything linearly, so scale it to hit the target

x,y=map(int, raw_input().split())
n=int(raw_input())

shields=[]
for _ in xrange(n):
    l,u,f=raw_input().split()
    shields.append((int(l), int(u), float(f)))

shields.sort()
shields.append((y,y,1.0))#sentinel

v = 1.
current_x=0.0
last=0
for shield in shields:
    current_x+=(shield[0]-last)*v
    current_x+=(shield[1]-shield[0])*shield[2]*v
    last=shield[1]

# current_x is the place we would hit with v=1
# we want to hit x instead => multiply v by (x/current_x)

print (v*x/current_x)
