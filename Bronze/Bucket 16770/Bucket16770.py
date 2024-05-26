n = int(input())
cowList = []
doneMilking = []
for i in range(n):
    cowList.append(list(map(int,input().split())))
    doneMilking.append(False)
time=1
availableBuckets=0
buckets=0
allDone=False
while(allDone==False):
    allDone=True
    for i in range(n):
        if(doneMilking[i]==False):
            allDone=False
            if(time==cowList[i][1]):
                doneMilking[i]=True
                availableBuckets+=cowList[i][2]
            elif(time==cowList[i][0]):
                bucketsNeeded = cowList[i][2]
                if(availableBuckets>=bucketsNeeded):
                    availableBuckets-=bucketsNeeded
                else:
                    bucketsNeeded-=availableBuckets
                    availableBuckets=0
                    buckets+=bucketsNeeded
    time+=1
print(buckets)