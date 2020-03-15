#include "Tree.h"

Tree :: ~Tree() {};

Tree::Tree(char symChar) {
	Tree::symbol = symChar;
	Tree::num = 0;
};

void Tree::setLeft(Tree* ptr) {
	Tree::leftCh = ptr;
}

void Tree::setRight(Tree* ptr) {
	Tree::rightCh = ptr;
}

Tree* Tree::getLeft() {
	return Tree::leftCh;
}

Tree* Tree::getRight() {
	return Tree::rightCh;
}

char Tree::getSymbol() {
	return Tree::symbol;
}

int Tree::getNum() {
	return Tree::num;
}

void Tree::changeSymbol(char newCh) {
	Tree::symbol = newCh;
}

void Tree::changeNum(int newNum) {
	Tree::num = newNum;
}
