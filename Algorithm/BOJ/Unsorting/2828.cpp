#include <bits/stdc++.h>

using namespace std;
int N, M;
int ret;
int gfirst, gsecond;
void go(int first, int second, int target) {
    // cout << "gfirst : " << gfirst << ", gsecond : " << gsecond << endl;
    // cout << "first : " << first << ", second : " << second << ", target : " << target << endl;
    if (first <= target && target <= second) {
        // cout << "target inbound" << endl;
        gfirst = first;
        gsecond = second;
        return;
    } else if (target < first && (first-1) >= 0) {
        // cout << "target minus" << endl;
        ret++;
        go(first-1, second-1, target);
    } else if (target > second && (second+1) <= (N-1)) {
        // cout << "target plus" << endl;
        ret++;
        go(first+1, second+1, target);
    } else {
        // cout << "error boundary" << "\n";
        return;
    }
}

int main() {

    cin >> N >> M;
    gfirst = 0;
    gsecond = M-1;
    int cnt;

    cin >> cnt;

    for (int i=0; i<cnt; i++) {
        int temp;
        cin >> temp;
        go(gfirst, gsecond, temp-1);
    }

    cout << ret << endl;

    return 0;
}