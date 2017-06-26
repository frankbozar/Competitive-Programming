n=int(input())
R=range(n)
a=[list(map(int, input().split())) for _ in R]
b=[0]*n
for i in R:
	for j in R:
		if a[j].count(i+1)==n-1:
			b[j]=i+1
			a[j]=[0]*n
			break
	for j in R:
		for k in R:
			if a[k][j]==i+1:
				a[k][j]+=1
print(*b)
