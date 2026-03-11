#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define cd complex<double>
using namespace std;
const double PI = acos(-1);
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    int carry = 0;
    for (int i = 0; i < n; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    return result;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string a,b; cin>>a>>b;
    vector<int> av(a.size()),bv(b.size());
    for(int i = 0; i < a.size(); ++i){
        av[a.size()-1-i] = a[i]-'0';
    }
    for(int i = 0; i < b.size(); ++i){
        bv[b.size()-1-i] = b[i]-'0';
    }
    vector<int> m = multiply(av,bv);
    bool f = 0;
    for(int i = m.size()-1; i >= 0; --i){
        if(!f && !m[i]) continue;
        f = 1;
        cout<<m[i];
    }
    if(!f) cout<<"0";
    cout<<"\n";
}