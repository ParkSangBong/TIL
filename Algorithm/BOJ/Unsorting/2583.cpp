#include <bits/stdc++.h>

using namespace std;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int adjArray[101][101];
bool visited[101][101];

int m, n, cnt, ret=0;
vector<int> retArr;

int dfs(int y, int x) {
    int pcnt = 1;
    visited[y][x] = 1;
    for (int i=0; i<4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= m || nx >= n) continue;
        if (adjArray[ny][nx] == 0 && !visited[ny][nx]) {
            pcnt = pcnt + dfs(ny, nx);
        }
    }
    return pcnt;
}

int main() {

    cin >> m >> n >> cnt;

    memset(adjArray, 0, sizeof(adjArray)); 
    memset(visited, 0, sizeof(visited)); 

    for (int i=0; i<cnt; i++) {
        int fX, fY, lX, lY;
        cin >> fX >> fY >> lX >> lY;
        for (int j=fX; j<lX; j++) {
            for (int k=fY; k<lY; k++) {
                adjArray[k][j] = 1;
            }
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (adjArray[j][i] == 0 && !visited[j][i]) {
                ret++;
                int temp = dfs(j, i);
                retArr.push_back(temp);
            }
        }
    }
    sort(retArr.begin(), retArr.end());
    cout << ret << endl;
    for (int num : retArr) {
        cout << num << " ";
    }
    return 0;
}