def f():
	a=p=0
	for x in sorted(map(int, input().split())):
		a+=p+x//2
		p+=x
	return a
for _ in range(int(input())):
	input()
	print(f()+f())
