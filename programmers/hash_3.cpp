#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    unordered_map<string, int> hash;
    
    for (vector<string> cloth : clothes) {
        hash[cloth[1]]++;
    }
    
    int answer = 1;
    for (auto it = hash.begin(); it != hash.end(); it++) {
        answer *= it->second + 1;
    }
    
    return answer -= 1;
}