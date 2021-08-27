#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> preProcess(string s) {
    vector<string> arr;
    if (s[0] >= 'A' && s[0] <= 'Z') s[0] -= ('A' - 'a');
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
        if (s[i-1] >= 'a' && s[i-1] <= 'z' && s[i] >='a' && s[i] <= 'z') {
            arr.push_back(s.substr(i - 1, 2));
        }
    }
    sort(arr.begin(), arr.end());
    return arr;
}

int solution(string str1, string str2) {
    vector<string> a = preProcess(str1);
    vector<string> b = preProcess(str2);
    if (a.size() == 0 && b.size() == 0) return 65536;
    int apos = 0, bpos = 0;
    int intersectionCnt = 0;
    while (apos < a.size() && bpos < b.size()) {
        if (a[apos] == b[bpos]) {
            ++intersectionCnt;
            ++apos;
            ++bpos;
        }
        else {
            if (a[apos] < b[bpos]) ++apos;
            else ++bpos;
        }
    }
    return intersectionCnt * 65536 / (a.size() + b.size() - intersectionCnt);
}

int main(void) {
    int ans = solution("FRANCE", "french"); //16384
    ans = solution("handshake", "shake hands"); //65536
    ans = solution("aa1+aa2", "AAAA12"); //43690
    ans = solution("E=M*C^2", "e=m*c^2"); //65536
    return 0;
}