#include <iostream>
#include <vector>
#include <string>
using namespace std;
int n;
string s;
bool answerFound = false;
bool passes(vector<int> &nums){
    int index = 0;
    for(int i = n; i >= 0; i--){
        int row = n-i;
        for(int col = row; col < n; col++){
            int sum = 0;
            for(int j = row; j <= col; j++){
                sum+=nums[j];
            }
            switch(s[index]){
                case '-':
                    if(sum>=0)
                        return false;
                    break;
                case '+':
                    if(sum<=0)
                        return false;
                    break;
                default:
                    if(sum!=0)
                        return false;
                    break;
            }
            index++;
        }
    }
    return true;
}
bool pairCheck(vector<int> &nums, int pos){
    int index = 0;
    for(int i = n; i >=0; i--){
        int row = n-i;
        if(row>pos){break;}
        for(int col = row; col < n; col++){
            if(col>pos){index++;continue;}
            int sum = 0;
            for(int j = row; j <= col; j++){
                sum+=nums[j];
            }
            switch(s[index]){
                case '-':
                    if(sum>=0)
                        return false;
                    break;
                case '+':
                    if(sum<=0)
                        return false;
                    break;
                default:
                    if(sum!=0)
                        return false;
                    break;
            }
            index++;
        }
    }
    return true;
}
void generate(vector<int>&nums,int pos){
    if(answerFound){return;}
    if(pos==n && passes(nums)){
        for(int i = 0; i < n; i++){
            cout<<nums[i]<<" ";
        }
        answerFound=true;
        return;
    }if(pos==n){return;}
    for(int i = nums[pos]<0 ? -10 : (nums[pos]>0 ? 10 : 0); nums[pos]<0 ? i<0 : (nums[pos]>0 ? i>0 : i==0); i+=nums[pos]<0 ? 1 : (nums[pos]>0 ? -1 : 1)){
        nums[pos]=i;
        if(pairCheck(nums,pos-1)){
            generate(nums,pos+1);
        }
        if(answerFound){return;}
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>s;
    int index = 0; 
    vector<int> nums(n);
    for(int i = n; i > 0; i--){
        switch(s[index]){
            case '-':
                nums[n-i] = -1;
                break;
            case '+':
                nums[n-i] = 1; 
                break;
            case '0':
                nums[n-i] = 0;
                break;
        }
        index+=i;
    }
    generate(nums,0);
    /*
    nums[0]=-1;
    nums[1]=5;
    nums[2]=-4;
    nums[3]=2;
    nums[0]=1;
    nums[1]=2;
    nums[2]=-3;
    nums[3]=4;
    nums[4]=-5;
    if(pairCheck(nums,4)){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }*/
}