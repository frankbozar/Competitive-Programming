n=int(input())
a=[list(map(int, input().split())) for _ in range(n)]
if any(a[i][0]!=a[i][1] for i in range(n)):
	print('rated')
elif a==list(reversed(sorted(a))):
	print('maybe')
else:
	print('unrated')
