def find(s, q, n, m, i, j):
	D=[[0, 1], [0, -1], [1, 0], [-1, 0], [1, 1], [1, -1], [-1, 1], [-1, -1]]
	for d in D:
		t=''
		for k in range(len(q)):
			x, y=i+d[0]*k, j+d[1]*k
			if 0<=x and x<n and 0<=y and y<m:
				t+=s[x][y]
		if q==t:
			return True
	return False

init=True
for _ in range(int(input())):
	if not init:
		print()
	init=False
	input()
	n, m=map(int, input().split())
	s=[input().lower() for __ in range(n)]
	for __ in range(int(input())):
		q=input().lower()
		x, y=-1, -1
		for i in range(n-1, -1, -1):
			for j in range(m-1, -1, -1):
				if s[i][j]!=q[0]:
					continue
				elif find(s, q, n, m, i, j):
					x, y=i, j
		print(x+1, y+1)
