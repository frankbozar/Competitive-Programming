n, k=map(int, input().split())
k-=1
ans=-1
for i in range(n-1, -1, -1):
	l=(1<<i)-1
	if k==l:
		ans=i+1
		break
	elif k>l:
		k-=l+1
print(ans)
