#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<vector<int>> order = {
        { 0 },
        { 1, 2, 3, 4, 5 },
        { 2, 1, 2, 3, 2, 4, 2, 5 },
        { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5, }
    };
    
    vector<int> cycle = {
        0,
        (int)order[1].size(),
        (int)order[2].size(),
        (int)order[3].size()
    };

    vector<int> scores(4, 0);
    for (int i = 0; i < answers.size(); i++) {
        for (int man = 1; man <= 3; man++) {
            scores[man] += (answers[i] == order[man][i % cycle[man]]) ? 1 : 0;
        }
    }

    vector<int> answer;
    int maxScore = *max_element(scores.begin(), scores.end());
    for (int man = 1; man <= 3; man++) {
        if (scores[man] == maxScore) {
            answer.push_back(man);
        }
    }

    return answer;
}