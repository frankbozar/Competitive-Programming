_, n, m=map(int, input().split())
n, m=n<<1, m-1
print(m//n+1, (m%n+2)>>1, 'LR'[m&1])
