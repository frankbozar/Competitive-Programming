from itertools import permutations as N
C=lambda n, m: 1 if n==m or m==0 else C(n-1, m)+C(n-1, m-1)
P=lambda n, x: 1 if x==0 else P(n-x%10, x//10)*C(n, x%10)
F=lambda s: 0 if s=='' else F(s[:-1])+ord(s[-1])-ord('0')
G=lambda x: 0 if x==0 else G(x//10)+x%10

def S(n, x):
	if G(x)>n:
		return 1
	s='0'*(n-G(x))
	for i in range(n):
		s+=chr(ord('0')+n-i)*(x//10**i%10)
	if F(s)>n:
		return P(n, x)+1
	ans=1
	for t in set(N(s)):
		y=int(''.join(t))
		if y!=x:
			ans+=S(n, y)
	return ans

for c in range(int(input())):
	s=input()
	print('Case #{0}: {1}'.format(c+1, S(len(s), int(s))))
