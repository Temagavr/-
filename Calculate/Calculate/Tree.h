#pragma once

class Tree {
private:
	Tree* leftCh;
	Tree* rightCh;
	char symbol;
	int num;
public:
	Tree(char symChar);
	~Tree();
	void setLeft(Tree* ptr);
	void setRight(Tree* ptr);
	Tree* getLeft();
	Tree* getRight();
	char getSymbol();
	int getNum();
	void changeSymbol(char newCh);
	void changeNum(int newNum);
};