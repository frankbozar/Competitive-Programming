n, k=map(int, input().split())
a=[i+1 for i in range(n*n)]
b=[[0]]
k-=1
for _ in range(n):
	b+=[ a[:k]+a[k-n:] ]
	a=a[k:k-n]
	b[0][0]+=b[-1][k]
for _ in b:
	print(*_)
