#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    unordered_map<string, int> hash;
    string answer = "";

    for (string name : completion) {
        hash[name]++;
    }
    
    for (string name : participant) {
        hash[name]--;
        
        if (hash[name] < 0) {
            answer = name;
            break;
        }
    }
    
    return answer;
}