def count(n):
    if(n==0):
        return 0
    return 2*count(n-1)+1
# move n disks from a -> b using c
def move(n, a, b, c):
    if(n==0):
        return
    move(n-1, a, c, b)
    print(str(a) + " " + str(b))
    move(n-1, c, b, a)
n = int(input())
print(count(n))
if(n<=20):
    move(n, 1, 3, 2)
