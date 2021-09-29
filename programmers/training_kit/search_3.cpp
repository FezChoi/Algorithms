#include <string>
#include <vector>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    
    int total = brown + yellow;
    
    for (int row = total - 3; row >= 3 && row >= (total / row); row--) {        
        if (total % row == 0 && yellow % (row - 2) == 0) {
            answer.push_back(row);
            answer.push_back(total / row);
            break;
        }
    }
    
    return answer;
}