ch=lambda x: chr(ord('a')+x)
ix=lambda x: ord(x)-ord('a')

def g(s, x):
	c=[0]*26
	n=len(s)
	for i in range(n):
		if x-i+n-1>0:
			c[ix(s[i])]+=(x-i+n-1)//n
	return c

def f(a, b, l, r):
	s=[ch(i) for i in range(a)]
	s+=s[-1:]*b
	
	while True:
		t=''.join(s[-a:])
		i=0
		for _ in range(a):
			while ch(i) in t:
				i+=1
			s+=[ch(i)]
			t+=ch(i)
		s+=s[-1:]*b
		if s[-a-b:]==s[:a+b]:
			break
	s=s[:-a-b]
	c=g(s, l-1)
	d=g(s, r)
	ans=0
	for i in range(26):
		if d[i]>c[i]:
			ans+=1
	return ans

a, b, l, r=map(int, input().split())
print(f(a, b, l, r))
