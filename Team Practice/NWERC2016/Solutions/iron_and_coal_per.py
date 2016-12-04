import sys
(n, m, k) = map(int, sys.stdin.readline().split())
ore = map(int, sys.stdin.readline().split())
coal = map(int, sys.stdin.readline().split())
adj = [[]] + [map(int, sys.stdin.readline().split()[1:]) for _ in range(n)]
radj = [[] for _ in range(n+1)]
for u in range(1, n+1):
    for v in adj[u]:
        radj[v].append(u)

def bfs(S, adj):
    dist = [n]*(n+1)
    q = [0]*(n+1)
    qh = qt = 0
    for s in S:
        dist[s] = 0
        q[qh] = s
        qh += 1
    while qt < qh:
        u = q[qt]
        qt += 1
        for v in adj[u]:
            if dist[v] == n:
                dist[v] = dist[u] + 1
                q[qh] = v
                qh += 1
    return dist

ans = min(map(lambda (d1, d2, d3): d1+d2+d3, zip(bfs(ore, radj), bfs(coal, radj), bfs([1], adj))))
print ans if ans < n else 'impossible'
