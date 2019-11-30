#include "Item.h"
#include <iostream>

using namespace std;

Item::Item(int cost = 1, int weight = 1) {
	this->cost = cost;
	this->weight = weight;
}

double Item::unitCost()
{
	return (double)cost / weight;
}

void Item::printItem() {
	cout << "Предмет:" << endl;
	cout << " Цена:\t\t" << this->cost << endl;
	cout << " Вес:\t\t" << this->weight << endl;
	cout << " Удельная цена:\t" << this->unitCost() << endl;
}

bool Item::operator<(Item& other) {
	return this->unitCost() < other.unitCost();
}

bool Item::operator>(Item& other) {
	return this->unitCost() > other.unitCost();
}

const int Item::getCost() {
	return this->cost;
}

const int Item::getWeight() {
	return this->weight;
}

ostream& operator<<(ostream& os, const Item& item) {
	os << "{" << item.cost << "/" << item.weight << "}";
	return os;
}