#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

unordered_map<string, int> Map;     // 키워드를 인덱스로 바꾸기 위한 Hash Table.
vector<int> List[4][3][3][3];       // 키워드에 해당하는 Score를 저장할 리스트.

vector<int> solution(vector<string> info, vector<string> query) {
    Map["-"] = 0;                                                   // 키워드 인덱스화.
    Map["cpp"] = 1;     Map["java"] = 2;    Map["python"] = 3;
    Map["backend"] = 1; Map["frontend"] = 2;
    Map["junior"] = 1;  Map["senior"] = 2;
    Map["chicken"] = 1; Map["pizza"] = 2;
    
    for (auto str : info) {                                             // 입력.
        stringstream ss(str);                                               // stringstream : str에서 " ", "\n"을 제외하여 필요한 자료형을 반환.
        string a, b, c, d;                                                  // 4개의 string
        int score;                                                          // 1개의 integer
        ss >> a >> b >> c >> d >> score;                                    // string을 잘라서 각각의 타입으로 반환.
        
        int arr[4] = { Map[a], Map[b], Map[c], Map[d] };                    // Combination 준비.
        for (int i = 0; i < (1 << 4); i++) {                                // (1 << 4) 가지 경우의 수를 확인. (0000 ~ 1111)
            int idx[4] = { Map["-"], };                                         // 모든걸 포함하는 "-" 인덱스로 초기화.
            for (int j = 0; j < 4; j++) {                                       // 인덱스 포함 여부 순회. 
                if (i & (1 << j)) {                                                 // j번째 인덱스가 1이면
                    idx[j] = arr[j];                                                    // 인덱스 업데이트.
                }                                                                   // 아니면 초기값인 Map["-"] = 0.
            }
            List[idx[0]][idx[1]][idx[2]][idx[3]].push_back(score);              // 해당 리스트에 score 추가.
        }                                                                   // 모든 조합에 대해 진행.
    }
    
    for (int a = 0; a < 4; a++) {                                           // 모든 인덱스의 리스트를 오름차순으로 정렬.
        for (int b = 0; b < 3; b++) {
            for (int c = 0; c < 3; c++) {
                for (int d = 0; d < 3; d++) {
                    sort(List[a][b][c][d].begin(), List[a][b][c][d].end());
                }
            }
        }
    }
    
    vector<int> answer;
    for (auto str : query) {                                                            // 퀘리.
        stringstream ss(str);
        string a, b, c, d, temp;                                                            // temp : "and"를 담기 위한 변수.
        int score;
        ss >> a >> temp >> b >> temp >> c >> temp >> d >> score;                            // "and"를 제외하고 받음.
        
        auto& qList = List[Map[a]][Map[b]][Map[c]][Map[d]];                                 // 해당 인덱스의 리스트를 reference로 받아옴.
        vector<int>::iterator low = lower_bound(qList.begin(), qList.end(), score);         // n 이상 = 오름차순 후 lower_bound부터 끝까지
        answer.push_back(qList.end() - low);                                                // answer에 개수 추가
    }
    
    return answer;
}