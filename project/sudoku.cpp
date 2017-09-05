#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;
bool tright[9][9][9] = { 0 };
void main(int argc, char** argv) {
	ofstream outfile("sudoku.txt", ios::out);
	srand(time(0));
	int i=0;							//用于写循环
	int c, d;
	int j ;
	char g[] = "-c";
	cout << argc << endl;
	if (argv[1] != NULL) {
		cout << argv[1] << endl;
		if (strcmp(argv[1],"-c")!=0 ){
			cout << "you enter a wrong paramter" << endl;
			return;
		}
	}
	else {
		cout << "The paramter is no empty" << endl;
		return;
	}
	if (argv[2] != NULL) {
		cout << argv[2] << endl;
		for (i = 0; argv[2][i] != '\0'; i++) {
			if (argv[2][i] < '0'||argv[2][i]>'9') {
				cout << "you enter a wrong number" << endl;
				return;
			}
		}
		sscanf_s(argv[2], "%d", &j);
	}
	int anyway = 0;					//记录一个随机数
	int x, y;						//记录当前写入数的坐标
	int all[9][9] = { 0 };
	bool upright[9][9] = { 0 };		//每横行为一个x，从上到下
	bool transverse[9][9] = { 0 };	//每竖列为一个x，从左到右
	bool square[9][9] = { 0 };		//每一个九宫格为一个x，顺序排列
	all[0][0] = 8;					//左上第一个数为8
	upright[0][7] = 1;				//第0行的8被占据
	transverse[0][7] = 1;			//第0列的8被占据
	square[0][7] = 1;				//第0个九宫格的8被占据
	x = 1;							//当前需要写入为横向第二格，纵向第一格
	y = 0;
	while (1) {
		anyway = rand();
		anyway = anyway % 9 + 1;
		if (tright[y][x][anyway - 1] == 0) {
			if (square[(x / 3) + 3 * (y / 3)][anyway - 1] == 0) {
				if (upright[y][anyway - 1] == 0) {
					if (transverse[x][anyway - 1] == 0) {
						all[y][x] = anyway;
						upright[y][anyway - 1] = 1;
						transverse[x][anyway - 1] = 1;
						square[(x / 3) + 3 * (y / 3)][anyway - 1] = 1;
						y = y + x / 8;
						x = (x + 1) % 9;
					}
					else tright[y][x][anyway - 1] = 1;
				}
				else tright[y][x][anyway - 1] = 1;
			}
			else tright[y][x][anyway - 1] = 1;
		}
		if (all[8][8] != 0) {
			for(c = 0; c < 9; c++) {
				for (d = 0; d < 9; d++) {
					outfile << all[c][d] << ' ';
				}
				outfile << endl;
			}
			outfile << endl;
			tright[8][8][all[8][8] - 1] = 1;
			upright[8][all[8][8] - 1] = 0;
			transverse[8][all[8][8] - 1] = 0;
			square[8][all[8][8] - 1] = 0;
			all[8][8] = 0;
			j = j - 1;
			if (j == 0) {
				break;
			}
		}
		for (i = 0; i < 9; i++) {
			if (tright[y][x][i] == 0) {
				i = 100;
				break;
			}
		}
		if (i != 100) {
			for (i = 0; i < 9; i++) {
				tright[y][x][i] = 0;
			}
			if (x == 0) {
				x = 8;
				y = y - 1;
			}
			else {
				x = x - 1;
			}
			tright[y][x][all[y][x]-1] = 1;
			upright[y][all[y][x] - 1] = 0;
			transverse[x][all[y][x] - 1] = 0;
			square[(x / 3) + 3 * (y / 3)][all[y][x] - 1] = 0;
			all[y][x] = 0;
		}
	}
	outfile.close();
	cout << "finish";
}