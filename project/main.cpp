#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;
bool tright[9][9][9] = { 0 };
void main(int argc, char** argv) {
	ofstream outfile(".//sudoku.txt", ios::out);
	srand(time(0));
	int i=0;							//用于写循环
	int c, d;							//用于将数独写入文件时对数组的定位
	int j ;								//用于记录需要生成多少个数独
	char g[] = "-c";
	if (argv[1] != NULL) {				//若存在第一个运行参数
		if (strcmp(argv[1],"-c")!=0 ){	//若第一个运行参数不为"-c"
			cout << "you enter a wrong paramter" << endl;
			return;
		}
	}
	else {
		cout << "The paramter is no empty" << endl;
		return;
	}
	if (argv[2] != NULL) {				//判断是否存在第二个运行参数
		for (i = 0; argv[2][i] != '\0'; i++) {	//判断第二个巡行参数是否合法
			if (argv[2][i] < '0'||argv[2][i]>'9') {
				cout << "you enter a wrong number" << endl;
				return;
			}
		}
		sscanf_s(argv[2], "%d", &j);		//将第二个参数从字符数组形式转变为数字
	}
	if (j == 0) return;
	int anyway = 0;					//记录一个随机数
	int x, y;						//记录当前写入数的坐标
	int all[9][9] = { 0 };			//用于记录生成的数独
	bool upright[9][9] = { 0 };		//每横行为一个x，从上到下
	bool transverse[9][9] = { 0 };	//每竖列为一个x，从左到右
	bool square[9][9] = { 0 };		//每一个九宫格为一个x，顺序排列
	/*初始化*/
	all[0][0] = 8;					//左上第一个数为8
	upright[0][7] = 1;				//第0行的8被占据
	transverse[0][7] = 1;			//第0列的8被占据
	square[0][7] = 1;				//第0个九宫格的8被占据
	x = 1;							//当前需要写入为横向第二格，纵向第一格
	y = 0;
	while (1) {
		anyway = rand();			//取一个随机数
		anyway = anyway % 9 + 1;	//将随机数转变为数独中可能出现的数
		if (tright[y][x][anyway - 1] == 0) {						//判断本格是否出现过此数并无法生成无冲突的数独
			if (square[(x / 3) + 3 * (y / 3)][anyway - 1] == 0) {	//判断本格所处的九宫格内是否存在此数
				if (upright[y][anyway - 1] == 0) {					//判断本格所处的行内是否存在此数
					if (transverse[x][anyway - 1] == 0) {			//判断本格所处的列内是否存在此数
						all[y][x] = anyway;							//将本数记录入数独内
						upright[y][anyway - 1] = 1;					//记录：本行已存在此数
						transverse[x][anyway - 1] = 1;				//记录：本列已存在此数
						square[(x / 3) + 3 * (y / 3)][anyway - 1] = 1;	//记录：本宫已存在此数
						y = y + x / 8;								
						x = (x + 1) % 9;							//移至下一个需要写入的位置
					}
					else tright[y][x][anyway - 1] = 1;				//本格不能填入此数
				}
				else tright[y][x][anyway - 1] = 1;					//同上
			}
			else tright[y][x][anyway - 1] = 1;						//同上上
		}
		if (all[8][8] != 0) {										//判断：是否填完数独
			for(c = 0; c < 9; c++) {
				for (d = 0; d < 9; d++) {
					
					outfile << all[c][d] ;
					if (d != 8) {
						outfile << " ";
					}
				}
				outfile << endl;
			}														//将已生成的数独写入文件
			outfile << endl;
			tright[8][8][all[8][8] - 1] = 1;						//将已生成的数独最后一个数弃用，继续生成其他的数独
			upright[8][all[8][8] - 1] = 0;
			transverse[8][all[8][8] - 1] = 0;
			square[8][all[8][8] - 1] = 0;
			all[8][8] = 0;
			j = j - 1;
			if (j == 0) {
				break;
			}
		}
		if (tright[y][x][anyway - 1] == 1) {	//若此格可填，则无需接下来的判断
			for (i = 0; i < 9; i++) {
				if (tright[y][x][i] == 0) {						//判断是否此处九个数均不能使用
					i = 100;
					break;
				}
			}
			if (i != 100) {						//若此处九个数均不能使用，则回溯至上一个数的位置并重新填写
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
				tright[y][x][all[y][x] - 1] = 1;
				upright[y][all[y][x] - 1] = 0;
				transverse[x][all[y][x] - 1] = 0;
				square[(x / 3) + 3 * (y / 3)][all[y][x] - 1] = 0;
				all[y][x] = 0;
			}
		}
	}
	outfile.close();
	cout << "finish";
}