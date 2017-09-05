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
	int i=0;							//����дѭ��
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
	int anyway = 0;					//��¼һ�������
	int x, y;						//��¼��ǰд����������
	int all[9][9] = { 0 };
	bool upright[9][9] = { 0 };		//ÿ����Ϊһ��x�����ϵ���
	bool transverse[9][9] = { 0 };	//ÿ����Ϊһ��x��������
	bool square[9][9] = { 0 };		//ÿһ���Ź���Ϊһ��x��˳������
	all[0][0] = 8;					//���ϵ�һ����Ϊ8
	upright[0][7] = 1;				//��0�е�8��ռ��
	transverse[0][7] = 1;			//��0�е�8��ռ��
	square[0][7] = 1;				//��0���Ź����8��ռ��
	x = 1;							//��ǰ��Ҫд��Ϊ����ڶ��������һ��
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