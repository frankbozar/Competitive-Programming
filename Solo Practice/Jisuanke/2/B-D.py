import sys
import inspect
from decimal import *
getcontext().prec=128
sys.setrecursionlimit(1024)
M=dict()

def __f(r):
	r=r.replace('float', 'Decimal')
	c, s='1234567890.', ''
	i=0
	while i<len(r):
		if r[i] not in c:
			s+=r[i]
			i+=1
		else:
			j=i
			while j<len(r) and r[j] in c:
				j+=1
			t=r[i:j]
			if '.' in t:
				t='Decimal(\''+t+'\')'
			s+=t
			i=j
	return s

for _ in range(int(input())):
	e, r=input().split('=')
	r=__f(r)
	s='def {0}:'.format(e)
	s+='\n\t_, _, _, v=inspect.getargvalues(inspect.currentframe())'
	s+='\n\tk=\'{0}\'+str(v)'.format(e)
	s+='\n\tglobal M'
	s+='\n\tif k not in M:'
	s+='\n\t\tM[k]={0}'.format(r)
	s+='\n\treturn M[k]'
	sys.stderr.write(s+'\n\n')
	exec(s)

try:
	ans=eval(__f(input()))
except RecursionError:
	print('No Answer')
	exit()

if type(ans) is int:
	print(ans)
else:
	print(ans.quantize(Decimal('1.000000')))
