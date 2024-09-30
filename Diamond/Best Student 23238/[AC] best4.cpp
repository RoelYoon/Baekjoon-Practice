#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Query{
	int L, R;
	int id;
};
int n, m;
vector<int> oarr;
vector<int> arr;
vector<int> zip;
vector<Query> q;
const int SZ = 79;
const int SQ = 111111 / SZ + 15; 
int ans[110005];
int bucketMode[SQ][SQ];
int curMode;
int mode;
int bucket_cnt[100005];
vector<vector<int>> idPos;
void arrayclear(int (&a)[100005]){
	for (int &i : a){
		i = 0;
	}
}
void preprocessing(){	
	for (int k = 0; k * SZ < n; k++){
		curMode = 0;
		mode = 0;
		arrayclear(bucket_cnt);
		for (int i = k*SZ; i <= n; i++){
			if (i == 0) continue;
			int t = arr[i];
			bucket_cnt[t]++;
			if (bucket_cnt[t] == curMode){ 
				mode = max(mode, t);
			}
			else if (bucket_cnt[t] > curMode){ 
				mode = t;
				curMode = bucket_cnt[t];
			}
			
			if (i % SZ == SZ-1 || i == n){ 
				bucketMode[k][i/SZ+1] = mode;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
	oarr.resize(100005);
	arr.resize(100005);
	idPos.resize(100005);
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		int t; cin >> t;
		oarr[i] = t;
		zip.push_back(t);
	}
	sort(zip.begin(), zip.end());
	zip.erase(unique(zip.begin(), zip.end()), zip.end());
	for (int i = 1; i <= n; i++){
		arr[i] = lower_bound(zip.begin(), zip.end(), oarr[i]) - zip.begin();
		idPos[arr[i]].push_back(i);
	}
	preprocessing();
	for (int i = 0; i < m; i++){
		int l, r; cin >> l >> r;
		q.push_back({l, r, i});
	}
	sort(q.begin(), q.end(), [](Query &a, Query &b){
        int al = a.L / SZ;
        int bl = b.L / SZ;
        if (al != bl) return al < bl;
        return a.R < b.R;
    });
	for (int i = 0; i < m; i++){
		int l = q[i].L, r = q[i].R;
		int idx = q[i].id;
		int modeID = 0;
		int modeVal = 0;
		
		if (l / SZ == r / SZ) { 
			for (int i = l; i <= r; i++){
				int t = upper_bound(idPos[arr[i]].begin(), idPos[arr[i]].end(), r) - lower_bound(idPos[arr[i]].begin(), idPos[arr[i]].end(), l);
				if (t == modeVal) {
					modeID = max(modeID, arr[i]); 
				}
				else if (t > modeVal){
					modeID = arr[i];
					modeVal = t;
				}
			}
		}
		else{
			vector<int> candidates;
			int lp = (l/SZ) + 1;
			if (l % SZ == 0) lp--;
			for (int i = l; i < (lp)*SZ; i++){
				candidates.push_back(arr[i]);
			}
			candidates.push_back(bucketMode[lp][r/SZ]);
			for (int i = r; i >= (r/SZ)*SZ; i--){
				candidates.push_back(arr[i]);
			}
			for (auto &i : candidates){
				int t = upper_bound(idPos[i].begin(), idPos[i].end(), r) - lower_bound(idPos[i].begin(), idPos[i].end(), l);
				if (t == modeVal) {
					modeID = max(modeID, i); 
				}
				else if (t > modeVal){
					modeID = i;
					modeVal = t;
				}
			}
			
		}
		ans[idx] = zip[modeID];
	}
	for (int i = 0; i < m; i++){
        cout<<ans[i]<<"\n";
    }
}