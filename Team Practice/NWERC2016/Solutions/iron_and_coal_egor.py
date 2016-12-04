# finds a node with dist(node->coal)+dist(node->ore)+dist(root->node) minimal
# the distances from root is found by bfs on the graph
# the distances from coals, ores found by bfs on the reverted graph
# Running time: O(n+m)

from collections import deque as Queue

MAX=10**9
def bfs(graph, start):
    n=len(graph)
    q, res=Queue(), [MAX]*n
    for s in start:
        res[s]=0;
        q.append(s)
    
    while q:
        cur=q.popleft()
        for next in graph[cur]:
            if res[next]==MAX:
                res[next]=res[cur]+1
                q.append(next)
    
    return res


#main:

n, m, k=map(int, raw_input().split())

graph=[[] for _ in xrange(n)]
rev_graph=[[] for _ in xrange(n)]

starts_ore=[x-1 for x in map(int, raw_input().split())]
starts_coal=[x-1 for x in map(int, raw_input().split())]

#set up the graphs:
for i in xrange(n):
    raw_edges=map(int, raw_input().split())
    for next in raw_edges[1:]:
        graph[i].append(next-1)
        rev_graph[next-1].append(i)
        

dist_root=bfs(graph, [0])
dist_ore=bfs(rev_graph, starts_ore)
dist_coal=bfs(rev_graph, starts_coal)

best=min([x+y+z for x,y,z in zip(dist_root, dist_ore, dist_coal)])

print best if best<MAX else "impossible"



