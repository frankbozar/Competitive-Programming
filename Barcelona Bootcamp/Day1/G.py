# NCTU_Foudre
import sys
from random import randint
A, B = [], []
n = 9
while len(A)==len(B) and len(A)<=10000:
	a, b, c = randint(1,n), randint(1,n), randint(1,n)
	while a == b or a == c or b == c:
		a, b, c = randint(1,n), randint(1,n), randint(1,n)
	ok = False
	for s in A:
		if not (a in s or b in s or c in s):
			s += [a,b,c]
			ok = True
			break
	if not ok:
		A.append([a,b,c])
	max_len = 0
	for s in B:
		if not (a in s or b in s or c in s):
			max_len = max(len(s),max_len)
	if max_len:
		for s in B:
			if len(s) != max_len: continue
			if not (a in s or b in s or c in s):
				s += [a,b,c]
				break
	else:
		B.append([a,b,c])
	print(a,b,c)
	print(A,file=sys.stderr)
	print(B,file=sys.stderr)
	input()
print(len(A), len(B))
