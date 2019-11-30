#pragma once
#include <iostream>

using namespace std;

class Item
{
public:

	Item(int, int);

	double unitCost();

	void printItem();

	friend ostream& operator<<(ostream&, const Item&);
	bool operator<(Item&);
	bool operator>(Item&);

	const int getCost();
	const int getWeight();

private:
	int cost;
	int weight;
};

