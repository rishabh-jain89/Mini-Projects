#include <bits/stdc++.h>
using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

int main(){
    int n;
    cin>>n;
    vector<int> arr(n);
    vector<vector<int>> classes(n, vector<int>(2));

    for (int i = 0; i < n; ++i) {
        cin >> classes[i][0] >> classes[i][1];
    }

    vector<int> aux(n,0);
    aux[0]=1;
    int count = 0, lastEnd = -1;
    for(int i=1;i<n;i++){
        if(classes[i][0]<endtime){

        }
    }

    sort(classes.begin(), classes.end(), cmp);


}
