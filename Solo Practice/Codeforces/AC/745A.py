s=input()
S=set()
for _ in range(len(s)):
	S|={s}
	s=s[1:]+s[0]
print(len(S))
