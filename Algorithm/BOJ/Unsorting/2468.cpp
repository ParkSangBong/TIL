#include <bits/stdc++.h>

using namespace std;

int adjArray[101][101];
bool visited[101][101];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int n, max_ret = 1, ny, nx;

void dfs(int y, int x, int d) {
    visited[y][x] = 1;
    for (int i=0; i<4; i++) {
        ny = y + dy[i];
        nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
        if (!visited[ny][nx] && adjArray[ny][nx] > d) {
            dfs(ny, nx, d);
        }
    }
    return;
}

int main() {
    
    cin >> n;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> adjArray[i][j];
        }
    }

    for (int i=1; i<101; i++) {
        memset(visited, 0, sizeof(visited)); 
        int ret = 0;
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                if (adjArray[j][k] > i && !visited[j][k]) {
                    dfs(j, k, i);
                    ret++; 
                }
            }
        }
        // cout << " i : " << i << ", ret : " << ret << ", max_ret : " << max_ret << endl;
        max_ret = max(max_ret, ret);
    }

    cout << max_ret << '\n';

    return 0;
}