#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> split(string record) {
    vector<string> terms(3);
    int pos = record.find(' ');
    terms[0] = record.substr(0, pos);
    record = record.substr(pos + 1);
    pos = record.find(' ');
    terms[1] = record.substr(0, pos);
    terms[2] = record.substr(pos + 1);
    return terms;
}

vector<string> solution(vector<string> record) {
    vector<pair<bool, string>> log;
    map<string, string> nickName;
    for (int i = 0; i < record.size(); ++i) {
        vector<string> terms = split(record[i]);
        switch (terms[0][0]) {
        case 'E' :
            log.push_back({ true, terms[1] });
            nickName[terms[1]] = terms[2];
            break;
        case 'L':
            log.push_back({ false, terms[1] });
            break;
        case 'C':
            nickName[terms[1]] = terms[2];
            break;
        }
    }
    vector<string> answer(log.size());
    for (int i = 0; i < log.size(); ++i) {
        if (log[i].first)
            answer[i] = nickName[log[i].second] + "님이 들어왔습니다.";
        else
            answer[i] = nickName[log[i].second] + "님이 나갔습니다.";
    }
    return answer;
}

int main(void) {
    auto ans = solution({"Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan"});
    //ans sholud be : {"Prodo님이 들어왔습니다.", "Ryan님이 들어왔습니다.", "Prodo님이 나갔습니다.", "Prodo님이 들어왔습니다."}
}