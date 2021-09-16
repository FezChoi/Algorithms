#include <iostream>
#include <memory>

using namespace std;

struct Node {
	Node** children = new Node* [26];
	bool isEnd;
	bool isHit;

	Node() {
		for (int i = 0; i < 26; i++) {
			children[i] = new Node(); // stack overflow!
		}
		isEnd = false;
		isHit = false;
	}

	void clearHit() {
		isHit = false;
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) {
				children[i]->clearHit();
			}
		}
	}

	bool hasChild(char c) {
		return (children[c - 'A'] != nullptr);
	}

	Node* getChild(char c) {
		return children[c - 'A'];
	}

	string toString() {
		string str = "";
		for (int i = 0; i < 26; i++) {
			if (children[i] != nullptr) {
				str += (char)(i + 'A')
					+ (children[i]->isEnd ? "end" : "") + '{'
					+ children[i]->toString() + '}';
			}
		}
		return str;
	}
};

Node* root = new Node();

const int dirX[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const int dirY[] = { 1, 0, -1, 0, 1, -1, 1, -1 };
const int scoreBoard[] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };

int W, N;
char map[4][4];
bool visited[4][4];

int totalScore = 0, totalCount = 0;
string answer = "";

void insertWord(string word);
void searchWord(int row, int col, int length, Node* node, string word);
void updateAnswer(string foundWord);

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> W;
	for (int i = 0; i < W; i++) {
		string tmp;
		cin >> tmp;
		insertWord(tmp);
	}
	cout << "hello" << endl;
	cin >> N;
	for (int tc = 0; tc < N; tc++) {
		memset(map, 0, 16 * sizeof(char));
		memset(visited, false, 16 * sizeof(bool));

		for (int i = 0; i < 4; i++) {
			cin >> map[i];
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				char c = map[i][j];
				if (root->hasChild(c)) {
					searchWord(i, j, 1, root->getChild(c), "");
				}
			}
		}

		cout << totalScore << " " << answer << " " << totalCount << '\n';
		root->clearHit();
	}

	return 0;
}

void insertWord(string word) {
	Node* curNode = root;

	for (char c : word) {
		int charIndex = c - 'A';

		if (curNode->children[charIndex] == nullptr) {
			curNode->children[charIndex] = new Node();
		}

		curNode = curNode->children[charIndex];
	}

	return;
}

void searchWord(int nowX, int nowY, int length, Node* node, string word) {
	// 1. check-in
	visited[nowX][nowY] = true;
	word.append(1, map[nowX][nowY]);

	// 2. is ended?
	if (node->isEnd && !node->isHit) {
		node->isHit = true;
		totalScore += scoreBoard[length];
		totalCount++;
		updateAnswer(word);
	}

	// 3. go to adj
	for (int i = 0; i < 8; i++) {
		int nextX = nowX + dirX[i];
		int nextY = nowY + dirY[i];

		// 4. is possible?
		if (nextX < 0 || nextX >= 4 || nextY < 0 || nextY >= 4) continue;
		if (visited[nextX][nextY] || !node->hasChild(map[nextX][nextY])) continue;

		// 5. go
		searchWord(nextX, nextY, length + 1, node->getChild(map[nextX][nextY]), word);
	}

	// 6. check-out
	visited[nowX][nowY] = false;
	word.pop_back();
}

void updateAnswer(string foundWord) {
	bool isUpdate = false;

	if (answer.length() > foundWord.length()) {
		return;
	}

	if (answer.length() < foundWord.length()) {
		answer = foundWord;
		return;
	}

	for (int i = 0; i < answer.length(); i++) {
		if (answer[i] < foundWord[i]) {
			return;
		}
		else if (answer[i] > foundWord[i]) {
			answer = foundWord;
			return;
		}
	}
}
