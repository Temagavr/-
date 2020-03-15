/*1.4. Реликтовая роща (6)
В заповеднике растет роща реликтовых деревьев. Для их защиты требуется обнести рощу забором.
Но для обеспечения доступа к остальной территории заповедника площадь участка, окруженного забором,
должна быть минимальной. Деревья растут точно в узлах координатной сетки на расстоянии одного метра друг от друга.
Любое из деревьев имеет хотя бы одного соседа (с юга, севера, востока или запада).
По заданной конфигурации рощи найти минимально необходимое число блоков для забора.

IDE - Visual Studio, Гаврилин Артем ПС-23*/
#include <iostream>
#include <fstream>
using namespace std;

typedef int Matrix[302][302];

int n, m;

void marker (int str, int stolb, int &count, Matrix matr) {
	if (matr[str][stolb] == 0) {
		matr[str][stolb] = 2;
		if (matr[str + 1][stolb] == 1 && str != n + 1) {
			++count;
		}
		if (matr[str - 1][stolb] == 1 && str != 0) {
			++count;
		}
		if (matr[str][stolb - 1] == 1 && stolb != 0) {
			++count;
		}
		if (matr[str][stolb + 1] == 1 && stolb != m + 1) {
			++count;
		}
		if (str != 0) { marker(str - 1, stolb, count, matr); }
		if (str != n + 1) { marker(str + 1, stolb, count, matr); }
		if (stolb != 0) { marker(str, stolb - 1, count, matr); }
		if (stolb != m + 1) { marker(str, stolb + 1, count, matr); }
		return;
	}
}


int main(int argc, char* argv[]) {
	ifstream fin;
	ofstream fout;
	(fin).open(argv[1]);
	(fout).open(argv[2]);
	if (!(fin).is_open() || !(fout).is_open()) {
		cout << "Error file not open!" << endl;
		return -1;
	}
	Matrix mat;
	fin >> n;
	fin >> m;
	for (int i = 0;i != n + 2; ++i) {
		for (int j = 0;j != m + 2; ++j) {
			if (i == 0 || i == n + 1) {
				mat[i][j] = 0;
				continue;
			}
			else if (j == 0 || j == m + 1) {
				mat[i][j] = 0;
				continue;
			}
			else {
				char c;
				fin >> c;
				mat[i][j] = c - '0';
			}
		}
	}

	int count = 0;
	for (int i = 0;i != n + 2; ++i) {
		for (int j = 0;j != m + 2; ++j) {
			if (mat[i][j] == 0) {
				marker(i, j, count, mat);
			}
			goto exit;
		}
	}
	exit:
	fout << count << endl;
}