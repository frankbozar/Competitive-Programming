import sys
M={}
for line in sys.stdin:
	if line.count('#')>0:
		break
	for s in line.split():
		cnt=sum(s.lower().count(chr(ord('a')+i))*(100**i) for i in range(26))
		if cnt not in M:
			M[cnt]=[]
		M[cnt]+=[s]
S=set()
for cnt in M:
	if len(M[cnt])==1:
		S|={M[cnt][0]}
print(*sorted(S), sep='\n')
