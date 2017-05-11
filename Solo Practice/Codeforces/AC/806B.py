def f(v, x, n):
	if v<0:
		return 0
	for i in range(1, 7):
		if x<<i>n or i==6:
			return (250-v)*i<<1

n=int(input())
a=[list(map(int, input().split())) for _ in range(n)]
c=[sum(_[i]>=0 for _ in a) for i in range(5)]
ans=-1
for i in range(10000):
	p, q=0, 0
	for j in range(5):
		if a[0][j]>a[1][j] and a[1][j]>=0:
			c[j]+=1
		p+=f(a[0][j], c[j], n+i)
		q+=f(a[1][j], c[j], n+i)
	if p>q:
		ans=i
		break
print(ans)

