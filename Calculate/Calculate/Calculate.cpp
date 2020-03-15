/*14.18. Вычисление выражения (7)
Во входной строке записано арифметическое выражение, состоящее из целых чисел и знаков операций «+», «-», «*»,
«/», «(», «)», «^». Пробелы в выражении отсутствуют. Требуется написать программу, которая вычислит значение данного
выражения.

Ввод. Входной файл INPUT.TXT содержит одну строку, состоящую не более чем из 255
символов. Числа в выражении не превышают по модулю 2×10^9. Гарантируется, что в процессе
вычислений получаемые значения не превышают по модулю 2×10^9.

Вывод. В единственной строке файла OUTPUT.TXT требуется вывести значение выражения с
точностью 4 знака после запятой.

IDE - Visual Studio, Гаврилин Артем ПС-23*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>
#include "Tree.h"

using namespace std;

void print_answer(ofstream* fout, double answer) {
	double intPart = 0, fractionalPart = 0;
	fractionalPart = modf(answer, &intPart);
	*fout << (int)intPart << ".";
	//fractionalPart = round(fractionalPart * 10000);
	if (fractionalPart < 0) { fractionalPart = fractionalPart * -1; }
	for (unsigned int i = 0; i < 4; ++i) {
		double temp = 0;
		fractionalPart = modf(fractionalPart*10, &temp);
		unsigned int tempInt = temp;
		if (tempInt < 0) {
			tempInt = tempInt * -1;
		}
		*fout << tempInt;
	}
	/*if (fractionalPart < 10) {
		*fout << fractionalPart << "000";
	}
	else if (fractionalPart < 100 && fractionalPart > 10) {
		*fout << fractionalPart << "00";
	}
	else if (fractionalPart < 1000 && fractionalPart > 100) {
		*fout << fractionalPart << "0";
	}
	else {
		*fout << fractionalPart;
	}*/
}

double print_down_bin(Tree* p, int level)
{
	if (p)
	{
		double left = print_down_bin(p->getLeft(), level + 1);
		double right = print_down_bin(p->getRight(), level + 1);
		/*for (int i = 0; i < level; i++)
			cout << '.';
		cout << p->getSymbol() << " ";
		cout << p->getNum() << endl;
		*/
		cout << "left = " << left << " right = " << right << endl;// Если это выводить то все окей  
		if (p->getNum() != 0 && p->getSymbol() == '#' && p->getLeft() == nullptr && p->getRight() == nullptr) {
			return p->getNum();
		}
		if (p->getSymbol() != '#') {
			if (p->getSymbol() == '+') {
				left = left + right;
			}
			if (p->getSymbol() == '-') {
				left = left - right;
			}
			else if (p->getSymbol() == '*') {
				left = left * right;
			}
			else if (p->getSymbol() == '/') {
				left = left / right;
			}
			else if (p->getSymbol() == '^') {
				left = pow(left, right);
			}
			return left;
		}
	}
}

void delExtraBrackets(string& str, int& it)
{
	if (str[0] == '(')
	{
		int bracketCount = 1;
		for (unsigned int i = 1; i < str.length(); ++i)
		{
			if (str[i] == '(') { ++bracketCount; }
			else if (str[i] == ')') { --bracketCount; }
			if (bracketCount == 0)
			{
				if (i == str.length() - 1)
				{
					str = str.substr(1, str.length() - 2);
				}
				else
				{
					it = 2;
					return;
				}
			}
			//cout << str[i] << " ";
			//cout << bracketCount << endl;
		}
		if (bracketCount != 0) { cout << "error with brackets!!!"; exit(0); }//ошибка при не равном количестве '(' и ')'
		it = 1;
	}
	else
	{
		it = 2;
	}
}

void split(string& str, set<char>& mySet, Tree* ssil)
{
	int ip = 0;
	while (ip != 2) {
		delExtraBrackets(str, ip);
	}
	int pos = -1, level = 0;
	string s2, s1;
	bool extendFl = false, umnFl = false;
	char ch = 'a';
	int someNum = 0, mathCount;
	mathCount = 0;
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '(')//пропуск скобок в выражении
		{
			++mathCount;
			++level;
			++i;
			while (level != 0)
			{
				if (str[i] == '(') { ++level; }
				if (str[i] == ')') { --level; }
				++i;
			};
			//if (str[i] == ')') { --level; }
		}
		if (mySet.find(i) == mySet.end())
		{
			++mathCount;
			//определение оператора
			if (str[i] == '+' || str[i] == '-')
			{
				pos = i;
				ch = str[pos];
			}
			if ((str[i] == '^') && (extendFl == false) && (ch != '*' && ch != '/'))
			{
				if (ch != '+' && ch != '-')
				{
					pos = i;
					ch = str[pos];
					extendFl = true;
				}
			}
			if (str[i] == '*' || str[i] == '/')
			{
				if ((ch != '+' && ch != '-' || pos == 0)/* && umnFl == false*/)
				{
					umnFl = true;
					pos = i;
					ch = str[pos];
				}
			}
		}
	}
	//cout << str[pos] << " some" << endl;
	if (mathCount != 0 && pos != -1) {
		s2 = str.substr(pos + 1, str.length() - pos);//right half
		s1 = str.substr(0, pos);
		ssil->changeSymbol(str[pos]);
	}
	if (mathCount >= 1 && pos != -1) {
		Tree* lt = new Tree('#');
		ssil->setLeft(lt);
		split(s1, mySet, lt);
		Tree* rt = new Tree('#');
		ssil->setRight(rt);
		split(s2, mySet, rt);
	}
	if(ch =='a') {
		for (char p : str) {
			if (isdigit(p)) {
				someNum = someNum * 10 + (p - '0');
			}
		}
		ssil->changeNum(someNum);
	}
}

int main(int argc, char* argv[]) {
	set<char> myS;
	myS.insert('+');
	myS.insert('-');
	myS.insert('/');
	myS.insert('*');
	myS.insert('^');
	string s;
	ifstream fin;
	ofstream fout;
	(fin).open("input.txt");
	(fout).open("output.txt");
	if (!(fin).is_open() || !(fout).is_open()) {
		cout << "Error file not open!" << endl;
		return -1;
	}
	fin >> s;
	Tree* root = new Tree('#');
	split(s, myS, root);
	double itog = print_down_bin(root, 0);
	print_answer(&fout, itog);
	//fout << round(itog * 10000) / 10000;
	//fout << (int)itog + modf(itog, &dr);
	return 0;
}



