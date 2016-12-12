init=True
while True:
	try:
		n=int(input())
	except:
		exit()
	if not init:
		print()
	init=False
	name=list(input().split())
	M={}
	for x in name:
		M[x]=0
	for _ in range(n):
		s=list(input().split())
		a, b=int(s[1]), int(s[2])
		if b==0:
			continue
		M[ s[0] ]-=a-a%b
		for i in range(b):
			M[ s[i+3] ]+=a//b
	for x in name:
		print(x, M[x])
