#include <string>
#include <vector>

using namespace std;

int blowUp(vector<string>& map) {
    int cnt = 0;
    vector<string> origin = map;
    for (int i = 0; i < map.size() - 1; ++i) {
        for (int j = 0; j < map[0].size() - 1; ++j) {
            if (origin[i][j] != 0 && origin[i][j] == origin[i][j + 1] && origin[i][j] == origin[i + 1][j] && origin[i][j] == origin[i + 1][j + 1]) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        if (map[i + k][j + l] != '0') {
                            map[i + k][j + l] = '0';
                            ++cnt;
                        }
                    }
                }

            }
        }
    }
    return cnt;
}

void move(vector<string>& map, int x, int y) {
    pair<int, int> cur = { x,y };
    pair<int, int>next = { x + 1,y };
    while (next.first < map.size()) {
        if (map[next.first][next.second] == '0') {
            map[next.first][next.second] = map[cur.first][cur.second];
            map[cur.first][cur.second] = '0';
            cur = next;
            next = { cur.first + 1,cur.second };
        }
        else break;
    }
}

void gravity(vector<string>& map) {
    for (int i = map.size() - 2; i >= 0; --i) {
        for (int j = 0; j < map[0].size(); ++j) {
            move(map, i, j);
        }
    }
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    for (int cnt = blowUp(board); cnt > 0; cnt = blowUp(board)) {
        answer += cnt;
        gravity(board);
    }
    return answer;
}

int main(void) {
    int ans = solution(4, 5, { "CCBDE", "AAADE", "AAABF", "CCBBF" }); //14
    ans = solution(6, 6, { "TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ" }); //15
    return 0;
}