import sys

data = sys.stdin.read().split()
(x,y) = map(float, data[:2])
L = map(int, data[3::3])
U = map(int, data[4::3])
F = map(float, data[5::3])
print x/(y + sum(map(lambda (l, u, f): (f-1)*(u-l), zip(L, U, F))))
