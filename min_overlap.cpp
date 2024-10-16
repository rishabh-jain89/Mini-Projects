#include <bits/stdc++.h>

using namespace std;

bool cmp(const vector<int>& a, const vector<int>& b) {
    return a[1] < b[1];
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> classes(n, vector<int>(2));

    for (int i = 0; i < n; ++i) {
        cin >> classes[i][0] >> classes[i][1];
    }

    sort(classes.begin(), classes.end(), cmp);

    int count = 0, lastEnd = -1;
    for (const auto& c : classes) {
        if (c[0] >= lastEnd) {
            ++count;
            lastEnd = c[1];
        }
    }

    cout << count << endl;
    return 0;
}
