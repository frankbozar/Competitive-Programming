n, m=map(int, input().split())
c, l, r, u, d=0, n, 0, m, 0
for i in range(n):
	s=input()
	for j in range(m):
		if s[j]=='X':
			c+=1
			l=min(l, i)
			r=max(r, i)
			u=min(u, j)
			d=max(d, j)
print('YES' if c==(r-l+1)*(d-u+1) else 'NO')
