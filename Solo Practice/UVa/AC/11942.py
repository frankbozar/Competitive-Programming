print('Lumberjacks:')
for _ in range(int(input())):
	a=list(map(int, input().split()))
	print('Ordered' if sorted(a) in [a, list(reversed(a))] else 'Unordered')
