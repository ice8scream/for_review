

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

#include "Item.h"
#include "MergeSort.h"

using namespace std;

void printVectorOfItems(vector<Item>& items, string msg = "") {
	cout << "Предметы";
	if (msg.length()) {
		cout << " " << msg;
	}
	cout << ":\n\t";
	for (vector<Item>::iterator it = items.begin(); it != items.end(); it++) {
		cout << *it;
		if (it + 1 != items.end()) {
			cout << ", ";
		}
	}
	cout << endl;
}

void printBackPackState(vector<Item>& items, vector<int>& inBP, map<int, int>& takeOther, int itemsWeight, int itemsCost, int BackPackSpace) {
	cout << "В рюкзак мы положим следующие предметы: {c/w}\n\t";
	for (unsigned int i = 0; i < items.size(); i++) {
		if (inBP[i] || takeOther.count(i)) {
			if (!takeOther.count(i)) {
				cout << "{" << items[i].getCost() << "/" << items[i].getWeight() << "} ";
			}
			else if (takeOther[i]) {
				cout << "{" << items[i].getCost() << "/" << items[i].getWeight() << "} ";
			}
		}
	}
	cout << "\nВектор предметов: { ";
	for (unsigned int i = 0; i < items.size(); i++) {
		if (takeOther.count(i)) {
			cout << takeOther[i];
		}
		else {
			cout << inBP[i];
		}
		if (i + 1 < items.size()) {
			cout << ", ";
		}
	}
	cout << " } (1 - значит в рюкзаке)\n";
	cout << "Рюкзак заполнен на " << itemsWeight << "/" << BackPackSpace << ", общая ценность предметов внутри: " << itemsCost << endl;
}

vector<Item> inputVector = { {3, 2}, {5, 5}, {2, 5}, {3, 4} };
vector<int> ItemInBP = { 0, 0, 0, 0 };
int BackPackSpace = 13;

int main() {

	map<int, int> emptyMap;
	printVectorOfItems(inputVector, "до сортировки");
	merge_sort(inputVector, 0, inputVector.size() - 1);
	printVectorOfItems(inputVector, "после сортировки");
	cout << endl;
	int itemsWeight = 0, itemsCost = 0, restCost = 0;
	unsigned int i;
	for (i = 0; i < inputVector.size(); i++) {
		if (itemsWeight + inputVector[i].getWeight() > BackPackSpace) break;
		itemsWeight += inputVector[i].getWeight();
		itemsCost += inputVector[i].getCost();
		ItemInBP[i] = 1;
	}

	if (itemsWeight != BackPackSpace) {
		cout << "Есть первый вариант заполнения рюкзака, а именно:\n";
		printBackPackState(inputVector, ItemInBP, emptyMap, itemsWeight, itemsCost, BackPackSpace);
		cout << endl;
		for (unsigned int j = 0; j < inputVector.size(); j++) {

			map<int, int> otherItems;
			otherItems[j] = 1 - ItemInBP[j];
			int otherWeight = itemsWeight + inputVector[j].getWeight() * (1 - ItemInBP[j] * 2);
			cout << "Попробуем " << (otherItems[j] ? "добавить " : "удалить ");
			cout << j + 1 << "-тый по счету предмет: {" << inputVector[j].getCost() << "/" << inputVector[j].getWeight() << "}\n";
			cout << endl;
			if (otherWeight <= BackPackSpace) {
				int otherCost = itemsCost + inputVector[j].getCost() * (1 - ItemInBP[j] * 2);
				if (i <= j) i = j + 1;
				for (unsigned int z = i; z < inputVector.size(); z++) {
					if (otherWeight + inputVector[z].getWeight() > BackPackSpace) break;
					otherWeight += inputVector[z].getWeight();
					otherCost += inputVector[z].getCost();
					otherItems[z] = 1;
				}
				if (otherItems.size() > 1) {
					map<int, int>::iterator key = otherItems.begin();
					key++;
					cout << "Так же добавим: ";
					while (key != otherItems.end()) {

						cout << "{" << inputVector[key->first].getCost() << "/" << inputVector[key->first].getWeight() << "} ";
						key++;
					}
					cout << endl;
				}
				cout << endl;
				cout << "Получим:\n";
				printBackPackState(inputVector, ItemInBP, otherItems, otherWeight, otherCost, BackPackSpace);
				cout << endl;
				if (otherCost > itemsCost) {
					cout << "Новый набор предметов по суммарной цене лучше старого (" << otherCost << ">" << itemsCost << "), значит теперь считаем оптимальным новый набор\n";
					itemsCost = otherCost;
					itemsWeight = otherWeight;
					for (map<int, int>::iterator key = otherItems.begin(); key != otherItems.end(); key++) {
						ItemInBP[key->first] = key->second;
					}
				}
				else {
					cout << "Новый набор предметов по суммарной цене не лучше старого (" << otherCost << "<=" << itemsCost << "), значит оптимальным остается старый набор\n";
				}
			}
			else {
				cout << "При добавлении предмета {" << inputVector[j].getCost() << "/" << inputVector[j].getWeight();
				cout << "} общий вес предметов в рюкзаке стал: " << otherWeight << ", что больше чем места в рюкзаке (" << BackPackSpace << ")\n";
			}
			cout << "---------------------------------\n\n";
			if (j + 1 < inputVector.size()) {
				cout << "Переходим к слудующему ветвлению!\n\n";
			}
		}
		cout << "----------------------------------------------|\n";
		cout << "Мы проверили все возможные варианты ветвлений!|\n";
		cout << "----------------------------------------------|\n\n";
	}
	else {
		cout << "Рюкзак полностью заполнен предметами с наибольшей удельной стоимостью!\n\n";
	}
	cout << "Итак, оптимальное решение:\n\n";
	printBackPackState(inputVector, ItemInBP, emptyMap, itemsWeight, itemsCost, BackPackSpace);
	system("PAUSE");
	return 0;
}
