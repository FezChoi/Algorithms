#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int dr[] = {0, -1, 1, 0,  0}; // up(1), down(2), right(3), left(4)
const int dc[] = {0,  0, 0, 1, -1};

vector<vector<int> > arr;

int R, C, M;
int cycleR, cycleC;
// int cycleR = 2 * R - 2;
// int cycleC = 2 * C - 2;

int totalSize = 0;

struct Shark {
    int r, c, s, d, z;
    bool caught;
    
    int check(int origin, int dist, int cycle, int limit) {
        int pos = origin + dist;

        if (pos > limit) {  // down, right
            pos = origin + dist % cycle;
            if (pos > limit) {
                pos = 2 * limit - pos;
                if (pos <= 0) pos = -pos + 2;

                d = (d == 2) ? 1 : 4; // up, left
                if (pos == 1) d = (d == 1) ? 2 : 3;
            }
        }
        else if (pos <= 0) {    // up, left 여기 수정!
            pos = origin - ((-dist) % cycle);
            if (pos <= 0) {
                pos = -pos + 2;
                if (pos > limit) pos = 2 * limit - pos;

                d = (d == 1) ? 2 : 3; // down, right
                if (pos == limit) d = (d == 2) ? 1 : 4;
            }
        }   

        return pos;
    }

    void move() {
        if (d <= 2) r = check(r, s * dr[d], cycleR, R);
        else        c = check(c, s * dc[d], cycleC, C);
    }
};

vector<Shark> sharks(1);

void printArray() {
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void solution(int col) {
    while (true) {
        // cout << "col : " << col << endl;

        // catch sharks
        for (int r = 1; r <= R; r++) {
            if (arr[r][col] != 0) {
                int id = arr[r][col];
                totalSize += sharks[id].z;
                sharks[id].caught = true;
                // cout << "caught : " << id << endl;
                break;
            }
        }
        // cout << "size : " << totalSize << endl;

        // printArray();

        if (++col > C) return;

        // reset map
        arr = vector<vector<int> >(R + 1, vector<int>(C + 1, 0));

        // update sharks
        for (int id = 1; id < sharks.size(); id++) {
            if (sharks[id].caught == true) continue;

            sharks[id].move();

            int r = sharks[id].r;
            int c = sharks[id].c;
            // cout << "move succeed : " << id << " " << r << "," << c << " " << sharks[id].d << endl;

            // cout << sharks[id].d << " ? " << r << ", " << c << endl; 

            // empty there
            if (arr[r][c] == 0) {
                arr[r][c] = id;
                continue;
            }

            // compare size, take bigger one
            int id2 = arr[r][c];
            if (sharks[id2].z < sharks[id].z) {
                sharks[id2].caught = true;
                arr[r][c] = id;
            }
            else {
                sharks[id].caught = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input.txt", "r", stdin);

    cin >> R >> C >> M;
    arr = vector<vector<int> >(R + 1, vector<int>(C + 1, 0));

    // positive : size 5 -> repeat 8 / size 4 -> repeat 6
    // positive repeat = 2 * size - 2
    cycleR = 2 * R - 2;
    cycleC = 2 * C - 2;

    int r, c, s, d, z;
    for (int i = 1; i <= M; i++) {
        cin >> r >> c >> s >> d >> z;
        sharks.push_back((Shark){r, c, s, d, z, false});
        arr[r][c] = i;
    }

    solution(1);

    cout << totalSize << endl;

    return 0;
}