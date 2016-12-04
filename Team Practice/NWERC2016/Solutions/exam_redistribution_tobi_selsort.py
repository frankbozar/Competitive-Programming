import sys
nums = map(int, sys.stdin.read().split()[1:])
used = [False] * len(nums)
maxi = -1
sumi = 0
for num in nums:
    maxi = max(maxi, num)
    sumi += num
if sumi - maxi < maxi:
    print "impossible"
else:
    cnt = 0
    while cnt < len(nums):
        maxi = -1
        maxidx = -1
        i = 0
        while i < len(nums):
            if not used[i] and maxi < nums[i]:
                maxidx = i
                maxi = nums[i]
            i = i+1
        used[maxidx] = True
        sys.stdout.write("%i " % (maxidx+1))
        cnt = cnt+1
