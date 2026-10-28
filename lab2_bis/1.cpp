#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

int dx[] = {1, 0, 0, -1};
int dy[] = {0, -1, 1, 0};
char dirChar[] = {'D', 'L', 'R', 'U'};

void findPaths(int x, int y, int n, const vector<vector<int>> &m, const vector<vector<int>> &dist, string currentPath, vector<string> &allPaths) {
    if (x == n - 1 && y == n - 1) {
        allPaths.push_back(currentPath);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < n && m[nx][ny] == 1) {
            if (dist[nx][ny] == dist[x][y] + 1) {
                findPaths(nx, ny, n, m, dist, currentPath + dirChar[i], allPaths);
            }
        }
    }
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) return 0;
    vector<vector<int>> m(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }

    if (m[0][0] == 0 || m[n - 1][n - 1] == 0) {
        return 0;
    }

    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<Point> q;
    dist[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        Point p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && m[nx][ny] == 1 && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[p.x][p.y] + 1;
                q.push({nx, ny});
            }
        }
    }

    if (dist[n - 1][n - 1] == -1) {
        return 0;
    }

    vector<string> allPaths;
    findPaths(0, 0, n, m, dist, "", allPaths);
    sort(allPaths.begin(), allPaths.end());

    for (const string &path : allPaths) {
        cout << path << endl;
    }

    return 0;
}
