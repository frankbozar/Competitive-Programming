I=lambda: map(int, input().split())
I()
n, a=sum(I()), -1
for _ in range(*I()):
	l, r=I()
	if n<=r:
		a=max(n, l)
		break
print(a)
