#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution2(vector<int> arr, int i, int j, int i_k) {
    sort(arr.begin() + i, arr.begin() + j + 1);
    
    return arr[i_k];
}

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    array.insert(array.begin(), 0);

    for(vector<int> cmd : commands) {
        int result = solution2(array, cmd[0], cmd[1], cmd[0] + cmd[2] - 1);
        answer.push_back(result);
    }
    
    return answer;
}