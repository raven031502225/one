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
	int i=0;							//����дѭ��
	int c, d;							//���ڽ�����д���ļ�ʱ������Ķ�λ
	int j ;								//���ڼ�¼��Ҫ���ɶ��ٸ�����
	char g[] = "-c";
	if (argv[1] != NULL) {				//�����ڵ�һ�����в���
		if (strcmp(argv[1],"-c")!=0 ){	//����һ�����в�����Ϊ"-c"
			cout << "you enter a wrong paramter" << endl;
			return;
		}
	}
	else {
		cout << "The paramter is no empty" << endl;
		return;
	}
	if (argv[2] != NULL) {				//�ж��Ƿ���ڵڶ������в���
		for (i = 0; argv[2][i] != '\0'; i++) {	//�жϵڶ���Ѳ�в����Ƿ�Ϸ�
			if (argv[2][i] < '0'||argv[2][i]>'9') {
				cout << "you enter a wrong number" << endl;
				return;
			}
		}
		sscanf_s(argv[2], "%d", &j);		//���ڶ����������ַ�������ʽת��Ϊ����
	}
	if (j == 0) return;
	int anyway = 0;					//��¼һ�������
	int x, y;						//��¼��ǰд����������
	int all[9][9] = { 0 };			//���ڼ�¼���ɵ�����
	bool upright[9][9] = { 0 };		//ÿ����Ϊһ��x�����ϵ���
	bool transverse[9][9] = { 0 };	//ÿ����Ϊһ��x��������
	bool square[9][9] = { 0 };		//ÿһ���Ź���Ϊһ��x��˳������
	/*��ʼ��*/
	all[0][0] = 8;					//���ϵ�һ����Ϊ8
	upright[0][7] = 1;				//��0�е�8��ռ��
	transverse[0][7] = 1;			//��0�е�8��ռ��
	square[0][7] = 1;				//��0���Ź����8��ռ��
	x = 1;							//��ǰ��Ҫд��Ϊ����ڶ��������һ��
	y = 0;
	while (1) {
		anyway = rand();			//ȡһ�������
		anyway = anyway % 9 + 1;	//�������ת��Ϊ�����п��ܳ��ֵ���
		if (tright[y][x][anyway - 1] == 0) {						//�жϱ����Ƿ���ֹ��������޷������޳�ͻ������
			if (square[(x / 3) + 3 * (y / 3)][anyway - 1] == 0) {	//�жϱ��������ľŹ������Ƿ���ڴ���
				if (upright[y][anyway - 1] == 0) {					//�жϱ��������������Ƿ���ڴ���
					if (transverse[x][anyway - 1] == 0) {			//�жϱ��������������Ƿ���ڴ���
						all[y][x] = anyway;							//��������¼��������
						upright[y][anyway - 1] = 1;					//��¼�������Ѵ��ڴ���
						transverse[x][anyway - 1] = 1;				//��¼�������Ѵ��ڴ���
						square[(x / 3) + 3 * (y / 3)][anyway - 1] = 1;	//��¼�������Ѵ��ڴ���
						y = y + x / 8;								
						x = (x + 1) % 9;							//������һ����Ҫд���λ��
					}
					else tright[y][x][anyway - 1] = 1;				//�������������
				}
				else tright[y][x][anyway - 1] = 1;					//ͬ��
			}
			else tright[y][x][anyway - 1] = 1;						//ͬ����
		}
		if (all[8][8] != 0) {										//�жϣ��Ƿ���������
			for(c = 0; c < 9; c++) {
				for (d = 0; d < 9; d++) {
					
					outfile << all[c][d] ;
					if (d != 8) {
						outfile << " ";
					}
				}
				outfile << endl;
			}														//�������ɵ�����д���ļ�
			outfile << endl;
			tright[8][8][all[8][8] - 1] = 1;						//�������ɵ��������һ�������ã�������������������
			upright[8][all[8][8] - 1] = 0;
			transverse[8][all[8][8] - 1] = 0;
			square[8][all[8][8] - 1] = 0;
			all[8][8] = 0;
			j = j - 1;
			if (j == 0) {
				break;
			}
		}
		if (tright[y][x][anyway - 1] == 1) {	//���˸�����������������ж�
			for (i = 0; i < 9; i++) {
				if (tright[y][x][i] == 0) {						//�ж��Ƿ�˴��Ÿ���������ʹ��
					i = 100;
					break;
				}
			}
			if (i != 100) {						//���˴��Ÿ���������ʹ�ã����������һ������λ�ò�������д
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