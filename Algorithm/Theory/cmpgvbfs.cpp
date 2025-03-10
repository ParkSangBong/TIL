#include <bits/stdc++.h>

using namespace std;

const int max_n = 104;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int n, m, adj[max_n][max_n], visited[max_n][max_n], y, x, sy, sx, ey, ex;

int main() {

    cin >> n >> m;
    cin >> sy >> sx;
    cin >> ey >> ex;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> adj[i][j];
        }
    }

    queue<pair<int, int>> que;
    visited[sy][sx] = 1;
    que.push({sy, sx});
    while (que.size()) {
        tie(y, x) = que.front();
        que.pop();
        for (int i=0; i<4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n || adj[ny][nx] == 0) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = visited[y][x] + 1;
            que.push({ny, nx});
        }
    }

    cout << visited[ey][ex] << endl;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout << visited[i][j] << ' ';
        }
        cout << "\n";
    }

    return 0;
}