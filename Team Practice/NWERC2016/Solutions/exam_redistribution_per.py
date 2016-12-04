# !/usr/bin/env python2
import sys
print((lambda x: ' '.join([str(x[0]+1) for x in sorted(enumerate(x), key=lambda y:-y[1])]) if 2*max(x) <= sum(x) else 'impossible')(map(int, sys.stdin.read().split()[1:])))

