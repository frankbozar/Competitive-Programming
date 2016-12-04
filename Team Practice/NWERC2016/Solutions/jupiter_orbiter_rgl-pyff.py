#!/usr/bin/env python3
from sys import exit
from collections import deque

#
# Direct port of rgl-dinitz.cc
#
# Has one mistake: uses the deque in BFS as a stack instead of a queue,
# which turns the whole algorithm into a particularly wasteful kind of
# Ford Fulkerson.
#
# Almost surprisingly it is still reasonably fast to do this.
#

windows, queues, instruments = map(int, input().split())
target = list(map(lambda x: int(x) - 1, input().split()))
capacity = list(map(int, input().split()))
total_data = 0

src = 0
sink = 1
def lab(x,y):
    return 2+(queues+1)*x+y

edges = list(map(lambda x: [], range(lab(windows,0))))
def add_edge(s,t,cap):
    # print('add_edge_',s,t,cap)
    edges[s] += [[t,cap,None]]
    edges[t] += [[s,0,edges[s][-1]]]
    edges[s][-1][2] = edges[t][-1]

for i in range(windows):
    downlink, *instrument_input = map(int, input().split())
    add_edge(lab(i,queues),sink,downlink)
    total_data += sum(instrument_input)

    added = [0] * queues
    for j in range(instruments):
        added[target[j]] += instrument_input[j]
    for j in range(queues):
        if added[j] > capacity[j]:
            print('impossible')
            exit(0)
        else:
            add_edge(lab(i,j),lab(i,queues),capacity[j])
            add_edge(src,lab(i,j),added[j])
            if i > 0 and added[j] < capacity[j]:
                add_edge(lab(i-1,j),lab(i,j),capacity[j]-added[j])

def bfs():
    dist = dict()
    dist[src] = 0
    q = deque([src])
    while len(q) > 0:
        x = q.pop()
        for i in edges[x]:
            if i[1] > 0 and i[0] not in dist:
                dist[i[0]] = dist[x] + 1
                if i[0] == sink:
                    return dist
                q.append(i[0])
    return None

def dfs(dist, x, limit=2**40):
    if x == sink:
        return limit

    res = 0
    for i in edges[x]:
        if i[1] > 0 and i[0] in dist and dist[i[0]] == dist[x] + 1:
            got = dfs(dist, i[0], min(limit, i[1]))
            if got == 0:
                del dist[i[0]]
            else:
                res += got
                limit -= got
                i[1] -= got
                i[2][1] += got
    return res

res = 0
while True:
    dists = bfs()
    if dists is None:
        break
    else:
        res += dfs(dists,src)

if res == total_data:
    print('possible')
else:
    print('impossible')
