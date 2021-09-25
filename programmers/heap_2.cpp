// programmers (level 3) : 디스크 컨트롤러
// reference : https://dokylee.tistory.com/68

#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

struct Comp {
    bool operator() (pii& a, pii& b) {
        return a.second > b.second;         // 작업시간 기준 오름차순으로 pq 정렬.
    }
};

int solution(vector<vector<int>> jobs) {
    sort(jobs.begin(), jobs.end());                             // 요청시간 오름차순으로 정렬.
        
    int idx = 0;        // 작업 요청 순번.
    int time = 0;       // 현재시간.
    int answer = 0;     // 대기시간 + 작업시간.
    
    priority_queue<pii, vector<pii>, Comp> pq;      // 작업시간 오름차순 정렬 컨테이너.

    while (idx < jobs.size() || !pq.empty()) {                  // 작업 요청이 남아있거나 진행할 작업이 있으면 반복한다.
        while (idx < jobs.size() && jobs[idx][0] <= time) {         // 작업이 남아있고, 현재시간보다 이전에 요청이 있었으면
            pq.push(make_pair(jobs[idx][0], jobs[idx][1]));             // pq에 넣는다.
            idx++;                                                      // 요청 순번 증가.
        }
        
        if (!pq.empty()) {                                          // 진행할 작업이 있으면
            pii now = pq.top(); pq.pop();                               // 진행할 작업을 뽑는다. (가장 짧은 작업시간이 걸리는 작업)
            time += now.second;                                         // 현재시간에 작업시간을 더한다.
            answer += time - now.first;                                 // 이번 작업의 총 소요시간을 더한다. 총 소요시간 = (작업완료 기준)현재시간 - 요청시간
        }
        else {                                                      // 진행할 작업이 없으면
            time = jobs[idx][0];                                        // 현재시간을 다음 작업 요청시간으로 바꾼다.
        }
    }
    
    return answer / jobs.size();                        // 모든 작업 소요시간들의 평균을 return 한다.
}