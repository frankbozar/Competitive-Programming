def relax(e, d):
	ans=False
	for u, v, w in e:
		if d[v]>d[u]+w:
			d[v]=d[u]+w
			ans=True
	return ans

def solve(e, n):
	d=[0]*(n+1)
	for i in range(n):
		if not relax(e, d):
			return False
	return relax(e, d)

while True:
	try:
		n, m=map(int, input().split())
	except:
		break
	e=[]
	for i in range(m):
		u, v, s, w=input().split()
		u, v, w=int(u), int(v), int(w)
		if s[0]=='g':
			e+=[(u-1, u+v, -w-1)]
		else:
			e+=[(u+v, u-1, w-1)]
	print('successful conspiracy' if solve(e, n) else 'lamentable kingdom')
