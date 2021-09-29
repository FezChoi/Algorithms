#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<string, int> psi;

bool comp_pii(pii a, pii b) {
    return a.second > b.second;
}

bool comp_psi(psi a, psi b) {
    return a.second > b.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    unordered_map<string, int> hash1;
    unordered_map<string, vector<pii>> hash2;

    for (int i = 0; i < genres.size(); i++) {
        hash1[genres[i]] += plays[i];
        hash2[genres[i]].push_back(make_pair(i, plays[i]));
    }
    
    vector<psi> vec1(hash1.begin(), hash1.end());
    sort(vec1.begin(), vec1.end(), comp_psi);
    
    vector<int> answer;

    for (psi v : vec1) {
        vector<pii> vec2(hash2[v.first].begin(), hash2[v.first].end());
        sort(vec2.begin(), vec2.end(), comp_pii);
                         
        for (int i = 0; i < vec2.size() && i < 2; i++) {
            answer.push_back(vec2[i].first);
        }
    }
    
    return answer;
}