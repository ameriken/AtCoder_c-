#include <bits/stdc++.h>
using namespace std;

int main() {

    int N;
    cin >> N;

    vector<int> A(N);
    vector<vector<int> > x(N), y(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        x[i] = vector<int>(A[i]);
        y[i] = vector<int>(A[i]);
        for (int j = 0; j < A[i]; j++) {
            cin >> x[i][j] >> y[i][j];
            x[i][j]--;
        }
    }

    int ans = 0;
    for (int bit = 0; bit < (1 << N); bit++) {
        int cnt = 0;
        bool good = true;
        for (int i = 0; i < N; i++) {
            if (bit & (1 << i)) {
                cnt++;
                for (int j = 0; j < A[i]; j++) {
                    if (((bit >> x[i][j]) & 1) != y[i][j]) {
                        good = false;
                    }
                }
            }
        }
        if (good) ans = max(ans, cnt);
    }

    cout << ans << endl;
}