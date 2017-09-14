for _ in range(int(input())):
	try:
		eval(input())
		print('legal expression')
	except SyntaxError:
		print('illegal expression')
	except:
		print('legal expression')
