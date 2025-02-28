#include <bits/stdc++.h>

using namespace std;

int inputArray[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};
const int inputCnt = 9;

const int dy4[] = {-1, 1, 0, 0};
const int dx4[] = {0, 0, -1, 1};

int main() {
    
    int tempNum;

    for (int i = 0; i < inputCnt; i++) {
        cin >> tempNum;
        cout << tempNum << " | i % 3 : " << i%3 << " | i / 3 :  " << i / 3 << endl;
        inputArray[i/3][i%3] = tempNum;
    }
    
    for (int i = 0; i < 4; i++) {
        int ny = y + dy4[i];
        int nx = x + dx4[i];
        if (ny < 0 || nx < 0 || ny > 2 || nx > 2) continue;
        if (inputArray[ny][nx] == 1) {
            
        }
    }

    cout << inputArray << endl;

    return 0;
}