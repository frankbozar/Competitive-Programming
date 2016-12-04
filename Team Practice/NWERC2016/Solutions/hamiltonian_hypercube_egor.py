#uses recursion
#
#id([s_n,s_n-1,...,s_1])=2^n-id([s_n-1,...s_1])-1 if s_n==1 else id([s_n-1,...s_1])
#
#bottom-up
#

def get_index(z):
    res,s=0,2
    for ch in reversed(z):
        if ch=='1':
            res=s-res-1
        s*=2
    return res
   
_,a,b=raw_input().split()# I guess n is not needed...

diff=get_index(b)-get_index(a)-1

assert(diff>=0)

print diff


