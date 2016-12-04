#performs binary search over the horizontal velocity
#         by simulating the flight for a given horizontal velocity


#the is no need for the sorting the shields, take them as they come...

x,y=map(float, raw_input().split())
n=int(raw_input())

shields=[]
for _ in xrange(n):
    shields.append(map(float, raw_input().split()))


shields.append((y,y,1.0))#sentinel

min_v, max_v=-100.0, 100.0 #actually -10.0, 10.0 would be enough...

while max_v-min_v>1e-9:
    middle=(min_v+max_v)/2.0
    current_x=0
    last=0
    for shield in shields:
        current_x+=(shield[0]-last)*middle
        current_x+=(shield[1]-shield[0])*shield[2]*middle
        last=shield[1]
    if current_x>x:
        max_v=middle
    else:
        min_v=middle
       
print (min_v+max_v)/2.0
