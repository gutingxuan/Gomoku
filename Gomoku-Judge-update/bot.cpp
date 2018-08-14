#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "jsoncpp/json.h" // C++编译时默认包含此库

using namespace std;

const int SIZE = 15;
bool Grid[SIZE][SIZE];

void placeAt(int x, int y)
{
	if (x >= 0 && y >= 0) {
		Grid[x][y] = true;
	}
}
Json::Value randomAvailablePosition()
{
	vector<int> xs, ys;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (Grid[i][j] == false) {
				xs.push_back(i);
				ys.push_back(j);
			}
		}
	}
	srand(time(0));
	int rand_pos = rand() % xs.size();
	Json::Value action;
	action["x"] = xs[rand_pos];
	action["y"] = ys[rand_pos];
	return action;
}
int main()
{
	// 读入JSON
	string str;
	//fstream cin("in.txt", ios_base::in | ios_base::out);
	getline(cin, str);
	Json::Reader reader;
	Json::Value input;
	reader.parse(str, input);

	// 分析自己收到的输入和自己过往的输出，并恢复状态
	int turnID = input["responses"].size();
	for (int i = 0; i < turnID; i++) {
		placeAt(input["requests"][i]["x"].asInt(), input["requests"][i]["y"].asInt());
		placeAt(input["responses"][i]["x"].asInt(), input["responses"][i]["y"].asInt());
	}
	placeAt(input["requests"][turnID]["x"].asInt(), input["requests"][turnID]["y"].asInt());
	// 做出决策存为myAction
	// 输出决策JSON
	Json::Value ret;
	ret["response"] = randomAvailablePosition();
	Json::FastWriter writer;
	cout << writer.write(ret) << endl;
	return 0;
}
