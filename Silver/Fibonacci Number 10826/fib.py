import sys
sys.setrecursionlimit(100000)
DP=[]
def fib(n):
    if(n==0):
        return 0
    if(n==1 or n==2):
        return 1
    if(DP[n]!=0):
        return DP[n]
    DP[n]=fib(n-1)+fib(n-2)
    return DP[n]
for i in range(0,100000):
    DP.append(0)
n=int(input())
print(fib(n))