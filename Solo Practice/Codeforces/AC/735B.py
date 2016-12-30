_, n, m=map(int, input().split())
a=list(reversed(sorted(map(int, input().split()))))
if n>m:
	n, m=m, n
print(sum(a[:n])/n+sum(a[n:n+m])/m)
