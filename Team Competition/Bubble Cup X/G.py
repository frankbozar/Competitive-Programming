n, m=map(int, input().split())
M=dict()
for i in range(n):
	s=input()
	if s not in M:
		M[s]=1
t=['', 'a', 'b', 'c', 'd', 'e']
for i in range(m):
	s=input()
	ans=0
	if '?' in s:
		for p in t:
			ans+=M.get(s.replace('?', p), 0)
	else:
		ans=M.get(s, 0)
	print(ans)
