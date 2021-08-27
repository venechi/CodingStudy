#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

//직선이동
vector<pair<int, int>> straight = {
    {-1,0},{1,0},{0,-1},{0,1}
};

//회전이동
vector<vector<pair<pair<int,int>, pair<int,int>>>> turn = {
    //가로로 넓은 모양일때
    {
        {{0,0},{-1,-1}},{{0,0},{1,-1}},{{-1,1},{0,0}},{{1,1},{0,0}}
    },
    //세로로 넓은 모양일때
    {
        {{0,0},{-1,-1}},{{0,0},{-1,1}},{{1,-1},{0,0}},{{1,1},{0,0}}
    }
};

vector<vector<int>> map;
set<pair<pair<int, int>, pair<int, int>>> visited;

bool isOkay(const pair<int, int>& a) {
    if (a.first < 0 || a.first >= map.size() || a.second < 0 || a.second >= map.size()) return false;
    if (map[a.first][a.second] == 1) return false;
    return true;
}

pair<pair<int, int>, pair<int, int>> org(const pair<pair<int, int>, pair<int, int>>& a) {
    if (a.first.first == a.second.first) {
        if (a.first.second < a.second.second) return { a.first, a.second };
        else return { a.second,a.first };
    }
    else {
        if (a.first.first < a.second.first) return { a.first, a.second };
        else return { a.second, a.first };
    }
}

int solution(vector<vector<int>> board) {
    map = board;
    visited.insert({ { 0,0 }, { 0,1 } });
    queue<pair<int, pair<pair<pair<int, int>, pair<int, int>>, bool>>> q;
    q.push({ 0,{ {{0,0},{0,1}}, false } });
    while (!q.empty()) {
        pair<int, pair<pair<pair<int, int>, pair<int, int>>, bool>> cur = q.front(); q.pop();
        pair<pair<int, int>, pair<int, int>>& pos = cur.second.first;
        //way -> false:hori true:vert
        bool way = cur.second.second;
        int cnt = cur.first;

        pair<pair<int, int>, pair<int, int>> next;
        pair<int, int> through;
        if (pos.second.first == map.size() - 1 && pos.second.second == map.size() - 1) return cnt;
        for (int i = 0; i < straight.size(); ++i) {
            next = org({ {pos.first.first + straight[i].first, pos.first.second + straight[i].second}, {pos.second.first + straight[i].first, pos.second.second + straight[i].second} });
            if (isOkay(next.first) && isOkay(next.second)) {
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push({ cnt + 1,{next, way} });
                }
            }
        }
        for (int i = 0; i < turn[1].size(); ++i) {
            if (way) next = org({ {pos.first.first + turn[1][i].first.first, pos.first.second + turn[1][i].first.second}, {pos.second.first + turn[1][i].second.first, pos.second.second + turn[1][i].second.second} });
            else next = org({ {pos.first.first + turn[0][i].first.first, pos.first.second + turn[0][i].first.second}, {pos.second.first + turn[0][i].second.first, pos.second.second + turn[0][i].second.second} });
            if (i < 2) through = { pos.second.first ^ next.first.first ^ next.second.first, pos.second.second ^ next.first.second ^ next.second.second };
            else through = { pos.first.first ^ next.first.first ^ next.second.first, pos.first.second ^ next.first.second ^ next.second.second };
            if (isOkay(next.first) && isOkay(next.second) && isOkay(through)) {
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push({ cnt + 1,{next,!way} });
                }
            }
        }
    }
    return -1;
}

int main(void) {
    int ans = solution({ {0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0} });
    //ans should be 7
    return 0;
}