from itertools import combinations as C
import sys
init=True
for line in sys.stdin:
	num=sorted(list(map(int, line.split()))[1:])
	if num==[]:
		break
	elif not init:
		print()
	init=False
	for c in C(num, 6):
		print(*c)
