def C(n, m):
	ans=1
	for i in range(m):
		ans*=n-i
		ans//=i+1
	return ans

def solve(n):
	if n&1:
		return 0
	ans, n=0, n>>1
	for i in range(0, n+1, 2):
		ans+=C((i>>1)+(n-i), n-i)
	return ans

for _ in range(int(input())):
	print(solve(int(input())))
