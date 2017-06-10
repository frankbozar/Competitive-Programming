I=lambda: map(int, input().split())
n, k=I()
a=list(I())
b=list(I())
if k>=2:
	print('Yes')
else:
	a=[b[0] if x==0 else x for x in a]
	print('Yes' if any(a[i]<=a[i-1] for i in range(1, n)) else 'No')

