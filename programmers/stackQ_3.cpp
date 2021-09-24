#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<int> bridge;
    
    int truck_id = 0;
    int bridge_weight = 0;
    int time = 0;
    
    while (truck_id < truck_weights.size()) {        
        if (bridge.size() == bridge_length) {
            int truck_passed = bridge.front();
            bridge.pop();
            bridge_weight -= truck_passed;
        }
        
        if (bridge_weight + truck_weights[truck_id] > weight) {
            bridge.push(0);
        }
        else {
            int truck_input = truck_weights[truck_id++];
            bridge.push(truck_input);
            bridge_weight += truck_input;
        }
        
        time += 1;
    }

    time += bridge_length;

    return time;
}