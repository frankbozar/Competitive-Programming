import sys

def pro(a):
	ans=1
	for x in a:
		ans*=x
	return ans

def solve(a):
	ans=-1<<2000
	n=len(a)
	for i in range(n):
		tmp=1
		for j in range(i, n):
			tmp*=a[j]
			ans=max(ans, tmp)
	return ans

for s in sys.stdin:
	s=s.strip()
	if s!='':
		print(solve(list(map(int, s.split()))))
