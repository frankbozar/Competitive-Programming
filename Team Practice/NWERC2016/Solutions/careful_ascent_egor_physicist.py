#calculates the effective tickness of every shield

x,y=map(float, raw_input().split()) # treat input ints as floats!
n=int(raw_input())

#calculate y_eff:
for _ in xrange(n):
    l,u,f=map(float, raw_input().split())
    y-=(u-l)*(1.0-f)

print x/y
