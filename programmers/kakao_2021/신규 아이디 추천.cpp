#include <string>
#include <vector>

using namespace std;

string solution(string new_id) {
    // stage 1
    int diff = 'A' - 'a';
    for (char& c : new_id) {
        if (c >= 'A' && c <= 'Z') {
            c -= diff;
        }
    }
    
    // stage 2
    string tmp_id = "";
    for (char c : new_id) {
        if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || 
             c == '-' || c == '_' || c == '.') {
            tmp_id += c;
        }
    }
    new_id = tmp_id;

    // stage 3
    tmp_id = "";
    for (char c : new_id) {
        if (!tmp_id.empty() && tmp_id.back() == '.' && c == '.') {
            continue;
        }
        tmp_id += c;
    }
    new_id = tmp_id;
    
    // stage 4
    if (new_id.front() == '.') new_id = new_id.substr(1);
    if (new_id.back()  == '.') new_id.pop_back();
    
    // stage 5
    if (new_id.length() == 0) new_id = 'a';
    
    // stage 6
    if (new_id.length() >= 16) new_id = new_id.substr(0, 15);
    if (new_id.back() == '.') new_id.pop_back();
    
    // stage 7
    while (new_id.length() <= 2) {
        new_id += new_id.back();
    }
    
    return new_id;
}