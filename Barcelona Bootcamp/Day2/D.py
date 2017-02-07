def f(x):
	return x ^ (x>>1)
x = int(input())
print(1,x)
y = f(x)
cnt = 2
while y != x:
	print(cnt,y)
	cnt += 1
	y = f(y)
print(cnt,y)

