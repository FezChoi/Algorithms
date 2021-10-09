#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define INF 2147000000

struct Point {
    int row, col, cnt;
};

vector<vector<int>> Board;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int BFS(Point src, Point dst) {
    bool visited[4][4] = { false, };

    queue<Point> q;
    q.push(src);

    while (!q.empty()) {
        Point now = q.front(); q.pop();

        if (now.row == dst.row && now.col == dst.col) {     // 도착
            return now.cnt;
        }

        for (int i = 0; i < 4; i++) {
            // 방향키
            int nr = now.row + dir[i][0];       // 1칸
            int nc = now.col + dir[i][1];
            if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) continue;

            if (!visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc, now.cnt + 1});  // 카운트 업
            }

            // Ctrl + 방향키
            for (int j = 0; j < 2; j++) {       // 최대 2칸 더 갈 수 있음
                if (Board[nr][nc] != 0) break;
                if (nr + dir[i][0] < 0 || nr + dir[i][0] >= 4 ||
                    nc + dir[i][1] < 0 || nc + dir[i][1] >= 4) break;
                
                nr += dir[i][0];
                nc += dir[i][1];
            }

            if (!visited[nr][nc]) {
                visited[nr][nc] = true;
                q.push({nr, nc, now.cnt + 1});  // 카운트 업
            }
        }
    }

    return INF;
}

int permutate(Point src) {
    int ret = INF;

    for (int num = 1; num <= 6; num++) {        // 모든 숫자 확인
        vector<Point> card;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (Board[i][j] == num) {
                    card.push_back({i, j, 0});
                }
            }
        }

        if (card.empty()) continue;     // 해당 숫자가 없으면 반복

        int one = BFS(src, card[0]) + BFS(card[0], card[1]) + 2;    // case 1 : 출발점 -> 첫 번째 카드 -> 두 번째 카드
        int two = BFS(src, card[1]) + BFS(card[1], card[0]) + 2;    // case 2 : 출발점 -> 두 번째 카드 -> 첫 번째 카드

        Board[card[0].row][card[0].col] = 0;        // 카드 제거
        Board[card[1].row][card[1].col] = 0;

        ret = min(ret, one + permutate(card[1]));   // case 1 : 마지막 위치가 두 번째 카드
        ret = min(ret, two + permutate(card[0]));   // case 2 : 마지막 위치가 첫 번째 카드

        Board[card[0].row][card[0].col] = num;      // 카드 복원 (permutation을 위함)
        Board[card[1].row][card[1].col] = num;
    }

    if (ret == INF) {
        return 0;
    }

    return ret;
}

int solution(vector<vector<int>> board, int r, int c) {
    Board = board;  // 편하게 전역 변수로 사용하기 위함.
    return permutate({r, c, 0});
}