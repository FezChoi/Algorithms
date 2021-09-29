#include <vector>

using namespace std;

void drawBox(vector<vector<int>> &table, int x, int y, int length) {
    for (; y <= y + length - 1; y++) {
        for (; x <= x + length - 1; x++) {
            table[x][y] = 1;
        }
    }
}

// input : [[1, 10], [3, 2], [2, 2]] square length, square count
vector<int> solution(vector<vector<int>> rectangle, int n, int m) {
    vector<int> lengthCount(11, 0);
    for (vector<int> r : rectangle) {
        lengthCount[r[0]] += r[1];
    }

    vector<vector<int>> table(n, vector<int>(m, 0));
    int x = 0, y = 0;

    vector<int> answer(3, 0);

    for (int length = 1; length <= 10; length++) {
        int cnt = lengthCount[length];

        while (cnt > 0) {
            while (y < m) {
                if (table[x][y] == 0 && table[x + length - 1][y] == 0) {
                    drawBox(table, x, y, length);
                    answer = { x, y, length };
                    cnt -= 1;
                }
                else {
                    x += 1;
                }

                if (x >= n) {
                    y += 1;
                    x = 0;
                }
            }
        }
    }

    return answer;
}