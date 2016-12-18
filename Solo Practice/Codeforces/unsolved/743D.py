import sys
sys.setrecursionlimit(1<<25)
INF=1<<60

def dfs(w, e, u=0, p=-1):
	ans, x, y=[-INF]*3
	s=w[u]
	for v in e[u]:
		if v==p:
			continue
		a, m, t=dfs(w, e, v, u)
		ans=max(ans, a)
		s+=t
		if y<m:
			y=m
		if x<y:
			x, y=y, x
	if y>-INF:
		ans=max(ans, x+y)
	return ans, max(x, s), s

n=int(input())
e=[[] for _ in range(n)]
w=list(map(int, input().split()))
for i in range(1, n):
	u, v=map(int, input().split())
	u, v=u-1, v-1
	e[u]+=[v]
	e[v]+=[u]
ans=dfs(w, e)[0]
print('Impossible' if ans<=-INF else ans)

