#include <bits/stdc++.h>

using namespace std;

const int n = 104;

int a[n][n], visited[n][n];

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int N, M, iY, iX, tY, tX;

void bfs(int y, int x) {
    queue<int[]> q;
    visited[y][x] = 1;
    q.push([y, x])
    while(q.size()) {
        for (int i=0; i<4; i++) {
            ny = y + dy[i];
            nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            if (a[ny][nx] == 1 && !visited[ny][nx]) {
                bfs(ny, nx);
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> iY >> iX >> tY >> tX;

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin >> a[i][j];
        }
    }

    bfs(iY, iX);

    cout << visited[tY][tX] << endl;

    return 0;
}