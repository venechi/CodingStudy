#include <iostream>
#include <vector>

using namespace std;
vector<pair<string, pair<int, int>>> items(101);
vector<vector<pair<int,int>>> cache;
int n, w;
pair<int, int> temp;

pair<int,int> calc(int last_item, int volume_remaining) {
	pair<int,int>& ret = cache[last_item][volume_remaining];
	if (ret.first != -1) return ret;
	ret.first = 0;
	if (volume_remaining <= 0) return ret;
	for (int i = last_item + 1; i <= n; ++i) {
		if (volume_remaining >= items[i].second.first) {
			temp = calc(i, volume_remaining - items[i].second.first);
			if (ret.first < items[i].second.second + temp.first) {
				temp.first += items[i].second.second;
				temp.second = i;
				ret = temp;
			}
		}
	}
	return ret;
}

vector<string> getTakenItems() {
	vector<string> answer;
	pair<int, int> current;
	int volume = w;
	current = cache[0][volume];
	while (current.second != -1) {
		answer.push_back(items[current.second].first);
		volume -= items[current.second].second.first;
		current = cache[current.second][volume];
	}
	return answer;
}

int main(void) {
	int tc, item_volume, item_desire;
	string name;
	cin >> tc;
	for (int i = 0; i < tc; ++i) {
		cin >> n >> w;
		for (int i = 1; i <= n; ++i) {
			cin >> name >> item_volume >> item_desire;
			items[i] = { name,{item_volume,item_desire} };
		}
		cache = vector<vector<pair<int, int>>>(n + 1, vector<pair<int, int>>(w + 1, { -1,-1 }));
		cout << calc(0, w).first << " ";
		vector<string> takenItems = getTakenItems();
		cout << takenItems.size() << endl;
		for (int i = 0; i < takenItems.size(); ++i)
			cout << takenItems[i] << endl;
	}
	return 0;
}