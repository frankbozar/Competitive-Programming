R=range(65)
x, y, l, r=map(int, input().split())
g=[l-1, r+1]
for a in [ x**i for i in R if x**i<=r ]:
	for b in [ y**i for i in R if y**i<=r-a ]:
		if l<=a+b:
			g+=[a+b]
g.sort()
a=0
for i in range(1, len(g)):
	a=max(a, g[i]-g[i-1]-1)
print(a)
