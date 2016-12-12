def gcd(a, b):
	if b==0:
		return a, 1, 0
	g, y, x=gcd(b, a%b)
	return g, x, y-x*(a//b)

def solve(n, a, b, c, d):
	flag=False
	if a*d>c*b:
		a, b, c, d, flag=c, d, a, b, True
	g, x, y=gcd(b, d)
	if n%g!=0:
		return ['failed']
	x*=n//g
	y*=n//g
	if y<0:
		delta=(b-y)//(b//g)
		x-=delta*(d//g)
		y+=delta*(b//g)
	if y>0:
		delta=y//(b//g)
		x+=delta*(d//g)
		y-=delta*(b//g)
	if x<0:
		return ['failed']
	elif flag:
		return y, x
	else:
		return x, y

while True:
	n=int(input())
	if n<=0:
		break
	a, b=map(int, input().split())
	c, d=map(int, input().split())
	print(*solve(n, a, b, c, d))
