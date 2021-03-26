#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cfloat>
#include <cmath>

using namespace std;

double getMinimunNoise(const vector<vector<pair<int, double>>>& graph, int from, int to) {
    queue<int> q;
    vector<double> minimumNoise(graph.size(), DBL_MAX);
    int current, next;
    q.push(from);
    //log1 == 0
    //잡음비는 1이 가장 낮은 수치
    minimumNoise[from] = 0;
    while (!q.empty()) {
        current = q.front();
        q.pop();
        for (const pair<int, double>& edge : graph[current]) {
            next = edge.first;
            //logA + logB == log(A*B)
            if (minimumNoise[next] > minimumNoise[current] + edge.second) {
                minimumNoise[next] = minimumNoise[current] + edge.second;
                q.push(next);
            }
        }
    }
    //A == exp(log(A))
    //구한 값은 로그값이므로 원래 값으로 복구하여 반환
    return exp(minimumNoise[to]);
}

int main(void) {
    int testcase, n, m, from, to;
    double noise;
    cin >> testcase;
    for (int i = 0; i < testcase; ++i) {
        cin >> n >> m;
        vector<vector<pair<int, double>>> graph(n, vector<pair<int, double>>());
        for (int j = 0; j < m; ++j) {
            cin >> from >> to >> noise;
            //노이즈 가중치에 log를 취하여 저장
            noise = log(noise);
            graph[from].push_back(pair<int, double>(to, noise));
            graph[to].push_back(pair<int, double>(from, noise));
        }
        //소수점 아래 10자리까지 출력
        printf("%.10f\n", getMinimunNoise(graph, 0, n - 1));
    }
}