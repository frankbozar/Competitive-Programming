def steps(array):
	if len(array) == 0:
		return 0
	pivot = array[0]
	count = 0
	lesser = []
	greater = []
	for element in array:
		count += 1
		if element < pivot:
			lesser.append(element)
		elif element > pivot:
			greater.append(element)
	return count + steps(lesser) + steps(greater)

a=list(map(int, input().split()))
print(steps(a))
