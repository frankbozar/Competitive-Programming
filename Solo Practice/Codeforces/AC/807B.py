def f(p, d, x, y):
	x+=d*50
	if x<y:
		return
	s=(x//50)%475
	for i in range(25):
		s=(96*s+42)%475
		if s+26==p:
			print(0 if d<0 else (d+1)>>1)
			exit()
p, x, y=map(int, input().split())
for i in range(-500, 500):
	f(p, i, x, y)
