#include <vector>

using namespace std;

vector<bool> visited;
int wgtMax = 0, cntMax = 0;

void DFS(vector<int> weights, int level, int wgt1, int cnt1, int wgt2, int cnt2) {
    if (level == weights.size()) {
        if (wgt1 == wgt2 && cnt1 + cnt2 >= cntMax) {
            cntMax = cnt1 + cnt2;
            wgtMax = (wgtMax > wgt1) ? wgtMax : wgt1;
        }
        return;
    }

    for (int i = level; i < weights.size(); i++) {
        if (visited[i]) continue;

        visited[i] = true;
        DFS(weights, level + 1, wgt1 + weights[i], cnt1 + 1, wgt2, cnt2);   // group 1
        DFS(weights, level + 1, wgt1, cnt1, wgt2 + weights[i], cnt2 + 1);   // group 2

        visited[i] = false;
        DFS(weights, level + 1, wgt1, cnt1, wgt2, cnt2);                    // no grouop
    }
}

vector<int> solution(vector<int> weights) {
    visited = vector<bool>(weights.size(), false);

    DFS(weights, 0, 0, 0, 0, 0);

    vector<int> answer = { cntMax, wgtMax };
    return answer;
}