import sys
for n in map(int, sys.stdin.read().split()):
	print((((n+1)**2)>>1)*3-9)
