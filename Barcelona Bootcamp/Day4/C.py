z = int(input())
for _ in range(z):
	n = int(input())
	if n == 1:
		print('1 1 1 2')
	elif n == 2:
		print('1 1 1 2')
		print('1 3 1 4')
		print('1 5 1 6')
	elif n == 3:
		print('1 1 1 2')
		print('1 3 1 4')
		print('2 3 3 3')
		print('1 5 2 5')
		print('2 4 3 4')
		print('4 3 4 4')
	elif n == 4:
		print(1,2,1,3)
		print(1,1,2,1)
		print(2,2,2,3)
		print(1,4,2,4)
		print(4,1,5,1)
		print(3,1,3,2)
		print(5,2,5,3)
		print(4,2,4,3)
		print(3,3,3,4)
		print(4,4,5,4)
	else:
		print('impossible')
