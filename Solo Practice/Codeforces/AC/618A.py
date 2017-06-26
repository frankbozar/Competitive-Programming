a=[0]
for _ in range(int(input())):
	a+=[1]
	while a[-2]==a[-1]:
		a.pop()
		a[-1]+=1
print(*a[1:])
