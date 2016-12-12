input()
case=1
import sys
for s in sys.stdin:
	n, k, p=map(int, s.split())
	print('Case {0}: {1}'.format(case, (k-1+p)%n+1))
	case+=1
