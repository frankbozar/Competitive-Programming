n=int(input())
a=list(map(int, input().split()))
p=s=sum(a)
for i in range(n-2, 0, -1):
	s-=a[i+1]
	p=max(p, s-p)
print(p)
