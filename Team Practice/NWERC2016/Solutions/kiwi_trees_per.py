#!/usr/bin/env python

import math
import sys
RAD = 4000.0
data = map(float, sys.stdin.read().split())
n = int(data[0])
P = zip(data[1::2], data[2::2])

def add(P1, P2):
    return (P1[0]+P2[0], P1[1]+P2[1])

def sub(P1, P2):
    return (P1[0]-P2[0], P1[1]-P2[1])

def mul(P, k):
    return (k*P[0], k*P[1])

def cross(P, Q):
    return Q[1]*P[0] - Q[0]*P[1]

def dot(P, Q):
    return P[0]*Q[0] + P[1]*Q[1]

def dist(P):
    return math.sqrt(dot(P, P))

def unit(P):
    L = dist(P)
    return (P[0] / L, P[1] / L)

def area(P):
    a = 0
    for i in range(len(P)):
        a += cross(P[i], P[i-1])
    return a

def corner(P0, P1, P2):
    D1 = sub(P0, P1)
    D2 = sub(P2, P1)
    if cross(D1, D2) < 0:
        return None
    theta = math.acos(dot(D1, D2) / dist(D1) / dist(D2)) / 2
    D = unit(add(unit(D1), unit(D2)))
    return add(P1, mul(D, RAD/math.sin(theta)))

def check(Tree, i):
    for j in range(n):
        if j in [i, (i+1)%n]: continue
        dP = sub(P[j-1], P[j])
        t = min(1, max(0, -dot(dP, sub(P[j], Tree))/dot(dP, dP)))
        C = sub(add(P[j], mul(dP, t)), Tree)
        if dot(C, C) < RAD*RAD:
            return False
    return True
    
def solve():
    T = []
    for i in range(n):
        Tree = corner(P[i-1], P[i], P[(i+1)%n])
        if Tree is not None and check(Tree, i):
            T.append(Tree)
    for T1 in T:
        for T2 in T:
            if dist(sub(T1, T2)) >= 2*RAD:
                print '%.9lf %.9lf\n%.9lf %.9lf' % (T1[0], T1[1], T2[0], T2[1])
                return
    print 'impossible'

solve()
