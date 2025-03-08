#include <bits/stdc++.h>

using namespace std;

const int n = 6;
vector<int> adj[n];
int visited[n];

void dfs(int u) {
    visited[u] = 1;
    cout << u << endl;
    for (int item : adj[u]) {
        if (visited[item] == 0) {
            dfs(item);
        }
    }
    cout << u << "로 부터 시작된 함수가 종료되었습니다. \n";
    return;
}

int main() {
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(4);
    adj[2].push_back(5);

    dfs(1);
    
    return 0;
}