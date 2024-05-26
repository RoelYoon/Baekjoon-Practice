n = int(input())
pos = []
for i in range(n):
    inp = input().split()
    x = int(inp[0])
    y = int(inp[1])
    pos.append((x,y))
pos = sorted(pos, key=lambda t: t[0])
maxX=pos[0][0]
length = 0
for i in range(n):
    if(pos[i][0]>=maxX):
        length+=abs(pos[i][1]-pos[i][0])
        maxX=pos[i][1]
    elif(pos[i][1]>maxX):
        length+=abs(pos[i][1]-maxX)
        maxX=pos[i][1]
print(length)