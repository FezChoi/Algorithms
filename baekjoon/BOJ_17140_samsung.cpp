// 2019 삼성 기출 : 이차원 배열과 연산

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> 	vi;
typedef pair<int, int> 	pii;
typedef vector<pii> 	vpii;

#define MAX_SIZE 101

struct NumCounter {				// 특정 line의 숫자들을 카운트하는 객체
	vpii numCounter;
	vi index;

	void init() {				// 새로운 line마다 init
		numCounter = vpii(); 		// pair<int, int>에서 first는 숫자, second는 중복 횟수
		index = vi(MAX_SIZE, -1);	// numCounter에서 count up할 숫자의 위치 저장 -> numCounter[index[number]].second++, 방문 여부를 알기 위해 (-1)로 초기화
	}

	void check(int a) {						// 숫자 반복 횟수 count
		if (index[a] == -1) {					// 인덱스가 초기값(-1)인 경우, 처음 방문한 숫자 
			index[a] = numCounter.size(); 			// 새로운 index를 설정
			numCounter.push_back(make_pair(a, 1));  	// numCounter에 새로 추가
		}
		else {							// 인덱스가 초기값이 아닌 경우, index[a]의 위치에 있는 numCounter pair의 중복 횟수를 up
			numCounter[index[a]].second++;
		}
	}

	static bool comp(pii a, pii b) {							// 1) 중복 횟수가 작은 순서, 2) 숫자가 작은 순서
		return (a.second == b.second) ? a.first < b.first : a.second < b.second;
	}

	vi getNewLine() { 							// numCounter를 참고하여 새로운 line을 만들어 반환
		sort(numCounter.begin(), numCounter.end(), comp); 		// 정렬

		vi newRow(1, 0); 						// 인덱스를 맞추기 위해 초기 사이즈 1
		for (int i = 0; i < numCounter.size(); i++) {
			newRow.push_back(numCounter[i].first);			// 숫자
			newRow.push_back(numCounter[i].second);			// 반복 횟수
		}

		return newRow;
	}
};

struct ArrHandler {			// 2차원 배열을 다루는 객체
	vector<vi> arr;			// 2차원 배열
	int rowSize;			// 최대 row 크기
	int colSize;			// 최대 column 크기
	NumCounter numCounter; 		// 카운터 객체

	ArrHandler() {						// 생성자 초기화
		arr = vector<vi>(MAX_SIZE, vi(MAX_SIZE, 0));
		rowSize = 3;
		colSize = 3;
	}
	
	int getValue(int rowIdx, int colIdx) {			// 2차원 배열의 값 확인
		return arr[rowIdx][colIdx];
	}

	bool isRowBigger() {					// row >= col 이면 R연산, 아니면 C연산
		return rowSize >= colSize;
	}

	void swapRow(int rowIdx, vi newRow) {				// 새 row를 구했을 때, 기존 row에 덮어쓰기
		int newSize = min(100, (int)newRow.size() - 1); 	// 100 보다 큰 인덱스는 버리기

		int colIdx = 1;
		for (; colIdx <= newSize; colIdx++) {
			arr[rowIdx][colIdx] = newRow[colIdx];
		}
		for (; colIdx <= colSize; colIdx++) { 			// 길이가 더 짧아졌으면, 나머지 0으로 채우기
			arr[rowIdx][colIdx] = 0;
		}

		colSize = max(colSize, newSize);
	}

	void sortRow() {							// R연산 : 모든 row에 대해 numCounter로 중복 숫자 체크하고, 새 row와 swap
		for (int rowIdx = 1; rowIdx <= rowSize; rowIdx++) {
			numCounter.init();
			for (int colIdx = 1; colIdx <= colSize; colIdx++) {
				if (arr[rowIdx][colIdx] == 0) continue;		// 0인 부분은 제외
				numCounter.check(arr[rowIdx][colIdx]);		// 해당 숫자 중복 카운트
			}

			swapRow(rowIdx, numCounter.getNewLine());		// 새 row를 만들어 swap
		}
	}

	void swapCol(int colIdx, vi newCol) {					// swapRow와 같은 역할
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

	void sortCol() {							// C연산 : sortRow와 비슷한 역할
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

ArrHandler arrhandler;				// 전역 변수

void solution(int r, int c, int k) {
	int t = 0;

	// 100초 동안 반복
	while (t <= 100) {
		// 값 확인
		if (arrhandler.getValue(r, c) == k) {
			cout << t << endl;		// 값이 같으면 시간 출력 후 종료
			return;
		}

		if (arrhandler.isRowBigger()) {		// row >= col 이면
			arrhandler.sortRow();  		// R연산
		}
		else {					// row < col 이면
			arrhandler.sortCol();		// C연산
		}

		t++; 					// 시간 증가
	}

	cout << -1 << endl;		// 100초 넘기면 -1 출력
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
