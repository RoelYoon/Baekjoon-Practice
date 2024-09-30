#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define MAX 100000
#define MAXSQ 1150
using namespace std;
struct Query{
    int L;
    int R;
    int id;
    Query(){}
};
int n;
int arr[MAX];
int zip[MAX];
int bucketMode[MAXSQ][MAXSQ];
int bucketCnt[MAX];
int ans[MAX];
Query qs[MAX];
vector<int> candidates;
bool added[MAX]{};
void clear(int a[MAX]){
    for(int i = 0; i < n; ++i)
        a[i]=0;
}
int main(){
    int q; scanf("%d%d",&n,&q);
    const int s = 79;
    vector<vector<int>> idPos(n);
    for(int i = 0; i < n; ++i){
        scanf("%d",&arr[i]);
        zip[i]=arr[i];
    }
    sort(zip,zip+n);
    int zipSz = unique(zip,zip+n)-zip;
    for(int i = 0; i < n; ++i){
        arr[i]=lower_bound(zip,zip+zipSz,arr[i])-zip;
        idPos[arr[i]].push_back(i);
    }
    for(int i = 0; i < q; ++i){
        scanf("%d%d",&qs[i].L,&qs[i].R);
        --qs[i].L,--qs[i].R;
        qs[i].id=i;
    }
    sort(qs,qs+q,[s](Query &a, Query &b){  
        int aL = a.L/s;
        int bL = b.L/s;      
        if (aL == bL) return a.R < b.R;
        return aL < bL;
    });
	for (int k = 0; k < s; ++k){
		int maxCnt = 0;
		int mode = 0;
        clear(bucketCnt);
		for (int i = k*s; i < n; ++i){			
			int c = arr[i];
			++bucketCnt[c];
			if (bucketCnt[c] == maxCnt){
				mode = max(mode, c);
			}
			else if (bucketCnt[c] > maxCnt){ 
				mode = c;
				maxCnt = bucketCnt[c];
			}
			if (i%s == s-1 || i == n-1){ 
				bucketMode[k][i/s+1] = mode;
			}
		}
	}
    for(int i = 0; i < q; ++i){
        int modeID, maxMode=0;
        int QL=qs[i].L, QR=qs[i].R;
        if(QL/s == QR/s){
            for(int i = QL; i <= QR; ++i){
                int mode = upper_bound(idPos[arr[i]].begin(),idPos[arr[i]].end(),QR) - lower_bound(idPos[arr[i]].begin(), idPos[arr[i]].end(), QL);
                if(mode == maxMode){
                    modeID = max(modeID,arr[i]);
                }else if(mode > maxMode){
                    maxMode = mode;
                    modeID = arr[i];
                }
            }
            ans[qs[i].id]=zip[modeID];
            continue;
        }
        int LS = QL/s + 1;
        if (QL % s == 0) --LS;
        for(int i = QL; i < min(LS*s,n); ++i){
            if(!added[arr[i]]){
                added[arr[i]]=1;
                candidates.push_back(arr[i]);
            }
        }
        int RS = QR/s;
        candidates.push_back(bucketMode[LS][RS]);
        for(int i = QR; i >= RS*s; --i){
            if(!added[arr[i]]){
                added[arr[i]]=1;
                candidates.push_back(arr[i]);
            }
        }
        for(int i = 0; i < candidates.size(); ++i){
            int c = candidates[i];
            int mode = upper_bound(idPos[c].begin(),idPos[c].end(),QR) - lower_bound(idPos[c].begin(), idPos[c].end(), QL);
            added[c]=0;
            if(mode == maxMode){
                modeID = max(modeID,c);
            }else if(mode > maxMode){
                maxMode = mode;
                modeID = c;
            }
        }
        candidates.clear();
        ans[qs[i].id]=zip[modeID];
    }
    for(int i = 0; i < q; ++i)
        printf("%d\n",ans[i]);
}