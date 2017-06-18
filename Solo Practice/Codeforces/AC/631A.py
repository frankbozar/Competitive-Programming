from functools import reduce
I=lambda: reduce(lambda x, y: x|y, map(int, input().split()))
input()
print(I()+I())
