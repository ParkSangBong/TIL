#include <bits/stdc++.h>

using namespace std;

string s;
int cnt, result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> cnt;

    for (int i=0; i<cnt; i++) {
        cin >> s;
        stack <char> stk;
        for (char a : s) {
            if (stk.size() && stk.top() == a) {
                stk.pop();
            } else {
                stk.push(a);
            }
        }    
        if (stk.size() == 0) {
            result++;
        }
    }
    cout << result << "\n";
    
    return 0;
}