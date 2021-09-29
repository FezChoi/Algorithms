#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(int a, int b) { return a > b; }

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), comp);
    vector<int> table(citations[0] + 1, 0);
    
    for (int c : citations) {
        for (int i = c; i >= 0; i--) {
            table[i] += 1;
        }
    }
    
    int answer = 0;

    for (int h = table.size() - 1; h >= 0; h--) {
        if (table[h] >= h) {
            answer = h;
            break;
        }
    }
    
    return answer;
}