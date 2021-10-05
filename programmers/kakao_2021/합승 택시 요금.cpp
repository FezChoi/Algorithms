/*
    모든 점들 사이의 최소 거리가 계속 필요했기 때문에 Prim 알고리즘을 떠올렸다.

    효율성 테스트에서 오류 발생 : 편향 그래프인 경우를 고려하지 못하여, dist의 초기값을 너무 작게 잡았음.
    효율성 테스트 오류 해결법 : 편향 그래프를 고려하여 (n * 100,000)을 초기값으로 설정.
*/

#include <vector>

using namespace std;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, n * 100000)); 

    for (auto fare : fares) {
        dist[fare[0]][fare[1]] = fare[2];
        dist[fare[1]][fare[0]] = fare[2];
    }
    
    for (int k = 1; k <= n; k++) {
        dist[k][k] = 0;
        for (int i = 1; i <= n; i++) {
            if (i == k) continue;
            for (int j = 1; j <= n; j++) {
                if (j == i || j == k) continue;
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    int answer = 2147000000;
    for (int k = 1; k <= n; k++) {
        if (answer > dist[s][k] + dist[k][a] + dist[k][b]) {
            answer = dist[s][k] + dist[k][a] + dist[k][b];
        }
    }
    
    return answer;
}