n=int(input())
s=input()
l, r, u, d=[-1]*4
ans=1
for i in range(n):
	if s[i]=='L':
		if r>=0:
			ans+=1
			l, r, u, d=[-1]*4
		l=i
	if s[i]=='R':
		if l>=0:
			ans+=1
			l, r, u, d=[-1]*4
		r=i
	if s[i]=='U':
		if d>=0:
			ans+=1
			l, r, u, d=[-1]*4
		u=i
	if s[i]=='D':
		if u>=0:
			ans+=1
			l, r, u, d=[-1]*4
		d=i
print(ans)
