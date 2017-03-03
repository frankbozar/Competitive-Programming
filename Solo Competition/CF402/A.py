s, t=input(), input()
a=[int(x)-1 for x in input().split()]
l, r, n=0, len(s), len(t)
while l<r:
	m, p=(l+r)>>1, 0
	for d in sorted(a[m:]):
		if s[d]==t[p]:
			p+=1
		if p>=n:
			break
	if p<n:
		r=m
	else:
		l, ans=m+1, m
print(ans)
