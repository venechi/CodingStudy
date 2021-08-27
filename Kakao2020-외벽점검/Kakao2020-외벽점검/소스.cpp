#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> spot;

int getChecked(vector<bool>& checked, int spotNum, int distance) {
    int cnt = 1;
    checked[spotNum] = true;
    for (int i = spotNum + 1; i < spot.size(); ++i) {
        if (spot[i] <= spot[spotNum] + distance && !checked[i % checked.size()]) {
            ++cnt;
            checked[i % checked.size()] = true;
        }
    }
    return cnt;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    spot = vector<int>(weak.size() * 2);
    for (int i = 0; i < weak.size(); ++i) {
        spot[i] = weak[i];
        spot[i + weak.size()] = weak[i] + n;
    }
    bool success = false;
    int opt = dist.size();
    do {
        for (int sp = 0; sp < weak.size(); ++sp) {
            int spotNum = sp;
            int cnt = 0;
            vector<bool> checked(weak.size(), false);
            for (int i = 0; i < opt; ++i) {
                int newChecked = getChecked(checked, spotNum, dist[i]);
                cnt += newChecked;
                spotNum = (spotNum + newChecked) % weak.size();
                if (cnt == weak.size()) {
                    success = true;
                    opt = min(opt, i + 1);
                    break;
                }
            }
        }
    } while (next_permutation(dist.begin(), dist.end()));
    if (!success) return -1;
    else return opt;
}

int main(void) {
    int ans = solution(12, { 1,5,6,10 }, { 1,2,3,4 }); //ans should be 2
    ans = solution(12, { 1,3,4,9,10 }, { 3,5,7 }); //ans should be 1
    return 0;
}