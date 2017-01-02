n=int(input())
a=[]
while n>len(a):
	a+=[len(a)+1]
	n-=a[-1]
a[-1]+=n
print(len(a))
print(*a)
