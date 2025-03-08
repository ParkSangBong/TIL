#include <bits/stdc++.h>

using namespace std;

long long n;

int main() {

    while (cin >> n) {

        long long cnt = 1;
        long long target = 1;

        while (true) {
            // cout << target << endl;
            if (target % n == 0) {
                // cout << "cnt : " << cnt << endl;
                break;
            } else {
                cnt++;
                target = (target * 10) + 1;
            }
            
        }
        
        cout << cnt << endl;
        
    }

    return 0;
}