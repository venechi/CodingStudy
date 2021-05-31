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
    //������� 1�� ���� ���� ��ġ
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
    //���� ���� �αװ��̹Ƿ� ���� ������ �����Ͽ� ��ȯ
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
            //������ ����ġ�� log�� ���Ͽ� ����
            noise = log(noise);
            graph[from].push_back(pair<int, double>(to, noise));
            graph[to].push_back(pair<int, double>(from, noise));
        }
        //�Ҽ��� �Ʒ� 10�ڸ����� ���
        printf("%.10f\n", getMinimunNoise(graph, 0, n - 1));
    }
}