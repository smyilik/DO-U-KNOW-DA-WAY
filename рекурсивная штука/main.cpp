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

void whereGo(vector<string> &maze, vector<bool>& whereCanIGo, int x, int y) {
	if (maze[y][x - 1] == ' ') whereCanIGo[0] = true;
	else whereCanIGo[0] = false;
	if (maze[y - 1][x] == ' ') whereCanIGo[1] = true;
	else whereCanIGo[1] = false;
	if (maze[y][x + 1] == ' ') whereCanIGo[2] = true;
	else whereCanIGo[2] = false;
	if (maze[y + 1][x] == ' ') whereCanIGo[3] = true;
	else whereCanIGo[3] = false;
}

bool isExit(vector<string>& maze, int x, int y)
{
	if (x - 1 == 0 && maze[y][x - 1] == ' ') return true;
	if (y - 1 == 0 && maze[y - 1][x] == ' ') return true;
	if (x + 1 == maze[0].size() - 1 && maze[y][x + 1] == ' ') return true;
	if (y + 1 == maze.size() - 1 && maze[y + 1][x] == ' ') return true;
	return false;
}

void Move(vector<string>& maze, int x, int y, vector<vector<int>> &moves)
{
	maze[y][x] = '1';
	if (maze[0][x] == '1' ||
		maze[y][0] == '1' ||
		maze[maze.size() - 1][x] == '1' ||
		maze[y][maze[0].size() - 1] == '1') {
		moves.push_back({ x, y });
		return;
	}
	if (y > 0 && maze[y - 1][x] == ' ') Move(maze, x, y - 1, moves);
	if (x > 0 && maze[y][x - 1] == ' ') Move(maze, x - 1, y, moves);
	if (y < maze.size() && maze[y + 1][x] == ' ') Move(maze, x, y + 1, moves);
	if (x < maze[0].size() && maze[y][x + 1]) Move(maze, x + 1, y, moves);
}

int main()
{
	cout << "Input the path to your maze file" << endl;
	string path;
	getline(cin, path);

	vector<string> maze = ReadFile(path);
	vector<vector<int>> moves = vector<vector<int>>();
	int y = MYstoi(maze[maze.size() - 2]);
	int x= MYstoi(maze[maze.size() - 1]);
	maze.pop_back();
	maze.pop_back();

	if (!MazeChecker(maze)) {
		cout << endl << "Your Maze was generated or imported wrongly!" << endl;
		return 0;
	}

	Move(maze, x, y, moves);

	cout << moves[0][0] << " " << moves[0][1] << endl << moves.size() << " steps were made";
	/*string path;
	getline(cin, path);
	vector<string> mass = ReadFile(path);
	for (int i = 0; i < mass.size(); i++) {
		for (int j = 0; j < mass[i].size(); j++) {
			if (mass[i][j] == '+') mass[i][j] = '*';
		}
	}

	for (int i = 0; i < mass.size(); i++) {
		cout << mass[i] << endl;
	}*/

	//maze[y][x] = '@';
	//for (int i = 0; i < maze.size(); i++) cout << maze[i] << endl;
}
