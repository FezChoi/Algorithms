#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;


int solution(vector<int> priorities, int location) {
    vector<pii> vec;
    for (int p : priorities) {
        vec.push_back(make_pair(p, 0));
    }
    
    vec[location].second = 1;
    
    int answer = 0;
    int pNow = 0;
    while (true) {
        bool isBiggist = true;
        int pNext = (pNow + 1) % vec.size();

        while (pNext != pNow) {
            if (vec[pNow].first < vec[pNext].first) {
                pNow = pNext;
                isBiggist = false;
                break;
            }
                
            pNext = (pNext + 1) % vec.size();
        }
        
        if (isBiggist) {
            if (vec[pNow].second == 1) {
                answer += 1;
                return answer;
            }
            else {
                vec.erase(vec.begin() + pNow);
                pNow = pNow % vec.size();
                answer += 1;
            }
        }
    }
    
    return answer;
}