k = int(input())
k = k & (-k)
ans = (pow(2,k,10**9+7)+10**9+6)%(10**9+7)
print(ans)
