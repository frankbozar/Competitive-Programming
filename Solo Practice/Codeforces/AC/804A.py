M, a, b=10**9+7, 0, 0
for c in reversed(input()):
	if c=='b':
		b+=1
	else:
		a+=b
		b=(b<<1)%M
print(a%M)
