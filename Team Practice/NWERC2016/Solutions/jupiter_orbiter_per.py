import sys
import heapq

(N, Q, I) = map(int, sys.stdin.readline().split())
queue = map(int, sys.stdin.readline().split())
size = map(int, sys.stdin.readline().split())

download = [0]*N
tot = [[0]*Q for _ in range(N+1)]
deadline = [N]*Q
nxt = []

for i in range(N):
    vals = map(int, sys.stdin.readline().split())
    download[i] = vals[0]
    for j in range(I):
        tot[i][queue[j]-1] += vals[j+1]
    for j in range(Q):
        if i > 0:
            tot[i][j] += tot[i-1][j]
        if deadline[j] >= i and tot[i][j] > size[j]:
            deadline[j] = i

for j in range(Q):
    tot[N][j] = 1<<40
    if tot[N-1][j] > 0:
        heapq.heappush(nxt, (deadline[j], j))
        
def go():
    sent = [0]*Q
    for i in range(N):
        rem = download[i]
        sat = []
        while rem > 0 and len(nxt) > 0:
            (dl, j) = heapq.heappop(nxt)
            if dl <= i:
                return False
            send = min(rem, min(tot[i][j]-sent[j], tot[dl][j]-size[j]-sent[j]))
            if send > 0:
                rem -= send
                sent[j] += send
                while dl < N and tot[dl][j]-sent[j] <= size[j]:
                    dl += 1
                if sent[j] < tot[N-1][j]:
                    heapq.heappush(nxt, (dl, j))
            elif sent[j] < tot[N-1][j]:
                sat.append((dl, j))
        for p in sat:
            heapq.heappush(nxt, p)
    return len(nxt) == 0

print 'possible' if go() else 'impossible'
