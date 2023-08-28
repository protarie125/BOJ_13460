#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

using vc = vector<char>;
using Board = vector<vc>;

class Node {
public:
	Board board{};
	int move{ 0 };
	int rx{};
	int ry{};
	int bx{};
	int by{};
	bool isR{ false };
	bool isB{ false };
};

int n, m;

void updateRed(Node& f, int dy, int dx) {
	if (dy < 0) {
		f.board[f.ry][f.rx] = '.';

		for (auto y = f.ry - 1; 0 <= y; --y) {
			if ('O' == f.board[y][f.rx]) {
				f.isR = true;
				f.rx = -1;
				f.ry = -1;
				break;
			}

			if ('#' == f.board[y][f.rx] ||
				'B' == f.board[y][f.rx]) {
				f.board[y + 1][f.rx] = 'R';
				f.ry = y + 1;
				break;
			}
		}

		return;
	}

	if (0 < dy) {
		f.board[f.ry][f.rx] = '.';

		for (auto y = f.ry + 1; y < n; ++y) {
			if ('O' == f.board[y][f.rx]) {
				f.isR = true;
				f.rx = -1;
				f.ry = -1;
				break;
			}

			if ('#' == f.board[y][f.rx] ||
				'B' == f.board[y][f.rx]) {
				f.board[y - 1][f.rx] = 'R';
				f.ry = y - 1;
				break;
			}
		}

		return;
	}

	if (dx < 0) {
		f.board[f.ry][f.rx] = '.';

		for (auto x = f.rx - 1; 0 <= x; --x) {
			if ('O' == f.board[f.ry][x]) {
				f.isR = true;
				f.rx = -1;
				f.ry = -1;
				break;
			}

			if ('#' == f.board[f.ry][x] ||
				'B' == f.board[f.ry][x]) {
				f.board[f.ry][x + 1] = 'R';
				f.rx = x + 1;
				break;
			}
		}

		return;
	}

	if (0 < dx) {
		f.board[f.ry][f.rx] = '.';

		for (auto x = f.rx + 1; x < m; ++x) {
			if ('O' == f.board[f.ry][x]) {
				f.isR = true;
				f.rx = -1;
				f.ry = -1;
				break;
			}

			if ('#' == f.board[f.ry][x] ||
				'B' == f.board[f.ry][x]) {
				f.board[f.ry][x - 1] = 'R';
				f.rx = x - 1;
				break;
			}
		}

		return;
	}
}

void updateBlue(Node& f, int dy, int dx) {
	if (dy < 0) {
		f.board[f.by][f.bx] = '.';

		for (auto y = f.by - 1; 0 <= y; --y) {
			if ('O' == f.board[y][f.bx]) {
				f.isB = true;
				f.bx = -1;
				f.by = -1;
				break;
			}

			if ('#' == f.board[y][f.bx] ||
				'R' == f.board[y][f.bx]) {
				f.board[y + 1][f.bx] = 'B';
				f.by = y + 1;
				break;
			}
		}

		return;
	}

	if (0 < dy) {
		f.board[f.by][f.bx] = '.';

		for (auto y = f.by + 1; y < n; ++y) {
			if ('O' == f.board[y][f.bx]) {
				f.isB = true;
				f.bx = -1;
				f.by = -1;
				break;
			}

			if ('#' == f.board[y][f.bx] ||
				'R' == f.board[y][f.bx]) {
				f.board[y - 1][f.bx] = 'B';
				f.by = y - 1;
				break;
			}
		}

		return;
	}

	if (dx < 0) {
		f.board[f.by][f.bx] = '.';

		for (auto x = f.bx - 1; 0 <= x; --x) {
			if ('O' == f.board[f.by][x]) {
				f.isB = true;
				f.bx = -1;
				f.by = -1;
				break;
			}

			if ('#' == f.board[f.by][x] ||
				'R' == f.board[f.by][x]) {
				f.board[f.by][x + 1] = 'B';
				f.bx = x + 1;
				break;
			}
		}

		return;
	}

	if (0 < dx) {
		f.board[f.by][f.bx] = '.';

		for (auto x = f.bx + 1; x < m; ++x) {
			if ('O' == f.board[f.by][x]) {
				f.isB = true;
				f.bx = -1;
				f.by = -1;
				break;
			}

			if ('#' == f.board[f.by][x] ||
				'R' == f.board[f.by][x]) {
				f.board[f.by][x - 1] = 'B';
				f.bx = x - 1;
				break;
			}
		}

		return;
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;

	Node init{};
	init.board = Board(n, vc(m));
	for (auto y = 0; y < n; ++y) {
		for (auto x = 0; x < m; ++x) {
			cin >> init.board[y][x];

			if ('R' == init.board[y][x]) {
				init.ry = y;
				init.rx = x;
			}

			if ('B' == init.board[y][x]) {
				init.by = y;
				init.bx = x;
			}
		}
	}

	auto q = queue<Node>{};
	q.push(init);

	while (!q.empty()) {
		auto f = q.front();
		q.pop();

		/*cout << "move = " << f.move << '\n';
		for (const auto& row : f.board) {
			for (const auto& c : row) {
				cout << c;
			}
			cout << '\n';
		}
		cout << '\n';*/

		if (f.isR && !f.isB) {
			cout << f.move;
			return 0;
		}

		if (f.isB) {
			continue;
		}

		{ // up
			auto next = f;

			if (next.ry < next.by) {
				updateRed(next, -1, 0);
				updateBlue(next, -1, 0);
			}
			else {
				updateBlue(next, -1, 0);
				updateRed(next, -1, 0);
			}

			++next.move;
			if (next.move <= 10) {
				if (!(f.rx == next.rx && f.ry == next.ry &&
					f.bx == next.bx && f.by == next.by)) {
					q.push(next);
				}
			}
		}

		{ // down
			auto next = f;

			if (next.ry < next.by) {
				updateBlue(next, 1, 0);
				updateRed(next, 1, 0);
			}
			else {
				updateRed(next, 1, 0);
				updateBlue(next, 1, 0);
			}

			++next.move;
			if (next.move <= 10) {
				if (!(f.rx == next.rx && f.ry == next.ry &&
					f.bx == next.bx && f.by == next.by)) {
					q.push(next);
				}
			}
		}

		{ // left
			auto next = f;

			if (next.rx < next.bx) {
				updateRed(next, 0, -1);
				updateBlue(next, 0, -1);
			}
			else {
				updateBlue(next, 0, -1);
				updateRed(next, 0, -1);
			}

			++next.move;
			if (next.move <= 10) {
				if (!(f.rx == next.rx && f.ry == next.ry &&
					f.bx == next.bx && f.by == next.by)) {
					q.push(next);
				}
			}
		}

		{ // right
			auto next = f;

			if (next.rx < next.bx) {
				updateBlue(next, 0, 1);
				updateRed(next, 0, 1);
			}
			else {
				updateRed(next, 0, 1);
				updateBlue(next, 0, 1);
			}

			++next.move;
			if (next.move <= 10) {
				if (!(f.rx == next.rx && f.ry == next.ry &&
					f.bx == next.bx && f.by == next.by)) {
					q.push(next);
				}
			}
		}
	}

	cout << -1;

	return 0;
}