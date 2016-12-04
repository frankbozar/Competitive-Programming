#walk into the largest room, after that the order does not matter...

import operator

n=int(raw_input())
s=map(int,raw_input().split())

index, m = max(enumerate(s), key=operator.itemgetter(1))

if 2*m>sum(s):
    print "impossible"
else:
    print " ".join(map(str, [index+1]+[x+1 for x in xrange(n) if x!=index]))

    
