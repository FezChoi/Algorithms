#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end());
    
    for (int i = 0; i < phone_book.size() - 1; i++) {
        string head = phone_book[i];
        string body = phone_book[i + 1];
        if (body.substr(0, head.size()) == head) return false;
    }
    
    return true;
}