input()
s=input()
a=''
while s!='':
	a=a+s[0] if len(s)&1==1 else s[0]+a
	s=s[1:]
print(a)
