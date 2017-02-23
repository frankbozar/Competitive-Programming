a, b=input().split()
print(a, b)

for _ in range(int(input())):
	c, d=input().split()
	if a==c:
		a=d
	else:
		b=d
	print(a, b)
