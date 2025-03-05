#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long d;
    // 세 수 입력, 1번을 2번만큼 거듭제곱 후 3으로 나눈 나머지 출력
    cin >> a >> b >> c;
    
    d = pow(a, b);

    int e = d % c;

    cout << e << endl;

    return 0;
}