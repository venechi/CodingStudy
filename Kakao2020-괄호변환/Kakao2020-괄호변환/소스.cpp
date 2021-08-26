#include <string>
#include <vector>

using namespace std;

bool isCorrect(string s) {
    int left = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(') ++left;
        else {
            if (left == 0) return false;
            else --left;
        }
    }
    return (left == 0);
}

int split(string s) {
    int left = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(') ++left;
        else --left;
        if (left == 0) return i + 1;
    }
}

string process(string s) {
    string ans = "";
    for (int i = 1; i < s.size() - 1; ++i) {
        if (s[i] == '(') ans += ')';
        else ans += '(';
    }
    return ans;
}

string solution(string p) {
    if (isCorrect(p)) return p;
    else {
        int pos = split(p);
        string u = p.substr(0, pos);
        string v = p.substr(pos);
        if (isCorrect(u)) return u + solution(v);
        else return "(" + solution(v) + ")" + process(u);
    }
}

int main(void) {
    string ans = solution("(()())()"); //ans should be : "(()())()"
    ans = solution(")(");   //ans should be : "()"
    ans = solution("()))((()"); //ans should be : "()(())()"
    return 0;
}