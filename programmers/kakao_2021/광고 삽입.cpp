/*
    레퍼런스 참고하여 작성된 코드.
    https://www.youtube.com/watch?v=idW6hlAiBO8&list=PL6YHvWRMtz7BhuSvZDVzaQhODpoKuaAtB&index=5
*/

#include <string>
#include <vector>
#include <sstream>

using namespace std;

int convert(string time) {
    stringstream ss(time);
    int h, m, s;
    char tmp;
    ss >> h >> tmp >> m >> tmp >> s;
    
    return h * 60 * 60 + m * 60 + s;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    int playSec = convert(play_time);
    int advSec  = convert(adv_time);
    
    int totalSec[100 * 3600] = { 0, };
    
    for (string log : logs) {
        int start = convert(log.substr(0, 8));
        int end   = convert(log.substr(9, 8));
        
        for (int i = start; i < end; i++) {
            totalSec[i] += 1;
        }
    }
    
    long long curSum = 0;
    for (int i = 0; i < advSec; i++) {
        curSum += totalSec[i];
    }
    
    long long maxSum = curSum;
    int maxIdx = 0;
    for (int i = advSec; i < playSec; i++) {
        curSum = curSum - totalSec[i - advSec] + totalSec[i];
        if (maxSum < curSum) {
            maxSum = curSum;
            maxIdx = i - advSec + 1;
        }
    }
    
    char buf[10];
    sprintf(buf, "%02d:%02d:%02d", (maxIdx / 60) / 60, (maxIdx / 60) % 60, maxIdx % 60);
    
    string answer = buf;
    return answer;
}