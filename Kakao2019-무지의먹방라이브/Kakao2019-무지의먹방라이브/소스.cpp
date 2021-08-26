#include <string>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int solution(vector<int> food_times, long long k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < food_times.size(); ++i)pq.push(food_times[i]);
    int cycle = 0;
    long long passed = 0;
    while (!pq.empty()) {
        for (; cycle < pq.top(); ++cycle) {
            if (passed + pq.size() <= k) {
                passed += pq.size();
            }
            else {
                //이번 사이클에 끝남
                for (int i = 0; i < food_times.size(); ++i) {
                    if (food_times[i] <= cycle) continue;
                    else {
                        if (passed == k) return (i + 1);
                        ++passed;
                    }
                }
            }
        }
        pq.pop();
    }
    return -1;
}

int main(void) {
    int ans = solution({ 3,1,2 }, 5);
    //ans should be : 1
}