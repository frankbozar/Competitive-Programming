def ctz(x):
	return 0 if x&1 else ctz(x>>1)+1

def clz(x):
	return len(bin(x))-3

def ok(a, b):
	p=0
	for i in range(40, -1, -1):
		p+=a[i]-a[i+1]-b[i]
		if p<0:
			return False
	return True

a=[0]*50
b=a[:]
c=[]
input()

for x in map(int, input().split()):
	if x==(x&-x):
		a[ctz(x)]+=1
	else:
		b[clz(x)]+=1

while a[0]>0:
	for i in range(40):
		if a[i]<a[i+1]:
			b[i+1]+=a[i+1]-a[i]
			a[i+1]=a[i]
	if not ok(a, b):
		break
	c+=[a[0]]
	a[0]-=1
	b[0]+=1

if c==[]:
	print(-1)
else:
	print(*reversed(c))
