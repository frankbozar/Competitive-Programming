def solve(s, t):
	n=len(s)
	M={}
	for i in range(n):
		if M.get(s[i], t[i])!=t[i] or M.get(t[i], s[i])!=s[i]:
			return -1
		M[ s[i] ]=t[i]
		M[ t[i] ]=s[i]
	return M
M=solve(input(), input())
if M==-1:
	print(-1)
else:
	M=list((c, M[c]) for c in M if c<M[c])
	print(len(M))
	for x in M:
		print(*x)
