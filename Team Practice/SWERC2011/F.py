from itertools import permutations as perm
def F(s):
	a=set()
	for c in s:
		if 'a'<=c and c<='z':
			a|={c}
	return sorted(list(a))
while True:
	S=list(map(int, input().split()))
	if S==[0]*2:
		break
	N=S[0]
	V=S[-1]
	A=sorted(S[1:-1])
	S=input()
	C=F(S)
	S=compile(S, '<string>', 'eval')
	ans=False
	for P in perm(C):
		for I in range(N):
			exec('{0}={1}'.format(P[I], A[I]))
		if eval(S)==V:
			ans=True
			break
	print('YES' if ans else 'NO')
