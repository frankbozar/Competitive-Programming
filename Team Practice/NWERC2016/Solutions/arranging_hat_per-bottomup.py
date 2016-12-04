import sys
sys.setrecursionlimit(8000)

(n, m) = map(int, sys.stdin.readline().split())
v = [map(int, list(x)) for x in sys.stdin.read().split()]

def enc(begin, end, pos, dig):
    return ((end*n+begin)*m+pos)*10+dig

opt = [None]*(n*(n+1)*m*10)

for end in range(n+1):
    for begin in range(end-1, -1, -1):
        for pos in range(m-1,-1,-1):
            for dig in range(9, -1, -1):
                here = 0
                res = 1<<20
                back = -1
                for i in range(begin, end+1):
                    c1 = opt[enc(begin, i, pos+1, 0)][0] if pos < m-1 and begin < i else 0
                    c2 = opt[enc(i, end, pos, dig+1)][0] if dig < 9 and i < end else 0 if i == end else 1<<20
                    if c1+c2+here < res:
                        res = c1+c2+here
                        back = i
                    if i < end and v[i][pos] != dig:
                        here += 1
                opt[enc(begin, end, pos, dig)] = (res, back)

def Sort(begin, end, pos, dig):
    if pos == m or end-begin <= 0:
        return
    back = opt[enc(begin, end, pos, dig)][1]
    for i in range(begin, back):
        v[i][pos] = dig
    Sort(begin, back, pos+1, 0)
    Sort(back, end, pos, dig+1)

Sort(0, n, 0, 0)
print ' '.join(''.join(map(str, x)) for x in v)

