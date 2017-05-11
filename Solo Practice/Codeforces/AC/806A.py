def gcd(a, b):
	if b==0:
		return a, 1, 0
	g, y, x=gcd(b, a%b)
	y-=x*(a//b)
	return g, x, y

for _ in range(int(input())):
	x, y, p, q=map(int, input().split())
	if p==0:
		print(0 if x==0 else -1)
		continue
	if q==1:
		print(0 if x==y else -1)
		continue
	a, b=gcd(q, p)[1:]
	a*=p*y-q*x
	b*=q*x-p*y
	if a<0:
		t=(-a+p-1)//p
		a+=t*p
		b+=t*q
	if b<a:
		t=(a-b+q-p-1)//(q-p)
		a+=t*p
		b+=t*q
	t=min(a//p, (b-a)//(q-p))
	a-=t*p
	b-=t*q
	print(b)
