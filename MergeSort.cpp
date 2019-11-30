#include "MergeSort.h"

void merge(vector<Item>& mergeVector, int left, int right) {
	int mid = left + (right - left) / 2;
	vector<Item> pull1, pull2;
	for (int i = mid; i >= left; i--) {
		pull1.push_back(mergeVector[i]);
	}
	for (int i = right; i > mid; i--) {
		pull2.push_back(mergeVector[i]);
	}
	int i = left;
	while (pull1.size() && pull2.size()) {
		if (pull1.back() > pull2.back()) {
			mergeVector[i] = pull1.back();
			pull1.pop_back();
		} else {
			mergeVector[i] = pull2.back();
			pull2.pop_back();
		}
		i++;
	}
	vector<Item>& restVector = pull1.size() ? pull1 : pull2;
	while (restVector.size()) {
		mergeVector[i] = restVector.back();
		restVector.pop_back();
		i++;
	}
}

void merge_sort(vector<Item>& mergeVector, int left, int right) {
	if (left == right) return;
	int mid = left + (right - left) / 2;
	merge_sort(mergeVector, left, mid);
	merge_sort(mergeVector, mid + 1, right);
	merge(mergeVector, left, right);
}
