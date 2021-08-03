#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> map;

vector<vector<pair<int, int>>> tetromino = {
	//bar
	{
		{0,0},{0,1},{0,2},{0,3},
	},
	{
		{0,0},
		{1,0},
		{2,0},
		{3,0}
	},

	//square
	{
		{0,0},{0,1},
		{1,0},{1,1}
	},

	//Fxxx
	{
		{0,0},{0,1},{0,2},
			  {1,1}
	},
	{
		{0,0},
		{1,0},{1,1},
		{2,0}
	},
	{
		     {-1,1},
		{0,0},{0,1},{0,2}
	},
	{
		       {0,0},
		{1,-1},{1,0},
		       {2,0}
	},

	//twist
	{
		{0,0},{0,1},
	          {1,1},{1,2}
	},
	{
			   {0,-1},{0,0},
		{1,-2},{1,-1}
	},
	{
		{0,0},
		{1,0},{1,1},
		      {2,1}
	},
	{
		       {0,0},
		{1,-1},{1,0},
		{2,-1}
	},

	//L
	{
		{0,0},
		{1,0},
		{2,0},{2,1}
	},
	{
		{0,0},{0,1},
		{1,0},
		{2,0}
	},
	{
		{0,0},{0,1},{0,2},
		{1,0}
	},
	{
		{0,0},{0,1},{0,2},
					{1,2}
	},
	{
					{-1,2},
		{0,0},{0,1},{0,2}
	},
	{
		{-1,0},
		{0,0},{0,1},{0,2}
	},
	{
		{0,0},{0,1},
			  {1,1},
			  {2,1}
	},
	{
		     {-2,1},
			 {-1,1},
		{0,0},{0,1}
	}
};

int getMaxScoreAtPoint(int x, int y) {
	int sum = 0, maxSum = 0;
	int calX, calY;
	for (int i = 0; i < tetromino.size(); ++i) {
		sum = 0;
		for (int j = 0; j < 4; ++j) {
			calX = tetromino[i][j].first + x;
			calY = tetromino[i][j].second + y;
			if (calX < 0 || calX >= N || calY < 0 || calY >= M) {
				sum = 0;
				break;
			}
			sum += map[calX][calY];
		}
		maxSum = max(maxSum, sum);
	}
	return maxSum;
}

int main(void) {
	cin >> N >> M;
	map = vector<vector<int>>(N, vector<int>(M));
	for (int i = 0; i < N; ++i)for (int j = 0; j < M; ++j)cin >> map[i][j];
	int maximum = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			maximum = max(maximum, getMaxScoreAtPoint(i, j));
		}
	}
	cout << maximum << endl;
	return 0;
}
