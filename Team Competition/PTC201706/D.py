import math
log=lambda x: math.log(x, 10)
ceil=lambda x: int(math.floor(x+1))
M={}
N={}
p=1
for i in range(1, 11):
	p*=i
	M[str(p)]=i
p=0
for i in range(1, 100001):
	p+=log(i)
	N[ceil(p)]=i
for _ in range(int(input())):
	s=input().strip().lstrip('0')
	print(M.get(s, N[len(s)]))

