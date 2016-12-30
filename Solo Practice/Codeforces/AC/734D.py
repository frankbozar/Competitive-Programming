INF=1<<100
n=int(input())
x, y=map(int, input().split())
a=[(INF, '')]*8
for _ in range(n):
	t, u, v=input().split()
	u, v=int(u)-x, int(v)-y
	if u==0:
		p=0 if v>0 else 1
		a[p]=min(a[p], (abs(v), t))
	elif v==0:
		p=2 if u>0 else 3
		a[p]=min(a[p], (abs(u), t))
	elif u==v:
		p=4 if u>0 else 5
		a[p]=min(a[p], (abs(u), t))
	elif u==-v:
		p=6 if v>0 else 7
		a[p]=min(a[p], (abs(v), t))
print('YES' if any(d<INF and t in ['Q', 'R'] for d, t in a[:4]) or any(d<INF and t in ['Q', 'B'] for d, t in a[4:]) else 'NO')
