#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> 	vi;
typedef pair<int, int> 	pii;
typedef vector<pii> 	vpii;

#define MAX_SIZE 101

struct NumCounter {
	vpii numCounter;
	vi index;

	void init() {
		numCounter = vpii();
		index = vi(MAX_SIZE, -1);
	}

	void check(int a) {
		if (index[a] == -1) {
			index[a] = numCounter.size();
			numCounter.push_back(make_pair(a, 1));
		}
		else {
			numCounter[index[a]].second++;
		}
	}

	static bool comp(pii a, pii b) {
		return (a.second == b.second) ? a.first < b.first : a.second < b.second;
	}

	vi getNewLine() { 
		sort(numCounter.begin(), numCounter.end(), comp);

		vi newRow(1, 0);
		for (int i = 0; i < numCounter.size(); i++) {
			newRow.push_back(numCounter[i].first);
			newRow.push_back(numCounter[i].second);
		}

		return newRow;
	}
};

NumCounter numCounter;

struct ArrHandler {
	vector<vi> arr;
	int rowSize;
	int colSize;

	ArrHandler() {
		arr = vector<vi>(MAX_SIZE, vi(MAX_SIZE, 0));
		rowSize = 3;
		colSize = 3;
	}
	
	int getValue(int rowIdx, int colIdx) {
		return arr[rowIdx][colIdx];
	}

	bool isRowBigger() {
		return rowSize >= colSize;
	}

	void swapRow(int rowIdx, vi newRow) {
		int newSize = min(100, (int)newRow.size() - 1);

		int colIdx = 1;
		for (; colIdx <= newSize; colIdx++) {
			arr[rowIdx][colIdx] = newRow[colIdx];
		}
		for (; colIdx <= colSize; colIdx++) {
			arr[rowIdx][colIdx] = 0;
		}

		colSize = max(colSize, newSize);
	}

	void sortRow() {
		for (int rowIdx = 1; rowIdx <= rowSize; rowIdx++) {
			numCounter.init();
			for (int colIdx = 1; colIdx <= colSize; colIdx++) {
				if (arr[rowIdx][colIdx] == 0) continue;
				numCounter.check(arr[rowIdx][colIdx]);
			}

			swapRow(rowIdx, numCounter.getNewLine());
		}
	}

	void swapCol(int colIdx, vi newCol) {
		int newSize = min(100, (int)newCol.size() - 1);

		int rowIdx = 1; 
		for (; rowIdx <= newSize; rowIdx++) {
			arr[rowIdx][colIdx] = newCol[rowIdx];
		}
		for (; rowIdx <= rowSize; rowIdx++) {
			arr[rowIdx][colIdx] = 0;
		}

		rowSize = max(rowSize, newSize);
	}

	void sortCol() {
		for (int colIdx = 1; colIdx <= colSize; colIdx++) {
			numCounter.init();
			for (int rowIdx = 1; rowIdx <= rowSize; rowIdx++) {
				if (arr[rowIdx][colIdx] == 0) continue;
				numCounter.check(arr[rowIdx][colIdx]);
			}

			swapCol(colIdx, numCounter.getNewLine());
		}
	}
};

ArrHandler arrhandler;

void solution(int r, int c, int k) {
	int t = 0;

	while (t <= 100) {
		if (arrhandler.getValue(r, c) == k) {
			cout << t << endl;
			return;
		}

		if (arrhandler.isRowBigger()) {
			arrhandler.sortRow();
		}
		else {
			arrhandler.sortCol();
		}

		t++;
	}

	cout << -1 << endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);

	int r, c, k;
	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arrhandler.arr[i][j];
		}
	}

	solution(r, c, k);

	return 0;
}