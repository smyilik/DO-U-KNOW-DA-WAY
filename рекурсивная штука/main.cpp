#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

int MYstoi(string str)
{
	if (str.size() < 1) return 0;
	int num = 1, finalnum, i = 0, ten = 1;
	bool minus = false;
	if (str[0] == '-') {
		i++;
		minus = true;
	}
	for (i; i < str.size(); i++) {
		num *= 10;
		num += str[i] - 48;
		ten *= 10;
	}
	finalnum = num % ten;
	if (minus) return finalnum * -1;
	return finalnum;
}

vector<string> ReadFile(string& path)
{
	ifstream fileRead;
	fileRead.open(path);
	if (fileRead.is_open()) {
		string line = "";
		vector<string> mass = vector <string>();
		while (getline(fileRead, line)) {
			mass.push_back(line);
		}
		return mass;
	}
	else return { };
}

bool MazeChecker(vector<string>& maze)
{
	for (int y = 0; y < maze.size(); y++) {
		for (int x = 0; x < maze[y].size(); x++) {
			if (maze[y][x] != '*' && maze[y][x] != ' ') return false;
		}
	}
	return true;
}

int main()
{
	cout << "Input the path to your maze file" << endl;
	string path;
	getline(cin, path);

	vector<string> maze = ReadFile(path);

	int spawnY = MYstoi(maze[maze.size() - 2]);
	int spawnX = MYstoi(maze[maze.size() - 1]);
	maze.pop_back();
	maze.pop_back();

	if (!MazeChecker(maze)) {
		cout << endl << "Your Maze was generated or imported wrongly!" << endl;
		return 0;
	}

	maze[spawnY][spawnX] = '@';

	for (int i = 0; i < maze.size(); i++) cout << maze[i] << endl;
}