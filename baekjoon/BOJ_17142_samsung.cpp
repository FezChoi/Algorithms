// 2019 삼성 기출 : 연구소 3
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Pos {
    int x, y;
};

const Pos dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int TIMELIMIT = 1000000;

int arr[51][51] = { 0, };
int N, M;
int minTime = TIMELIMIT;

vector<Pos> virus;

void BFS(vector<int> select) {
    int tmpArr[51][51] = { 0, };                    // time array
    int tmpVis[51][51] = { 0, };                    // visit array

    queue<Pos> q;

    for (int s : select) {                          // BFS start with active viruses
        tmpVis[virus[s].x][virus[s].y] = 1;
        q.push(virus[s]);  
    }

    int time = 0;

    while (!q.empty()) {
        Pos c = q.front(); q.pop();

        if (arr[c.x][c.y] == 0) {                   // KEY POINT!!! Meeting virus must not update minimum time!
            time = max(time, tmpArr[c.x][c.y]);
            if (time >= minTime) return;
        }

        for (Pos d : dir) {
            Pos n = { c.x + d.x, c.y + d.y };
            if (n.x < 0 || n.x >= N || n.y < 0 || n.y >= N) continue;       // out of range
            if (arr[n.x][n.y] == 1 || tmpVis[n.x][n.y] == 1) continue;     // wall or visited(including starting points)

            tmpVis[n.x][n.y] = 1;                                           // set visited
            tmpArr[n.x][n.y] = tmpArr[c.x][c.y] + 1;                        // set time
            q.push(n);
        }
    }

    for (int i = 0; i < N; i++) {                               // check if zero exist
        for (int j = 0; j < N; j++) {
            if (arr[i][j] == 0 && tmpVis[i][j] == 0) return;
        }
    }

    minTime = min(minTime, time);                               // update minTime
}


void DFS(int level, vector<int> select) {
    if (select.size() == M) {
        BFS(select);
        return;
    }

    if (level == virus.size()) return;

    select.push_back(level);
    DFS(level + 1, select);
    select.pop_back();
    DFS(level + 1, select);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);
    
    cin >> N >> M;

    bool isNoSpace = true;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int tmp; cin >> arr[i][j];

            if (arr[i][j] == 0) {               // space
                isNoSpace = false;
            }
            else if (arr[i][j] == 2) {          // virus
                virus.push_back((Pos){i, j});
            }
        }
    }

    if (isNoSpace) {
        minTime = 0;
    }
    else if (virus.empty()) {
        minTime = -1;
    }
    else {
        DFS(0, vector<int>(0));
    }

    cout << (minTime == TIMELIMIT ? -1 : minTime) << endl;

    return 0;
}