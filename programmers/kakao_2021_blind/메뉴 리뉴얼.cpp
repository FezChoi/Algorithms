#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
typedef pair<string, int> psi;

bool comp(psi a, psi b) {                           // 코스 길이 오름차순 -> 호출 횟수 내림차순.
    if (a.first.length() == b.first.length()) {
        return a.second > b.second;
    }
    return a.first.length() < b.first.length();
}

unordered_map<string, int> map;         // hash table, 코스 카운트.
unordered_map<string, int> check;       // check table, 각 주문의 코스가 이미 체크되었는지 확인.

void DFS(string order, int index, string course) {          // 현재 주문에서 코스의 모든 종류를 체크하는 함수, order는 사전 순서로 정렬되어 넘어옴.
    if (course.length() >= 2 && check[course] == 0) {           // 코스 길이가 2 이상이고, 현재 주문에서 체크되지 않았으면
        check[course] = 1;                                      // 체크하고, hash[코스] 카운트 업.
        map[course] += 1;
    }
    
    if (index >= order.length()) {                              // 인덱스가 넘어가면 종료.
        return;
    }
                                                                // order가 정렬되어 있기 때문에 이전 인덱스들은 순회할 필요 없다.
    for (; index < order.length(); index++) {                   // 다음 인덱스부터 마지막 인덱스 중        
        DFS(order, index + 1, course + order[index]);               // 현재 방문한 인덱스 + 1 넘겨주면서, 코스에 현재 알파벳 추가.
        DFS(order, index + 1, course);                              // 현재 방문한 인덱스 + 1 넘겨주면서, 코스는 그대로.
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    for (string order : orders) {               // 주문 하나씩 순회.
        check.clear();                          // 체크 테이블 초기화.
        sort(order.begin(), order.end());       // 주문 사전 순으로 정렬.            
        DFS(order, 0, "");                      // 주문 조합마다 체크.
    }
    
    vector<psi> vec(map.begin(), map.end());    // 복사.
    sort(vec.begin(), vec.end(), comp);         // 코스 길이 오름차순 -> 호출 횟수 내림차순 정렬.
    
    vector<string> answer;

    for (int i = 0, j = 0; i < vec.size(); i++) {
        if (vec[i].first.length() == course[j] &&               // 코스 길이가 course[j]와 같고, 2번 이상 호출 되었을 때, 정담에 추가.
            vec[i].second >= 2) {
            answer.push_back(vec[i].first);                        
            
            while (vec[i + 1].first.length() == course[j] &&        // 위와 같은 길이와 호출 횟수의 코스들도 정답에 추가.
                   vec[i + 1].second == vec[i].second) {
                answer.push_back(vec[i + 1].first);
                i++;
            }
            j++;                                                    // 다음 코스 길이.
        }
    }
    
    sort(answer.begin(), answer.end());                 // 사전 순으로 정렬.
    
    return answer;
}