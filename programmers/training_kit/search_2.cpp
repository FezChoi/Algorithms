#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<bool> visit;
set<int> table;
int answer = 0;

void check_prime(string numStr) {
    if (numStr.length() == 0) return;

    int numInt = 0;
    for (int i = numStr.length() - 1; i >= 0; i--) {
        numInt *= 10;
        numInt += numStr[i] - '0';
    }

    if (table.insert(numInt).second == false) return;
    if (numInt == 1 || (numInt != 2 && numInt % 2 == 0)) return;
    
    for (int i = 3; i * i <= numInt; i += 2) {
        if (numInt % i == 0) return;
    }
    
    answer++;
    return;
}

void DFS(string numbers, string numStr, int level) {
    check_prime(numStr);

    if (level >= numbers.length()) return;

    for (int i = 0; i < numbers.length(); i++) {        
        if (visit[i] == true) continue;
        
        visit[i] = true;
        DFS(numbers, numStr + numbers[i], level + 1);
        visit[i] = false;
    }
}

int solution(string numbers) {
    visit = vector<bool>(numbers.size(), false);

    DFS(numbers, "", 0);
    
    return answer;
}