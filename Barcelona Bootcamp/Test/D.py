l, r=1, int(input())+1
while l<r:
	m=(l+r)>>1
	print('?', m, flush=True)
	if input()=='<':
		r=m
	else:
		ans=m
		l=m+1
print('!', ans, flush=True)
