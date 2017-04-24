n, k=map(int, input().split())
a=list(map(int, input().split()))
m=min(a)
if any((p-m)%k!=0 for p in a):
	print(-1)
else:
	print(sum((p-m)//k for p in a))
