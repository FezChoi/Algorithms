#include <string>
#include <vector>

using namespace std;

typedef pair<int, bool> pib;

int solution(vector<int> priorities, int location) {
    vector<pib> printer;
    for (int i = 0; i < priorities.size(); i++) {
        printer.push_back(make_pair(priorities[i], false));
    }
    
    printer[location].second = true;
    
    int idx = 0;
    int printed = 0;
    int size = printer.size();

    while (!printer.empty()) {
        bool isPrint = true;
        
        for (int i = (idx + 1) % size; i != idx; i = (i + 1) % size) {
            if (printer[idx].first < printer[i].first) {
                isPrint = false;
                idx = i;
                break;
            }
        }
        
        if (isPrint) {
            printed += 1;

            if (printer[idx].second) {
                break;
            }
            printer.erase(printer.begin() + idx);
            size = printer.size();
            idx %= size;
        }
    }
    
    return printed;
}