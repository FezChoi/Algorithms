#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool comp(string a, string b) {
    return a + b > b + a;
}

string solution(vector<int> numbers) {
    unordered_map<char, vector<string>> hash;
    
    for (int numInt : numbers) {
        string numStr = to_string(numInt);
        hash[numStr[0]].push_back(numStr);
    }
    
    string answer = "";

    for (char i = 9 + '0'; i >= '0'; i--) {
        if (hash[i].empty()) continue;
        
        sort(hash[i].begin(), hash[i].end(), comp);

        for (string num : hash[i]) {
            answer += num;
        }
    }
    
    if (answer[0] == '0') return "0";
    
    return answer;
}
