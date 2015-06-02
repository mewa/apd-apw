#include <iostream>
#include <cstdlib>
#include "Backpack.h"

using namespace std;

void printForPerm(Backpack<int, int> const& backpack, int val);

void printFromTab(Backpack<int, int> const& backpack, vector<vector<int> >& v, int i, int j) {
	//cout << "i: " << i << " j: " << j << endl;
	if (v[i][j] && i > 0 && j > 0) {
		if (v[i][j] != v[i - 1][j]) {
			cout << i << " ";
			printFromTab(backpack, v, i - 1, j - backpack.sizeOf(i));
		}
		else {
			printFromTab(backpack, v, i - 1, j);
		}
	}
}

void dyna(Backpack<int, int> const& backpack) {
	vector<vector<int> > W(backpack.n + 1);
	for (int i = 0; i < W.size(); ++i) {
		W[i].resize(backpack.size + 1);
	}
	for (int i = 1; i < W.size(); ++i) { // for each item
		for (int j = 1; j < W[i].size(); ++j) { // for each capacity
			if (j < backpack.sizeOf(i)) {
				W[i][j] = W[i - 1][j];
			}
			else {
				if (W[i - 1][j] >= W[i - 1][j - backpack.sizeOf(i)] + backpack.valueOf(i)) {
					W[i][j] = W[i - 1][j];
				}
				else {
					W[i][j] = W[i - 1][j - backpack.sizeOf(i)] + backpack.valueOf(i);
				}
			}
		}
	}
	/*
	// odkomentowaæ aby wyœwietliæ tablicê dynamiczn¹
	cout << "W:\n";
	for (int i = 0; i < W.size(); ++i) {
		for (int j = 0; j < W[i].size(); ++j) {
			cout << W[i][j] << " ";
		}
		cout << endl;
	}
	*/
	cout << "answer: ";
	printFromTab(backpack, W, W.size() - 1, W[0].size() - 1);
	cout << "---" << endl;
}

void brute(Backpack<int, int> const& backpack) {
	cout << "brute" << endl;
	vector<vector<int> > W(backpack.n + 1);
	int maxPerm = 0;
	int maxValue = 0;
	for (int i = 0; i < pow(2, backpack.n); ++i) {
		int gray = i ^ (i >> 1);
		int value = 0;
		int size = 0;
		for (int j = 0; j < backpack.size; ++j) {
			if (gray & (1 << j)) {
				value += backpack.valueOf(j + 1);
				size += backpack.sizeOf(j + 1);
			}
		}
		if (size <= backpack.size) {
			if (value > maxValue) {
				maxValue = value;
				maxPerm = gray;
			}
		}
	}
	cout << "answer: ";
	printForPerm(backpack, maxPerm);
	cout << "---" << endl;
}

void printForPerm(Backpack<int, int> const& backpack, int val) {
	for (int j = 0; j < backpack.size; ++j) {
		if (val & (1 << j)) {
			cout << j + 1 << " ";
		}
	}
}

int main(int argc, char** argv) {
	int n, size;
	cin >> n >> size;						// pakuj plecak
	Backpack<int, int> backpack(n, size);
	for (int i = 0; i < n; ++i) {
		int s, v;
		cin >> v >> s;
		backpack.sizes.push_back(s);
		backpack.values.push_back(v);
	}
	backpack.print();
	dyna(backpack);  // dynamiczne
	//brute(backpack); // brute-force

	return 0;
}