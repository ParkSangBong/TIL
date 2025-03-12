#include <bits/stdc++.h>

using namespace std;

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int adjArray[54][54];
bool visited[54][54];

int cnt, cnt2, m, n, ret, ny, nx;

void dfs(int y, int x) {
    visited[y][x] = 1;
    for (int i=0; i<4; i++) {
        ny = y + dy[i];
        nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
        if (adjArray[ny][nx] == 1 && !visited[ny][nx]) {
            dfs(ny, nx);
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> cnt;

    for (int i=0; i<cnt; i++) {
        
        ret = 0;

        memset(adjArray, 0, sizeof(adjArray)); 
        memset(visited, 0, sizeof(visited)); 

        cin >> n >> m >> cnt2;

        for (int j=0; j<cnt2; j++) {
            int tempY, tempX;
            cin >> tempY >> tempX;
            adjArray[tempY][tempX] = 1;
        }

        for (int j=0; j<n; j++) {
            for (int k=0; k<m; k++) {
                if (adjArray[j][k] == 1 && !visited[j][k]) {
                    ret++;
                    dfs(j, k);
                }
            }
        }

        cout << ret << '\n';

    }

    return 0;
}